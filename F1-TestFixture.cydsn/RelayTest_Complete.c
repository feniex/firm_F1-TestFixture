/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include "CommonVariables.h"
#include "RelayTest.h"
#include "SirenTest.h"
#include "UART_115200_Functions.h"
#include "UART_230400_Functions.h"
#include "UART_460800_Functions.h"
#include "CD4051BPW_Driver.h"

#define VOLTAGE_SYSTEM      120             // (Voltage * 10)
#define TOLERANCE_VOLTAGE   5  
#define CURRENT_LOAD        9              // (ohms)
#define TOLERANCE_CURRENT   2 
#define CONFIRM_TIME        100            // How many msec to show pass/fail for each step

#define DEBOUNCE_COUNT      2           // (5 * 20msec)

static RxPacket_RelaySiren rxPacket_Relay;          // Inputs - 'D' relay to controller
static RxPacket_RelaySiren * pRxPacket_Relay;       // UART_SIREN
static RxPacket_RelaySiren rxPacket_RelaySiren;     // *** these are redundant 'D' packets 
static RxPacket_RelaySiren * pRxPacket_RelaySiren;  // OVERLOAD

static TxPacket_RelaySiren txPacket_RelaySiren;         // SetRelayOutputs - 'I' (also 3,S,P) controller to relay
static TxPacket_RelaySiren * pTxPacket_RelaySiren;      // 

//static TxPacket_Relay txPacket_Relay;            
//static TxPacket_Relay * pTxPacket_Relay;

//static RxPacket_Siren rxPacket_Siren;             // 'S' relay to siren
//static RxPacket_Siren * pRxPacket_Siren;  

static Packet_H txPacket_H;          //     Packet 'H' Tx
static Packet_H * pTxPacket_H;      //

static Packet_H rxPacket_H;          //     Packet 'H'  Rx
static Packet_H * pRxPacket_H;      //

static RxPacket_Quad txPacket_Quad;          //*** 
static RxPacket_Quad * pTxPacket_Quad;      //***
//RxPacket_Quad * getRxPacket_Quad(void);

//static RxPacket_RelaySiren rxPacket_Relay;          //     Packet 'D'
//static RxPacket_RelaySiren * pRxPacket_Relay;      //

//------------GLOABAL variables--------------------

static uint16 RTest_Complete_20ms_isr_count = 0;
static uint16 RTest_Complete_20ms_isr_EN = 0;

static uint8 PB_NextAction_Pressed = 0;
static uint8 PB_NextAction_Released = 0;

void StartTimeout(void);
void StopTimeout(void);

enum DATA_TYPE_460800
{ 
    CTEST_AUDIO,        // This is for both cont and relay tests
    CTEST_RTEST_QUAD,   // CTest/RTest - quad normal - (controller to relay, relay to quad)
//    CTEST_A,            //*** needs to  (*** not used - only need to look for 'L' packet)
//    QTEST_QUAD          // (*** not used - Quad-Controller packets - type 'C')
};

enum MUX_460800_CHANNEL
{ 
    CTEST_QUAD,       
    CTEST_AUDIOSTREAM,
    RTEST_QUAD_1,    
    RTEST_QUAD_2,
    RTEST_QUAD_3,
    RTEST_QUAD_4,
    RTEST_QUAD_5,
    RTEST_QUAD_6,
    RTEST_QUAD_7,
    RTEST_QUAD_8            
};

enum DEMUX_460800_CHANNEL
{ 
    CTEST_OBDII_TX,     
    RTEST_QUAD_TX,        
    STEST_AUDIO_TX,
};

enum MUX_DEMUX_230400_CHANNEL              
{ 
    CTEST_RELAY, 
    RTEST_CONT,
    RTEST_SIREN,
    STEST_RELAY            
};

enum DATATYPE_115200         
{ 
    RTEST_DLINK
};
enum MUX_115200_CHANNEL      
{ 
    RTEST_DLINK1,    
    RTEST_DLINK2,    
    CTEST_USB_DEBUG,
    DIAG_UART_RX        
};

// --------------Test steps---------------
#define NUMBER_TEST_STEPS   16
static uint16 RTest_Complete_TimeoutCount[NUMBER_TEST_STEPS] = {50,500,200,50,100,50,100,50,50,50,50,50,50,1000,50,50};  //,   50,50,50,50,50,100,50};  // Number of 20msec counts before failure timeout, for each step
                                    
static uint8 RTest_CompleteStatus[NUMBER_TEST_STEPS];

enum TestStep               // *** (relay firmware needs the 'H' packet payload count updated)
{ 
    /* Relay Test Steps*/
    INITIALIZE_TEST,    // COMPLETE
    TEST_OUTPUTS,       // COMPLETE - same
    DATALINK,           // COMPLETE - same
    QUAD_PORTS,         // COMPLETE - same
    INPUTS,             // COMPLETE - same
    VBATT,              // COMPLETE - same
    BLOCK_CURRENTS,     // COMPLETE - same
    
