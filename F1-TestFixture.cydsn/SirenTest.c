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
#include "SirenTest.h"
#include "UART_230400_Functions.h"

#define TIMEOUT_FAIL        50          // Number of 20msec counts before failure timeout
#define DEBOUNCE_COUNT      2           // (5 * 20msec)

enum MUX_DEMUX_230400_CHANNEL              
{ 
    CTEST_RELAY, 
    RTEST_CONT,
    RTEST_SIREN,
    STEST_RELAY            
};


// --------------Test steps---------------
#define NUMBER_TEST_STEPS 7
enum TestStep
{ 
    INITIALIZE_TEST,            // ------------------------------------------------ 
    RRB_AMP1,                   // (230400 tx tested)
    MIC_AMP2,                   // ???
    AUDIO_STREAM,               // (460800 tx tested)
    FLASH,                      // ???
    OVERLOAD,                   // (230400 rx tested)
    FAIL                        // ------------------------------------------------
};
// Test UART to and from relay  // RX TESTED(not implemented in this test yet)    -

static uint16 STest_20ms_isr_count = 0;         // Test step timeout variables
static uint16 STest_20ms_isr_EN = 0;

static uint8 PB_NextAction_Pressed = 0;
static uint8 PB_NextAction_Released = 0;

static uint8 STestStatus[NUMBER_TEST_STEPS];


uint8 SirenTest(void)
{

    switch(CurrentTest.TestStep)
    {   
        
        //-------------------------         
        case INITIALIZE_TEST:
        
            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)            // Reset Status of aall test steps to 0
                STestStatus[i] = '_';
        
            //TestState = RRB_AMP1;
            CurrentTest.TestStep = RRB_AMP1;
        
        break;
        
        //-------------------------        
        case RRB_AMP1:
                
            STestStatus[CurrentTest.TestStep] = 'B';                                        // Set status to 'busy' until all 3 freqs play
            
            // 230400 - 'S' - Send a command to enable RRB
            // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - through the RRB of the Siren
            CyDelay(1000);
            
            STestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
            
            while( (!PB_NextAction_Released) && (STestStatus[CurrentTest.TestStep] != 'F') )
            {} 
            PB_NextAction_Released = 0;
            
            if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
                STestStatus[CurrentTest.TestStep] = 'P';                                        // Set status to 'busy' until all 3 freqs play
        
            CurrentTest.TestStep = MIC_AMP2;
        
        break;    
        
        //-------------------------        
        case MIC_AMP2:  
                
            STestStatus[CurrentTest.TestStep] = 'B';                                        // Set status to 'busy' until all 3 freqs play
            
            // 230400 - 'S' - Send a command to enable RRB
            // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - through the RRB of the Siren
            CyDelay(1000);
            
            STestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
            
            while( (!PB_NextAction_Released) && (STestStatus[CurrentTest.TestStep] != 'F') )
            {} 
            PB_NextAction_Released = 0;
            
            if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
                STestStatus[CurrentTest.TestStep] = 'P';                                        // Set status to 'busy' until all 3 freqs play
        
            CurrentTest.TestStep = AUDIO_STREAM;
        break;        
        
        //-------------------------        
        case AUDIO_STREAM:  
        
            //TestState = FLASH;
            CurrentTest.TestStep = FLASH;
        
        break;  
        
        //-------------------------        
        case FLASH:  
        
            //TestState = OVERLOAD;
            CurrentTest.TestStep = OVERLOAD;
                
        break;  
        
        //-------------------------        
        case OVERLOAD:
        
                
            CyDelay(1000);
            //TestState = INITIALIZE_TEST;
            CurrentTest.TestStep = INITIALIZE_TEST;
            
        break;  
        
        //-------------------------        
        case FAIL:  
            CurrentTest.TestStep = FAIL;
        break;          
           
    }

    return(0);
}

//--------------------------------------Test Functions----------------------------------
uint8 STest_Test_Amp1(void)
{
    
    return(0);
}




//----------------------------------------Timer Interrupts------------------------------
void STest_isr_PB(void)
{
    static uint8 PB_NextAction_debouncecount = 0;
    static uint8 PB_NextAction_failcount = 0;
    static uint8 PB_NextAction_prevstate = 0;
    
    static uint8 debouncetrue = 0;
    
    static uint8 PB_reading = 0;
    static uint8 PB_reading_previous = 0;
    PB_reading = PB_NextAction_Read();
    
    
    if(PB_reading == PB_reading_previous)                                       // If reading is the same as the last, increment debounce_count
        PB_NextAction_debouncecount++;
    else
        PB_NextAction_debouncecount = 0;
    
    if(PB_NextAction_debouncecount > DEBOUNCE_COUNT)                            // Set debouncetrue
    {
        debouncetrue = PB_reading;
        PB_NextAction_debouncecount = 0;
    }

    PB_reading_previous = PB_reading;                                           // Save current reading for next interrupt
    
    if(debouncetrue == 1)                                                       // If debounced and asserted
    {
        PB_NextAction_Pressed = 1;
        PB_NextAction_failcount++;
    }
    else
    {
        PB_NextAction_Pressed = 0;
        PB_NextAction_failcount = 0;
    }
    

    if(PB_NextAction_failcount > 100)                       // If PB is held for (150 * 20msec = 3sec) then fail
    {  
        STestStatus[CurrentTest.TestStep] = 'F';
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

void STest_20ms_isr(void)
{
    
    //CurrentTest.TestStep = TestState;           // Update current status of test
    
    STest_20ms_isr_count++;                     // Manage Timeout for failure
    if(STest_20ms_isr_count > TIMEOUT_FAIL)
    {
        STest_20ms_isr_count = 0;
        
        if(STest_20ms_isr_EN == 1)
        {
            STestStatus[CurrentTest.TestStep] = 'F';
            //CurrentTest.Failures = ???;           // Indicate what failed during the current test step
        }
            
        return;
    }
    
    if(STest_20ms_isr_count > 65000)
        STest_20ms_isr_count = 0;
    
    return;
       
}

void STest_50ms_isr(void)
{
    STest_sendDiagPacket();

//        if( (TestState == TEST_OUTPUTS) ||
//            (TestState == DATALINK) ||
//            (TestState == UART_SIREN) ||
//            (TestState == INPUTS) ||
//            (TestState == BLOCK_CURRENTS) )
//        {      
//            //sendPacketToRelaySiren();
//        }
    
    return;    
    
}

//-------------------------------UART diagnostics--------------------------------------------
void STest_sendDiagPacket(void)
{

    static uint8 STestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        STestStatus_display[i*2] = STestStatus[i];
        STestStatus_display[(i*2) + 1] = ' ';
    }
    
    DEMUX_CTRL_230400_Write(RTEST_SIREN);
    
    UART_230400_PutArray(STestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_230400_PutChar('\r');
    UART_230400_PutChar('\n');
    
    return;
}

/* [] END OF FILE */
