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
#include "UART_460800_Functions.h"

#define TIMEOUT_FAIL        50          // Number of 20msec counts before failure timeout
#define DEBOUNCE_COUNT      2           // (5 * 20msec)

enum MUX_DEMUX_230400_CHANNEL              
{ 
    CTEST_RELAY, 
    RTEST_CONT,
    RTEST_SIREN,
    STEST_RELAY            
};

enum DEMUX_460800_CHANNEL              
{ 
    CTEST_OBDII, 
    RTEST_QUAD,
    STEST_AUDIO            
};


// --------------Test steps---------------
#define NUMBER_TEST_STEPS 11
enum TestStep
{ 
    INITIALIZE_TEST,            // ------------------------------------------------ 
    UART_RX,                    //  NO ACTION - COMPLETE
    UART_TX,                    // 230400 RX TESTED - COMPLETED
    AMP1,                       // 230400 TX TESTED - COMPLETED
    AMP2,                       // 230400 TX TESTED - COMPLETED
    RRB,                        // SKIP FOR NOW - (230400 tx tested - RRB is not implemented properly on Siren side) (generated test tone kinda sucks)
    MIC,                        // (generated test tone kinda sucks) 
    AUDIO_STREAM,               // SKIP FOR NOW - NOT PRIORITY - (460800 tx tested) (***not sampling fast enough - needs 1ms or faster timer)
    FLASH,                      // 230400 TX TESTED - COMPLETED
    OVERLOAD,                   // (230400 rx tested) (siren does not seem to be sending data during overload - not getting set flags)
    PASS                        // ------------------------------------------------
};
// Test UART to and from relay  // RX TESTED(not implemented in this test yet)    -

static uint16 STest_20ms_isr_count = 0;         // Test step timeout variables
static uint16 STest_20ms_isr_EN = 0;

static uint8 PB_NextAction_Pressed = 0;
static uint8 PB_NextAction_Released = 0;

static uint8 STestStatus[NUMBER_TEST_STEPS];

static TxPacket_RelaySiren txPacket_RelaySiren;         // SetRelayOutputs - 'I' (also 3,S,P) controller to relay
static TxPacket_RelaySiren * pTxPacket_RelaySiren;      // 

static RxPacket_RelaySiren rxPacket_RelaySiren;         // SetRelayOutputs - 'D' - relay to controller
static RxPacket_RelaySiren * pRxPacket_RelaySiren;      // 