    /* Siren Test Stuff*/
    UART_TX,            // U ('D' packet - firmware versions are the only thing that is unread)
    AMP1,               // COMPLETE (low volume)
    AMP2,               // COMPLETE (low volume)
    RRB,                // COMPLETE (hi volume - adjustable)
    MIC,                // COMPLETE (hi volume)
    FLASH,              // COMPLETE (kind of loud/weak)
    OVERLOAD,           // ??? U (cannot be used with loaded 
    
    GPS,                // ***Need to add this in still
    
    PASS                // COMPLETE
};

//----------------------------------------
// Main state machine for F1-Relay Test
//----------------------------------------
uint8 RelayTest_Complete(void)
{
    
    switch(CurrentTest.TestStep)
    {   
               
        case INITIALIZE_TEST:            
        
            STest_SIREN_EN_Write(1);  // Less muted - for Mic test
            CyDelay(250);
                
            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)                 // Reset Status of aall test steps to 0
                RTest_CompleteStatus[i] = '_';
                
            RTest_CompleteStatus[CurrentTest.TestStep] = 'I';
            CurrentTest.Status = 'I'; 

            pTxPacket_RelaySiren = getTxPacket_RelaySiren();        // Tx - Initialize TX_RelaySiren packet 
            for(uint8 i;i<79;i++)
                pTxPacket_RelaySiren->bytes[i] = 0;

            pTxPacket_RelaySiren->Payload.StartByte_FLB = '~';
            pTxPacket_RelaySiren->Payload.FLB_PacketType = '3';
            pTxPacket_RelaySiren->Payload.StopByte1_FLB = 0x0D;
            pTxPacket_RelaySiren->Payload.StopByte2_FLB = 0x0A;    
            pTxPacket_RelaySiren->Payload.StartByte1_Siren = '~';    
            pTxPacket_RelaySiren->Payload.Siren_PacketType = 'S';
            pTxPacket_RelaySiren->Payload.StopByte1_Siren = 0x0D;
            pTxPacket_RelaySiren->Payload.StopByte2_Siren = 0x0A;                       
            pTxPacket_RelaySiren->Payload.StartByte1_Relay = '~';
            pTxPacket_RelaySiren->Payload.Relay_PacketType = 'P';
            pTxPacket_RelaySiren->Payload.StopByte1_Relay = 0x0D;
            pTxPacket_RelaySiren->Payload.StopByte2_Relay = 0x0A;                    
 
            // Deactivate each input
            // RTest_HSide1_Write(0);
            // RTest_HSide2_Write(0);
            // RTest_HSide3_Write(0);
            // RTest_HSide4_Write(0);
            // RTest_HSide5_Write(0);
            // RTest_HSide6_Write(0);
            // RTest_HSide7_Write(0);
            // RTest_HSide8_Write(0);
                
            RTest_CompleteStatus[CurrentTest.TestStep] = 'P';
            CurrentTest.Status = 'P'; 
            
//            STest_SIREN_EN_Write(0);
//            CyDelay(1000);
//            STest_SIREN_EN_Write(1);
//            CyDelay(1000);
                    
            CyDelay(CONFIRM_TIME);
            
            //CurrentTest.TestStep = INITIALIZE_TEST;
            CurrentTest.TestStep = TEST_OUTPUTS;
            //CurrentTest.TestStep = DATALINK;
            //CurrentTest.TestStep = QUAD_PORTS;
            //CurrentTest.TestStep = UART_SIREN;
            //CurrentTest.TestStep = INPUTS;
            //CurrentTest.TestStep = VBATT; 
            //CurrentTest.TestStep = BLOCK_CURRENTS; 
            //CurrentTest.TestStep = GPS; 
            
            //CurrentTest.TestStep = AMP1;
            //CurrentTest.TestStep = RRB;
            //CurrentTest.TestStep = MIC;
            //CurrentTest.TestStep = FLASH;
            //CurrentTest.TestStep = OVERLOAD;
                   
        break;      
              
        case TEST_OUTPUTS:  
                
            RTest_Complete_StartAutomatedStep(); 
            //SetRelayOutputs(1);
            //While(1);
            while( (!RTest_Test_Outputs()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}   
            
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = TEST_OUTPUTS;
                CurrentTest.TestStep = DATALINK;    
            }
            
        break;        
              
        case DATALINK: 

            RTest_Complete_StartAutomatedStep();
            
            while( (!RTest_Complete_Test_DataLink()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}          
 
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                CurrentTest.TestStep = QUAD_PORTS; 
            }
            
        break;  
            
        case QUAD_PORTS: 
                
            RTest_Complete_StartAutomatedStep();  
                
            DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Select TX xhannel
                      
            while( (!RTest_Test_QuadPorts()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
                  
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                CurrentTest.TestStep = INPUTS;   
            }
            
        break;      
              
        case INPUTS:          
                
            RTest_Complete_StartAutomatedStep();          
                
            while( (!RTest_Test_Inputs()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}   
            
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
             
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;  
                CurrentTest.TestStep = VBATT;  
            }
            
        break;          

        case VBATT:                                     // Tested and working
                
            RTest_Complete_StartAutomatedStep();
                
            while( (!RTest_Test_Vbatt()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}    
            
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
             
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST; 
                CurrentTest.TestStep = BLOCK_CURRENTS; 
            }
            
        break; 
         
        case BLOCK_CURRENTS:                            //*** Tested and working
            
            SetRelayOutputs(1);                         // Send command to turn on relay outputs
                
            RTest_Complete_StartAutomatedStep();
             
            while( (!RTest_Test_BlockCurrents()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {} 
            
            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
             
            SetRelayOutputs(0);                         // Send command to turn off relay outputs
            
            CyDelay(100);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                CurrentTest.TestStep = GPS;
                //CurrentTest.TestStep = PASS;
                CurrentTest.TestStep = UART_TX;
            }
            
        break; 
                    
        case UART_TX:                               // Automated - 
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'U';
            CurrentTest.Status = 'U';
                
//            RTest_Complete_StartAutomatedStep();
//        
//            //MUX_CTRL_230400_Write(STEST_RELAY);     // Mux 230400 from siren
//            MUX_CTRL_230400_Write(CTEST_RELAY);     // Mux 230400 from relay
//            
//            //VerifyPacket_230400(RTEST_SIREN);       // Verify a 'H' packet
//            while( (!VerifyPacket_230400(RTEST_SIREN)) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
//            {} 
//            
//            RTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                CurrentTest.TestStep = AMP1;
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = PASS;
            }
        
        break;  
                  
        case AMP1:                                  // Manual - 
            
            STest_SIREN_EN_Write(0);        // Turn on muted speaker load
            CyDelay(250);
                  
            DEMUX_CTRL_230400_Write(RTEST_CONT);
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x01; 
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            CyDelay(1000);
        
            RTest_Complete_PB_WaitForAction();
            
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x00;    // Turn off wail tone
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = AMP1;
                CurrentTest.TestStep = AMP2;
            }
        
        break;    
             
        case AMP2:                                  // Manual - 
            
            STest_SIREN_EN_Write(0);        // Turn on muted speaker load
            CyDelay(250);
                       
            DEMUX_CTRL_230400_Write(RTEST_CONT);
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x01;   
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            CyDelay(1000);
             
            RTest_Complete_PB_WaitForAction();                         
            
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x00;    // Turn off wail tone
            //CyDelay(1000);
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                CurrentTest.TestStep = RRB;
                //CurrentTest.TestStep = FLASH;
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = PASS;
            }
                
        break;
            
        case RRB:    
            
