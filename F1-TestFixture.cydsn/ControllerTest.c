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
#include "ControllerTest.h"
#include "UART_460800_Functions.h"
#include "UART_230400_Functions.h"

#define DEBOUNCE_COUNT      2           // (5 * 20msec)


static RxPacket_Controller rxPacket_Controller;         // 'I' (includes 'P') packet (controller to relay) - Pushbuttons         
static RxPacket_Controller * pRxPacket_Controller;

static TxPacket_Controller txPacket_Controller;         // 'D' packet (relay to controller) - Initialize,     
static TxPacket_Controller * pTxPacket_Controller;

static TxPacket_RelaySiren txPacket_Relay;              // 'I' packet (relay to controller) - LEDS_RGB     
static TxPacket_RelaySiren * pTxPacket_Relay;


static uint16 CTest_20ms_isr_count = 0;         // Test step timeout variables
static uint16 CTest_20ms_isr_EN = 0;

static uint8 PB_NextAction_Pressed = 0;         // Pushbutton 
static uint8 PB_NextAction_Released = 0;


enum DATA_TYPE_460800
{ 
    CTEST_AUDIO,        // This is for both cont and relay tests
    CTEST_RTEST_QUAD   // CTest/RTest - quad normal - (controller to relay, relay to quad)
//    CTEST_A,            //*** needs to  (*** not used - only need to look for 'L' packet)
//    QTEST_QUAD          // (*** not used - Quad-Controller packets - type 'C')
};

