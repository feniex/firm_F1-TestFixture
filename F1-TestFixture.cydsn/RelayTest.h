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

//extern uint16 _100ms_flag;
extern uint16 isr_count;

uint8 RelayTest(void);

uint8 RTest_Test_Outputs(void);
uint8 RTest_Test_DataLink(void);
uint8 RTest_Test_QuadPorts(void);
uint8 RTest_Test_UART_Siren(void);
uint8 RTest_Test_Inputs(void);
uint8 RTest_Test_Vbatt(void);
uint8 RTest_Test_BlockCurrents(void);
uint8 RTest_Test_GPS(void);

void RTest_sendDiagPacket(void);
void ProcessFailure(void);

uint8 RTest_BlockCurrent(uint8);

void RTest_10ms_isr(void);
void RTest_20ms_isr(void);
void RTest_50ms_isr(void);
//void RTest_20ms_isr_reset(void);

void SetRelayOutputs(uint8 enable);

void RTest_StartAutomatedStep(void);
void RTest_StopAutomatedStep(void);

void SetRelayInputs(uint8 enable);

//****** Stuff added for RelayTest_Complete
uint8 RelayTest_Complete(void);

uint8 RTest_Complete_Test_DataLink(void);

void RTest_Complete_StopAutomatedStep(void);
void RTest_Complete_StartAutomatedStep(void);

void RTest_Complete_20ms_isr(void);   
void RTest_Complete_50ms_isr(void);

void RTest_Complete_sendDiagPacket(void);



/* [] END OF FILE */
