/*******************************************************************************
* File Name: ModeStatus2ISR.h
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
#if !defined(CY_ISR_ModeStatus2ISR_H)
#define CY_ISR_ModeStatus2ISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ModeStatus2ISR_Start(void);
void ModeStatus2ISR_StartEx(cyisraddress address);
void ModeStatus2ISR_Stop(void);

CY_ISR_PROTO(ModeStatus2ISR_Interrupt);

void ModeStatus2ISR_SetVector(cyisraddress address);
cyisraddress ModeStatus2ISR_GetVector(void);

void ModeStatus2ISR_SetPriority(uint8 priority);
uint8 ModeStatus2ISR_GetPriority(void);

void ModeStatus2ISR_Enable(void);
uint8 ModeStatus2ISR_GetState(void);
void ModeStatus2ISR_Disable(void);

void ModeStatus2ISR_SetPending(void);
void ModeStatus2ISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ModeStatus2ISR ISR. */
#define ModeStatus2ISR_INTC_VECTOR            ((reg32 *) ModeStatus2ISR__INTC_VECT)

/* Address of the ModeStatus2ISR ISR priority. */
#define ModeStatus2ISR_INTC_PRIOR             ((reg8 *) ModeStatus2ISR__INTC_PRIOR_REG)

/* Priority of the ModeStatus2ISR interrupt. */
#define ModeStatus2ISR_INTC_PRIOR_NUMBER      ModeStatus2ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ModeStatus2ISR interrupt. */
#define ModeStatus2ISR_INTC_SET_EN            ((reg32 *) ModeStatus2ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ModeStatus2ISR interrupt. */
#define ModeStatus2ISR_INTC_CLR_EN            ((reg32 *) ModeStatus2ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ModeStatus2ISR interrupt state to pending. */
#define ModeStatus2ISR_INTC_SET_PD            ((reg32 *) ModeStatus2ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ModeStatus2ISR interrupt. */
#define ModeStatus2ISR_INTC_CLR_PD            ((reg32 *) ModeStatus2ISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_ModeStatus2ISR_H */


/* [] END OF FILE */
