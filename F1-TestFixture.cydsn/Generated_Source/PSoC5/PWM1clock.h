/*******************************************************************************
* File Name: PWM1clock.h
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

#if !defined(CY_CLOCK_PWM1clock_H)
#define CY_CLOCK_PWM1clock_H

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

void PWM1clock_Start(void) ;
void PWM1clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void PWM1clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void PWM1clock_StandbyPower(uint8 state) ;
void PWM1clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 PWM1clock_GetDividerRegister(void) ;
void PWM1clock_SetModeRegister(uint8 modeBitMask) ;
void PWM1clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 PWM1clock_GetModeRegister(void) ;
void PWM1clock_SetSourceRegister(uint8 clkSource) ;
uint8 PWM1clock_GetSourceRegister(void) ;
#if defined(PWM1clock__CFG3)
void PWM1clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 PWM1clock_GetPhaseRegister(void) ;
#endif /* defined(PWM1clock__CFG3) */

#define PWM1clock_Enable()                       PWM1clock_Start()
#define PWM1clock_Disable()                      PWM1clock_Stop()
#define PWM1clock_SetDivider(clkDivider)         PWM1clock_SetDividerRegister(clkDivider, 1u)
#define PWM1clock_SetDividerValue(clkDivider)    PWM1clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define PWM1clock_SetMode(clkMode)               PWM1clock_SetModeRegister(clkMode)
#define PWM1clock_SetSource(clkSource)           PWM1clock_SetSourceRegister(clkSource)
#if defined(PWM1clock__CFG3)
#define PWM1clock_SetPhase(clkPhase)             PWM1clock_SetPhaseRegister(clkPhase)
#define PWM1clock_SetPhaseValue(clkPhase)        PWM1clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(PWM1clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define PWM1clock_CLKEN              (* (reg8 *) PWM1clock__PM_ACT_CFG)
#define PWM1clock_CLKEN_PTR          ((reg8 *) PWM1clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define PWM1clock_CLKSTBY            (* (reg8 *) PWM1clock__PM_STBY_CFG)
#define PWM1clock_CLKSTBY_PTR        ((reg8 *) PWM1clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define PWM1clock_DIV_LSB            (* (reg8 *) PWM1clock__CFG0)
#define PWM1clock_DIV_LSB_PTR        ((reg8 *) PWM1clock__CFG0)
#define PWM1clock_DIV_PTR            ((reg16 *) PWM1clock__CFG0)

/* Clock MSB divider configuration register. */
#define PWM1clock_DIV_MSB            (* (reg8 *) PWM1clock__CFG1)
#define PWM1clock_DIV_MSB_PTR        ((reg8 *) PWM1clock__CFG1)

/* Mode and source configuration register */
#define PWM1clock_MOD_SRC            (* (reg8 *) PWM1clock__CFG2)
#define PWM1clock_MOD_SRC_PTR        ((reg8 *) PWM1clock__CFG2)

#if defined(PWM1clock__CFG3)
/* Analog clock phase configuration register */
#define PWM1clock_PHASE              (* (reg8 *) PWM1clock__CFG3)
#define PWM1clock_PHASE_PTR          ((reg8 *) PWM1clock__CFG3)
#endif /* defined(PWM1clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define PWM1clock_CLKEN_MASK         PWM1clock__PM_ACT_MSK
#define PWM1clock_CLKSTBY_MASK       PWM1clock__PM_STBY_MSK

/* CFG2 field masks */
#define PWM1clock_SRC_SEL_MSK        PWM1clock__CFG2_SRC_SEL_MASK
#define PWM1clock_MODE_MASK          (~(PWM1clock_SRC_SEL_MSK))

#if defined(PWM1clock__CFG3)
/* CFG3 phase mask */
#define PWM1clock_PHASE_MASK         PWM1clock__CFG3_PHASE_DLY_MASK
#endif /* defined(PWM1clock__CFG3) */

#endif /* CY_CLOCK_PWM1clock_H */


/* [] END OF FILE */
