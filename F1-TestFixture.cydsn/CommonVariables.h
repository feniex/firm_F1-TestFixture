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
#include "project.h"

//extern uint8 SelectedTest;
//extern struct structTestInfo
struct structTestInfo
{
    uint8 SelectedTest;
    uint8 TestStep;
    uint8 Status;
    //uint8 Failures;
}Test;

typedef struct structTestInfo StructTestInfo;

extern StructTestInfo CurrentTest;


//-----------------------------------------
uint8 ControllerTest_Complete(void);
uint8 ControllerCableTest_Complete(void);

void CableTest_Complete_20ms_isr(void);
void CableTest_Complete_50ms_isr(void);

void CableTest_Complete_StopAutomatedStep(void);
void CableTest_Complete_StartAutomatedStep(void);


/* [] END OF FILE */