//            RTest_CompleteStatus[CurrentTest.TestStep] = 'U';           
//            CurrentTest.Status = 'U'; 
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            
            STest_SIREN_EN_Write(1);        // Turn on the less muted speaker load
            CyDelay(250);
                         
            DEMUX_CTRL_230400_Write(RTEST_CONT);             // 230400 - 'S' - Send a command to enable RRB          
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.RRB = 0x01;  
            
            WaveDAC_Start();  
            //STest_PlayTestTone();                               // Play test tone for 3sec
            
            CyDelay(1000);
 
            RTest_Complete_PB_WaitForAction();
            
            WaveDAC_Stop();  
            pTxPacket_RelaySiren->Payload.RRB = 0x00;  
         
            CyDelay(CONFIRM_TIME);

            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = AMP1;
                //CurrentTest.TestStep = RRB;
                CurrentTest.TestStep = MIC;
                //CurrentTest.TestStep = INITIALIZE_TEST;
            }
        
        break;   
            
        case MIC:                               

            STest_SIREN_EN_Write(1);  // Less muted
            CyDelay(250);
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'W';  
            CurrentTest.Status = 'W'; 
            
            //STest_SIREN_EN_Write(1);  // Less muted
            
            RTest_Complete_PB_WaitForAction();        
            
            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = MIC;
                CurrentTest.TestStep = FLASH;
                //CurrentTest.TestStep = INITIALIZE_TEST;
            }
        
        break;    
               
        case FLASH:                                         // Manual - 
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';  
            CurrentTest.Status = 'B'; 
            
            STest_SIREN_EN_Write(1);  // 
            CyDelay(250);
            
            /*this is test code to scroll through tones with PB*/
            DEMUX_CTRL_230400_Write(RTEST_CONT);             // 230400 - 'S' - Send a command to play an audio tone          
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            
            pTxPacket_RelaySiren->Payload.Siren1Tone = 16; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 16; 
            
            CyDelay(1000);

            RTest_Complete_PB_WaitForAction();
       
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0; 

            CyDelay(CONFIRM_TIME);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                CurrentTest.TestStep = OVERLOAD;
                //CurrentTest.TestStep = MIC;
                //CurrentTest.TestStep = FLASH;
                //CurrentTest.TestStep = INITIALIZE_TEST;
            }
                
        break;  
             
        case OVERLOAD:     
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';           
            CurrentTest.Status = 'B'; 
            
            CyDelay(5000);
            STest_SIREN_EN_Write(0);  // 
            CyDelay(250);

            //MUX_CTRL_230400_Write(STEST_RELAY);     // Rx - 'D' packet
            MUX_CTRL_230400_Write(RTEST_CONT);          // Rx - 'D' packet
    
            //DEMUX_CTRL_230400_Write(STEST_RELAY);   // Tx - 'S' packet
            DEMUX_CTRL_230400_Write(RTEST_CONT);        // Tx - 'I' packet (includes 'S' packet)

            RTest_Complete_StartAutomatedStep();
            
            Overload1_Write(0);                
            Overload2_Write(1);                
            
            CyDelay(100);
            
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp1
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 1;     
            
            CyDelay(100);
             
            pRxPacket_RelaySiren = getRxPacket_RelaySiren();
            while( (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 1) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}
                
            RTest_Complete_StopAutomatedStep();
            
            Overload1_Write(0);               
            Overload2_Write(0);
                
            CyDelay(1000);
            
            Overload1_Write(0);                                 // Turn everything off
            Overload2_Write(0);
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0;  
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0; 
                
            //--------------------------------------
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'B';
            CurrentTest.Status = 'B';
            while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 0) || (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 0) )
            {}
            
            //--------------------------------------

            RTest_Complete_StartAutomatedStep();
            
            Overload1_Write(1);               
            Overload2_Write(0);              
            
            CyDelay(100);
            
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp1
            pTxPacket_RelaySiren->Payload.Siren1Tone = 1;     
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0;    
            
            CyDelay(100);
                
            while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 1) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}
                
            RTest_Complete_StopAutomatedStep();
            
            Overload1_Write(0);                                 // Turn everything off
            Overload2_Write(0);

            pTxPacket_RelaySiren->Payload.Siren1Tone = 0; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0; 
            
            CyDelay(1000);
            
            if(RTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = MIC;
                //CurrentTest.TestStep = OVERLOAD;
                CurrentTest.TestStep = GPS;
                //CurrentTest.TestStep = PASS;
            }
            
        break;  
            
        case GPS:         
            
            RTest_CompleteStatus[CurrentTest.TestStep] = 'U';
            CurrentTest.Status = 'U';

