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

uint8 ControllerTest(void);

//uint8 CTest_VerifyPacket_QUAD(void);

uint8 CTest_ReadPushbuttons(void);
uint8 CTest_ReadPowerMode(void);

void CTest_SendIgnitionState(uint8 ignition_state);

void sendDataToController(void);

void CTest_isr_PB(void);

//void CTest_10ms_isr(void);
void CTest_20ms_isr(void);
void CTest_50ms_isr(void);

void CTest_sendDiagPacket(void);

void CTest_StartAutomatedStep(void);
void CTest_StopAutomatedStep(void);

void CTest_PB_WaitForAction(void);

void setLEDs(uint8 color);

/****************************************/
void CTest_Complete_sendDiagPacket(void);
void CTest_Complete_isr_PB(void);
void CTest_Complete_20ms_isr(void);
void CTest_Complete_50ms_isr(void);

void CTest_Complete_StartAutomatedStep(void);
void CTest_Complete_StopAutomatedStep(void);


/* [] END OF FILE */
