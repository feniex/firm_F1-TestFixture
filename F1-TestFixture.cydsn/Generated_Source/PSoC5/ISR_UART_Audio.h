/*******************************************************************************
* File Name: ISR_UART_Audio.h
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
#if !defined(CY_ISR_ISR_UART_Audio_H)
#define CY_ISR_ISR_UART_Audio_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_UART_Audio_Start(void);
void ISR_UART_Audio_StartEx(cyisraddress address);
void ISR_UART_Audio_Stop(void);

CY_ISR_PROTO(ISR_UART_Audio_Interrupt);

void ISR_UART_Audio_SetVector(cyisraddress address);
cyisraddress ISR_UART_Audio_GetVector(void);

void ISR_UART_Audio_SetPriority(uint8 priority);
uint8 ISR_UART_Audio_GetPriority(void);

void ISR_UART_Audio_Enable(void);
uint8 ISR_UART_Audio_GetState(void);
void ISR_UART_Audio_Disable(void);

void ISR_UART_Audio_SetPending(void);
void ISR_UART_Audio_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_UART_Audio ISR. */
#define ISR_UART_Audio_INTC_VECTOR            ((reg32 *) ISR_UART_Audio__INTC_VECT)

/* Address of the ISR_UART_Audio ISR priority. */
#define ISR_UART_Audio_INTC_PRIOR             ((reg8 *) ISR_UART_Audio__INTC_PRIOR_REG)

/* Priority of the ISR_UART_Audio interrupt. */
#define ISR_UART_Audio_INTC_PRIOR_NUMBER      ISR_UART_Audio__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_UART_Audio interrupt. */
#define ISR_UART_Audio_INTC_SET_EN            ((reg32 *) ISR_UART_Audio__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_UART_Audio interrupt. */
#define ISR_UART_Audio_INTC_CLR_EN            ((reg32 *) ISR_UART_Audio__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_UART_Audio interrupt state to pending. */
#define ISR_UART_Audio_INTC_SET_PD            ((reg32 *) ISR_UART_Audio__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_UART_Audio interrupt. */
#define ISR_UART_Audio_INTC_CLR_PD            ((reg32 *) ISR_UART_Audio__INTC_CLR_PD_REG)


#endif /* CY_ISR_ISR_UART_Audio_H */


/* [] END OF FILE */
