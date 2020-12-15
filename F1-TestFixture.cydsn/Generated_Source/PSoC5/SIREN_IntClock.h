/*******************************************************************************
* File Name: SIREN_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SIREN_IntClock_H)
#define CY_CLOCK_SIREN_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SIREN_IntClock_Start(void) ;
void SIREN_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SIREN_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SIREN_IntClock_StandbyPower(uint8 state) ;
void SIREN_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SIREN_IntClock_GetDividerRegister(void) ;
void SIREN_IntClock_SetModeRegister(uint8 modeBitMask) ;
void SIREN_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 SIREN_IntClock_GetModeRegister(void) ;
void SIREN_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 SIREN_IntClock_GetSourceRegister(void) ;
#if defined(SIREN_IntClock__CFG3)
void SIREN_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 SIREN_IntClock_GetPhaseRegister(void) ;
#endif /* defined(SIREN_IntClock__CFG3) */

#define SIREN_IntClock_Enable()                       SIREN_IntClock_Start()
#define SIREN_IntClock_Disable()                      SIREN_IntClock_Stop()
#define SIREN_IntClock_SetDivider(clkDivider)         SIREN_IntClock_SetDividerRegister(clkDivider, 1u)
#define SIREN_IntClock_SetDividerValue(clkDivider)    SIREN_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define SIREN_IntClock_SetMode(clkMode)               SIREN_IntClock_SetModeRegister(clkMode)
#define SIREN_IntClock_SetSource(clkSource)           SIREN_IntClock_SetSourceRegister(clkSource)
#if defined(SIREN_IntClock__CFG3)
#define SIREN_IntClock_SetPhase(clkPhase)             SIREN_IntClock_SetPhaseRegister(clkPhase)
#define SIREN_IntClock_SetPhaseValue(clkPhase)        SIREN_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SIREN_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SIREN_IntClock_CLKEN              (* (reg8 *) SIREN_IntClock__PM_ACT_CFG)
#define SIREN_IntClock_CLKEN_PTR          ((reg8 *) SIREN_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SIREN_IntClock_CLKSTBY            (* (reg8 *) SIREN_IntClock__PM_STBY_CFG)
#define SIREN_IntClock_CLKSTBY_PTR        ((reg8 *) SIREN_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SIREN_IntClock_DIV_LSB            (* (reg8 *) SIREN_IntClock__CFG0)
#define SIREN_IntClock_DIV_LSB_PTR        ((reg8 *) SIREN_IntClock__CFG0)
#define SIREN_IntClock_DIV_PTR            ((reg16 *) SIREN_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define SIREN_IntClock_DIV_MSB            (* (reg8 *) SIREN_IntClock__CFG1)
#define SIREN_IntClock_DIV_MSB_PTR        ((reg8 *) SIREN_IntClock__CFG1)

/* Mode and source configuration register */
#define SIREN_IntClock_MOD_SRC            (* (reg8 *) SIREN_IntClock__CFG2)
#define SIREN_IntClock_MOD_SRC_PTR        ((reg8 *) SIREN_IntClock__CFG2)

#if defined(SIREN_IntClock__CFG3)
/* Analog clock phase configuration register */
#define SIREN_IntClock_PHASE              (* (reg8 *) SIREN_IntClock__CFG3)
#define SIREN_IntClock_PHASE_PTR          ((reg8 *) SIREN_IntClock__CFG3)
#endif /* defined(SIREN_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SIREN_IntClock_CLKEN_MASK         SIREN_IntClock__PM_ACT_MSK
#define SIREN_IntClock_CLKSTBY_MASK       SIREN_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define SIREN_IntClock_SRC_SEL_MSK        SIREN_IntClock__CFG2_SRC_SEL_MASK
#define SIREN_IntClock_MODE_MASK          (~(SIREN_IntClock_SRC_SEL_MSK))

#if defined(SIREN_IntClock__CFG3)
/* CFG3 phase mask */
#define SIREN_IntClock_PHASE_MASK         SIREN_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(SIREN_IntClock__CFG3) */

#endif /* CY_CLOCK_SIREN_IntClock_H */


/* [] END OF FILE */
