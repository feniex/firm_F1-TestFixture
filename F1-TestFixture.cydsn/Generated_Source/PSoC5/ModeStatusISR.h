/*******************************************************************************
* File Name: ModeStatusISR.h
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
#if !defined(CY_ISR_ModeStatusISR_H)
#define CY_ISR_ModeStatusISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ModeStatusISR_Start(void);
void ModeStatusISR_StartEx(cyisraddress address);
void ModeStatusISR_Stop(void);

CY_ISR_PROTO(ModeStatusISR_Interrupt);

void ModeStatusISR_SetVector(cyisraddress address);
cyisraddress ModeStatusISR_GetVector(void);

void ModeStatusISR_SetPriority(uint8 priority);
uint8 ModeStatusISR_GetPriority(void);

void ModeStatusISR_Enable(void);
uint8 ModeStatusISR_GetState(void);
void ModeStatusISR_Disable(void);

void ModeStatusISR_SetPending(void);
void ModeStatusISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ModeStatusISR ISR. */
#define ModeStatusISR_INTC_VECTOR            ((reg32 *) ModeStatusISR__INTC_VECT)

/* Address of the ModeStatusISR ISR priority. */
#define ModeStatusISR_INTC_PRIOR             ((reg8 *) ModeStatusISR__INTC_PRIOR_REG)

/* Priority of the ModeStatusISR interrupt. */
#define ModeStatusISR_INTC_PRIOR_NUMBER      ModeStatusISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ModeStatusISR interrupt. */
#define ModeStatusISR_INTC_SET_EN            ((reg32 *) ModeStatusISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ModeStatusISR interrupt. */
#define ModeStatusISR_INTC_CLR_EN            ((reg32 *) ModeStatusISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ModeStatusISR interrupt state to pending. */
#define ModeStatusISR_INTC_SET_PD            ((reg32 *) ModeStatusISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ModeStatusISR interrupt. */
#define ModeStatusISR_INTC_CLR_PD            ((reg32 *) ModeStatusISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_ModeStatusISR_H */


/* [] END OF FILE */
