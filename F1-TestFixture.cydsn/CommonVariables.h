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
    uint8 Failures;
}Test;

typedef struct structTestInfo StructTestInfo;

extern StructTestInfo CurrentTest;


/* [] END OF FILE */
