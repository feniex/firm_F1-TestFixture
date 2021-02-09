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
#include "CommonVariables.h"

//#include "UART_230400.h"
#include "ControllerTest.h"
#include "RelayTest.h"
#include "SirenTest.h"

//#include "isr_Timer_Quick.h"

//#define TIMEOUT 100
#define INITIALIZE_TEST     0;

#define PCBA_TESTFIXTURE    0
#define FINAL_TESTFIXTURE    1

/**********DEFINED CONSTANTS**********/

enum DataType
{ 
    CTEST, 
    RTEST,
    STEST,
    CTEST_COMPLETE,
    RTEST_COMPLETE
};

/**********DATA STRUCTURES**********/

/**********GLOBAL VARIABLES**********/
//extern uint8 SelectedTest;
//extern struct structTestInfo
//struct structTestInfo
//{
//    uint8 SelectedTest;
//    uint8 TestStep;
//    uint8 Failures;
//}Test;
//
//typedef struct structTestInfo StructTestInfo;
//
//extern StructTestInfo CurrentTest;

/**********FUNCTION PROTOTYPES**********/
static void initializePeripherals(void);

//uint8 Timer_Quick_INT_GetFlag(void);
//void Timer_Quick_INT_ClearFlag(void);
void StartTimeout(void);
void StopTimeout(void);
void ProcessFailure(void);

/**********DEFINED FUNCTIONS**********/
uint8 TESTFIXTURE_TYPE = 0;


static uint8 rs1_value = 0;
static uint8 rs2_value = 0;


int main()
{
    TESTFIXTURE_TYPE = FINAL_TESTFIXTURE;                    //*** Define testfixture hardware type
    
    initializePeripherals();
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    
    for(;;)
    {     
        rs1_value = RS1_Read();
        rs2_value = RS2_Read();
        
        if(TESTFIXTURE_TYPE == PCBA_TESTFIXTURE)
        {
            if( (RS1_Read() == 1) && (RS2_Read() == 0) )
                CurrentTest.SelectedTest = CTEST;
            else if( (RS1_Read() == 0) && (RS2_Read() == 0) )
                CurrentTest.SelectedTest = RTEST;
            else if( (RS1_Read() == 0) && (RS2_Read() == 1) )
                CurrentTest.SelectedTest = STEST;
        }
        else if(TESTFIXTURE_TYPE == FINAL_TESTFIXTURE)
        {
            if( (RS1_Read() == 1) && (RS2_Read() == 0) )
                CurrentTest.SelectedTest = CTEST_COMPLETE;
            else if( (RS1_Read() == 0) && (RS2_Read() == 0) )
                CurrentTest.SelectedTest = RTEST_COMPLETE;
//            else if( (RS1_Read() == 0) && (RS2_Read() == 1) )
//                CurrentTest.SelectedTest = STEST;
        }
                    
        //CurrentTest.SelectedTest = STEST;
        CurrentTest.SelectedTest = RTEST_COMPLETE;
        

        switch(CurrentTest.SelectedTest)
        {
            case CTEST:
            
                CurrentTest.TestStep = INITIALIZE_TEST;
                while(!ControllerTest())
                {}

            break;
                
            case RTEST:
            
                CurrentTest.TestStep = INITIALIZE_TEST;
                while(!RelayTest())
                {}

            break;    
                
            case STEST:
            
                CurrentTest.TestStep = INITIALIZE_TEST;
                while(!SirenTest())
                {}

            break;   
                
            case CTEST_COMPLETE:
            
                CurrentTest.TestStep = INITIALIZE_TEST;
                while(!ControllerTest_Complete())
                {}

            break;   
                
            case RTEST_COMPLETE:                            // Test 
            
                CurrentTest.TestStep = INITIALIZE_TEST;
                while(!RelayTest_Complete())
                {}

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
    
    //----------Start UART_460800--------
    UART_460800_Start();    
    isr_UART_460800_Start();
    //----------Start UART_230400--------
    UART_230400_Start();    
    isr_UART_230400_Start();
    //----------Start UART_115200--------
    UART_115200_Start();    
    isr_UART_115200_Start();
    //----------Start UART_9600----------
//    UART_9600_Start();    
//    isr_UART_9600_Start();
    
    //-----------------------------------
    
    Timer_50ms_Start();
    isr_Timer_50ms_Start();
    
    Timer_20ms_Start();
    isr_Timer_20ms_Start();
    
    Timer_10ms_Start();
    isr_Timer_10ms_Start();
    
    WaveDAC_Start();
    
//    Timer_DAC_Start();
    
    //ADC_AudioStream_Start();
    //isr_ADC_AudioStream_Start();

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
