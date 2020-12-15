/*******************************************************************************
* File Name: HornRingISR.h
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
#if !defined(CY_ISR_HornRingISR_H)
#define CY_ISR_HornRingISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void HornRingISR_Start(void);
void HornRingISR_StartEx(cyisraddress address);
void HornRingISR_Stop(void);

CY_ISR_PROTO(HornRingISR_Interrupt);

void HornRingISR_SetVector(cyisraddress address);
cyisraddress HornRingISR_GetVector(void);

void HornRingISR_SetPriority(uint8 priority);
uint8 HornRingISR_GetPriority(void);

void HornRingISR_Enable(void);
uint8 HornRingISR_GetState(void);
void HornRingISR_Disable(void);

void HornRingISR_SetPending(void);
void HornRingISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the HornRingISR ISR. */
#define HornRingISR_INTC_VECTOR            ((reg32 *) HornRingISR__INTC_VECT)

/* Address of the HornRingISR ISR priority. */
#define HornRingISR_INTC_PRIOR             ((reg8 *) HornRingISR__INTC_PRIOR_REG)

/* Priority of the HornRingISR interrupt. */
#define HornRingISR_INTC_PRIOR_NUMBER      HornRingISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable HornRingISR interrupt. */
#define HornRingISR_INTC_SET_EN            ((reg32 *) HornRingISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the HornRingISR interrupt. */
#define HornRingISR_INTC_CLR_EN            ((reg32 *) HornRingISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the HornRingISR interrupt state to pending. */
#define HornRingISR_INTC_SET_PD            ((reg32 *) HornRingISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the HornRingISR interrupt. */
#define HornRingISR_INTC_CLR_PD            ((reg32 *) HornRingISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_HornRingISR_H */


/* [] END OF FILE */
