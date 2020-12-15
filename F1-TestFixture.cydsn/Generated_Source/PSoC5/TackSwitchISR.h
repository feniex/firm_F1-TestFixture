/*******************************************************************************
* File Name: TackSwitchISR.h
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
#if !defined(CY_ISR_TackSwitchISR_H)
#define CY_ISR_TackSwitchISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TackSwitchISR_Start(void);
void TackSwitchISR_StartEx(cyisraddress address);
void TackSwitchISR_Stop(void);

CY_ISR_PROTO(TackSwitchISR_Interrupt);

void TackSwitchISR_SetVector(cyisraddress address);
cyisraddress TackSwitchISR_GetVector(void);

void TackSwitchISR_SetPriority(uint8 priority);
uint8 TackSwitchISR_GetPriority(void);

void TackSwitchISR_Enable(void);
uint8 TackSwitchISR_GetState(void);
void TackSwitchISR_Disable(void);

void TackSwitchISR_SetPending(void);
void TackSwitchISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TackSwitchISR ISR. */
#define TackSwitchISR_INTC_VECTOR            ((reg32 *) TackSwitchISR__INTC_VECT)

/* Address of the TackSwitchISR ISR priority. */
#define TackSwitchISR_INTC_PRIOR             ((reg8 *) TackSwitchISR__INTC_PRIOR_REG)

/* Priority of the TackSwitchISR interrupt. */
#define TackSwitchISR_INTC_PRIOR_NUMBER      TackSwitchISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TackSwitchISR interrupt. */
#define TackSwitchISR_INTC_SET_EN            ((reg32 *) TackSwitchISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TackSwitchISR interrupt. */
#define TackSwitchISR_INTC_CLR_EN            ((reg32 *) TackSwitchISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TackSwitchISR interrupt state to pending. */
#define TackSwitchISR_INTC_SET_PD            ((reg32 *) TackSwitchISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TackSwitchISR interrupt. */
#define TackSwitchISR_INTC_CLR_PD            ((reg32 *) TackSwitchISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_TackSwitchISR_H */


/* [] END OF FILE */
