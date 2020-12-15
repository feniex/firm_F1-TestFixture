/*******************************************************************************
* File Name: RadioMicKeyISR.h
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
#if !defined(CY_ISR_RadioMicKeyISR_H)
#define CY_ISR_RadioMicKeyISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RadioMicKeyISR_Start(void);
void RadioMicKeyISR_StartEx(cyisraddress address);
void RadioMicKeyISR_Stop(void);

CY_ISR_PROTO(RadioMicKeyISR_Interrupt);

void RadioMicKeyISR_SetVector(cyisraddress address);
cyisraddress RadioMicKeyISR_GetVector(void);

void RadioMicKeyISR_SetPriority(uint8 priority);
uint8 RadioMicKeyISR_GetPriority(void);

void RadioMicKeyISR_Enable(void);
uint8 RadioMicKeyISR_GetState(void);
void RadioMicKeyISR_Disable(void);

void RadioMicKeyISR_SetPending(void);
void RadioMicKeyISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RadioMicKeyISR ISR. */
#define RadioMicKeyISR_INTC_VECTOR            ((reg32 *) RadioMicKeyISR__INTC_VECT)

/* Address of the RadioMicKeyISR ISR priority. */
#define RadioMicKeyISR_INTC_PRIOR             ((reg8 *) RadioMicKeyISR__INTC_PRIOR_REG)

/* Priority of the RadioMicKeyISR interrupt. */
#define RadioMicKeyISR_INTC_PRIOR_NUMBER      RadioMicKeyISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RadioMicKeyISR interrupt. */
#define RadioMicKeyISR_INTC_SET_EN            ((reg32 *) RadioMicKeyISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RadioMicKeyISR interrupt. */
#define RadioMicKeyISR_INTC_CLR_EN            ((reg32 *) RadioMicKeyISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RadioMicKeyISR interrupt state to pending. */
#define RadioMicKeyISR_INTC_SET_PD            ((reg32 *) RadioMicKeyISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RadioMicKeyISR interrupt. */
#define RadioMicKeyISR_INTC_CLR_PD            ((reg32 *) RadioMicKeyISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_RadioMicKeyISR_H */


/* [] END OF FILE */
