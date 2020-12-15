/*******************************************************************************
* File Name: DualDelayISR.h
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
#if !defined(CY_ISR_DualDelayISR_H)
#define CY_ISR_DualDelayISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DualDelayISR_Start(void);
void DualDelayISR_StartEx(cyisraddress address);
void DualDelayISR_Stop(void);

CY_ISR_PROTO(DualDelayISR_Interrupt);

void DualDelayISR_SetVector(cyisraddress address);
cyisraddress DualDelayISR_GetVector(void);

void DualDelayISR_SetPriority(uint8 priority);
uint8 DualDelayISR_GetPriority(void);

void DualDelayISR_Enable(void);
uint8 DualDelayISR_GetState(void);
void DualDelayISR_Disable(void);

void DualDelayISR_SetPending(void);
void DualDelayISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DualDelayISR ISR. */
#define DualDelayISR_INTC_VECTOR            ((reg32 *) DualDelayISR__INTC_VECT)

/* Address of the DualDelayISR ISR priority. */
#define DualDelayISR_INTC_PRIOR             ((reg8 *) DualDelayISR__INTC_PRIOR_REG)

/* Priority of the DualDelayISR interrupt. */
#define DualDelayISR_INTC_PRIOR_NUMBER      DualDelayISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DualDelayISR interrupt. */
#define DualDelayISR_INTC_SET_EN            ((reg32 *) DualDelayISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DualDelayISR interrupt. */
#define DualDelayISR_INTC_CLR_EN            ((reg32 *) DualDelayISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DualDelayISR interrupt state to pending. */
#define DualDelayISR_INTC_SET_PD            ((reg32 *) DualDelayISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DualDelayISR interrupt. */
#define DualDelayISR_INTC_CLR_PD            ((reg32 *) DualDelayISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_DualDelayISR_H */


/* [] END OF FILE */
