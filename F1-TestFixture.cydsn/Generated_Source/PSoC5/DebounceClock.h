/*******************************************************************************
* File Name: DebounceClock.h
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

#if !defined(CY_CLOCK_DebounceClock_H)
#define CY_CLOCK_DebounceClock_H

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

void DebounceClock_Start(void) ;
void DebounceClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DebounceClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DebounceClock_StandbyPower(uint8 state) ;
void DebounceClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DebounceClock_GetDividerRegister(void) ;
void DebounceClock_SetModeRegister(uint8 modeBitMask) ;
void DebounceClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 DebounceClock_GetModeRegister(void) ;
void DebounceClock_SetSourceRegister(uint8 clkSource) ;
uint8 DebounceClock_GetSourceRegister(void) ;
#if defined(DebounceClock__CFG3)
void DebounceClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 DebounceClock_GetPhaseRegister(void) ;
#endif /* defined(DebounceClock__CFG3) */

#define DebounceClock_Enable()                       DebounceClock_Start()
#define DebounceClock_Disable()                      DebounceClock_Stop()
#define DebounceClock_SetDivider(clkDivider)         DebounceClock_SetDividerRegister(clkDivider, 1u)
#define DebounceClock_SetDividerValue(clkDivider)    DebounceClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define DebounceClock_SetMode(clkMode)               DebounceClock_SetModeRegister(clkMode)
#define DebounceClock_SetSource(clkSource)           DebounceClock_SetSourceRegister(clkSource)
#if defined(DebounceClock__CFG3)
#define DebounceClock_SetPhase(clkPhase)             DebounceClock_SetPhaseRegister(clkPhase)
#define DebounceClock_SetPhaseValue(clkPhase)        DebounceClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DebounceClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DebounceClock_CLKEN              (* (reg8 *) DebounceClock__PM_ACT_CFG)
#define DebounceClock_CLKEN_PTR          ((reg8 *) DebounceClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DebounceClock_CLKSTBY            (* (reg8 *) DebounceClock__PM_STBY_CFG)
#define DebounceClock_CLKSTBY_PTR        ((reg8 *) DebounceClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DebounceClock_DIV_LSB            (* (reg8 *) DebounceClock__CFG0)
#define DebounceClock_DIV_LSB_PTR        ((reg8 *) DebounceClock__CFG0)
#define DebounceClock_DIV_PTR            ((reg16 *) DebounceClock__CFG0)

/* Clock MSB divider configuration register. */
#define DebounceClock_DIV_MSB            (* (reg8 *) DebounceClock__CFG1)
#define DebounceClock_DIV_MSB_PTR        ((reg8 *) DebounceClock__CFG1)

/* Mode and source configuration register */
#define DebounceClock_MOD_SRC            (* (reg8 *) DebounceClock__CFG2)
#define DebounceClock_MOD_SRC_PTR        ((reg8 *) DebounceClock__CFG2)

#if defined(DebounceClock__CFG3)
/* Analog clock phase configuration register */
#define DebounceClock_PHASE              (* (reg8 *) DebounceClock__CFG3)
#define DebounceClock_PHASE_PTR          ((reg8 *) DebounceClock__CFG3)
#endif /* defined(DebounceClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DebounceClock_CLKEN_MASK         DebounceClock__PM_ACT_MSK
#define DebounceClock_CLKSTBY_MASK       DebounceClock__PM_STBY_MSK

/* CFG2 field masks */
#define DebounceClock_SRC_SEL_MSK        DebounceClock__CFG2_SRC_SEL_MASK
#define DebounceClock_MODE_MASK          (~(DebounceClock_SRC_SEL_MSK))

#if defined(DebounceClock__CFG3)
/* CFG3 phase mask */
#define DebounceClock_PHASE_MASK         DebounceClock__CFG3_PHASE_DLY_MASK
#endif /* defined(DebounceClock__CFG3) */

#endif /* CY_CLOCK_DebounceClock_H */


/* [] END OF FILE */
