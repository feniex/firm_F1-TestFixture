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

static RxPacket_RelaySiren rxPacket_Relay;            
static RxPacket_RelaySiren * pRxPacket_Relay; 

static TxPacket_RelaySiren txPacket_RelaySiren;            
static TxPacket_RelaySiren * pTxPacket_RelaySiren;

static TxPacket_Relay txPacket_Relay;            
static TxPacket_Relay * pTxPacket_Relay;

static RxPacket_Quad txPacket_Quad;          //*** 
static RxPacket_Quad * pTxPacket_Quad;      //***
//RxPacket_Quad * getRxPacket_Quad(void);

//------------GLOABAL variables--------------------
static uint16 RTest_20ms_isr_count = 0;
static uint16 RTest_20ms_isr_EN = 0;

void StartTimeout(void);
void StopTimeout(void);

enum MUX_460800_CHANNEL
{ 
    CTEST_QUAD,             // This is for both cont and relay tests
    CTEST_QUADSERIAL,       // This is for both cont and relay tests
    CTEST_AUDIO,
    QTEST_QUAD              //***Not for F1 - detects Quad-Controller packets (type 'C')
};
enum DEMUX_460800_CHANNEL
{ 
    CTEST_OBDII_TX,         // 
    RTEST_QUAD_TX,          // 
    STEST_AUDIO_TX,
};

enum MUX_230400_CHANNEL              
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
enum TestStep               // *** Need to get muxes setup permanently, 
{ 
    INITIALIZE_TEST, 
    SIREN_EN,               // (Implemented - need hardware to test)
    TEST_OUTPUTS,           // (rx tested) -  TX TESTED - (***needs hardware) - (hardware drivers tested)
    DATALINK,               // (rx tested *** needs to test 115200)
    QUAD_PORTS,             // (rx_tested - with 'C' packet, ***need to test for 'Y' and 'L') - (tx tested)
    UART_SIREN,             // (rx tested - *** (IMPLEMENT NEXT)
    INPUTS,                 // RX_TESTED -  ***needs tx, ***needs hardware
    VBATT,                  // RX_TESTED - COMPLETE
    BLOCK_CURRENTS,         // RX_TESTED - TX TESTED - COMPLETE
    GPS,                    // *** needs 9600, needs hardware drivers
    FAIL
};

static uint8 RelayTestStatus[10];

static uint8 TestState = INITIALIZE_TEST;

