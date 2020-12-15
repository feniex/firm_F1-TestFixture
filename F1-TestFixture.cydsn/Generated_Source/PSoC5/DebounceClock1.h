/*******************************************************************************
* File Name: DebounceClock1.h
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

#if !defined(CY_CLOCK_DebounceClock1_H)
#define CY_CLOCK_DebounceClock1_H

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

void DebounceClock1_Start(void) ;
void DebounceClock1_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DebounceClock1_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DebounceClock1_StandbyPower(uint8 state) ;
void DebounceClock1_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DebounceClock1_GetDividerRegister(void) ;
void DebounceClock1_SetModeRegister(uint8 modeBitMask) ;
void DebounceClock1_ClearModeRegister(uint8 modeBitMask) ;
uint8 DebounceClock1_GetModeRegister(void) ;
void DebounceClock1_SetSourceRegister(uint8 clkSource) ;
uint8 DebounceClock1_GetSourceRegister(void) ;
#if defined(DebounceClock1__CFG3)
void DebounceClock1_SetPhaseRegister(uint8 clkPhase) ;
uint8 DebounceClock1_GetPhaseRegister(void) ;
#endif /* defined(DebounceClock1__CFG3) */

#define DebounceClock1_Enable()                       DebounceClock1_Start()
#define DebounceClock1_Disable()                      DebounceClock1_Stop()
#define DebounceClock1_SetDivider(clkDivider)         DebounceClock1_SetDividerRegister(clkDivider, 1u)
#define DebounceClock1_SetDividerValue(clkDivider)    DebounceClock1_SetDividerRegister((clkDivider) - 1u, 1u)
#define DebounceClock1_SetMode(clkMode)               DebounceClock1_SetModeRegister(clkMode)
#define DebounceClock1_SetSource(clkSource)           DebounceClock1_SetSourceRegister(clkSource)
#if defined(DebounceClock1__CFG3)
#define DebounceClock1_SetPhase(clkPhase)             DebounceClock1_SetPhaseRegister(clkPhase)
#define DebounceClock1_SetPhaseValue(clkPhase)        DebounceClock1_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DebounceClock1__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DebounceClock1_CLKEN              (* (reg8 *) DebounceClock1__PM_ACT_CFG)
#define DebounceClock1_CLKEN_PTR          ((reg8 *) DebounceClock1__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DebounceClock1_CLKSTBY            (* (reg8 *) DebounceClock1__PM_STBY_CFG)
#define DebounceClock1_CLKSTBY_PTR        ((reg8 *) DebounceClock1__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DebounceClock1_DIV_LSB            (* (reg8 *) DebounceClock1__CFG0)
#define DebounceClock1_DIV_LSB_PTR        ((reg8 *) DebounceClock1__CFG0)
#define DebounceClock1_DIV_PTR            ((reg16 *) DebounceClock1__CFG0)

/* Clock MSB divider configuration register. */
#define DebounceClock1_DIV_MSB            (* (reg8 *) DebounceClock1__CFG1)
#define DebounceClock1_DIV_MSB_PTR        ((reg8 *) DebounceClock1__CFG1)

/* Mode and source configuration register */
#define DebounceClock1_MOD_SRC            (* (reg8 *) DebounceClock1__CFG2)
#define DebounceClock1_MOD_SRC_PTR        ((reg8 *) DebounceClock1__CFG2)

#if defined(DebounceClock1__CFG3)
/* Analog clock phase configuration register */
#define DebounceClock1_PHASE              (* (reg8 *) DebounceClock1__CFG3)
#define DebounceClock1_PHASE_PTR          ((reg8 *) DebounceClock1__CFG3)
#endif /* defined(DebounceClock1__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DebounceClock1_CLKEN_MASK         DebounceClock1__PM_ACT_MSK
#define DebounceClock1_CLKSTBY_MASK       DebounceClock1__PM_STBY_MSK

/* CFG2 field masks */
#define DebounceClock1_SRC_SEL_MSK        DebounceClock1__CFG2_SRC_SEL_MASK
#define DebounceClock1_MODE_MASK          (~(DebounceClock1_SRC_SEL_MSK))

#if defined(DebounceClock1__CFG3)
/* CFG3 phase mask */
#define DebounceClock1_PHASE_MASK         DebounceClock1__CFG3_PHASE_DLY_MASK
#endif /* defined(DebounceClock1__CFG3) */

#endif /* CY_CLOCK_DebounceClock1_H */


/* [] END OF FILE */
