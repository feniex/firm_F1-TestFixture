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
//#include "ControllerTest.h"
#include "UART_230400_Functions.h"

static uint8 TestState = 0;

// --------------Test steps---------------
enum DataType
{ 
    CONFIRM_BOOTUP, 
    RRB_AMP1,
    MIC_AMP2,
    AUDIO_STREAM,
    FLASH,
    OVERLOAD,
    FAIL
};

void SirenTest(void)
{
    
    switch(TestState)
    {   
        
        //-------------------------         
        case CONFIRM_BOOTUP:
        
        break;
        
        //-------------------------        
        case RRB_AMP1:  
        
        break;    
        
        //-------------------------        
        case MIC_AMP2:  
        
        break;        
        
        //-------------------------        
        case AUDIO_STREAM:  
        
        break;  
        
        //-------------------------        
        case FLASH:  
        
        break;  
        
        //-------------------------        
        case OVERLOAD:  
        
        break;  
        
        //-------------------------        
        case FAIL:  
        
        break;          
           
    }

}

/* [] END OF FILE */
