/*******************************************************************************
* File Name: sirenRxISR.h
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
#if !defined(CY_ISR_sirenRxISR_H)
#define CY_ISR_sirenRxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void sirenRxISR_Start(void);
void sirenRxISR_StartEx(cyisraddress address);
void sirenRxISR_Stop(void);

CY_ISR_PROTO(sirenRxISR_Interrupt);

void sirenRxISR_SetVector(cyisraddress address);
cyisraddress sirenRxISR_GetVector(void);

void sirenRxISR_SetPriority(uint8 priority);
uint8 sirenRxISR_GetPriority(void);

void sirenRxISR_Enable(void);
uint8 sirenRxISR_GetState(void);
void sirenRxISR_Disable(void);

void sirenRxISR_SetPending(void);
void sirenRxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the sirenRxISR ISR. */
#define sirenRxISR_INTC_VECTOR            ((reg32 *) sirenRxISR__INTC_VECT)

/* Address of the sirenRxISR ISR priority. */
#define sirenRxISR_INTC_PRIOR             ((reg8 *) sirenRxISR__INTC_PRIOR_REG)

/* Priority of the sirenRxISR interrupt. */
#define sirenRxISR_INTC_PRIOR_NUMBER      sirenRxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable sirenRxISR interrupt. */
#define sirenRxISR_INTC_SET_EN            ((reg32 *) sirenRxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the sirenRxISR interrupt. */
#define sirenRxISR_INTC_CLR_EN            ((reg32 *) sirenRxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the sirenRxISR interrupt state to pending. */
#define sirenRxISR_INTC_SET_PD            ((reg32 *) sirenRxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the sirenRxISR interrupt. */
#define sirenRxISR_INTC_CLR_PD            ((reg32 *) sirenRxISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_sirenRxISR_H */


/* [] END OF FILE */
