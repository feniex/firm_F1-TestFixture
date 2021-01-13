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

//#define TIMEOUT_FAIL        50        // Number of 20msec counts before failure timeout
#define DEBOUNCE_COUNT      2           // (5 * 20msec)
#define CONFIRM_TIME        1000         // How many msec to show pass/fail for each step

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
static uint16 STest_TimeoutCount[NUMBER_TEST_STEPS] = {50,50,300,50,50,50,50,50,50,50,50};  // Number of 20msec counts before failure timeout, for each step

enum TestStep
{ 
    INITIALIZE_TEST,            // ------------------------------------------------ 
    UART_RX,                    // (no action)
    UART_TX,                    // COMPLETE
    AMP1,                       // COMPLETE
    AMP2,                       // COMPLETE
    RRB,                        // (exclude - need speaker to hear it)
    MIC,                        // (not working ???) 
    AUDIO_STREAM,               // (exclude)
    FLASH,                      // COMPLETE
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
                
            STestStatus[CurrentTest.TestStep] = 'I';
            CurrentTest.Status = 'I';
            
            STest_SIREN_EN_Write(1);                    // Enable Siren
            
//            WaveDAC_Start();
//            
//            while(1)
//            {
//               STest_PlayTestTone();   // Play test tone for 3sec
//            }
            
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
            
            STestStatus[CurrentTest.TestStep] = 'P';
            CurrentTest.Status = 'P'; 
        
            CyDelay(CONFIRM_TIME);
  
            CurrentTest.TestStep = UART_RX;
            //CurrentTest.TestStep = AMP1;
            //CurrentTest.TestStep = FLASH;
            //CurrentTest.TestStep = OVERLOAD;
            //CurrentTest.TestStep = RRB;
            //CurrentTest.TestStep = MIC;
        
        break;
                  
        case UART_RX:                               // No Action -  (this is already proven by testing the AMPs)
                
            STestStatus[CurrentTest.TestStep] = 'P';
            CurrentTest.Status = 'P'; 
            CyDelay(CONFIRM_TIME);
            
            CurrentTest.TestStep = UART_TX;
        
        break;  
                    
        case UART_TX:                               // Automated - 
                
            StartAutomatedStep();
        
            MUX_CTRL_230400_Write(STEST_RELAY);     // Mux 230400 from siren
            
            VerifyPacket_230400(RTEST_SIREN);       // Verify a 'H' packet
            while( (!VerifyPacket_230400(RTEST_SIREN)) && (STestStatus[CurrentTest.TestStep] != 'F') )    // Wait for test to complete or fail
            {} 
            
            StopAutomatedStep();
            
            CyDelay(CONFIRM_TIME);
            
            CurrentTest.TestStep = AMP1;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;  
                  
        case AMP1:                                  // Manual - 
                  
            DEMUX_CTRL_230400_Write(STEST_RELAY);
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x01; 
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            CyDelay(3000);
        
            PB_WaitForAction();
            
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0x00;    // Turn off wail tone
            
            CyDelay(CONFIRM_TIME);
            
            //CurrentTest.TestStep = AMP1;
            CurrentTest.TestStep = AMP2;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;    
             
        case AMP2:                                  // Manual - 
                       
            DEMUX_CTRL_230400_Write(STEST_RELAY);
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x01;   
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            CyDelay(3000);
             
            PB_WaitForAction();                         
            
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0x00;    // Turn off wail tone
            CyDelay(1000);
            
            CurrentTest.TestStep = RRB;
            //CurrentTest.TestStep = FLASH;
            //CurrentTest.TestStep = INITIALIZE_TEST;
                
        break;        
            
        case RRB:    
            
            STestStatus[CurrentTest.TestStep] = 'U';           
            CurrentTest.Status = 'U'; 
                         
//            DEMUX_CTRL_230400_Write(STEST_RELAY);             // 230400 - 'S' - Send a command to enable RRB          
//            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
//            pTxPacket_RelaySiren->Payload.RRB = 0x01;  
//            
//            STest_PlayTestTone();                               // Play test tone for 3sec

////            while( (STestStatus[CurrentTest.TestStep] != 'P') && (STestStatus[CurrentTest.TestStep] != 'F') )
////            {
////                STest_PlayTestTone();   // Play test tone for 3sec
////                
////                if(PB_NextAction_Released) 
////                {
////                    //LED_EN_Write(1);
////                    STestStatus[CurrentTest.TestStep] = 'P'; 
////                    PB_NextAction_Released = 0;
////                }
////                
////            }
//             
//            //while(1);
//            
//            PB_WaitForAction();
//            
//            pTxPacket_RelaySiren->Payload.RRB = 0x00;  
//            
//            CyDelay(CONFIRM_TIME);

            CurrentTest.TestStep = MIC;
            //CurrentTest.TestStep = RRB;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;   
            
        case MIC:                               
            
