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

/* F1-Controller Test ***********************************************************
*  - Designed to test a F1-Controller PCBA with a SOM installed (w OS and image)   
*  - Requires a configfile (for Desktop Software) that consists of:
*       - PB 1-16 turn on Outputs 1-16 (toggle)
*       - PB 1 sends Quad packet (any packet)
*       - OBDII turns on Output 32
*********************************************************************************/

#include <project.h>
#include "CommonVariables.h"
#include "ControllerTest.h"
#include "UART_460800_Functions.h"
#include "UART_230400_Functions.h"

#define DEBOUNCE_COUNT      2           // (5 * 20msec)
#define CONFIRM_TIME        100


static RxPacket_Controller rxPacket_Controller;         // 'I' (includes 'P') packet (controller to relay) - Pushbuttons         
static RxPacket_Controller * pRxPacket_Controller;

static TxPacket_Controller txPacket_Controller;         // 'D' packet (relay to controller) - Initialize,     
static TxPacket_Controller * pTxPacket_Controller;

static TxPacket_RelaySiren txPacket_Relay;              // 'I' packet (relay to controller) - LEDS_RGB     
static TxPacket_RelaySiren * pTxPacket_Relay;

static TxPacket_Intermotive txPacket_Intermotive;       // Intermotive Packet - for ignition and OBDII test
static TxPacket_Intermotive * pTxPacket_Intermotive;    // 


static uint16 CTest_20ms_isr_count = 0;         // Test step timeout variables
static uint16 CTest_20ms_isr_EN = 0;

static uint8 PB_NextAction_Pressed = 0;         // Pushbutton 
static uint8 PB_NextAction_Released = 0;

enum LEDColor
{ 
    RED,       
    BLUE,  
    GREEN,
    OFF
};


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
#define NUMBER_TEST_STEPS       8
static uint16 CTest_Complete_TimeoutCount[NUMBER_TEST_STEPS] = {50,2000,100,50,100,50,50,50};    // Number of 20msec counts before failure timeout, for each step

static uint8 CTest_CompleteStatus[NUMBER_TEST_STEPS];

enum TestStep           
{ 
    INITIALIZE_TEST,        // COMPLETE
    CONFIRM_BOOTUP,         // COMPLETE
    CONFIG_FILE,            // (unused - the config file does not need to be manually programmed)
    TEST_POWERMODES,        // COMPLETE (***not testing usb power only)(resets pushbuttons) 
    OBDII,                  // COMPLETE (configfile) (***this is already tested by using it for ignition)
                        // Add the touchscreen and slideswitch stuff here
    PUSHBUTTONS,            // COMPLETE (configfile)
                        // Verify button beep with this step
    QUAD_STREAM,            // COMPLETE (configfile)
    //LEDS_RGB,               // *** remove this COMPLETE (***leds take up to 5 seconds to turn on)
    //AUDIO_STREAM,           // (unused - not included)
    //DEBUG_PORT,             // (unused - not included)
    PASS                    // COMPLETE
};


//static uint8 CTest_CompleteStatus[NUMBER_TEST_STEPS];