enum MUX_460800_CHANNEL
{ 
    CTEST_QUAD,  
    CTEST_AUDIOSTREAM,
    //QTEST_QUAD             
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

// --------------Test steps---------------
#define NUMBER_TEST_STEPS       10
static uint16 CTest_TimeoutCount[NUMBER_TEST_STEPS] = {50,1500,100,50,50,50,50,50,50};    // Number of 20msec counts before failure timeout, for each step

static uint8 CTestStatus[NUMBER_TEST_STEPS];

enum TestStep           
{ 
    INITIALIZE_TEST, 
    CONFIRM_BOOTUP,         // TESTED (needs timeout adjustment)
    CONFIG_FILE,
    TEST_POWERMODES,        // (had controller issue) - Tests Vbatt detect, USB_5V detect - (uses input ignition and OBDII ignition also)
    QUAD_STREAM,            // ***config (need to test)
    AUDIO_STREAM,           // (not a priority)
    DEBUG_PORT,             // (not a priority)
    OBDII,                  // ***config (need to test)
    LEDS_RGB,               // (need to implement packet on controller side)
    PUSHBUTTONS,            // ***config (need to test)
};


static uint8 CTestStatus[NUMBER_TEST_STEPS];

//static uint8 TestState = INITIALIZE_TEST;

// Should have SOM installed (maybe with test software embedded)
// Controller should already be programmed with a test config file



uint8 ControllerTest(void)
{
    
    switch(CurrentTest.TestStep)
    {   
        
        //----------------Set Default States----------------------------
        // Controller should be powered only by Vbatt at this time, with ignition ON
        //  - Enable Vbatt
        //  - Disable USB_5V
        //  - Send packet simulating ignition ON event
        //--------------------------------------------------------------
        
        
        // *** Wire up the boards so that they are powered through ech other, simultaneously
        // ***Try new programmer on existing boards (maybe change micros on one or both)
        // ***Setup a controller with a relay normally - see it working and load a config file
        // ***Config file needs to: 
        // ***
        // ***See that the controller powers up through the TF and cable - start talking testing from here
        
        case INITIALIZE_TEST:
        
            CTest_CONT_VBATT_EN_Write(1);                           // Enable Vbatt power to controller
            CTest_USB_5V_EN_Write(0);
        
            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)                 // Reset Status of aall test steps to 0
                CTestStatus[i] = '_';
        
//            for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)                  // Set current state to 'Initialize'
//                CTestStatus[i] = 'I';        
            CurrentTest.Status = 'I';
        
            pTxPacket_Controller = getTxPacket_Controller();        // Tx - Initialize Tx packet, and begin sending 'relay ignition on'
//            if( PB_NextAction_Read())
                pTxPacket_Controller->Payload.RelayInputs = 0x01;
//            else
//                pTxPacket_Controller->Payload.RelayInputs = 0x00;

            CyDelay(1000);
      
            //CurrentTest.TestStep = INITIALIZE_TEST;
            CurrentTest.TestStep = CONFIRM_BOOTUP;
            //CurrentTest.TestStep = TEST_POWERMODES;
//            CurrentTest.TestStep = DEBUG_PORT;
//            CurrentTest.TestStep = QUAD_STREAM;
//            CurrentTest.TestStep = AUDIO_STREAM;
//            CurrentTest.TestStep = LEDS_RGB;
//            CurrentTest.TestStep = PUSHBUTTONS;
        
        break;
        
        case CONFIRM_BOOTUP:
        
            CTest_StartAutomatedStep();

            MUX_CTRL_230400_Write(CTEST_RELAY);

            while( (!VerifyPacket_230400(CTEST_RELAY)) && (CTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {} 
            
            CTest_StopAutomatedStep();
            
            CyDelay(1000);

            //CurrentTest.TestStep = INITIALIZE_TEST; 
            CurrentTest.TestStep = CONFIG_FILE;
            //CurrentTest.TestStep = TEST_POWERMODES;
            //CurrentTest.TestStep = QUAD_STREAM;
        
        break;
            
        case CONFIG_FILE:       // User must manually load config file using desktop software
        
            CTest_CONT_VBATT_EN_Write(1);                           // Enable Vbatt power to controller
            CTest_USB_5V_EN_Write(1);
        
            CTest_PB_WaitForAction();
            
            CTest_CONT_VBATT_EN_Write(1);                           // Enable Vbatt power to controller
            CTest_USB_5V_EN_Write(0);

            //CurrentTest.TestStep = INITIALIZE_TEST;                   
            //CurrentTest.TestStep = TEST_POWERMODES;
            CurrentTest.TestStep = QUAD_STREAM;
        
        break;
        
        case TEST_POWERMODES:           // Vbatt Detect, USB Detect - 230400bps 
            
            //CTestStatus[CurrentTest.TestStep] = 'B';
            CTest_StartAutomatedStep();
                
            CTest_CONT_VBATT_EN_Write(1);                           // Set initial power mode conditions
            CTest_USB_5V_EN_Write(0);     
            
            pTxPacket_Controller = getTxPacket_Controller();        // Tx - Send relay ignition 'off';
            pTxPacket_Controller->Payload.RelayInputs = 0x00;
                           
            pRxPacket_Controller = getRxPacket_Controller();
            while( (pRxPacket_Controller->Payload.PowerState != 0x00) && (CTestStatus[CurrentTest.TestStep] != 'F') )
            {}
            
            pTxPacket_Controller->Payload.RelayInputs = 0x01;       // Tx - Send relay ignition 'on'
            
            while( (pRxPacket_Controller->Payload.PowerState != 0x01) && (CTestStatus[CurrentTest.TestStep] != 'F') )
            {}
                                   
            CTest_USB_5V_EN_Write(1);                               // Turn on USB_5V

            while( (pRxPacket_Controller->Payload.PowerState != 0x02) && (CTestStatus[CurrentTest.TestStep] != 'F') )
            {}
            
            CTest_StopAutomatedStep();
            
            CyDelay(1000);

            //CurrentTest.TestStep = INITIALIZE_TEST;
            CurrentTest.TestStep = QUAD_STREAM;
            
        break;
                
        case QUAD_STREAM:
            // Config file should be sending a quad stream based on a pushbutton/slideswitch

            LED_EN_Write(1);        
        
            CTest_StartAutomatedStep();

            MUX_CTRL_230400_Write(CTEST_QUAD);

            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (CTestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}
            
            CTest_StopAutomatedStep();
            
            CyDelay(1000);
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = AUDIO_STREAM;

        break;
                       
        case AUDIO_STREAM:
                
            // Audio Stream (not a priority)
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = DEBUG_PORT;
                
        break;
                         
        case DEBUG_PORT:   
                
            // Debug Port (will need hardware to test) 
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = OBDII;
      
        break;  
            
        case OBDII:  
                
            // OBDII - (requires a config file)
            // Send a known vehicle event
            // Verify expected response - (corresponding output will be enabled)
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = LEDS_RGB;
      
        break;             
            
        case LEDS_RGB:   
                
            // Send a 'I' packet upstream to controller to manually control the LEDs
            // Make them full bright red for 1 sec, then green, then blue
            
            pTxPacket_Relay = getTxPacket_Relay();        // Tx - Initialize Tx packet, and begin sending 'relay ignition on'

            pTxPacket_Relay->Payload.LED_01_B = 0xFF;
            pTxPacket_Relay->Payload.LED_02_B = 0xFF;
            pTxPacket_Relay->Payload.LED_03_B = 0xFF;
            pTxPacket_Relay->Payload.LED_04_B = 0xFF;
            pTxPacket_Relay->Payload.LED_05_B = 0xFF;
            pTxPacket_Relay->Payload.LED_06_B = 0xFF;
            pTxPacket_Relay->Payload.LED_07_B = 0xFF;
            pTxPacket_Relay->Payload.LED_08_B = 0xFF;
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            //CurrentTest.TestStep = PUSHBUTTONS;
      
        break;  
            
        case PUSHBUTTONS:  
            // configfile - Controller should have the config file setup to turn on all outputs with each pushbutton
            // wait until all 

            CTestStatus[CurrentTest.TestStep] = 'W';
            
            while( (!CTest_ReadPushbuttons()) && (CTestStatus[CurrentTest.TestStep] != 'F') )   // Check that the packet is turning all Relay Outputs on
            {}
            
            CTestStatus[CurrentTest.TestStep] = 'P';
                
            CurrentTest.TestStep = INITIALIZE_TEST;
      
        break;  
            
    }
    
    return(0);
}



uint8 CTest_ReadPushbuttons()
{

    MUX_CTRL_230400_Write(CTEST_RELAY);                             // Read a 'I' (includes 'P') packet
    pRxPacket_Controller = getRxPacket_Controller();    
    
    if( (pRxPacket_Controller->Payload.Outputs_1to8 == 0xFF) &&
        (pRxPacket_Controller->Payload.Outputs_9to16 == 0xFF) &&
        (pRxPacket_Controller->Payload.Outputs_17to24 == 0xFF) &&
        (pRxPacket_Controller->Payload.Outputs_25to32 == 0xFF) )
    {
        return(1);
    } 
    else
        return(0);
       
}

//uint8 CTest_ReadPowerMode()
//{  
//    
//    //*** We need to inlude Relay ignition signal, and OBD as triggers
//    //*** (Controller config file should have all input logic set to Hi???)
//    
//    // Switch MUX_230400 to read CTest_RS485_Relay_Rx
////        MUX_CTRL_230400_Write(0x00);
//     
//    // Read the PowerState byte, Return the Powerstate byte
//        pRxPacket_Controller = getRxPacket_Controller();
//        return(pRxPacket_Controller->Payload.PowerState);
//   
//}

//void CTest_SendIgnitionState(uint8 ignition_state)           //*** This function needs work
//{
//    
//    pTxPacket_Controller = getTxPacket_Controller();
//    pTxPacket_Controller->Payload.RelayInputs = (pTxPacket_Controller->Payload.RelayInputs | 0x01);
//    
//    MUX_CTRL_230400_Write(0x00);                        // Set the Mux channel
//    
//    
//    return;
//}


TxPacket_RelaySiren * getTxPacket_Relay(void)
{
    pTxPacket_Relay = &txPacket_Relay;
    
    return pTxPacket_Relay;
}

RxPacket_Controller * getRxPacket_Controller(void)
{
    pRxPacket_Controller = &rxPacket_Controller;
    
    return pRxPacket_Controller;
}

TxPacket_Controller * getTxPacket_Controller(void)
{
    pTxPacket_Controller = &txPacket_Controller;
    
    return pTxPacket_Controller;
}

void CTest_sendDiagPacket(void)
{

    static uint8 CTestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        CTestStatus_display[i*2] = CTestStatus[i];
        CTestStatus_display[(i*2) + 1] = ' ';
    }
    
    //DEMUX_CTRL_115200_Write();
    
    UART_115200_PutArray(CTestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_115200_PutChar('\r');
    UART_115200_PutChar('\n');

    //LED_EN_Write(1);
    
    return;
}
//----------------------------------------Timer Interrupts------------------------------
void CTest_isr_PB(void)
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
        CTestStatus[CurrentTest.TestStep] = 'F';
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
void CTest_20ms_isr(void)
{
    
//    if(CurrentTest.TestStep == QUAD_PORTS)       // *** send quad packet if needed 
//    {
//        sendPacketToRelay_Quad();
//    }
    
    CTest_20ms_isr_count++;                                         // 

    if(CTest_20ms_isr_count > CTest_TimeoutCount[CurrentTest.TestStep])
    {
        CTest_20ms_isr_count = 0;
        
        if(CTest_20ms_isr_EN == 1)
        {
            CTestStatus[CurrentTest.TestStep] = 'F';
            CurrentTest.Status = 'F';
        }
            
        return;
    }
    
    if(CTest_20ms_isr_count > 65000)
        CTest_20ms_isr_count = 0;
    
    return;
       
}

void CTest_50ms_isr(void)
{
    
    CTest_sendDiagPacket();                                 // Send diagnostic packet to terminal

    if( (CurrentTest.TestStep == INITIALIZE_TEST) ||      // Send packet to controller if it applies to this step
            (CurrentTest.TestStep == CONFIRM_BOOTUP) || //)//||
            (CurrentTest.TestStep == TEST_POWERMODES) )//||
//            (TestState == INPUTS) ||
//            (CurrentTest.TestStep == BLOCK_CURRENTS) )
    {      
        sendPacket_RelayToController();
    }
    
    return;    
    
}

void CTest_StartAutomatedStep(void)
{
    
    CTestStatus[CurrentTest.TestStep] = 'B';
    CurrentTest.Status = 'B';
    
    CTest_20ms_isr_count = 0;
    CTest_20ms_isr_EN = 1;
    
    return;
    
}

void CTest_StopAutomatedStep(void)
{
    
    CTest_20ms_isr_EN = 0;
    if(CTestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
    {
        CTestStatus[CurrentTest.TestStep] = 'P';
        CurrentTest.Status = 'P';
    }
    
    return;
    
}

void CTest_PB_WaitForAction(void)
{
    
    CTestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
    
    while( (CTestStatus[CurrentTest.TestStep] != 'P') && (CTestStatus[CurrentTest.TestStep] != 'F') )
    {
        if(PB_NextAction_Released) 
        {
            //LED_EN_Write(1);
            CTestStatus[CurrentTest.TestStep] = 'P'; 
            PB_NextAction_Released = 0;
        }
    } 

    LED_EN_Write(0);    // ***not sure why this seems to be needed to make it work
    
    return;
}



/* [] END OF FILE */