//            RTest_Complete_StartAutomatedStep();
//
//            MUX_CTRL_230400_Write(RTEST_CONT);
//               
//            while( (!VerifyPacket_GPS()) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
//            {}        
//            
//            RTest_Complete_StopAutomatedStep();

            CyDelay(CONFIRM_TIME);
             
            //CurrentTest.TestStep = INITIALIZE_TEST; 
            //CurrentTest.TestStep = GPS;
            //CurrentTest.TestStep = UART_TX;
            CurrentTest.TestStep = PASS;
            
        break;   
            
        case PASS:  
            
            for(uint8 i=0;i<(NUMBER_TEST_STEPS-1);i++)
            {
                if( (RTest_CompleteStatus[i] != 'P') && (RTest_CompleteStatus[i] != 'U') )
                {
                    RTest_CompleteStatus[CurrentTest.TestStep] = 'f';
                    CurrentTest.Status = 'f';                      
                }    
            }
 
            if(RTest_CompleteStatus[CurrentTest.TestStep] != 'f')
            {
                RTest_CompleteStatus[CurrentTest.TestStep] = 'p';
                CurrentTest.Status = 'p'; 
            }
            
            while(1);            
//            while(PB_NextAction_Read() != 1){};
//            RTestStatus[CurrentTest.TestStep] = 'r';
//            CurrentTest.Status = 'r'; 
//            CyDelay(1000);
//            CurrentTest.TestStep = INITIALIZE_TEST;

        break;          
           
    }
      
    return(0);
    
}

/* 230400bps ********************************************************************************
*  Send 'P' packet (or 'I' packet)   (controller to relay)  - turn on all relay outputs
*  Read Hardware                            - read each input, verify all are active
*  Return: Pass/Fail
*********************************************************************************************/
//uint8 RTest_Test_Outputs(void)
//{
//
//    uint32 OutputsState = 0;
//    uint32 testval = 0;
//    
//    SetRelayOutputs(1);                                                     // Send command to turn on relay outputs
//    //while(1);
//    for (uint8 channel=0; channel<32; channel++)                            // Address and read channels '0-31' in hardware
//    {
//        selectADCChannelMux(channel);                                       //*** This needs to be fleshed out when hardware arrives 
//        CyDelay(1);
//        testval = RTest_DEMUX_COM_Read();
//
//        OutputsState = ( OutputsState | (testval << channel) );             // Read RTest_INPUT_DEMUX and store each bit in OutputsState   
//    }
//    
//    //SetRelayOutputs(0);                                                     // Send command to turn off relay outputs
//    
//    if(OutputsState == 0xFFFFFFFF)
//        return(1);                                                          // If all outputs are turned on, then return pass
//    else
//        return(0);                                                          // If not pass, then return fail
//}