uint8 ControllerTest_Complete(void)
{
    
    switch(CurrentTest.TestStep)
    {   
       
        case INITIALIZE_TEST:
        
            CTest_CONT_VBATT_EN_Write(1);                           // Enable Vbatt power to controller
            CTest_USB_5V_EN_Write(0);

            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)                 // Reset Status of aall test steps to 0
                CTest_CompleteStatus[i] = '_';
            
            CTest_CompleteStatus[CurrentTest.TestStep] = 'I';
            CurrentTest.Status = 'I';

            CyDelay(CONFIRM_TIME);
            
//            CTestStatus[CurrentTest.TestStep] = 'P';
//            CurrentTest.Status = 'P';
      
            //CurrentTest.TestStep = INITIALIZE_TEST;
            CurrentTest.TestStep = CONFIRM_BOOTUP;
            //CurrentTest.TestStep = TEST_POWERMODES;
            //CurrentTest.TestStep = DEBUG_PORT;
            //CurrentTest.TestStep = QUAD_STREAM;
            //CurrentTest.TestStep = AUDIO_STREAM;
            //CurrentTest.TestStep = OBDII;     
            //CurrentTest.TestStep = LEDS_RGB;
            //CurrentTest.TestStep = PUSHBUTTONS;
        
        break;
        
        case CONFIRM_BOOTUP:
        
            CTest_Complete_StartAutomatedStep();

            MUX_CTRL_230400_Write(CTEST_RELAY);

            while( (!VerifyPacket_230400(CTEST_RELAY)) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {} 
            
            CTest_Complete_StopAutomatedStep();
            
            pTxPacket_Intermotive = getTxPacket_Intermotive();   // Send ignition on signal (OBDII)
            pTxPacket_Intermotive->Payload.Data5 = 0x02; 
            
            CyDelay(CONFIRM_TIME);
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                CurrentTest.TestStep = CONFIG_FILE;
                //CurrentTest.TestStep = TEST_POWERMODES;
                //CurrentTest.TestStep = QUAD_STREAM;
                //CurrentTest.TestStep = LEDS_RGB;
            }
        
        break;
            
        case CONFIG_FILE:   // configfile is already programmed to the SOM by default
            
            CTest_CompleteStatus[CurrentTest.TestStep] = 'U';           
            CurrentTest.Status = 'U'; 
//            pTxPacket_Intermotive = getTxPacket_Intermotive();   // Send ignition on signal (OBDII)
//            pTxPacket_Intermotive->Payload.Data5 = 0x02; 
//            CTest_PB_WaitForAction();
 
            CyDelay(CONFIRM_TIME);
            
            //CurrentTest.TestStep = INITIALIZE_TEST;                   
            CurrentTest.TestStep = TEST_POWERMODES;
            //CurrentTest.TestStep = QUAD_STREAM;
            //CurrentTest.TestStep = LEDS_RGB;
        
        break;
        
        case TEST_POWERMODES:  // Test Vbatt detect and USB detect

            MUX_CTRL_230400_Write(CTEST_RELAY);
            
            pRxPacket_Controller = getRxPacket_Controller();        // 'I' packet - check powermode
            pTxPacket_Intermotive = getTxPacket_Intermotive();      // '1' packet - set ignition 
            //pTxPacket_Controller = getTxPacket_Controller();      // 'D' packet - set ignition (not used)
            
//            //CTest_StartAutomatedStep();
//            //CTest_PB_WaitForAction();
//         
//            /**** Live Power Mode (Normal Mode) - Vbatt-on, USB_5V-on, Ignition-on ***/
//            CTest_CONT_VBATT_EN_Write(1);                   
//            CTest_USB_5V_EN_Write(1);
//            pTxPacket_Intermotive->Payload.Data5 = 0x02;
////            while( (pRxPacket_Controller->Payload.PowerState != 0x01) && (CTestStatus[CurrentTest.TestStep] != 'F') )
////            {}
//            CyDelay(1000);
//            CTest_PB_WaitForAction();
//            
////            CTest_CONT_VBATT_EN_Write(1);                   
////            CTest_USB_5V_EN_Write(1);
////            pTxPacket_Intermotive->Payload.Data5 = 0x00;
////            CyDelay(1000);
//
//            /**** Low Power Mode (USB Power Only) - Vbatt-off, USB_5V-on, Ignition-off ***/
//            CTest_CONT_VBATT_EN_Write(0);               
//            CTest_USB_5V_EN_Write(1);
//            pTxPacket_Intermotive->Payload.Data5 = 0x00;    
////            while( (pRxPacket_Controller->Payload.PowerState != 0x00) && (CTestStatus[CurrentTest.TestStep] != 'F') )
////            {}
//            CyDelay(1000);             
//            CTest_PB_WaitForAction();
//            
//            /**** Normal Power Mode - Vbatt-on, USB_5V-on, Ignition-on ***/
//            CTest_CONT_VBATT_EN_Write(1);                                       
//            CTest_USB_5V_EN_Write(1);
//            pTxPacket_Intermotive->Payload.Data5 = 0x02;
//            
//            CyDelay(1000);   
//            CTest_PB_WaitForAction();
//            
//            CTest_CONT_VBATT_EN_Write(1);                                    
//            CTest_USB_5V_EN_Write(0);
//            pTxPacket_Intermotive->Payload.Data5 = 0x02;
////            while( (pRxPacket_Controller->Payload.PowerState != 0x01) && (CTestStatus[CurrentTest.TestStep] != 'F') )
////            {}
//            CyDelay(1000);
//            CTest_PB_WaitForAction();
//            
//            //CTest_StopAutomatedStep();
            
            CTest_Complete_StartAutomatedStep();
            //CTest_PB_WaitForAction();
         
            /**** Low Power Mode - Vbatt-on, USB_5V-off, Ignition-off ***/
            CTest_CONT_VBATT_EN_Write(1);                   
            CTest_USB_5V_EN_Write(0);
            pTxPacket_Intermotive->Payload.Data5 = 0x00;
            while( (pRxPacket_Controller->Payload.PowerState != 0x00) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}
//            CyDelay(1000);
            //CTest_PB_WaitForAction();
            
            /**** Low Power Mode (USB Power Only) - Vbatt-on, USB_5V-on, Ignition-on ***/
            CTest_CONT_VBATT_EN_Write(1);               
            CTest_USB_5V_EN_Write(1);
            pTxPacket_Intermotive->Payload.Data5 = 0x02;    
            while( (pRxPacket_Controller->Payload.PowerState != 0x01) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}
//            CyDelay(1000);             
            //CTest_PB_WaitForAction();
            
            /**** Normal Power Mode - Vbatt-on, USB_5V-on, Ignition-on ***/
            CTest_CONT_VBATT_EN_Write(1);                                       
            CTest_USB_5V_EN_Write(0);
            pTxPacket_Intermotive->Payload.Data5 = 0x02;
            while( (pRxPacket_Controller->Payload.PowerState != 0x01) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {}
//            CyDelay(1000);
            //CTest_PB_WaitForAction();
            
            CTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = TEST_POWERMODES;
                CurrentTest.TestStep = OBDII;
                //CurrentTest.TestStep = PASS;
            }
            
        break;
            
        case OBDII: //configfile
            
//            pTxPacket_Intermotive = getTxPacket_Intermotive(); 
//            pTxPacket_Intermotive->Payload.Data5 = 0x00; 

            CTest_Complete_StartAutomatedStep();

            MUX_CTRL_230400_Write(CTEST_RELAY);                             // Read a 'I' (includes 'P') packet
            pRxPacket_Controller = getRxPacket_Controller();    
            
            while( ( !(pRxPacket_Controller->Payload.Outputs_25to32 >> 7) ) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )
            {
                sendPacketToController_OBDII();                             // Send 'drivers side door open' command
            }
            
            CTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);    
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = LEDS_RGB;
                CurrentTest.TestStep = PUSHBUTTONS;
            }
      
        break;  
            
        case PUSHBUTTONS:  // configfile - Controller should have the config file setup to turn on all outputs with each pushbutton

            CTest_CompleteStatus[CurrentTest.TestStep] = 'W';
            CurrentTest.Status = 'W';
            
            while( (!CTest_ReadPushbuttons()) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )   // Check that the packet is turning all Relay Outputs on
            {}
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
            {
                CTest_CompleteStatus[CurrentTest.TestStep] = 'P';
                CurrentTest.Status = 'P';
            }
            
            CyDelay(CONFIRM_TIME);
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {    
                CurrentTest.TestStep = QUAD_STREAM;
                //CurrentTest.TestStep = PASS;
            }
      
        break;  
                
        case QUAD_STREAM:   // configfile     
        
            CTest_Complete_StartAutomatedStep();

            MUX_CTRL_460800_Write(CTEST_QUAD);

            while( (!VerifyPacket_460800(CTEST_RTEST_QUAD)) && (CTest_CompleteStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {}
            
            CTest_Complete_StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
            {
                CurrentTest.TestStep = PASS;
            }
            else
            {
                //CurrentTest.TestStep = INITIALIZE_TEST;
                //CurrentTest.TestStep = AUDIO_STREAM;
                //CurrentTest.TestStep = QUAD_STREAM;
                //CurrentTest.TestStep = LEDS_RGB;
                CurrentTest.TestStep = PASS;
            }

        break;
            
//        case LEDS_RGB:   
//            
//            //CTest_PB_WaitForAction();
//            setLEDs(RED);
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'B';
//            CurrentTest.Status = 'B';            
//            CyDelay(5000);
//            CTest_PB_WaitForAction();  
//            
//            setLEDs(BLUE);
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'B';
//            CurrentTest.Status = 'B';            
//            CyDelay(5000);
//            CTest_PB_WaitForAction();
//            
//            setLEDs(GREEN);
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'B';
//            CurrentTest.Status = 'B';
//            CyDelay(5000);
//            CTest_PB_WaitForAction();
//            
////            setLEDs(OFF);
////            CTest_CompleteStatus[CurrentTest.TestStep] = 'B';
////            CurrentTest.Status = 'B';
////            //CyDelay(5000);
//////            CTest_PB_WaitForAction();
//
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'P';
//            CurrentTest.Status = 'P';
//            
//            CyDelay(CONFIRM_TIME);
//            
//            if(CTest_CompleteStatus[CurrentTest.TestStep] == 'F')
//            {
//                CurrentTest.TestStep = PASS;
//            }
//            else
//            {
//                //CurrentTest.TestStep = LEDS_RGB;
//                CurrentTest.TestStep = AUDIO_STREAM;
//                //CurrentTest.TestStep = PUSHBUTTONS;
//            }
//      
//        break; 
//                       
//        case AUDIO_STREAM:  // (not a priority)
//            
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'U';           
//            CurrentTest.Status = 'U'; 
//            CyDelay(CONFIRM_TIME);
////            CTestStatus[CurrentTest.TestStep] = 'P';
////            CurrentTest.Status = 'P';
////            CyDelay(CONFIRM_TIME);
//            
//            CurrentTest.TestStep = DEBUG_PORT;
//                
//        break;
//                         
//        case DEBUG_PORT:    // (not a priority)    
//            
//            CTest_CompleteStatus[CurrentTest.TestStep] = 'U';           
//            CurrentTest.Status = 'U'; 
//            CyDelay(CONFIRM_TIME);
////            CTestStatus[CurrentTest.TestStep] = 'P';
////            CurrentTest.Status = 'P';
////            CyDelay(CONFIRM_TIME);
//            
//            //CurrentTest.TestStep = INITIALIZE_TEST;
//            //CurrentTest.TestStep = OBDII;
//            CurrentTest.TestStep = PASS;
//      
//        break;  
            
        case PASS:   

            for(uint8 i=0;i<(NUMBER_TEST_STEPS-1);i++)
            {
                if( (CTest_CompleteStatus[i] != 'P') && (CTest_CompleteStatus[i] != 'U') && (CTest_CompleteStatus[i] != 'I') )
                {
                    CTest_CompleteStatus[CurrentTest.TestStep] = 'f';
                    CurrentTest.Status = 'f';                      
                }    
            }
 
            if(CTest_CompleteStatus[CurrentTest.TestStep] != 'f')
            {
                CTest_CompleteStatus[CurrentTest.TestStep] = 'p';
                CurrentTest.Status = 'p'; 
            }
            
            while(1);
//            while(PB_NextAction_Read() != 1){};
//            CTestStatus[CurrentTest.TestStep] = 'r';
//            CurrentTest.Status = 'r'; 
//            CyDelay(1000);
//            CurrentTest.TestStep = INITIALIZE_TEST;
      
        break; 
       
    }
    
    return(0);
}



