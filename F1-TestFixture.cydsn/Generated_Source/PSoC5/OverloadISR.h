/*******************************************************************************
* File Name: OverloadISR.h
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
#if !defined(CY_ISR_OverloadISR_H)
#define CY_ISR_OverloadISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OverloadISR_Start(void);
void OverloadISR_StartEx(cyisraddress address);
void OverloadISR_Stop(void);

CY_ISR_PROTO(OverloadISR_Interrupt);

void OverloadISR_SetVector(cyisraddress address);
cyisraddress OverloadISR_GetVector(void);

void OverloadISR_SetPriority(uint8 priority);
uint8 OverloadISR_GetPriority(void);

void OverloadISR_Enable(void);
uint8 OverloadISR_GetState(void);
void OverloadISR_Disable(void);

void OverloadISR_SetPending(void);
void OverloadISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OverloadISR ISR. */
#define OverloadISR_INTC_VECTOR            ((reg32 *) OverloadISR__INTC_VECT)

/* Address of the OverloadISR ISR priority. */
#define OverloadISR_INTC_PRIOR             ((reg8 *) OverloadISR__INTC_PRIOR_REG)

/* Priority of the OverloadISR interrupt. */
#define OverloadISR_INTC_PRIOR_NUMBER      OverloadISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OverloadISR interrupt. */
#define OverloadISR_INTC_SET_EN            ((reg32 *) OverloadISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OverloadISR interrupt. */
#define OverloadISR_INTC_CLR_EN            ((reg32 *) OverloadISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OverloadISR interrupt state to pending. */
#define OverloadISR_INTC_SET_PD            ((reg32 *) OverloadISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OverloadISR interrupt. */
#define OverloadISR_INTC_CLR_PD            ((reg32 *) OverloadISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_OverloadISR_H */


/* [] END OF FILE */