            STestStatus[CurrentTest.TestStep] = 'U';           
            CurrentTest.Status = 'U'; 
                
//            // *** user needs to plug in mic cable now - (so it keys now, but not during the rest of the test)
//            
//            STestStatus[CurrentTest.TestStep] = 'W';  
//            CurrentTest.Status = 'W'; 
//            
////            while(1)
////            {
////                STest_PlayTestTone();   // Play test tone for 3sec
////            }
//
////            // repeat test tone - so user has a chance to attach cable and hear it (if they forgot)
////            while( (STestStatus[CurrentTest.TestStep] != 'P') && (STestStatus[CurrentTest.TestStep] != 'F') )
////            {
////                STest_PlayTestTone();   // Play test tone for 3sec
////                
////                if(PB_NextAction_Released) 
////                {
////                    //LED_EN_Write(1);
////                    STestStatus[CurrentTest.TestStep] = 'P'; 
////                    CurrentTest.Status = 'P'; 
////                    PB_NextAction_Released = 0;
////                }
////                
////            }
//
//            //PB_WaitForAction();
            
            //CurrentTest.TestStep = MIC;
            CurrentTest.TestStep = AUDIO_STREAM;
            //CurrentTest.TestStep = RRB_AMP1;
            //CurrentTest.TestStep = INITIALIZE_TEST;
        
        break;   
             
        case AUDIO_STREAM:                                  // Low Priority - skip for now
            
            STestStatus[CurrentTest.TestStep] = 'U';           
            CurrentTest.Status = 'U'; 
            
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
                        
            DEMUX_CTRL_230400_Write(STEST_RELAY);             // 230400 - 'S' - Send a command to play an audio tone          
            pTxPacket_RelaySiren = getTxPacket_RelaySiren();    
            pTxPacket_RelaySiren->Payload.Siren1Tone = 22; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 22; 
            
            STestStatus[CurrentTest.TestStep] = 'B';            // Let tone play for 3sec
            CurrentTest.Status = 'B'; 
            CyDelay(3000);
            
            PB_WaitForAction();
            
            pTxPacket_RelaySiren->Payload.Siren1Tone = 0; 
            pTxPacket_RelaySiren->Payload.Siren2Tone = 0; 
            
            CyDelay(CONFIRM_TIME);
            
            CurrentTest.TestStep = OVERLOAD;
            //CurrentTest.TestStep = FLASH;
            //CurrentTest.TestStep = INITIALIZE_TEST;
                
        break;  
             
        case OVERLOAD:                                      // Automated -                              
            // *** note - the overload channels are backwards
            // ***Turn on relays to short the speaker outputs for Amp1
            
            MUX_CTRL_230400_Write(STEST_RELAY); 
            DEMUX_CTRL_230400_Write(STEST_RELAY); 
            
            //PB_WaitForAction();
            
            StartAutomatedStep();
            
            //Overload1_Write(1);             // This is for amp2
            Overload2_Write(1);                 // This is for amp1
            
            //while(1);
            CyDelay(1000);
            
                pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp1
                pTxPacket_RelaySiren->Payload.Siren2Tone = 1;     
                
                pRxPacket_RelaySiren = getRxPacket_RelaySiren();                // Read 'D' packet, wait for overload to be triggered   
////                while( (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 1) && (STestStatus[CurrentTest.TestStep] != 'F') )
////                {}
////                if( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 0) || (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 0))
////                    LED_EN_Write(0);
//                 
//                // *** this packet gets sent only once per second
//                while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent == 0) && (pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent == 0))
//                {
//                    LED_EN_Write(0);
//                    
//                }
//                
//                //LED_EN_Write(0);
                
                StopAutomatedStep();
                
//                STestStatus[CurrentTest.TestStep] = 'P'; 
//                CurrentTest.Status = 'P'; 
//                
//                CyDelay(5000);
                
                CyDelay(1000);
                
                Overload1_Write(0);
                Overload2_Write(0);
                
                pTxPacket_RelaySiren->Payload.Siren2Tone = 0;  
                
            //StopAutomatedStep();
            
//            // *** need to set the LED_MODE to busy
//            //STestStatus[CurrentTest.TestStep] = 'B';
//            //CyDelay(16000);      
//            while(pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 0) // Wait for the previous overload fault to clear
//            {}
//            // ***Turn on relays to short the speaker outputs for Amp2
//            
//            //PB_WaitForAction();
//            
//            StartAutomatedStep();
//            
//                pTxPacket_RelaySiren = getTxPacket_RelaySiren();                // 230400 - 'S' - Send a command to enable Wail tone on Amp2
//                pTxPacket_RelaySiren->Payload.Siren1Tone = 1;     
//                
//                pRxPacket_RelaySiren = getRxPacket_RelaySiren();                // Read 'D' packet, wait for overload to be triggered   
//                while( (pRxPacket_RelaySiren->Payload.Speaker1_Overcurrent != 1) && (STestStatus[CurrentTest.TestStep] != 'F') )
//                {}    
//                
//                pTxPacket_RelaySiren->Payload.Siren1Tone = 0;  
//                
//            StopAutomatedStep();
//            
//            //CyDelay(16000);                                                  // Wait for the previous overload fault to clear
//            while(pRxPacket_RelaySiren->Payload.Speaker2_Overcurrent != 0) // Wait for the previous overload fault to clear
//            {}
                