//uint8 CTest_ReadPushbuttons()
//{
//
//    MUX_CTRL_230400_Write(CTEST_RELAY);                             // Read a 'I' (includes 'P') packet
//    pRxPacket_Controller = getRxPacket_Controller();    
//    
//    if( (pRxPacket_Controller->Payload.Outputs_1to8 == 0xFF) &&
//        (pRxPacket_Controller->Payload.Outputs_9to16 == 0xFF) ) //&&
////        (pRxPacket_Controller->Payload.Outputs_17to24 == 0xFF) &&
////        (pRxPacket_Controller->Payload.Outputs_25to32 == 0xFF) )
//    {
//        return(1);
//    } 
//    else
//        return(0);
//       
//}

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


//TxPacket_RelaySiren * getTxPacket_Relay(void)
//{
//    pTxPacket_Relay = &txPacket_Relay;
//    
//    return pTxPacket_Relay;
//}

//RxPacket_Controller * getRxPacket_Controller(void)
//{
//    pRxPacket_Controller = &rxPacket_Controller;
//    
//    return pRxPacket_Controller;
//}

//TxPacket_Controller * getTxPacket_Controller(void)
//{
//    pTxPacket_Controller = &txPacket_Controller;
//    
//    return pTxPacket_Controller;
//}

void CTest_Complete_sendDiagPacket(void)
{

    static uint8 CTestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        CTestStatus_display[i*2] = CTest_CompleteStatus[i];
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
//void CTest_isr_PB(void)
//{
//    static uint8 PB_NextAction_debouncecount = 0;
//    static uint8 PB_NextAction_failcount = 0;
//    static uint8 PB_NextAction_prevstate = 0;
//    
//    static uint8 debouncetrue = 0;
//    
//    static uint8 PB_reading = 0;
//    static uint8 PB_reading_previous = 0;
//    PB_reading = PB_NextAction_Read();
//    
//    
//    if(PB_reading == PB_reading_previous)               // If reading is the same as the last, increment debounce_count
//        PB_NextAction_debouncecount++;
//    else
//        PB_NextAction_debouncecount = 0;
//    
//    if(PB_NextAction_debouncecount > DEBOUNCE_COUNT)    // Set debouncetrue
//    {
//        debouncetrue = PB_reading;
//        PB_NextAction_debouncecount = 0;
//    }
//
//    PB_reading_previous = PB_reading;                   // Save current reading for next interrupt
//    
//    if(debouncetrue == 1)                               // If debounced and asserted
//    {
//        PB_NextAction_Pressed = 1;
//        PB_NextAction_failcount++;
//    }
//    else
//    {
//        PB_NextAction_Pressed = 0;
//        PB_NextAction_failcount = 0;
//    }
//    
//
//    if(PB_NextAction_failcount > 75)                       // If PB is held for (150 * 20msec = 3sec) then fail
//    {  
//        CTestStatus[CurrentTest.TestStep] = 'F';
//        CurrentTest.Status = 'F';
//        PB_NextAction_failcount = 0;
//        
//    }
//    
//
//    if( (PB_NextAction_prevstate == 1) && (PB_NextAction_Pressed == 0) )        // Determine if PB was pressed momentarily and then released
//    {
//        PB_NextAction_Released = 1;
//    }
//    else
//        PB_NextAction_Released = 0;
//    
//    PB_NextAction_prevstate = PB_NextAction_Pressed;
//    
//    return;
//}

void CTest_Complete_20ms_isr(void)
{
    
//    if(CurrentTest.TestStep == QUAD_PORTS)       // *** send quad packet if needed 
//    {
//        sendPacketToRelay_Quad();
//    }
    
    CTest_20ms_isr_count++;                                         // 

    if(CTest_20ms_isr_count > CTest_Complete_TimeoutCount[CurrentTest.TestStep])
    {
        CTest_20ms_isr_count = 0;
        
        if(CTest_20ms_isr_EN == 1)
        {
            CTest_CompleteStatus[CurrentTest.TestStep] = 'F';
            CurrentTest.Status = 'F';
        }
            
        return;
    }
    
    if(CTest_20ms_isr_count > 65000)
        CTest_20ms_isr_count = 0;
    
    return;
       
}

void CTest_Complete_50ms_isr(void)
{
    
    CTest_Complete_sendDiagPacket();                             // Send diagnostic packet to terminal
//    pRxPacket_Controller = getRxPacket_Controller();  
//    UART_115200_WriteTxData(pRxPacket_Controller->Payload.PowerState + 48);
//    UART_115200_WriteTxData('\r');
//    UART_115200_WriteTxData('\n');
    
    
    sendPacket_OBDII();

    if( (CurrentTest.TestStep == INITIALIZE_TEST) ||    // Send packet to controller if it applies to this step
        (CurrentTest.TestStep == CONFIRM_BOOTUP) || 
        (CurrentTest.TestStep == CONFIG_FILE) ||
        (CurrentTest.TestStep == TEST_POWERMODES) )     // This is just to test relay ignition signal
    {      
        //sendPacket_OBDII();
        sendPacket_RelayToController();
    }
//    if( (CurrentTest.TestStep == LEDS_RGB) || (CurrentTest.TestStep == PASS) )
//    {      
//        //sendIgnition_OBDII();
//        sendPacket_RelayToController_Test();
//    }
    
    return;    
    
}

void CTest_Complete_StartAutomatedStep(void)
{
    
    CTest_CompleteStatus[CurrentTest.TestStep] = 'B';
    CurrentTest.Status = 'B';
    
    CTest_20ms_isr_count = 0;
    CTest_20ms_isr_EN = 1;
    
    return;
    
}

void CTest_Complete_StopAutomatedStep(void)
{
    
    CTest_20ms_isr_EN = 0;
    if(CTest_CompleteStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
    {
        CTest_CompleteStatus[CurrentTest.TestStep] = 'P';
        CurrentTest.Status = 'P';
    }
    
    return;
    
}

//void CTest_PB_WaitForAction(void)
//{
//    
//    CTestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
//    CurrentTest.Status = 'W';
//    
//    while( (CTestStatus[CurrentTest.TestStep] != 'P') && (CTestStatus[CurrentTest.TestStep] != 'F') )
//    {
//        if(PB_NextAction_Released) 
//        {
//            //LED_EN_Write(1);
//            CTestStatus[CurrentTest.TestStep] = 'P';
//            CurrentTest.Status = 'P';
//            PB_NextAction_Released = 0;
//        }
//    } 
//
//    LED_EN_Write(0);    // ***not sure why this seems to be needed to make it work
//    
//    return;
//}

//TxPacket_Intermotive * getTxPacket_Intermotive()          // CTest Tx - Intermotive packet sent to controller
//{
//    pTxPacket_Intermotive = &txPacket_Intermotive;
//    
//    return pTxPacket_Intermotive;
//}

//void setLEDs(uint8 color)
//{
//    
//    pTxPacket_Relay = getTxPacket_Relay();
//    pRxPacket_Controller = getRxPacket_Controller();
//    
//    if(color == RED)
//    {
//        pTxPacket_Relay->Payload.LED_01_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_02_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_03_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_04_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_05_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_06_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_07_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_08_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_09_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_10_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_11_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_12_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_13_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_14_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_15_R = 0xFF;
//        pTxPacket_Relay->Payload.LED_16_R = 0xFF;
//        
//        pTxPacket_Relay->Payload.LED_01_B = 0x00;
//        pTxPacket_Relay->Payload.LED_02_B = 0x00;
//        pTxPacket_Relay->Payload.LED_03_B = 0x00;
//        pTxPacket_Relay->Payload.LED_04_B = 0x00;
//        pTxPacket_Relay->Payload.LED_05_B = 0x00;
//        pTxPacket_Relay->Payload.LED_06_B = 0x00;
//        pTxPacket_Relay->Payload.LED_07_B = 0x00;
//        pTxPacket_Relay->Payload.LED_08_B = 0x00;
//        pTxPacket_Relay->Payload.LED_09_B = 0x00;
//        pTxPacket_Relay->Payload.LED_10_B = 0x00;
//        pTxPacket_Relay->Payload.LED_11_B = 0x00;
//        pTxPacket_Relay->Payload.LED_12_B = 0x00;
//        pTxPacket_Relay->Payload.LED_13_B = 0x00;
//        pTxPacket_Relay->Payload.LED_14_B = 0x00;
//        pTxPacket_Relay->Payload.LED_15_B = 0x00;
//        pTxPacket_Relay->Payload.LED_16_B = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_G = 0x00;
//        pTxPacket_Relay->Payload.LED_02_G = 0x00;
//        pTxPacket_Relay->Payload.LED_03_G = 0x00;
//        pTxPacket_Relay->Payload.LED_04_G = 0x00;
//        pTxPacket_Relay->Payload.LED_05_G = 0x00;
//        pTxPacket_Relay->Payload.LED_06_G = 0x00;
//        pTxPacket_Relay->Payload.LED_07_G = 0x00;
//        pTxPacket_Relay->Payload.LED_08_G = 0x00;
//        pTxPacket_Relay->Payload.LED_09_G = 0x00;
//        pTxPacket_Relay->Payload.LED_10_G = 0x00;
//        pTxPacket_Relay->Payload.LED_11_G = 0x00;
//        pTxPacket_Relay->Payload.LED_12_G = 0x00;
//        pTxPacket_Relay->Payload.LED_13_G = 0x00;
//        pTxPacket_Relay->Payload.LED_14_G = 0x00;
//        pTxPacket_Relay->Payload.LED_15_G = 0x00;
//        pTxPacket_Relay->Payload.LED_16_G = 0x00;
//    }
//    
//    else if(color == BLUE)
//    {
//        pTxPacket_Relay->Payload.LED_01_R = 0x00;
//        pTxPacket_Relay->Payload.LED_02_R = 0x00;
//        pTxPacket_Relay->Payload.LED_03_R = 0x00;
//        pTxPacket_Relay->Payload.LED_04_R = 0x00;
//        pTxPacket_Relay->Payload.LED_05_R = 0x00;
//        pTxPacket_Relay->Payload.LED_06_R = 0x00;
//        pTxPacket_Relay->Payload.LED_07_R = 0x00;
//        pTxPacket_Relay->Payload.LED_08_R = 0x00;
//        pTxPacket_Relay->Payload.LED_09_R = 0x00;
//        pTxPacket_Relay->Payload.LED_10_R = 0x00;
//        pTxPacket_Relay->Payload.LED_11_R = 0x00;
//        pTxPacket_Relay->Payload.LED_12_R = 0x00;
//        pTxPacket_Relay->Payload.LED_13_R = 0x00;
//        pTxPacket_Relay->Payload.LED_14_R = 0x00;
//        pTxPacket_Relay->Payload.LED_15_R = 0x00;
//        pTxPacket_Relay->Payload.LED_16_R = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_02_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_03_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_04_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_05_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_06_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_07_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_08_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_09_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_10_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_11_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_12_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_13_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_14_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_15_B = 0xFF;
//        pTxPacket_Relay->Payload.LED_16_B = 0xFF;
//        
//        pTxPacket_Relay->Payload.LED_01_G = 0x00;
//        pTxPacket_Relay->Payload.LED_02_G = 0x00;
//        pTxPacket_Relay->Payload.LED_03_G = 0x00;
//        pTxPacket_Relay->Payload.LED_04_G = 0x00;
//        pTxPacket_Relay->Payload.LED_05_G = 0x00;
//        pTxPacket_Relay->Payload.LED_06_G = 0x00;
//        pTxPacket_Relay->Payload.LED_07_G = 0x00;
//        pTxPacket_Relay->Payload.LED_08_G = 0x00;
//        pTxPacket_Relay->Payload.LED_09_G = 0x00;
//        pTxPacket_Relay->Payload.LED_10_G = 0x00;
//        pTxPacket_Relay->Payload.LED_11_G = 0x00;
//        pTxPacket_Relay->Payload.LED_12_G = 0x00;
//        pTxPacket_Relay->Payload.LED_13_G = 0x00;
//        pTxPacket_Relay->Payload.LED_14_G = 0x00;
//        pTxPacket_Relay->Payload.LED_15_G = 0x00;
//        pTxPacket_Relay->Payload.LED_16_G = 0x00;
//    }
//    
//    else if(color == GREEN)
//    {
//        pTxPacket_Relay->Payload.LED_01_R = 0x00;
//        pTxPacket_Relay->Payload.LED_02_R = 0x00;
//        pTxPacket_Relay->Payload.LED_03_R = 0x00;
//        pTxPacket_Relay->Payload.LED_04_R = 0x00;
//        pTxPacket_Relay->Payload.LED_05_R = 0x00;
//        pTxPacket_Relay->Payload.LED_06_R = 0x00;
//        pTxPacket_Relay->Payload.LED_07_R = 0x00;
//        pTxPacket_Relay->Payload.LED_08_R = 0x00;
//        pTxPacket_Relay->Payload.LED_09_R = 0x00;
//        pTxPacket_Relay->Payload.LED_10_R = 0x00;
//        pTxPacket_Relay->Payload.LED_11_R = 0x00;
//        pTxPacket_Relay->Payload.LED_12_R = 0x00;
//        pTxPacket_Relay->Payload.LED_13_R = 0x00;
//        pTxPacket_Relay->Payload.LED_14_R = 0x00;
//        pTxPacket_Relay->Payload.LED_15_R = 0x00;
//        pTxPacket_Relay->Payload.LED_16_R = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_B = 0x00;
//        pTxPacket_Relay->Payload.LED_02_B = 0x00;
//        pTxPacket_Relay->Payload.LED_03_B = 0x00;
//        pTxPacket_Relay->Payload.LED_04_B = 0x00;
//        pTxPacket_Relay->Payload.LED_05_B = 0x00;
//        pTxPacket_Relay->Payload.LED_06_B = 0x00;
//        pTxPacket_Relay->Payload.LED_07_B = 0x00;
//        pTxPacket_Relay->Payload.LED_08_B = 0x00;
//        pTxPacket_Relay->Payload.LED_09_B = 0x00;
//        pTxPacket_Relay->Payload.LED_10_B = 0x00;
//        pTxPacket_Relay->Payload.LED_11_B = 0x00;
//        pTxPacket_Relay->Payload.LED_12_B = 0x00;
//        pTxPacket_Relay->Payload.LED_13_B = 0x00;
//        pTxPacket_Relay->Payload.LED_14_B = 0x00;
//        pTxPacket_Relay->Payload.LED_15_B = 0x00;
//        pTxPacket_Relay->Payload.LED_16_B = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_02_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_03_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_04_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_05_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_06_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_07_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_08_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_09_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_10_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_11_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_12_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_13_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_14_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_15_G = 0xFF;
//        pTxPacket_Relay->Payload.LED_16_G = 0xFF;
//    }
//    
//    else
//    {
//        pTxPacket_Relay->Payload.LED_01_R = 0x00;
//        pTxPacket_Relay->Payload.LED_02_R = 0x00;
//        pTxPacket_Relay->Payload.LED_03_R = 0x00;
//        pTxPacket_Relay->Payload.LED_04_R = 0x00;
//        pTxPacket_Relay->Payload.LED_05_R = 0x00;
//        pTxPacket_Relay->Payload.LED_06_R = 0x00;
//        pTxPacket_Relay->Payload.LED_07_R = 0x00;
//        pTxPacket_Relay->Payload.LED_08_R = 0x00;
//        pTxPacket_Relay->Payload.LED_09_R = 0x00;
//        pTxPacket_Relay->Payload.LED_10_R = 0x00;
//        pTxPacket_Relay->Payload.LED_11_R = 0x00;
//        pTxPacket_Relay->Payload.LED_12_R = 0x00;
//        pTxPacket_Relay->Payload.LED_13_R = 0x00;
//        pTxPacket_Relay->Payload.LED_14_R = 0x00;
//        pTxPacket_Relay->Payload.LED_15_R = 0x00;
//        pTxPacket_Relay->Payload.LED_16_R = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_B = 0x00;
//        pTxPacket_Relay->Payload.LED_02_B = 0x00;
//        pTxPacket_Relay->Payload.LED_03_B = 0x00;
//        pTxPacket_Relay->Payload.LED_04_B = 0x00;
//        pTxPacket_Relay->Payload.LED_05_B = 0x00;
//        pTxPacket_Relay->Payload.LED_06_B = 0x00;
//        pTxPacket_Relay->Payload.LED_07_B = 0x00;
//        pTxPacket_Relay->Payload.LED_08_B = 0x00;
//        pTxPacket_Relay->Payload.LED_09_B = 0x00;
//        pTxPacket_Relay->Payload.LED_10_B = 0x00;
//        pTxPacket_Relay->Payload.LED_11_B = 0x00;
//        pTxPacket_Relay->Payload.LED_12_B = 0x00;
//        pTxPacket_Relay->Payload.LED_13_B = 0x00;
//        pTxPacket_Relay->Payload.LED_14_B = 0x00;
//        pTxPacket_Relay->Payload.LED_15_B = 0x00;
//        pTxPacket_Relay->Payload.LED_16_B = 0x00;
//        
//        pTxPacket_Relay->Payload.LED_01_G = 0x00;
//        pTxPacket_Relay->Payload.LED_02_G = 0x00;
//        pTxPacket_Relay->Payload.LED_03_G = 0x00;
//        pTxPacket_Relay->Payload.LED_04_G = 0x00;
//        pTxPacket_Relay->Payload.LED_05_G = 0x00;
//        pTxPacket_Relay->Payload.LED_06_G = 0x00;
//        pTxPacket_Relay->Payload.LED_07_G = 0x00;
//        pTxPacket_Relay->Payload.LED_08_G = 0x00;
//        pTxPacket_Relay->Payload.LED_09_G = 0x00;
//        pTxPacket_Relay->Payload.LED_10_G = 0x00;
//        pTxPacket_Relay->Payload.LED_11_G = 0x00;
//        pTxPacket_Relay->Payload.LED_12_G = 0x00;
//        pTxPacket_Relay->Payload.LED_13_G = 0x00;
//        pTxPacket_Relay->Payload.LED_14_G = 0x00;
//        pTxPacket_Relay->Payload.LED_15_G = 0x00;
//        pTxPacket_Relay->Payload.LED_16_G = 0x00;
//    }
//    
//    return;
//}



/* [] END OF FILE */
