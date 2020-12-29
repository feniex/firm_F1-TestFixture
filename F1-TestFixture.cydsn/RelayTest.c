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
#include "UART_115200_Functions.h"
#include "UART_230400_Functions.h"
#include "UART_460800_Functions.h"
#include "CD4051BPW_Driver.h"

#define VOLTAGE_SYSTEM      120             // (Voltage * 10)
#define TOLERANCE_VOLTAGE   5  
#define CURRENT_LOAD        9              // (ohms)
#define TOLERANCE_CURRENT   2 
#define TIMEOUT_FAIL        50              // Number of 20msec counts before failure timeout

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

static Packet_H txPacket_H;          //     Packet 'H'
static Packet_H * pTxPacket_H;      //

static Packet_H rxPacket_H;          //     Packet 'H'
static Packet_H * pRxPacket_H;      //

static RxPacket_Quad txPacket_Quad;          //*** 
static RxPacket_Quad * pTxPacket_Quad;      //***
//RxPacket_Quad * getRxPacket_Quad(void);

//------------GLOABAL variables--------------------

//extern uint16 _100ms_flag;
//uint16 _100ms_flag = 0;
//uint16 isr_count;

static uint16 RTest_20ms_isr_count = 0;
static uint16 RTest_20ms_isr_EN = 0;

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
    CTEST_OBDII_TX,         // 
    RTEST_QUAD_TX,          // 
    STEST_AUDIO_TX,
};

enum MUX_DEMUX_230400_CHANNEL              
{ 
    CTEST_RELAY, 
    RTEST_CONT,
    RTEST_SIREN,
    STEST_RELAY            
};

enum MUX_115200_CHANNEL      
{ 
    RTEST_DLINK1,    
    RTEST_DLINK2,    
    CTEST_USB_DEBUG,
    DIAG_UART_RX        
};

// --------------Test steps---------------
#define NUMBER_TEST_STEPS   18

enum TestStep               // *** Need to get muxes setup permanently, 
{ 
    INITIALIZE_TEST, 
    SIREN_EN,               // *** (Implemented - need hardware to test)
    TEST_OUTPUTS,           // ---------------------- 230400 TX TESTED      - (needs hardware)
    DATALINK,               // (***115200 rx tested)
    //QUAD_PORTS,           // 460800 RX TESTED   460800 TX TESTED      (*** need to implement last 4 channels and test them all)
        QUAD_PORT_1,
        QUAD_PORT_2,
        QUAD_PORT_3,
        QUAD_PORT_4,
        QUAD_PORT_5,
        QUAD_PORT_6,
        QUAD_PORT_7,
        QUAD_PORT_8,
    UART_SIREN,             // 230400 RX_TESTED     - 230400 TX TESTED      - 
    INPUTS,                 // 230400 RX_TESTED     - 230400 TX TESTED      - (needs hardware)
    VBATT,                  // 230400 RX_TESTED                             - COMPLETE
    BLOCK_CURRENTS,         // 230400 RX_TESTED     - 230400 TX TESTED      - COMPLETE
    GPS,                    // (230400 rx tested)
    FAIL
};

static uint8 RTestStatus[NUMBER_TEST_STEPS];