            STestStatus[CurrentTest.TestStep] = 'P';        
            CurrentTest.Status = 'P'; 
            
            //CurrentTest.TestStep = OVERLOAD;
            CurrentTest.TestStep = PASS;
            
        break;  
               
        case PASS:  
   
            for(uint8 i=0;i<(NUMBER_TEST_STEPS-1);i++)
            {
                if( (STestStatus[i] != 'P') && (STestStatus[i] != 'U') )
                {
                    STestStatus[CurrentTest.TestStep] = 'f';
                    CurrentTest.Status = 'f';                      
                }    
            }
 
            if(STestStatus[CurrentTest.TestStep] != 'f')
            {
                STestStatus[CurrentTest.TestStep] = 'p';
                CurrentTest.Status = 'p'; 
            }
            
            while(PB_NextAction_Read() != 1){};

            STestStatus[CurrentTest.TestStep] = 'r';
            CurrentTest.Status = 'r'; 
            
            CyDelay(1000);
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

void STest_10ms_isr(void)                       // Times Quad and Audio packets
{

    if(CurrentTest.TestStep == AUDIO_STREAM) 
    {
        
        //ADC_AudioStream_StartConvert(); // Read ADC of generated waveform
        
        sendPacketToSiren_Audio();      // Send audio stream to siren
 
    }

    return;
    
}

void STest_20ms_isr(void)
{
    
    //CurrentTest.TestStep = TestState;           // Update current status of test
    
    STest_20ms_isr_count++;                     // Manage Timeout for failure
    if(STest_20ms_isr_count > STest_TimeoutCount[CurrentTest.TestStep])
    {
        STest_20ms_isr_count = 0;
        
        if(STest_20ms_isr_EN == 1)
        {
            STestStatus[CurrentTest.TestStep] = 'F';
            CurrentTest.Status = 'F';
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

        if( (CurrentTest.TestStep == INITIALIZE_TEST) ||        //*** This needs some work
            (CurrentTest.TestStep == AMP1) ||
            (CurrentTest.TestStep == AMP2) ||
            (CurrentTest.TestStep == RRB) ||
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
    
    UART_115200_PutArray(STestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_115200_PutChar('\r');
    UART_115200_PutChar('\n');
    
    return;
}

void PB_WaitForAction(void)
{
    
    STestStatus[CurrentTest.TestStep] = 'W';                                        // Set status to 'waiting' until user hits the 'next action' button
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
            
    while( (STestStatus[CurrentTest.TestStep] != 'P') && (STestStatus[CurrentTest.TestStep] != 'F') )
    {
        if(PB_NextAction_Released) 
        {
            //LED_EN_Write(1);
            STestStatus[CurrentTest.TestStep] = 'P'; 
            CurrentTest.Status = 'P';
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
    CurrentTest.Status = 'B';
    
    //WaveDAC_Start();                                  // Turn on DAC
    
//    Timer_DAC_WritePeriod(5);     //~8.5kHz    // Send a 1V 200Hz PWM (using DAC) for 1sec, then 1kHz, then 10kHz - through the RRB of the Siren
//    CyDelay(1000);
    Timer_DAC_WritePeriod(50);    // ~1kHz
    CyDelay(1000);
//    Timer_DAC_WritePeriod(500);     // ~100Hz
//    CyDelay(1000);
    
    //pTxPacket_RelaySiren->Payload.RRB = 0x00;           // Turn off RRB
    
    //WaveDAC_Stop();                                   // Turn off DAC
    
    return;
}

void STest_PlayTestTone_AudioStream(void)
{
    
    //DEMUX_CTRL_460800_Write(STEST_AUDIO);   // mux the 460800 channel to STest_Audio
    
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();    // Tx - Get pointers to packet   
    pTxPacket_RelaySiren->Payload.SirenEnable = 0x01;   // ***not sure this is the right way to control this - Turn on Audio Streaming
    
    STestStatus[CurrentTest.TestStep] = 'B';            // Set status to 'busy' until all 3 freqs play
    CurrentTest.Status = 'B';
    
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
    CurrentTest.Status = 'B';
    STest_20ms_isr_count = 0;
    STest_20ms_isr_EN = 1;
    
    return;
    
}

void StopAutomatedStep(void)
{
    
    STest_20ms_isr_EN = 0;
    if(STestStatus[CurrentTest.TestStep] != 'F')       // If not failed, then pass
    {
        STestStatus[CurrentTest.TestStep] = 'P';
        CurrentTest.Status = 'P';
    }
    
    return;
    
}

//TxPacket_RelaySiren * getTxPacket_Siren()
//{
//    pTxPacket_Siren = &txPacket_Siren;
//    
//    return pTxPacket_Siren;
//}

/* [] END OF FILE */
