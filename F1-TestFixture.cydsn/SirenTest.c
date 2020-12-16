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
#include "SirenTest.h"
#include "UART_230400_Functions.h"

#define NUMBER_TEST_STEPS 8

// --------------Test steps---------------
enum TestStep
{ 
    INITIALIZE_TEST, 
    RRB_AMP1,
    MIC_AMP2,
    AUDIO_STREAM,
    FLASH,
    OVERLOAD,
    FAIL
};

static uint8 STestStatus[NUMBER_TEST_STEPS];

static uint8 TestState = INITIALIZE_TEST;

void SirenTest(void)
{
    
    switch(TestState)
    {   
        
        //-------------------------         
        case INITIALIZE_TEST:
        
            TestState = RRB_AMP1;
        
        break;
        
        //-------------------------        
        case RRB_AMP1:
                        
            STestStatus[TestState] = 'B';

            //STest_20ms_isr_count = 0;
            //STest_20ms_isr_EN = 1;
             
            //while( (!STest_Test_Amp1()) && (STestStatus[TestState] != 'F') )              // Wait for test to complete or fail          
            //{} 
            
            //STest_20ms_isr_EN = 0;
            
            if(STestStatus[TestState] != 'F')       // If not failed, then pass
                STestStatus[TestState] = 'P';
        
            TestState = MIC_AMP2;
        
        break;    
        
        //-------------------------        
        case MIC_AMP2:  
        
            TestState = AUDIO_STREAM;
        
        break;        
        
        //-------------------------        
        case AUDIO_STREAM:  
        
            TestState = FLASH;
        
        break;  
        
        //-------------------------        
        case FLASH:  
        
            TestState = OVERLOAD;
        
        break;  
        
        //-------------------------        
        case OVERLOAD:
        
            TestState = INITIALIZE_TEST;
        
        break;  
        
        //-------------------------        
        case FAIL:  
        
        break;          
           
    }

}

void STest_20ms_isr(void)
{
    
    
    
}

void STest_50ms_isr(void)
{
    
    
}

void STest_sendDiagPacket(void)
{

    static uint8 STestStatus_display[ (NUMBER_TEST_STEPS*2) ];
    
    for(uint8 i=0;i<NUMBER_TEST_STEPS;i++)
    {
        STestStatus_display[i*2] = STestStatus[i];
        STestStatus_display[(i*2) + 1] = ' ';
    }
    
    //DEMUX_CTRL_230400_Write();
    
    UART_230400_PutArray(STestStatus_display, (NUMBER_TEST_STEPS*2) );
    
    UART_230400_PutChar('\r');
    UART_230400_PutChar('\n');

    //LED_EN_Write(1);
    
    return;
}

/* [] END OF FILE */
