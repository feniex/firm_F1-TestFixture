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

void ControllerTest(void);

uint8 CTest_VerifyPacket_QUAD(void);

uint8 CTest_ReadPushbuttons(void);
uint8 CTest_ReadPowerMode(void);

void CTest_SendIgnitionState(uint8 ignition_state);

void sendDataToController(void);

//void CTest_10ms_isr(void);
void CTest_20ms_isr(void);
void CTest_50ms_isr(void);

void CTest_sendDiagPacket(void);


/* [] END OF FILE */