/* 230400/115200bps **************************************************************************
*  230400 - Tx - Send 'S' packet   (controller to relay/siren)    - turn on all relay outputs
*  115200 - Rx - Read 'S' packet   (relay to datalink device)     - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
uint8 RTest_Complete_Test_DataLink(void)
{
    
    MUX_CTRL_115200_Write(RTEST_DLINK1);            //Select the RTest_RS485_DLink1_RX channel 
    while( (!VerifyPacket_115200(RTEST_DLINK)) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
    {}  
    
    MUX_CTRL_115200_Write(RTEST_DLINK2);            //Select the RTest_RS485_DLink2_RX channel     
    while( (!VerifyPacket_115200(RTEST_DLINK)) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
    {} 
    
    if(RTest_CompleteStatus[CurrentTest.TestStep] != 'F')
        return(1);                                      // If both packets get verified, then return pass
    else
        return(0); 
}

/* 460800bps ********************************************************************************
*  Send 'L' packet   (controller to relay)
*  Read 'L' packet   (relay to quad device)  - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
//uint8 RTest_Test_QuadPorts(void)
//{
//    for(uint8 i=0;i<8;i++)
//    {
//        MUX_CTRL_460800_Write(RTEST_QUAD_1 + i);                // Select RX channel         
//        while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
//        {}
//    }
//    
//    return(1);
//
//}

//*** This needs some work
/* 230400bps ********************************************************************************
*  ***Send 'H' packet   (siren to relay)
*  ***Read 'D' packet   (relay to controller)   - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
//uint8 RTest_Test_UART_Siren(void)
//{
//           
//    pTxPacket_H = getTxPacket_H();                          // Tx - Send a 'H' packet from siren to relay              
//    pTxPacket_H->Payload.SirenFirm_0 = 's';
//    pTxPacket_H->Payload.SirenFirm_1 = 's';
//    pTxPacket_H->Payload.SirenFirm_2 = 's';
//    pTxPacket_H->Payload.Speaker1_Overcurrent = 's';
//    pTxPacket_H->Payload.Speaker2_Overcurrent = 's';
//
//    MUX_CTRL_230400_Write(RTEST_CONT);                      // Rx - Verify data sent from relay to controller
//    
//    pRxPacket_Relay = getRxPacket_RelaySiren();                              // Rx - Get pointers to packet      
//    while(  ( (pRxPacket_RelaySiren->Payload.SirenFirm_0 != 's' ) &&           // Wait for the packet to be verified
//            (pRxPacket_RelaySiren->Payload.SirenFirm_1 != 's' ) &&
//            (pRxPacket_RelaySiren->Payload.SirenFirm_2 != 's' ) //&&
//            //(pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 's' ) &&
//            //(pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 's' )
//            ) && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
//    {}
//          
//
//    //DEMUX_CTRL_230400_Write(RTEST_CONT);                            // Tx - Send a 'S' packet to relay (from controller)
//    
////    MUX_CTRL_230400_Write(RTEST_SIREN);                             // Rx - Verify a 'S' packet is received from relay (by siren)
////    while( (!VerifyPacket_230400(STEST_RELAY)) && (RTestStatus[CurrentTest.TestStep] != 'F') )
////    {}
//
//    return(1);
//}


/* 230400bps *****************************************************************************
*  Send 'P' packet (controller to relay) - set input logic  
*  Read 'D' packet (relay to controller) - verify the 'RelayInputs' byte 
*  Return: Pass/Fail
******************************************************************************************/
//uint8 RTest_Test_Inputs(void)
//{
//    
////    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Send a 'P' packet to set input logic to be all lo
////    pTxPacket_RelaySiren = getTxPacket_RelaySiren();   
////    pTxPacket_RelaySiren->Payload.HiLoInputLogic = 0x00; 
////    
////    SetRelayInputs(0);
////    
////    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Verify all inputs are deactivated, if not then fail
////    pRxPacket_Relay = getRxPacket_Relay();              
////    if(pRxPacket_Relay->Payload.RelayInputs != 0x00) 
////        return(0);
//    
//    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Send a 'P' packet to set input logic to be all hi
//    pTxPacket_RelaySiren = getTxPacket_RelaySiren();  
//    pTxPacket_RelaySiren->Payload.HiLoInputLogic = 0xFF; 
//
////    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Verify all inputs are deactivated, if not then fail
////    pRxPacket_Relay = getRxPacket_Relay();              
////    if(pRxPacket_Relay->Payload.RelayInputs != 0x00) 
////        return(0);
//    
//    SetRelayInputs(1);
//
//    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Verify all inputs are deactivated, if not then fail
//    pRxPacket_Relay = getRxPacket_Relay();  
//    if(pRxPacket_RelaySiren->Payload.RelayInputs == 0xFF)    // Verify all inputs are activated, if not then return fail
//        return(1);
//    
//    return(0);                                          // If this step was not failed, return pass
//}