//----------------------------------------
// Main state machine for F1-Relay Test
//----------------------------------------
uint8 RelayTest(void)
{
    //TestState = VBATT;                  //*** Comment this out
    
    switch(CurrentTest.TestStep)
    {   
               
        case INITIALIZE_TEST:
        
            //isr_count = 0;
        
//            if(_100ms_flag == 1)
//                LED_EN_Write(0);
//        
//            else if(_100ms_flag == 0)
//                LED_EN_Write(0);
                
            //CyDelay(1000);                      // Pause before next test
        
            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)            // Reset Status of aall test steps to 0
                RTestStatus[i] = '_';
   
            // Initialize TX_RelaySiren packet
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet 
            for(uint8 i;i<79;i++)
                pTxPacket_RelaySiren->bytes[i] = i;

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
            
            
            //CurrentTest.TestStep = SIREN_EN;
            CurrentTest.TestStep = TEST_OUTPUTS;
            //CurrentTest.TestStep = DATALINK;
            //CurrentTest.TestStep = QUAD_PORT_1;
            //CurrentTest.TestStep = UART_SIREN; 
                   
        break;
             
        case SIREN_EN:
                
            //RTest_StartAutomatedStep(); 
             
            //while( (!RTest_SIREN_EN_Read()) && (RelayTestStatus[TestState] != 'F') )              // Wait for test to complete or fail          
            {} 
            
            //RTest_StopAutomatedStep();
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = TEST_OUTPUTS;        
        break;    
              
        case TEST_OUTPUTS:  
                
            RTest_StartAutomatedStep(); 
            
            while(!RTest_Test_Outputs())                                                        // Wait for test to complete or fail
            {}  
//            while( (!RTest_Test_Outputs()) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
//            {}   
            
//            RTest_StopAutomatedStep();

            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = DATALINK;        
        break;        
              
        case DATALINK: 

            RTest_StartAutomatedStep();           
             
            while( (!RTest_Test_DataLink()) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}  
            
            RTest_StopAutomatedStep();
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = QUAD_PORT_1;        
        break;  
              
        case QUAD_PORT_1: 
                
            RTest_StartAutomatedStep();  
                
            DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Select TX xhannel
            MUX_CTRL_460800_Write(RTEST_QUAD_1);                // Select RX channel
                      
            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_StopAutomatedStep();
                  
            CurrentTest.TestStep = QUAD_PORT_2;      
        break;  
            
        case QUAD_PORT_2: 
                
            RTest_StartAutomatedStep();  
                
            DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Select TX xhannel
            MUX_CTRL_460800_Write(RTEST_QUAD_2);                // Select RX channel
                      
            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_StopAutomatedStep();
                  
            CurrentTest.TestStep = QUAD_PORT_3;      
        break;  
            
        case QUAD_PORT_3: 
                
            RTest_StartAutomatedStep();  
                
            DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Select TX xhannel
            MUX_CTRL_460800_Write(RTEST_QUAD_3);                // Select RX channel
                      
            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_StopAutomatedStep();
                  
            CurrentTest.TestStep = QUAD_PORT_4;      
        break;  
            
        case QUAD_PORT_4: 
                
            RTest_StartAutomatedStep();  
                
            DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Select TX xhannel
            MUX_CTRL_460800_Write(RTEST_QUAD_4);                // Select RX channel
                      
            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (RTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_StopAutomatedStep();
                  
            //CurrentTest.TestStep = QUAD_PORT_5; 
            CurrentTest.TestStep = INITIALIZE_TEST;
        break;  
                
        case UART_SIREN: 
                
//            RTestStatus[CurrentTest.TestStep] = 'B';
//
//            RTest_20ms_isr_count = 0;
//            RTest_20ms_isr_EN = 1;       
            
            RTest_StartAutomatedStep();
                
            while( (!RTest_Test_UART_Siren()) && (RTestStatus[CurrentTest.TestStep] != 'F') )
            {}    
            
            RTest_StopAutomatedStep();
            
//            RTest_20ms_isr_EN = 0;
//            
//            if(RTestStatus[CurrentTest.TestStep] != 'F')                                   // If not failed, then pass
//                RTestStatus[CurrentTest.TestStep] = 'P';
                
            CurrentTest.TestStep = INITIALIZE_TEST;  
            //TestState = INPUTS;                
        break;  
              
        case INPUTS:          
                
            RTestStatus[CurrentTest.TestStep] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_Inputs()) && (RTestStatus[CurrentTest.TestStep] != 'F') )
            {}   
            
            RTest_20ms_isr_EN = 0;
            
            if(RTestStatus[CurrentTest.TestStep] != 'F')                                   // If not failed, then pass
                RTestStatus[CurrentTest.TestStep] = 'P';
                
            CurrentTest.TestStep = VBATT;                
        break;          

        case VBATT:                                     // Tested and working
                
            RTestStatus[CurrentTest.TestStep] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_Vbatt()) && (RTestStatus[CurrentTest.TestStep] != 'F') )
            {}    
            
            RTest_20ms_isr_EN = 0;
            
            if(RTestStatus[CurrentTest.TestStep] != 'F')                                   // If not failed, then pass
                RTestStatus[CurrentTest.TestStep] = 'P';
            
            CurrentTest.TestStep = BLOCK_CURRENTS;                
        break; 
         
        case BLOCK_CURRENTS:                            //*** Tested and working
            
            SetRelayOutputs(1);                         // Send command to turn on relay outputs
                
            RTestStatus[CurrentTest.TestStep] = 'B';

            RTest_20ms_isr_count = 0;                   // Start timeout
            RTest_20ms_isr_EN = 1;            
            
            while( (!RTest_Test_BlockCurrents()) && (RTestStatus[CurrentTest.TestStep] != 'F') )
            {} 
            
            RTest_20ms_isr_EN = 0;                      // Stop timeout
            
            SetRelayOutputs(0);                         // Send command to turn off relay outputs
            
            if(RTestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
                RTestStatus[CurrentTest.TestStep] = 'P';
                
            //TestState = INITIALIZE_TEST;
            CurrentTest.TestStep = GPS;  
        break; 
    //---------------------------------------------------------------------------------------------------           
        case GPS:         
                
            RTestStatus[CurrentTest.TestStep] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_GPS()) && (RTestStatus[CurrentTest.TestStep] != 'F') )
            {}        
            
            RTest_20ms_isr_EN = 0;
            
            if(RTestStatus[CurrentTest.TestStep] != 'F')                                   // If not failed, then pass
                RTestStatus[CurrentTest.TestStep] = 'P';
            
            CyDelay(1000);
            CurrentTest.TestStep = INITIALIZE_TEST;                
        break;   
            
        case FAIL:  
        
        break;          
           
    }
      
    return(0);
    
}