uint8 SirenTest(void)
{

    switch(CurrentTest.TestStep)
    {   
                
        case INITIALIZE_TEST:
        
            for (uint8 i=0;i<NUMBER_TEST_STEPS;i++)            // Reset Status of all test steps to 0
                STestStatus[i] = '_';
        
            CyDelay(1000);
            
            // ***Enable Siren
                
            //CurrentTest.TestStep = FLASH;
            //CurrentTest.TestStep = UART_RX;
            CurrentTest.TestStep = OVERLOAD;
        
        break;
                  
        case UART_RX:                               // No Action -  (this is already proven by testing the AMPs)
                
            CurrentTest.TestStep = UART_TX;
        
        break;  
                    
        case UART_TX:                               // Automated - 
                
            StartAutomatedStep();
        
                //MUX_CTRL_230400_Write(RTEST_SIREN);     // Mux 230400 from siren
            
                VerifyPacket_230400(RTEST_SIREN);       // Verify a 'H' packet
            
            StopAutomatedStep();
            
            CurrentTest.TestStep = AMP1;
        
        break;  
                  
        case AMP1:                                  // Manual - 
                  
            //DEMUX_CTRL_230400_Write(RTEST_SIREN);               // 230400 - 'S' - Send a command to enable Wail tone on Amp1       
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x01; 
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CyDelay(3000);
        
            PB_WaitForAction();
            
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x00;    // Turn off wail tone
            CyDelay(1000);
            
            CurrentTest.TestStep = AMP2;
        
        break;    
             
        case AMP2:                                  // Manual - 
                       
            //DEMUX_CTRL_230400_Write(RTEST_SIREN);               // 230400 - 'S' - Send a command to enable Wail tone on Amp2           
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x01;   
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CyDelay(3000);
             
            PB_WaitForAction();                         
            
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x00;    // Turn off wail tone
            CyDelay(1000);
            
            CurrentTest.TestStep = RRB;
                
        break;        
            
        case RRB:                                   // Manual - 
                         
            //DEMUX_CTRL_230400_Write(RTEST_SIREN);             // 230400 - 'S' - Send a command to enable RRB          
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.RRB = 0x01;  
            
            STest_PlayTestTone();                               // Play test tone for 3sec
             
            PB_WaitForAction();

            CurrentTest.TestStep = MIC;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;   
            
        case MIC:                                   // Manual - 
                
            // *** user needs to plug in mic cable now - (so it keys now, but not during the rest of the test)
            
            STestStatus[CurrentTest.TestStep] = 'W';            

            // repeat test tone - so user has a chance to attach cable and hear it (if they forgot)
            while( (STestStatus[CurrentTest.TestStep] != 'P') && (STestStatus[CurrentTest.TestStep] != 'F') )
            {
                STest_PlayTestTone();   // Play test tone for 3sec
                
                if(PB_NextAction_Released) 
                {
                    //LED_EN_Write(1);
                    STestStatus[CurrentTest.TestStep] = 'P'; 
                    PB_NextAction_Released = 0;
                }
                
            }

            //PB_WaitForAction();
            
            CurrentTest.TestStep = AUDIO_STREAM;
            //CurrentTest.TestStep = RRB_AMP1;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;   
             
        case AUDIO_STREAM:                                  // Low Priority - skip for now
            
//            // 230400 - 'S' - Send a command to enable RRB
//            // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - through the RRB of the Siren
//            //CyDelay(1000);            
//            
//            STest_PlayTestTone_AudioStream();   // Stream test tone for 3sec
//            
//            PB_WaitForAction();
        
            CurrentTest.TestStep = FLASH;
        
        break;  
               
        case FLASH:                                         // Manual - 
                        
            //DEMUX_CTRL_230400_Write(RTEST_SIREN);             // 230400 - 'S' - Send a command to play an audio tone          
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren1Tone = 22; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 22; 
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CyDelay(3000);
            
            PB_WaitForAction();
            
            CurrentTest.TestStep = OVERLOAD;
                
        break;  
             
        case OVERLOAD:                                      // Automated -                              
            // *** note - the overload channels are backwards
            // ***Turn on relays to short the speaker outputs for Amp1
            
            PB_WaitForAction();
            
            StartAutomatedStep();
            
                pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp1
                pTxPacket_RelaySiren->Payload.Siren2Tone = 1;     
                
                pRxPacket_RelaySiren = getRxPacket_RelaySiren();                // Read 'D' packet, wait for overload to be triggered   
//                while( (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 1) && (STestStatus[CurrentTest.TestStep] != 'F') )
//                {}
//                if( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 0) || (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 0))
//                    LED_EN_Write(0);
                 
                // *** this packet gets sent only once per second
                while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent == 0) && (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent == 0))
                {
                    LED_EN_Write(0);
                    
                }
                
                LED_EN_Write(0);
                
                
                
                pTxPacket_RelaySiren->Payload.Siren2Tone = 0;  
                
            StopAutomatedStep();
            
            // *** need to set the LED_MODE to busy
            //STestStatus[CurrentTest.TestStep] = 'B';
            //CyDelay(16000);      
            while(pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 0) // Wait for the previous overload fault to clear
            {}
            // ***Turn on relays to short the speaker outputs for Amp2
            
            //PB_WaitForAction();
            
            StartAutomatedStep();
            
                pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp2
                pTxPacket_RelaySiren->Payload.Siren1Tone = 1;     
                
                pRxPacket_RelaySiren = getRxPacket_RelaySiren();                // Read 'D' packet, wait for overload to be triggered   
                while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 1) && (STestStatus[CurrentTest.TestStep] != 'F') )
                {}    
                
                pTxPacket_RelaySiren->Payload.Siren1Tone = 0;  
                
            StopAutomatedStep();
            
            //CyDelay(16000);                                                  // Wait for the previous overload fault to clear
            while(pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 0) // Wait for the previous overload fault to clear
            {}
            
            CurrentTest.TestStep = PASS;
            
        break;  
               
        case PASS:  
            
            //while(1);
            
            CurrentTest.TestStep = INITIALIZE_TEST;
            
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