/* 230400bps *****************************************************************************
*  Read a 'D' packet (relay to controller)  - verify the 'Voltage_BATT' byte
*  Return: Pass/Fail
******************************************************************************************/
//uint8 RTest_Test_Vbatt(void)
//{
//    MUX_CTRL_230400_Write(RTEST_CONT);                              // Rx - Select the mux channel
//    pRxPacket_RelaySiren = getRxPacket_RelaySiren();                          // Rx - Get pointers to packet
//    
//    uint8 Vbatt_Reading = 0;
//    
//    Vbatt_Reading = pRxPacket_RelaySiren->Payload.Voltage_BATT;          // Read Vbatt value
//    
//    if( (Vbatt_Reading < (VOLTAGE_SYSTEM + TOLERANCE_VOLTAGE) ) &&
//        (Vbatt_Reading > (VOLTAGE_SYSTEM - TOLERANCE_VOLTAGE) ) )
//        return(1);                                                  // If Vbatt is within TOLERANCE_VOLTAGE, return pass
//    else
//        return(0);                                                  // If not pass, then return fail
//}

/* 230400bps ***************************************************************
*  Send a 'P'/'I' packet (controller to relay)  - Controller packet to turn on all the Relay outputs
*  Read a 'D' packet (relay to controller)  - verify block currents are within a tolerance
****************************************************************************/
//uint8 RTest_Test_BlockCurrents(void)
//{
//    
//    uint8 BlockCurrentPass = 0x00;
//    uint8 BlockCurrentValue = 0x00;
//    
//    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Select the mux channel 
//    pRxPacket_RelaySiren = getRxPacket_RelaySiren();              // Rx - Get pointers to packet
//    
//    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
//    pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet
//    
//    for(uint8 i=0;i<4;i++)                              // Save pass/fail for each block channel
//    {
//        BlockCurrentValue = RTest_BlockCurrent(i);
//        BlockCurrentPass = (BlockCurrentPass << 1) | BlockCurrentValue;
//    }
//    
//    if( (BlockCurrentPass & 0x0F) == 0x0F)
//        return(1);                                      // If all block currents are within TOLERANCE_CURRENT, return pass 
//    else
//        return(0);                                      // If not pass, then return fail
//
//}

///* 230400bps ****************************************************
//*   (wait for the GPS hardware to acquire a signal)
//*   Read the GPS packet - search for the GPS formated data
//*****************************************************************/
//uint8 RTest_Test_GPS(void)
//{
//    
//    //static uint8 targetstring[6] = {'$','G','P','M','R','C'};
//
//    uint8 findpacket(uint8 dataByte);  // - this should pass the target string
//    //processByteReceivedHandler_230400(&targetstring);
//
//    
//    
//    return(0);
//}

//RxPacket_RelaySiren * getRxPacket_Relay(void)
//{
//    pRxPacket_Relay = &rxPacket_Relay;
//    
//    return pRxPacket_Relay;
//}

//RxPacket_RelaySiren * getRxPacket_RelayS(void)
//{
//    pRxPacket_Relay = &rxPacket_Relay;
//    
//    return pRxPacket_Relay;

//TxPacket_Relay * getTxPacket_Relay()
//{
//    pTxPacket_Relay = &txPacket_Relay;
//    
//    return pTxPacket_Relay;
//}

//RxPacket_Siren * getRxPacket_Siren()
//{
//    pRxPacket_Siren = &rxPacket_Siren;
//    
//    return pRxPacket_Siren;
//}

//TxPacket_RelaySiren * getTxPacket_RelaySiren()          // STest Tx - 'I' packet sent to relay and siren from controller
//{
//    pTxPacket_RelaySiren = &txPacket_RelaySiren;
//    
//    return pTxPacket_RelaySiren;
//}

//RxPacket_RelaySiren * getRxPacket_RelaySiren()          // STest - 'D' packet sent to controller from relay and siren
//{
//    pRxPacket_RelaySiren = &rxPacket_RelaySiren;
//    
//    return pRxPacket_RelaySiren;
//}

//Packet_H * getPacket_H(void);
//Packet_H * getTxPacket_H()
//{
//    pTxPacket_H = &txPacket_H;
//    
//    return pTxPacket_H;
//}

//Packet_H * getRxPacket_H()
//{
//    pRxPacket_H = &rxPacket_H;
//    
//    return pRxPacket_H;
//}


//RxPacket_Quad * getTxPacket_Quad()              //***
//{
//    pTxPacket_Quad = &txPacket_Quad;
//    
//    return pTxPacket_Quad;
//}

