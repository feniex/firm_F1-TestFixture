/*******************************************************************************
* File Name: isr_UART_115200.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_UART_115200_H)
#define CY_ISR_isr_UART_115200_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_UART_115200_Start(void);
void isr_UART_115200_StartEx(cyisraddress address);
void isr_UART_115200_Stop(void);

CY_ISR_PROTO(isr_UART_115200_Interrupt);

void isr_UART_115200_SetVector(cyisraddress address);
cyisraddress isr_UART_115200_GetVector(void);

void isr_UART_115200_SetPriority(uint8 priority);
uint8 isr_UART_115200_GetPriority(void);

void isr_UART_115200_Enable(void);
uint8 isr_UART_115200_GetState(void);
void isr_UART_115200_Disable(void);

void isr_UART_115200_SetPending(void);
void isr_UART_115200_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_UART_115200 ISR. */
#define isr_UART_115200_INTC_VECTOR            ((reg32 *) isr_UART_115200__INTC_VECT)

/* Address of the isr_UART_115200 ISR priority. */
#define isr_UART_115200_INTC_PRIOR             ((reg8 *) isr_UART_115200__INTC_PRIOR_REG)

/* Priority of the isr_UART_115200 interrupt. */
#define isr_UART_115200_INTC_PRIOR_NUMBER      isr_UART_115200__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_UART_115200 interrupt. */
#define isr_UART_115200_INTC_SET_EN            ((reg32 *) isr_UART_115200__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_UART_115200 interrupt. */
#define isr_UART_115200_INTC_CLR_EN            ((reg32 *) isr_UART_115200__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_UART_115200 interrupt state to pending. */
#define isr_UART_115200_INTC_SET_PD            ((reg32 *) isr_UART_115200__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_UART_115200 interrupt. */
#define isr_UART_115200_INTC_CLR_PD            ((reg32 *) isr_UART_115200__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_UART_115200_H */


/* [] END OF FILE */