/* 230400bps ********************************************************************************
*  Send 'P' packet (or 'I' packet)   (controller to relay)  - turn on all relay outputs
*  Read Hardware                            - read each input, verify all are active
*  Return: Pass/Fail
*********************************************************************************************/
uint8 RTest_Test_Outputs(void)
{

    uint32 OutputsState = 0;
    static uint32 channel = 0;
    
    SetRelayOutputs(1);                                                     // Send command to turn on relay outputs

    for (uint8 channel=0; channel<32; channel++)                            // Address and read channels '0-31' in hardware
    {
        selectADCChannelMux(channel);                                       //*** This needs to be fleshed out when hardware arrives
        //OutputsState = ( RTest_DEMUX_COM | (RTest_DEMUX_COM << channel) )   // Read RTest_INPUT_DEMUX and store each bit in OutputsState
    }
    
    SetRelayOutputs(0);                                                     // Send command to turn off relay outputs
    
    if(OutputsState == 0xFFFFFF)
        return(1);                                                          // If all outputs are turned on, then return pass
    else
        return(0);                                                          // If not pass, then return fail
}

/* 230400/115200bps **************************************************************************
*  230400 - Tx - Send 'S' packet   (controller to relay/siren)    - turn on all relay outputs
*  115200 - Rx - Read 'S' packet   (relay to datalink device)     - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
uint8 RTest_Test_DataLink(void)
{
    
//    //*** 230400bps - Send simulated controller packet - (siren packet)
//    //  (I think this packet should be sent all the time)
//        pTxPacket_Relay->Payload.Siren1Tone;
//        pTxPacket_Relay->Payload.Siren2Tone;
//        pTxPacket_Relay->Payload.SirenEnable;
    
//    //MUX_CTRL_115200_Write(RTEST_DLINK1);            //Select the RTest_RS485_DLink1_RX channel 
//    while( !VerifyPacket_115200(RTEST_DLINK1) )     //Read and verify datalink packet
//    {}
//    //MUX_CTRL_115200_Write(RTEST_DLINK2);            //Select the RTest_RS485_DLink1_RX channel 
//    while( !VerifyPacket_115200(RTEST_DLINK2) )     //Read and verify datalink packet
//    {}
    
    return(1);                                      // If both packets get verified, then return pass
}

/* 460800bps ********************************************************************************
*  Send 'L' packet   (controller to relay)
*  Read 'L' packet   (relay to quad device)  - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
//uint8 RTest_Test_QuadPorts(uint8 muxchannel)
//{
//    //static uint8 muxchannelsuccess[8] = {0,0,0,0,0,0,0,0};
//    //uint8 muxchannel = 0;
//
//    DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Tx - Select Quad_Tx demux channel
//    //DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Tx - Select Quad_Tx demux channel
//    
////    //*** Select the mux channel to test - need to do all of them sequentially
////    //MUX_CTRL_460800_Write(0);           // *** just for test
//////    MUX_CTRL_460800_Write(muxchannel);
//////    
//////    if( VerifyPacket_460800(CTEST_RTEST_QUAD) )
//////            muxchannelsuccess[muxchannel]++;
////    
////    for(uint8 muxchannel = 0; muxchannel < 8; muxchannel++)
////    {
////        MUX_CTRL_460800_Write(muxchannel);
////        
////        RTest_StartAutomatedStep();
////        
//////        if( VerifyPacket_460800(CTEST_RTEST_QUAD) )
//////            muxchannelsuccess[muxchannel]++;
////            
//////        if( muxchannelsuccess[muxchannel] > 10)
//////            muxchannelsuccess[muxchannel] = 0;
////
////        
////        while( !VerifyPacket_460800(CTEST_RTEST_QUAD) )
////        {}
////        LED_EN_Write(0);
////        
////        RTest_StopAutomatedStep();
////        
////        //if(CurrentTest.TestStep =
//        
////    }
////    
////
////    
//////    if(muxchannelsuccess[muxchannel] == )
////
////    //return(1);          // If pass return a 1
////    return(0);          // else
//    
//    return( VerifyPacket_460800(CTEST_RTEST_QUAD) );
//    return( VerifyPacket_460800(CTEST_RTEST_QUAD) );
//}

//*** This needs some work
/* 230400bps ********************************************************************************
*  ***Send 'H' packet   (siren to relay)
*  ***Read 'D' packet   (relay to controller)   - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/
uint8 RTest_Test_UART_Siren(void)
{
// We need to send a Siren packet (through relay to controller) - ***passes through the micro
// Then check that the packet going from the relay to the controller    
   
    // test receive from siren
    //DEMUX_CTRL_230400_Write(RTEST_SIREN);                  // Rx - Select the demux channel

    pTxPacket_H = getTxPacket_H();                          // Load the packet with data to check for in 'D' packet 
    pTxPacket_H->Payload.SirenFirm_0 = 's';
    pTxPacket_H->Payload.SirenFirm_1 = 's';
    pTxPacket_H->Payload.SirenFirm_2 = 's';
    pTxPacket_H->Payload.Speaker1_Overcurrent = 's';
    pTxPacket_H->Payload.Speaker2_Overcurrent = 's';

    
    // test transmit to controller ***need tx wires on relay to test
    MUX_CTRL_230400_Write(RTEST_CONT);                                  // Rx - Select the mux channel
    
//    pRxPacket_Relay = getRxPacket_Relay();                              // Rx - Get pointers to packet      
//    while(  (pRxPacket_Relay->Payload.SirenFirm_0 != 's' ) &&           // Wait for the packet to be verified
//            (pRxPacket_Relay->Payload.SirenFirm_1 != 's' ) &&
//            (pRxPacket_Relay->Payload.SirenFirm_2 != 's' ) &&
//            (pRxPacket_Relay->Payload.Speaker1_Overcurrent != 's' ) &&
//            (pRxPacket_Relay->Payload.Speaker2_Overcurrent != 's' ) )
//    {}
//          
//    LED_EN_Write(1);
//----------------------------------------------------------------------------------------------
    
// ***We need to detect a packet going (from the relay to the siren)
// Send a 'S' packet (from controller to relay/siren)
// Read and verify 'S' packets (from relay to siren)
    
    //DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
    //(no need to load the packet)
    //CyDelay(100);
    
//////    pTxPacket_Relay = getTxPacket_Relay();              // Tx - Get pointers to packet
//////    pTxPacket_Relay->Payload.SirenFirm_0 = 0;          // Tx - Setup packet with test data
//////    pTxPacket_Relay->Payload.SirenFirm_1 = 1;
//////    pTxPacket_Relay->Payload.SirenFirm_2 = 2;
//////    pTxPacket_Relay->Payload.Speaker1_Overcurrent = 1;
//////    pTxPacket_Relay->Payload.Speaker2_Overcurrent = 1;
    
    //MUX_CTRL_230400_Write(RTEST_SIREN);                                  // Rx - Select the mux channel
    //CyDelay(100);
    //return( VerifyPacket_230400(STEST_RELAY) );          // Rx - When packet has been verified, return 'pass'

    return(0);
}


/* 230400bps *****************************************************************************
*  Send 'P' packet (controller to relay) - set input logic  
*  Read 'D' packet (relay to controller) - verify the 'RelayInputs' byte 
*  Return: Pass/Fail
******************************************************************************************/
uint8 RTest_Test_Inputs(void)
{
    
    //MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Select the mux channel
    pRxPacket_Relay = getRxPacket_Relay();              // Rx - Get pointers to packet
    
    //DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet
    
    // RTest_HSide1_Write(0);                           // Deactivate all inputs
    // RTest_HSide2_Write(0);
    // RTest_HSide3_Write(0);
    // RTest_HSide4_Write(0);
    // RTest_HSide5_Write(0);
    // RTest_HSide6_Write(0);
    // RTest_HSide7_Write(0);
    // RTest_HSide8_Write(0);
    
    pTxPacket_RelaySiren->Payload.HiLoInputLogic = 0x00;     // Set the input logic to be all low
    
    //while(1);
    
//    if(pRxPacket_Relay->Payload.RelayInputs != 0x00)    // Verify all inputs are deactivated, if not then fail
//        return(0);
    
    pTxPacket_RelaySiren->Payload.HiLoInputLogic = 0xFF;     // Set the input logic to be all hi
    
    
    
//    if(pRxPacket_Relay->Payload.RelayInputs != 0x00)    // Verify all inputs are deactivated, if not then fail
//        return(0);
    
    // RTest_HSide1_Write(1);                           // Activate all inputs
    // RTest_HSide2_Write(1);
    // RTest_HSide3_Write(1);
    // RTest_HSide4_Write(1);
    // RTest_HSide5_Write(1);
    // RTest_HSide6_Write(1);
    // RTest_HSide7_Write(1);
    // RTest_HSide8_Write(1);
    
    if(pRxPacket_Relay->Payload.RelayInputs != 0xFF)    // Verify all inputs are activated, if not then return fail
        return(0);
    
    return(1);                                          // If this step was not failed, return pass
}


