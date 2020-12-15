/*******************************************************************************
* File Name: StatusClock.h
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

#if !defined(CY_CLOCK_StatusClock_H)
#define CY_CLOCK_StatusClock_H

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

void StatusClock_Start(void) ;
void StatusClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void StatusClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void StatusClock_StandbyPower(uint8 state) ;
void StatusClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 StatusClock_GetDividerRegister(void) ;
void StatusClock_SetModeRegister(uint8 modeBitMask) ;
void StatusClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 StatusClock_GetModeRegister(void) ;
void StatusClock_SetSourceRegister(uint8 clkSource) ;
uint8 StatusClock_GetSourceRegister(void) ;
#if defined(StatusClock__CFG3)
void StatusClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 StatusClock_GetPhaseRegister(void) ;
#endif /* defined(StatusClock__CFG3) */

#define StatusClock_Enable()                       StatusClock_Start()
#define StatusClock_Disable()                      StatusClock_Stop()
#define StatusClock_SetDivider(clkDivider)         StatusClock_SetDividerRegister(clkDivider, 1u)
#define StatusClock_SetDividerValue(clkDivider)    StatusClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define StatusClock_SetMode(clkMode)               StatusClock_SetModeRegister(clkMode)
#define StatusClock_SetSource(clkSource)           StatusClock_SetSourceRegister(clkSource)
#if defined(StatusClock__CFG3)
#define StatusClock_SetPhase(clkPhase)             StatusClock_SetPhaseRegister(clkPhase)
#define StatusClock_SetPhaseValue(clkPhase)        StatusClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(StatusClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define StatusClock_CLKEN              (* (reg8 *) StatusClock__PM_ACT_CFG)
#define StatusClock_CLKEN_PTR          ((reg8 *) StatusClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define StatusClock_CLKSTBY            (* (reg8 *) StatusClock__PM_STBY_CFG)
#define StatusClock_CLKSTBY_PTR        ((reg8 *) StatusClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define StatusClock_DIV_LSB            (* (reg8 *) StatusClock__CFG0)
#define StatusClock_DIV_LSB_PTR        ((reg8 *) StatusClock__CFG0)
#define StatusClock_DIV_PTR            ((reg16 *) StatusClock__CFG0)

/* Clock MSB divider configuration register. */
#define StatusClock_DIV_MSB            (* (reg8 *) StatusClock__CFG1)
#define StatusClock_DIV_MSB_PTR        ((reg8 *) StatusClock__CFG1)

/* Mode and source configuration register */
#define StatusClock_MOD_SRC            (* (reg8 *) StatusClock__CFG2)
#define StatusClock_MOD_SRC_PTR        ((reg8 *) StatusClock__CFG2)

#if defined(StatusClock__CFG3)
/* Analog clock phase configuration register */
#define StatusClock_PHASE              (* (reg8 *) StatusClock__CFG3)
#define StatusClock_PHASE_PTR          ((reg8 *) StatusClock__CFG3)
#endif /* defined(StatusClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define StatusClock_CLKEN_MASK         StatusClock__PM_ACT_MSK
#define StatusClock_CLKSTBY_MASK       StatusClock__PM_STBY_MSK

/* CFG2 field masks */
#define StatusClock_SRC_SEL_MSK        StatusClock__CFG2_SRC_SEL_MASK
#define StatusClock_MODE_MASK          (~(StatusClock_SRC_SEL_MSK))

#if defined(StatusClock__CFG3)
/* CFG3 phase mask */
#define StatusClock_PHASE_MASK         StatusClock__CFG3_PHASE_DLY_MASK
#endif /* defined(StatusClock__CFG3) */

#endif /* CY_CLOCK_StatusClock_H */


/* [] END OF FILE */