void RTest_Complete_sendDiagPacket(void)
{

    static uint8 RelayTestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        RelayTestStatus_display[i*2] = RTest_CompleteStatus[i];
        RelayTestStatus_display[(i*2) + 1] = ' ';
    }
    
    //DEMUX_CTRL_115200_Write(RTEST_SIREN);
    
    UART_115200_PutArray(RelayTestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_115200_PutChar('\r');
    UART_115200_PutChar('\n');
    
    return;
}

//void ProcessFailure(void)
//{
////    
////    RelayTestStatus[TestState] = 'F';
////    //RelayTestStatus[TestState] = 'B';                   // *** dont fail the unit, keep trying
////    
//////    TestState++;
//////    if(TestState >=10)
//////        TestState = 0;
////    
////    LED_EN_Write(1);
////    
////    return;
//}

/**********************************************************************
*   230400bps
*   - Read (the output bytes) and see that they are within TOLERANCE_CURRENT
*   - Return: pass/fail
**********************************************************************/
//uint8 RTest_BlockCurrent(uint8 block)
//{
//    
//    uint8 Current_Reading = 0;
//    
//    pRxPacket_RelaySiren = getRxPacket_RelaySiren();
//    
//    if(block == 0)
//        Current_Reading = pRxPacket_RelaySiren->Payload.BlockCurrent_1;
//    else if(block == 1)
//        Current_Reading = pRxPacket_RelaySiren->Payload.BlockCurrent_2;
//    else if(block == 2)
//        Current_Reading = pRxPacket_RelaySiren->Payload.BlockCurrent_3;
//    else if(block == 3)
//        Current_Reading = pRxPacket_RelaySiren->Payload.BlockCurrent_4;
//    else 
//        return(0);
//    
//    if( (Current_Reading < (CURRENT_LOAD + TOLERANCE_CURRENT) ) &&
//        (Current_Reading > (CURRENT_LOAD - TOLERANCE_CURRENT) ) )
//        return(1);
//    else
//        return(0);
//        
//}

//void RTest_10ms_isr(void)                       // Times Quad and Audio packets
//{
//
//    if(CurrentTest.TestStep == QUAD_PORTS)        // *** moved to 20ms  
//        sendPacketToRelay_Quad();
//
//    return;
//    
//}

void RTest_Complete_isr_PB(void)
{
    static uint8 PB_NextAction_debouncecount = 0;
    static uint8 PB_NextAction_failcount = 0;
    static uint8 PB_NextAction_prevstate = 0;
    
    static uint8 debouncetrue = 0;
    
    static uint8 PB_reading = 0;
    static uint8 PB_reading_previous = 0;
    PB_reading = PB_NextAction_Read();
    
    
    if(PB_reading == PB_reading_previous)               // If reading is the same as the last, increment debounce_count
        PB_NextAction_debouncecount++;
    else
        PB_NextAction_debouncecount = 0;
    
    if(PB_NextAction_debouncecount > DEBOUNCE_COUNT)    // Set debouncetrue
    {
        debouncetrue = PB_reading;
        PB_NextAction_debouncecount = 0;
    }

    PB_reading_previous = PB_reading;                   // Save current reading for next interrupt
    
    if(debouncetrue == 1)                               // If debounced and asserted
    {
        PB_NextAction_Pressed = 1;
        PB_NextAction_failcount++;
    }
    else
    {
        PB_NextAction_Pressed = 0;
        PB_NextAction_failcount = 0;
    }
    

    if(PB_NextAction_failcount > 75)                       // If PB is held for (150 * 20msec = 3sec) then fail
    {  
        RTest_CompleteStatus[CurrentTest.TestStep] = 'F';
        CurrentTest.Status = 'F';
        PB_NextAction_failcount = 0;
    }
    

    if( (PB_NextAction_prevstate == 1) && (PB_NextAction_Pressed == 0) )        // Determine if PB was pressed momentarily and then released
    {
        PB_NextAction_Released = 1;
    }
    else
        PB_NextAction_Released = 0;
    
    PB_NextAction_prevstate = PB_NextAction_Pressed;
    
    return;
}

void RTest_Complete_20ms_isr(void)                       // Manage Timeout for failure
{
    if(CurrentTest.TestStep == QUAD_PORTS)       // *** send quad packet if needed 
    {
        sendPacketToRelay_Quad();
    }
    
    RTest_Complete_20ms_isr_count++;                                         // 

    if(RTest_Complete_20ms_isr_count > RTest_Complete_TimeoutCount[CurrentTest.TestStep])
    {
        RTest_Complete_20ms_isr_count = 0;
        
        if(RTest_Complete_20ms_isr_EN == 1)
        {
            RTest_CompleteStatus[CurrentTest.TestStep] = 'F';
            CurrentTest.Status = 'F';
        }
            
        return;
    }
    
    if(RTest_Complete_20ms_isr_count > 65000)
        RTest_Complete_20ms_isr_count = 0;
    
    return;
    
}

