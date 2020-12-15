/*******************************************************************************
* File Name: PWMclock.h
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

#if !defined(CY_CLOCK_PWMclock_H)
#define CY_CLOCK_PWMclock_H

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

void PWMclock_Start(void) ;
void PWMclock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void PWMclock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void PWMclock_StandbyPower(uint8 state) ;
void PWMclock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 PWMclock_GetDividerRegister(void) ;
void PWMclock_SetModeRegister(uint8 modeBitMask) ;
void PWMclock_ClearModeRegister(uint8 modeBitMask) ;
uint8 PWMclock_GetModeRegister(void) ;
void PWMclock_SetSourceRegister(uint8 clkSource) ;
uint8 PWMclock_GetSourceRegister(void) ;
#if defined(PWMclock__CFG3)
void PWMclock_SetPhaseRegister(uint8 clkPhase) ;
uint8 PWMclock_GetPhaseRegister(void) ;
#endif /* defined(PWMclock__CFG3) */

#define PWMclock_Enable()                       PWMclock_Start()
#define PWMclock_Disable()                      PWMclock_Stop()
#define PWMclock_SetDivider(clkDivider)         PWMclock_SetDividerRegister(clkDivider, 1u)
#define PWMclock_SetDividerValue(clkDivider)    PWMclock_SetDividerRegister((clkDivider) - 1u, 1u)
#define PWMclock_SetMode(clkMode)               PWMclock_SetModeRegister(clkMode)
#define PWMclock_SetSource(clkSource)           PWMclock_SetSourceRegister(clkSource)
#if defined(PWMclock__CFG3)
#define PWMclock_SetPhase(clkPhase)             PWMclock_SetPhaseRegister(clkPhase)
#define PWMclock_SetPhaseValue(clkPhase)        PWMclock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(PWMclock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define PWMclock_CLKEN              (* (reg8 *) PWMclock__PM_ACT_CFG)
#define PWMclock_CLKEN_PTR          ((reg8 *) PWMclock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define PWMclock_CLKSTBY            (* (reg8 *) PWMclock__PM_STBY_CFG)
#define PWMclock_CLKSTBY_PTR        ((reg8 *) PWMclock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define PWMclock_DIV_LSB            (* (reg8 *) PWMclock__CFG0)
#define PWMclock_DIV_LSB_PTR        ((reg8 *) PWMclock__CFG0)
#define PWMclock_DIV_PTR            ((reg16 *) PWMclock__CFG0)

/* Clock MSB divider configuration register. */
#define PWMclock_DIV_MSB            (* (reg8 *) PWMclock__CFG1)
#define PWMclock_DIV_MSB_PTR        ((reg8 *) PWMclock__CFG1)

/* Mode and source configuration register */
#define PWMclock_MOD_SRC            (* (reg8 *) PWMclock__CFG2)
#define PWMclock_MOD_SRC_PTR        ((reg8 *) PWMclock__CFG2)

#if defined(PWMclock__CFG3)
/* Analog clock phase configuration register */
#define PWMclock_PHASE              (* (reg8 *) PWMclock__CFG3)
#define PWMclock_PHASE_PTR          ((reg8 *) PWMclock__CFG3)
#endif /* defined(PWMclock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define PWMclock_CLKEN_MASK         PWMclock__PM_ACT_MSK
#define PWMclock_CLKSTBY_MASK       PWMclock__PM_STBY_MSK

/* CFG2 field masks */
#define PWMclock_SRC_SEL_MSK        PWMclock__CFG2_SRC_SEL_MASK
#define PWMclock_MODE_MASK          (~(PWMclock_SRC_SEL_MSK))

#if defined(PWMclock__CFG3)
/* CFG3 phase mask */
#define PWMclock_PHASE_MASK         PWMclock__CFG3_PHASE_DLY_MASK
#endif /* defined(PWMclock__CFG3) */

#endif /* CY_CLOCK_PWMclock_H */


/* [] END OF FILE */
