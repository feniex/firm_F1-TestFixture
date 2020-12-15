/*******************************************************************************
* File Name: CyDividedClock.h
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

#if !defined(CY_CLOCK_CyDividedClock_H)
#define CY_CLOCK_CyDividedClock_H

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

void CyDividedClock_Start(void) ;
void CyDividedClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CyDividedClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CyDividedClock_StandbyPower(uint8 state) ;
void CyDividedClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CyDividedClock_GetDividerRegister(void) ;
void CyDividedClock_SetModeRegister(uint8 modeBitMask) ;
void CyDividedClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 CyDividedClock_GetModeRegister(void) ;
void CyDividedClock_SetSourceRegister(uint8 clkSource) ;
uint8 CyDividedClock_GetSourceRegister(void) ;
#if defined(CyDividedClock__CFG3)
void CyDividedClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 CyDividedClock_GetPhaseRegister(void) ;
#endif /* defined(CyDividedClock__CFG3) */

#define CyDividedClock_Enable()                       CyDividedClock_Start()
#define CyDividedClock_Disable()                      CyDividedClock_Stop()
#define CyDividedClock_SetDivider(clkDivider)         CyDividedClock_SetDividerRegister(clkDivider, 1u)
#define CyDividedClock_SetDividerValue(clkDivider)    CyDividedClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define CyDividedClock_SetMode(clkMode)               CyDividedClock_SetModeRegister(clkMode)
#define CyDividedClock_SetSource(clkSource)           CyDividedClock_SetSourceRegister(clkSource)
#if defined(CyDividedClock__CFG3)
#define CyDividedClock_SetPhase(clkPhase)             CyDividedClock_SetPhaseRegister(clkPhase)
#define CyDividedClock_SetPhaseValue(clkPhase)        CyDividedClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CyDividedClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CyDividedClock_CLKEN              (* (reg8 *) CyDividedClock__PM_ACT_CFG)
#define CyDividedClock_CLKEN_PTR          ((reg8 *) CyDividedClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CyDividedClock_CLKSTBY            (* (reg8 *) CyDividedClock__PM_STBY_CFG)
#define CyDividedClock_CLKSTBY_PTR        ((reg8 *) CyDividedClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CyDividedClock_DIV_LSB            (* (reg8 *) CyDividedClock__CFG0)
#define CyDividedClock_DIV_LSB_PTR        ((reg8 *) CyDividedClock__CFG0)
#define CyDividedClock_DIV_PTR            ((reg16 *) CyDividedClock__CFG0)

/* Clock MSB divider configuration register. */
#define CyDividedClock_DIV_MSB            (* (reg8 *) CyDividedClock__CFG1)
#define CyDividedClock_DIV_MSB_PTR        ((reg8 *) CyDividedClock__CFG1)

/* Mode and source configuration register */
#define CyDividedClock_MOD_SRC            (* (reg8 *) CyDividedClock__CFG2)
#define CyDividedClock_MOD_SRC_PTR        ((reg8 *) CyDividedClock__CFG2)

#if defined(CyDividedClock__CFG3)
/* Analog clock phase configuration register */
#define CyDividedClock_PHASE              (* (reg8 *) CyDividedClock__CFG3)
#define CyDividedClock_PHASE_PTR          ((reg8 *) CyDividedClock__CFG3)
#endif /* defined(CyDividedClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CyDividedClock_CLKEN_MASK         CyDividedClock__PM_ACT_MSK
#define CyDividedClock_CLKSTBY_MASK       CyDividedClock__PM_STBY_MSK

/* CFG2 field masks */
#define CyDividedClock_SRC_SEL_MSK        CyDividedClock__CFG2_SRC_SEL_MASK
#define CyDividedClock_MODE_MASK          (~(CyDividedClock_SRC_SEL_MSK))

#if defined(CyDividedClock__CFG3)
/* CFG3 phase mask */
#define CyDividedClock_PHASE_MASK         CyDividedClock__CFG3_PHASE_DLY_MASK
#endif /* defined(CyDividedClock__CFG3) */

#endif /* CY_CLOCK_CyDividedClock_H */


/* [] END OF FILE */
