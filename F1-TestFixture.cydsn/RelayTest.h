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


void RelayTest(void);

uint8 RTest_Test_Outputs(void);
uint8 RTest_Test_DataLink(void);
uint8 RTest_Test_QuadPorts(void);
uint8 RTest_Test_UART_Siren(void);
uint8 RTest_Test_Inputs(void);
uint8 RTest_Test_Vbatt(void);
uint8 RTest_Test_BlockCurrents(void);
uint8 RTest_Test_GPS(void);

void sendDiagPacket(void);
void ProcessFailure(void);

uint8 RTest_BlockCurrent(uint8);

void RTest_20ms_isr(void);
void RTest_20ms_isr_reset(void);

void SetRelayOutputs(uint8 enable);


/* [] END OF FILE */