/* 230400bps *****************************************************************************
*  Read a 'D' packet (relay to controller)  - verify the 'Voltage_BATT' byte
*  Return: Pass/Fail
******************************************************************************************/
uint8 RTest_Test_Vbatt(void)
{
//    MUX_CTRL_230400_Write(RTEST_CONT);                              // Rx - Select the mux channel
    pRxPacket_Relay = getRxPacket_Relay();                          // Rx - Get pointers to packet
    
    uint8 Vbatt_Reading = 0;
    
    Vbatt_Reading = pRxPacket_Relay->Payload.Voltage_BATT;          // Read Vbatt value
    
    if( (Vbatt_Reading < (VOLTAGE_SYSTEM + TOLERANCE_VOLTAGE) ) &&
        (Vbatt_Reading > (VOLTAGE_SYSTEM - TOLERANCE_VOLTAGE) ) )
        return(1);                                                  // If Vbatt is within TOLERANCE_VOLTAGE, return pass
    else
        return(0);                                                  // If not pass, then return fail
}

/* 230400bps ***************************************************************
*  Send a 'P'/'I' packet (controller to relay)  - Controller packet to turn on all the Relay outputs
*  Read a 'D' packet (relay to controller)  - verify block currents are within a tolerance
****************************************************************************/
uint8 RTest_Test_BlockCurrents(void)
{
    
    uint8 BlockCurrentPass = 0x00;
    uint8 BlockCurrentValue = 0x00;
    
//    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Select the mux channel 
    pRxPacket_Relay = getRxPacket_Relay();              // Rx - Get pointers to packet
    
    //DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet
    
    for(uint8 i=0;i<4;i++)                              // Save pass/fail for each block channel
    {
        BlockCurrentValue = RTest_BlockCurrent(i);
        BlockCurrentPass = (BlockCurrentPass << 1) | BlockCurrentValue;
    }
    
    if( (BlockCurrentPass & 0x0F) == 0x0F)
        return(1);                                      // If all block currents are within TOLERANCE_CURRENT, return pass 
    else
        return(0);                                      // If not pass, then return fail

}