void STest_10ms_isr(void)                       // Times Quad and Audio packets
{

    if(CurrentTest.TestStep == AUDIO_STREAM) 
    {
        
        ADC_AudioStream_StartConvert(); // Read ADC of generated waveform
        
        sendPacketToSiren_Audio();      // Send audio stream to siren
 
    }

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
    //STest_sendDiagPacket();

        if( (CurrentTest.TestStep == INITIALIZE_TEST) ||        //*** This needs some work
            (CurrentTest.TestStep == AMP1) ||
            (CurrentTest.TestStep == AMP2) ||
            (CurrentTest.TestStep == AUDIO_STREAM) ||
            (CurrentTest.TestStep == FLASH) ||    
            (CurrentTest.TestStep == OVERLOAD) ||    
            (CurrentTest.TestStep == PASS) )

        {      
            sendPacketToRelaySiren();
        }
    
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
    
    //DEMUX_CTRL_230400_Write(RTEST_SIREN);
    
    UART_230400_PutArray(STestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_230400_PutChar('\r');
    UART_230400_PutChar('\n');
    
    return;
}

void PB_WaitForAction(void)
{
    
            STestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
            
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
            
            while( (STestStatus[CurrentTest.TestStep] != 'P') && (STestStatus[CurrentTest.TestStep] != 'F') )
            {
                if(PB_NextAction_Released) 
                {
                    //LED_EN_Write(1);
                    STestStatus[CurrentTest.TestStep] = 'P'; 
                    PB_NextAction_Released = 0;
                }
            } 
            
            //CyDelay(1000);
            LED_EN_Write(0);    // ***not sure why this seems to be needed to make it work
    
    
    return;
}

void STest_PlayTestTone(void)
{
    // 230400 - 'S' - Send a command to enable RRB (*** is this the right packet?)
    // enable power amp also
    
//    pTxPacket_RelaySiren = getTxPacket_RelaySiren();    // Tx - Get pointers to packet   
//    pTxPacket_RelaySiren->Payload.RRB = 0x01;           // Turn on RRB
    
    STestStatus[CurrentTest.TestStep] = 'B';            // Set status to 'busy' until all 3 freqs play
    
    WaveDAC_Start();                                  // Turn on DAC
    
    Timer_DAC_WritePeriod(5);     //~8.5kHz    // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - through the RRB of the Siren
    CyDelay(1000);
    Timer_DAC_WritePeriod(50);    // ~1kHz
    CyDelay(1000);
    Timer_DAC_WritePeriod(500);     // ~100Hz
    CyDelay(1000);
    
    //pTxPacket_RelaySiren->Payload.RRB = 0x00;           // Turn off RRB
    
    WaveDAC_Stop();                                   // Turn off DAC
    
    return;
}

void STest_PlayTestTone_AudioStream(void)
{
    
    //DEMUX_CTRL_460800_Write(STEST_AUDIO);   // mux the 460800 channel to STest_Audio
    
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();    // Tx - Get pointers to packet   
    pTxPacket_RelaySiren->Payload.SirenEnable = 0x01;   // ***not sure this is the right way to control this - Turn on Audio Streaming
    
    STestStatus[CurrentTest.TestStep] = 'B';            // Set status to 'busy' until all 3 freqs play
    
    WaveDAC_Start();                                    // Turn on DAC
    
    Timer_DAC_WritePeriod(5);                           // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - to be read with ADC and sent through RS485
    CyDelay(1000);
    Timer_DAC_WritePeriod(50);
    CyDelay(1000);
    Timer_DAC_WritePeriod(500);
    CyDelay(1000);
    
    //pTxPacket_RelaySiren->Payload.RRB = 0x00;           // Turn off RRB
    
    
    WaveDAC_Stop();                                   // Turn off DAC
    
    return;

}

void StartAutomatedStep(void)
{
    
    STestStatus[CurrentTest.TestStep] = 'B';
    STest_20ms_isr_count = 0;
    STest_20ms_isr_EN = 1;
    
    return;
    
}

void StopAutomatedStep(void)
{
    
    STest_20ms_isr_EN = 0;
    if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
        STestStatus[CurrentTest.TestStep] = 'P';
    
    return;
    
}

//TxPacket_RelaySiren * getTxPacket_Siren()
//{
//    pTxPacket_Siren = &txPacket_Siren;
//    
//    return pTxPacket_Siren;
//}

/* [] END OF FILE */