//----------------------------------------
// Main state machine for F1-Relay Test
//----------------------------------------
void RelayTest(void)
{
    //TestState = VBATT;                  //*** Comment this out
    
    switch(TestState)
    {   
               
        case INITIALIZE_TEST:
        
            CyDelay(1000);                      // Pause before next test
        
            for (uint8 i=0;i<10;i++)            // Reset Status of aall test steps to 0
                RelayTestStatus[i] = '_';
   
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
            
            TestState = BLOCK_CURRENTS;  
            //TestState = SIREN_EN;        
        break;
             
        case SIREN_EN:
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;
             
            //while(1);
            //while( (!RTest_SIREN_EN_Read()) && (RelayTestStatus[TestState] != 'F') )              // Wait for test to complete or fail          
            {} 
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')       // If not failed, then pass
                RelayTestStatus[TestState] = 'P';

            TestState = TEST_OUTPUTS;        
        break;    
              
        case TEST_OUTPUTS:  
                
            SetRelayOutputs(1);                         // Send command to turn on relay outputs
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;
             
            while( (!RTest_Test_Outputs()) && (RelayTestStatus[TestState] != 'F') )    // Wait for test to complete or fail
            {}   
            
            RTest_20ms_isr_EN = 0;
            
            SetRelayOutputs(0);                         // Send command to turn off relay outputs
            
            if(RelayTestStatus[TestState] != 'F')       // If not failed, then pass
                RelayTestStatus[TestState] = 'P';

            TestState = DATALINK;        
        break;        
              
        case DATALINK: 
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
             
            while( (!RTest_Test_DataLink()) && (RelayTestStatus[TestState] != 'F') )    // Wait for test to complete or fail
            {}  
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')       // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
            
            TestState = QUAD_PORTS;        
        break;  
              
        case QUAD_PORTS: 
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_QuadPorts()) && (RelayTestStatus[TestState] != 'F') )    // Wait for test to complete or fail
            {}    
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')                                   // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
                   
            TestState = UART_SIREN;        
        break;  
                
        case UART_SIREN: 
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_UART_Siren()) && (RelayTestStatus[TestState] != 'F') )
            {}    
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')                                   // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
                
            TestState = INPUTS;                
        break;  
              
        case INPUTS:          
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_Inputs()) && (RelayTestStatus[TestState] != 'F') )
            {}   
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')                                   // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
                
            TestState = VBATT;                
        break;          

        case VBATT:                                     // Tested and working
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_Vbatt()) && (RelayTestStatus[TestState] != 'F') )
            {}    
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')                                   // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
            
            TestState = BLOCK_CURRENTS;                
        break; 
         
        case BLOCK_CURRENTS:                            //*** Tested and working
            
            SetRelayOutputs(1);                         // Send command to turn on relay outputs
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;                   // Start timeout
            RTest_20ms_isr_EN = 1;            
            
            while( (!RTest_Test_BlockCurrents()) && (RelayTestStatus[TestState] != 'F') )
            {} 
            
            RTest_20ms_isr_EN = 0;                      // Stop timeout
            
            SetRelayOutputs(0);                         // Send command to turn off relay outputs
            
            if(RelayTestStatus[TestState] != 'F')       // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
                
            TestState = INITIALIZE_TEST;
            //TestState = GPS;  
        break; 
    //---------------------------------------------------------------------------------------------------           
        case GPS:         
                
            RelayTestStatus[TestState] = 'B';

            RTest_20ms_isr_count = 0;
            RTest_20ms_isr_EN = 1;            
                
            while( (!RTest_Test_GPS()) && (RelayTestStatus[TestState] != 'F') )
            {}        
            
            RTest_20ms_isr_EN = 0;
            
            if(RelayTestStatus[TestState] != 'F')                                   // If not failed, then pass
                RelayTestStatus[TestState] = 'P';
            
            CyDelay(1000);
            TestState = INITIALIZE_TEST;                
        break;   
            
        case FAIL:  
        
        break;          
           
    }
      
}