/* 230400bps ****************************************************
*   (wait for the GPS hardware to acquire a signal)
*   Read the GPS packet - search for the GPS formated data
*****************************************************************/
uint8 RTest_Test_GPS(void)
{
    
    static uint8 targetstring[6] = {'$','G','P','M','R','C'};

    //uint8 findpacket(uint8 dataByte) - this should pass the target string
    //processByteReceivedHandler_230400(&targetstring);

    
    
    return(0);
}

RxPacket_RelaySiren * getRxPacket_Relay(void)
{
    pRxPacket_Relay = &rxPacket_Relay;
    
    return pRxPacket_Relay;
}

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

TxPacket_RelaySiren * getTxPacket_RelaySiren()          // STest Tx - 'I' packet sent to relay and siren from controller
{
    pTxPacket_RelaySiren = &txPacket_RelaySiren;
    
    return pTxPacket_RelaySiren;
}

RxPacket_RelaySiren * getRxPacket_RelaySiren()          // STest - 'D' packet sent to controller from relay and siren
{
    pRxPacket_RelaySiren = &rxPacket_RelaySiren;
    
    return pRxPacket_RelaySiren;
}

//Packet_H * getPacket_H(void);
Packet_H * getTxPacket_H()
{
    pTxPacket_H = &txPacket_H;
    
    return pTxPacket_H;
}

