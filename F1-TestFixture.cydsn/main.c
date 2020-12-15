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

// This firmare is meant to be run on the F1-Siren-REV02 board
// It serves as a sandbox to develope test fixture firmware while waiting for hardware to arrive

/********************Version Changes***************************
*
*   Started test fixture firmware on 11-4-20
*
*   Initial commit to GitHub on 12-15-20
*
***********************************************/

/**********PREPROCESSOR DIRECTIVES**********/
#include <project.h>

#include "UART_230400.h"
#include "ControllerTest.h"
#include "RelayTest.h"
#include "SirenTest.h"

#include "isr_Timer_Quick.h"

//#define TIMEOUT 100



/**********DEFINED CONSTANTS**********/

//#define CTEST
enum DataType
{ 
    CTEST, 
    RTEST,
    STEST
};

/**********DATA STRUCTURES**********/

/**********GLOBAL VARIABLES**********/
static uint8 SelectedTest = 0;

/**********FUNCTION PROTOTYPES**********/
static void initializePeripherals(void);

//uint8 Timer_Quick_INT_GetFlag(void);
//void Timer_Quick_INT_ClearFlag(void);
void StartTimeout(void);
void StopTimeout(void);
void ProcessFailure(void);

/**********DEFINED FUNCTIONS**********/

int main()
{
    initializePeripherals();
    CyGlobalIntEnable; /* Enable global interrupts. */
    
//    MUX_CTRL_230400_Write(1);
//    while(1);

    for(;;)
    {     
        SelectedTest = RTEST;
        
        //sendDiagPacket();
        
        switch(SelectedTest)
        {
            case 0:
            
                ControllerTest();

            break;
                
            case RTEST:
            
                RelayTest();

            break;         
        }
            
    }
    
}

/*******************************************************************************
* Function Name: initializePeripherals
********************************************************************************
*
* Summary:
*  Sets up the watchdog timer, disables, power amplifiers, and enables all ISRs
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void initializePeripherals(void)
{
    
//    RS485_RX_EN_Write(1);                       // *** for testing with siren board only
    
    //----------Start UART_460800--------
    UART_460800_Start();    
    isr_UART_460800_Start();
    //----------Start UART_230400--------
    UART_230400_Start();    
    isr_UART_230400_Start();
    //----------Start UART_115200--------
//    UART_115200_Start();    
//    isr_UART_115200_Start();
    //----------Start UART_9600----------
//    UART_9600_Start();    
//    isr_UART_9600_Start();

    
    //-----------------------------------
    Timer_20ms_Start();
    isr_Timer_20ms_Start();
    
    Timer_Quick_Start();
    isr_Timer_Quick_Start();

    return;
}

void StartTimeout(void)
{
    

    return;
}

void StopTimeout(void)
{


    return;
}





/* [] END OF FILE */
