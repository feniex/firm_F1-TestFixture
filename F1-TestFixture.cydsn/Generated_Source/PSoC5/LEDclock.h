/*******************************************************************************
* File Name: LEDclock.h
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

#if !defined(CY_CLOCK_LEDclock_H)
#define CY_CLOCK_LEDclock_H

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

void LEDclock_Start(void) ;
void LEDclock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void LEDclock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void LEDclock_StandbyPower(uint8 state) ;
void LEDclock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 LEDclock_GetDividerRegister(void) ;
void LEDclock_SetModeRegister(uint8 modeBitMask) ;
void LEDclock_ClearModeRegister(uint8 modeBitMask) ;
uint8 LEDclock_GetModeRegister(void) ;
void LEDclock_SetSourceRegister(uint8 clkSource) ;
uint8 LEDclock_GetSourceRegister(void) ;
#if defined(LEDclock__CFG3)
void LEDclock_SetPhaseRegister(uint8 clkPhase) ;
uint8 LEDclock_GetPhaseRegister(void) ;
#endif /* defined(LEDclock__CFG3) */

#define LEDclock_Enable()                       LEDclock_Start()
#define LEDclock_Disable()                      LEDclock_Stop()
#define LEDclock_SetDivider(clkDivider)         LEDclock_SetDividerRegister(clkDivider, 1u)
#define LEDclock_SetDividerValue(clkDivider)    LEDclock_SetDividerRegister((clkDivider) - 1u, 1u)
#define LEDclock_SetMode(clkMode)               LEDclock_SetModeRegister(clkMode)
#define LEDclock_SetSource(clkSource)           LEDclock_SetSourceRegister(clkSource)
#if defined(LEDclock__CFG3)
#define LEDclock_SetPhase(clkPhase)             LEDclock_SetPhaseRegister(clkPhase)
#define LEDclock_SetPhaseValue(clkPhase)        LEDclock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(LEDclock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LEDclock_CLKEN              (* (reg8 *) LEDclock__PM_ACT_CFG)
#define LEDclock_CLKEN_PTR          ((reg8 *) LEDclock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LEDclock_CLKSTBY            (* (reg8 *) LEDclock__PM_STBY_CFG)
#define LEDclock_CLKSTBY_PTR        ((reg8 *) LEDclock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LEDclock_DIV_LSB            (* (reg8 *) LEDclock__CFG0)
#define LEDclock_DIV_LSB_PTR        ((reg8 *) LEDclock__CFG0)
#define LEDclock_DIV_PTR            ((reg16 *) LEDclock__CFG0)

/* Clock MSB divider configuration register. */
#define LEDclock_DIV_MSB            (* (reg8 *) LEDclock__CFG1)
#define LEDclock_DIV_MSB_PTR        ((reg8 *) LEDclock__CFG1)

/* Mode and source configuration register */
#define LEDclock_MOD_SRC            (* (reg8 *) LEDclock__CFG2)
#define LEDclock_MOD_SRC_PTR        ((reg8 *) LEDclock__CFG2)

#if defined(LEDclock__CFG3)
/* Analog clock phase configuration register */
#define LEDclock_PHASE              (* (reg8 *) LEDclock__CFG3)
#define LEDclock_PHASE_PTR          ((reg8 *) LEDclock__CFG3)
#endif /* defined(LEDclock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LEDclock_CLKEN_MASK         LEDclock__PM_ACT_MSK
#define LEDclock_CLKSTBY_MASK       LEDclock__PM_STBY_MSK

/* CFG2 field masks */
#define LEDclock_SRC_SEL_MSK        LEDclock__CFG2_SRC_SEL_MASK
#define LEDclock_MODE_MASK          (~(LEDclock_SRC_SEL_MSK))

#if defined(LEDclock__CFG3)
/* CFG3 phase mask */
#define LEDclock_PHASE_MASK         LEDclock__CFG3_PHASE_DLY_MASK
#endif /* defined(LEDclock__CFG3) */

#endif /* CY_CLOCK_LEDclock_H */


/* [] END OF FILE */