Packet_H * getRxPacket_H()
{
    pRxPacket_H = &rxPacket_H;
    
    return pRxPacket_H;
}


//RxPacket_Quad * getTxPacket_Quad()              //***
//{
//    pTxPacket_Quad = &txPacket_Quad;
//    
//    return pTxPacket_Quad;
//}

void RTest_sendDiagPacket(void)
{

    static uint8 RelayTestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        RelayTestStatus_display[i*2] = RTestStatus[i];
        RelayTestStatus_display[(i*2) + 1] = ' ';
    }
    
    DEMUX_CTRL_230400_Write(RTEST_SIREN);
    
    UART_230400_PutArray(RelayTestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_230400_PutChar('\r');
    UART_230400_PutChar('\n');
    
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
uint8 RTest_BlockCurrent(uint8 block)
{
    
    uint8 Current_Reading = 0;
    
    pRxPacket_Relay = getRxPacket_Relay();
    
    if(block == 0)
        Current_Reading = pRxPacket_Relay->Payload.BlockCurrent_1;
    else if(block == 1)
        Current_Reading = pRxPacket_Relay->Payload.BlockCurrent_2;
    else if(block == 2)
        Current_Reading = pRxPacket_Relay->Payload.BlockCurrent_3;
    else if(block == 3)
        Current_Reading = pRxPacket_Relay->Payload.BlockCurrent_4;
    else 
        return(0);
    
    if( (Current_Reading < (CURRENT_LOAD + TOLERANCE_CURRENT) ) &&
        (Current_Reading > (CURRENT_LOAD - TOLERANCE_CURRENT) ) )
        return(1);
    else
        return(0);
        
}

void RTest_10ms_isr(void)                       // Times Quad and Audio packets
{

//    if(CurrentTest.TestStep == QUAD_PORTS)        // *** moved to 20ms  
//        sendPacketToRelay_Quad();

    return;
    
}

void RTest_20ms_isr(void)                       // Manage Timeout for failure
{
        if( (CurrentTest.TestStep == QUAD_PORT_1) ||        // *** send quad packet if needed 
            (CurrentTest.TestStep == QUAD_PORT_2) ||
            (CurrentTest.TestStep == QUAD_PORT_3) ||
            (CurrentTest.TestStep == QUAD_PORT_4) ||
            (CurrentTest.TestStep == QUAD_PORT_5) ||
            (CurrentTest.TestStep == QUAD_PORT_6) ||
            (CurrentTest.TestStep == QUAD_PORT_7) ||
            (CurrentTest.TestStep == QUAD_PORT_8) )
        {
            sendPacketToRelay_Quad();
        }
    
    RTest_20ms_isr_count++;
    if(RTest_20ms_isr_count > TIMEOUT_FAIL)
    {
        RTest_20ms_isr_count = 0;
        
        if(RTest_20ms_isr_EN == 1)
        {
            RTestStatus[CurrentTest.TestStep] = 'F';
            CurrentTest.Status = 'F';
        }
            
        return;
    }
    
    if(RTest_20ms_isr_count > 65000)
        RTest_20ms_isr_count = 0;
    
    return;
    
}

void RTest_50ms_isr(void)                       // Times interboard comms, and serial diagnostics
{
    
    //RTest_sendDiagPacket();
    
    //if(isr_count > 5)
        
//    if( (isr_count % 5) == 0 )
//    {
        if( (CurrentTest.TestStep == TEST_OUTPUTS) ||
            (CurrentTest.TestStep == DATALINK) ||
            (CurrentTest.TestStep == UART_SIREN) ||
            (CurrentTest.TestStep == INPUTS) ||
            (CurrentTest.TestStep == BLOCK_CURRENTS) )
        {      
            sendPacketToRelaySiren();               //*** used for UART_SIREN
        }
            
        if( CurrentTest.TestStep == UART_SIREN )
        {   
            sendPacket_SirenToRelay();              //*** used for UART_SIREN
        }
//    }
    
    return;
    
}

void SetRelayOutputs(uint8 enable)
{
    
    //DEMUX_CTRL_230400_Write(RTEST_CONT);                        // Tx - Select the demux channel
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();            // Tx - Get pointers to packet   
    
    if(enable == 1)
    {
        pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0xFF;       // Turn on all Relay outputs
        pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0xFF;
        pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0xFF;
        pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0xFF;
    }
    else
    {
        pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0x00;       // Turn off all Relay outputs
        pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0x00;
        pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0x00;
        pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0x00;
    }
        
    return;
    
}

//void RTest_20ms_isr_start(void)
//{
//    
//    RTest_20ms_isr_count = 0;
//    
//    return;
//    
//}

void RTest_StartAutomatedStep(void)
{
    
    RTestStatus[CurrentTest.TestStep] = 'B';
    CurrentTest.Status = 'B';
    
    RTest_20ms_isr_count = 0;
    RTest_20ms_isr_EN = 1;
    
    return;
    
}

void RTest_StopAutomatedStep(void)
{
    
    RTest_20ms_isr_EN = 0;
    if(RTestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
    {
        RTestStatus[CurrentTest.TestStep] = 'P';
        CurrentTest.Status = 'P';
    }
    
    return;
    
}

/* [] END OF FILE */