void RTest_Complete_50ms_isr(void)                       // Times interboard comms, and serial diagnostics
{
    
    RTest_Complete_sendDiagPacket();
    
    if( (CurrentTest.TestStep == INITIALIZE_TEST) ||
        (CurrentTest.TestStep == TEST_OUTPUTS) ||
        (CurrentTest.TestStep == DATALINK) ||
        //(CurrentTest.TestStep == UART_SIREN) ||
        (CurrentTest.TestStep == INPUTS) ||
        (CurrentTest.TestStep == BLOCK_CURRENTS) ||
        (CurrentTest.TestStep == AMP1) ||
        (CurrentTest.TestStep == AMP2) ||
        (CurrentTest.TestStep == RRB) ||
        (CurrentTest.TestStep == FLASH) ||
        (CurrentTest.TestStep == OVERLOAD) )
    {      
        sendPacketToRelaySiren();               //*** used for UART_SIREN
    }
        
    CyDelay(5);                                 // *** Give some time for first transmit to finish - this could be better if toggled
    
//    if( CurrentTest.TestStep == UART_SIREN )
//    {   
//        sendPacket_SirenToRelay();              //*** used for UART_SIREN
//    }
    
    return;
    
}

//void SetRelayOutputs(uint8 enable)
//{
//    
//    DEMUX_CTRL_230400_Write(RTEST_CONT);                        // Tx - Select the demux channel
//    pTxPacket_RelaySiren = getTxPacket_RelaySiren();            // Tx - Get pointers to packet   
//    
//    if(enable == 1)
//    {
//        pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0xFF;       // Turn on all Relay outputs
//        pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0xFF;
//        pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0xFF;
//        pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0xFF;
//    }
//    else
//    {
//        pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0x00;       // Turn off all Relay outputs
//        pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0x00;
//        pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0x00;
//        pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0x00;
//    }
//        
//    return;
//    
//}

//void RTest_20ms_isr_start(void)
//{
//    
//    RTest_20ms_isr_count = 0;
//    
//    return;
//    
//}

void RTest_Complete_StartAutomatedStep(void)
{
    
    RTest_CompleteStatus[CurrentTest.TestStep] = 'B';
    CurrentTest.Status = 'B';
    
    RTest_Complete_20ms_isr_count = 0;
    RTest_Complete_20ms_isr_EN = 1;
    
    return;
    
}

void RTest_Complete_StopAutomatedStep(void)
{
    
    RTest_Complete_20ms_isr_EN = 0;
    if(RTest_CompleteStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
    {
        RTest_CompleteStatus[CurrentTest.TestStep] = 'P';
        CurrentTest.Status = 'P';
    }
    
    return;
    
}

//void SetRelayInputs(uint8 enable)
//{
//    
//    if(enable == 1)
//    {
//        RTest_HSide1_Write(1);       // Activate all inputs
//        RTest_HSide2_Write(1);
//        RTest_HSide3_Write(1);
//        RTest_HSide4_Write(1);
//        RTest_HSide5_Write(1);
//        RTest_HSide6_Write(1);
//        RTest_HSide7_Write(1);
//        RTest_HSide8_Write(1);
//    }
//    
//    else
//    {
//        RTest_HSide1_Write(0);      // Deactivate all inputs
//        RTest_HSide2_Write(0);
//        RTest_HSide3_Write(0);
//        RTest_HSide4_Write(0);
//        RTest_HSide5_Write(0);
//        RTest_HSide6_Write(0);
//        RTest_HSide7_Write(0);
//        RTest_HSide8_Write(0);   
//    }
//    
//    return;
//}

void RTest_Complete_PB_WaitForAction(void)
{
    
    RTest_CompleteStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
    CurrentTest.Status = 'W';
            
//            while( (!PB_NextAction_Released) && (STestStatus[CurrentTest.TestStep] != 'F') )
//            {} 
//            PB_NextAction_Released = 0;
//            
//            if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
//                STestStatus[CurrentTest.TestStep] = 'P';                                        // Set status to 'busy' until all 3 freqs play

            
//            if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
//            {
//                STestStatus[CurrentTest.TestStep] = 'P';                                        // Set status to 'busy' until all 3 freqs play
//                //CyDelay(1000);
//            }
            
    while( (RTest_CompleteStatus[CurrentTest.TestStep] != 'P') && (RTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
    {
        if(PB_NextAction_Released) 
        {
            //LED_EN_Write(1);
            RTest_CompleteStatus[CurrentTest.TestStep] = 'P'; 
            CurrentTest.Status = 'P';
            PB_NextAction_Released = 0;
        }
    }
            
    //CyDelay(1000);
    LED_EN_Write(0);    // ***not sure why this seems to be needed to make it work
    
    
    return;
}

/* [] END OF FILE */