/* 230400bps ********************************************************************************
*  Send 'P' packet (or 'I' packet)   (controller to relay)  - turn on all relay outputs
*  Read Hardware                            - read each input, verify all are active
*  Return: Pass/Fail
*********************************************************************************************/
uint8 RTest_Test_Outputs(void)
{

    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet   
    
    pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0xFF;       // Turn on all outputs
    pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0xFF; 
    pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0xFF;
    pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0xFF;
    
    //while(1);
    
    uint32 OutputsState = 0;
    static uint32 channel = 0;
    
    //*** Address channel 'channel 0-31' in hardware
    //selectADCChannelMux(0);                           //*** This needs to be fleshed out when hardware arrives
    
    for (uint8 channel=0; channel<32; channel++)
    {
        //*** Address channel 'channel'
        // OutputsState = ( RTest_INPUT_DEMUX | (RTest_INPUT_DEMUX << channel) )    // Read RTest_INPUT_DEMUX and store each bit in OutputsState
    }
    
    pTxPacket_RelaySiren->Payload.Outputs_1to8 = 0x00;       // Turn off all Relay outputs
    pTxPacket_RelaySiren->Payload.Outputs_9to16 = 0x00;
    pTxPacket_RelaySiren->Payload.Outputs_17to24 = 0x00;
    pTxPacket_RelaySiren->Payload.Outputs_25to32 = 0x00;
    
    if(OutputsState == 0xFFFFFF)
        return(1);                                      // If all outputs are turned on, then return pass
    else
        return(0);                                      // If not pass, then return fail
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
uint8 RTest_Test_QuadPorts(void)
{
    //DEMUX_CTRL_460800_Write(RTEST_QUAD_TX);             // Tx - Select Quad_Tx demux channel
    
    // Need to stop sending other 460800 packets
    // Need to chnge rate of sending - which is ????
    
    //pTxPacket_Quad = getTxPacket_Quad();              // Tx - Get pointers to packet
    //pTxPacket_Quad->Payload.Arrow_Module1 = 0;
    
    
    // Select the mux channel to test - need to do all of them sequentially
    for(uint8 muxchannel = 0; muxchannel < 8; muxchannel++)
    {
        //MUX_CTRL_460800_Write(muxchannel);
        
        // verify that channel
    }
    
    
    return( VerifyPacket_460800(QTEST_QUAD) );
}

/* 230400bps ********************************************************************************
*  Send 'H' packet   (siren to relay)
*  Read 'D' packet   (relay to controller)   - verify successful packet reception
*  Return: Pass/Fail
*********************************************************************************************/

uint8 RTest_Test_UART_Siren(void)
{
//    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Select the mux channel
        
    //DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
    pTxPacket_Relay = getTxPacket_Relay();              // Tx - Get pointers to packet
    
    pTxPacket_Relay->Payload.SirenFirm_0 = 0;          // Tx - Setup packet with test data
    pTxPacket_Relay->Payload.SirenFirm_1 = 1;
    pTxPacket_Relay->Payload.SirenFirm_2 = 2;
    pTxPacket_Relay->Payload.Speaker1_Overcurrent = 1;
    pTxPacket_Relay->Payload.Speaker2_Overcurrent = 1;
    
    //***
    return( VerifyPacket_230400(RTEST_CONT) );          // Rx - When packet has been verified, return 'pass'
}


/* 230400bps *****************************************************************************
*  Send 'P' packet (controller to relay) - set input logic  
*  Read 'D' packet (relay to controller) - verify the 'RelayInputs' byte 
*  Return: Pass/Fail
******************************************************************************************/
uint8 RTest_Test_Inputs(void)
{
    
//    MUX_CTRL_230400_Write(RTEST_CONT);                  // Rx - Select the mux channel
    pRxPacket_Relay = getRxPacket_Relay();              // Rx - Get pointers to packet
    
    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
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
    
    DEMUX_CTRL_230400_Write(RTEST_CONT);                // Tx - Select the demux channel
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

uint8 RTest_Test_GPS(void)
{
    
//    // 9600bps - Read packet coming in
//    // Wait to see the GPS formated data
    
    // 230400bps - Search for the GPS packet
    uint8 targetstring[6] = {'$','G','P','M','R','C'};
    
    return(0);
}

RxPacket_RelaySiren * getRxPacket_Relay(void)
{
    pRxPacket_Relay = &rxPacket_Relay;
    
    return pRxPacket_Relay;
}

TxPacket_Relay * getTxPacket_Relay()
{
    pTxPacket_Relay = &txPacket_Relay;
    
    return pTxPacket_Relay;
}

//TxPacket_Siren * getTxPacket_Siren()
//{
//    pTxPacket_Siren = &txPacket_Siren;
//    
//    return pTxPacket_Siren;
//}

TxPacket_RelaySiren * getTxPacket_RelaySiren()
{
    pTxPacket_RelaySiren = &txPacket_RelaySiren;
    
    return pTxPacket_RelaySiren;
}

//RxPacket_Quad * getTxPacket_Quad()              //***
//{
//    pTxPacket_Quad = &txPacket_Quad;
//    
//    return pTxPacket_Quad;
//}

void sendDiagPacket(void)
{

//    static uint8 RelayTestStatus_display[20];
//    
//    for(uint8 i=0;i<10;i++)
//    {
//        RelayTestStatus_display[i*2] = RelayTestStatus[i];
//        RelayTestStatus_display[(i*2) + 1] = ' ';
//    }
//    
//    UART_115200_PutArray(RelayTestStatus_display,20);
//    
//    UART_115200_PutChar('\r');
//    UART_115200_PutChar('\n');

    //LED_EN_Write(1);
    
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

void RTest_20ms_isr(void)
{
    
    RTest_20ms_isr_count++;
    if(RTest_20ms_isr_count > TIMEOUT_FAIL)
    {
        RTest_20ms_isr_count = 0;
        
        if(RTest_20ms_isr_EN == 1)
            RelayTestStatus[TestState] = 'F';
            
        return;
    }
    
    if(RTest_20ms_isr_count > 65000)
        RTest_20ms_isr_count = 0;
    
    return;
    
}

void SetRelayOutputs(uint8 enable)
{
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

/* [] END OF FILE */
