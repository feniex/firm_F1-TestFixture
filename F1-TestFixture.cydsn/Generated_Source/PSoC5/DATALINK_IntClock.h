/*******************************************************************************
* File Name: DATALINK_IntClock.h
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

#if !defined(CY_CLOCK_DATALINK_IntClock_H)
#define CY_CLOCK_DATALINK_IntClock_H

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

void DATALINK_IntClock_Start(void) ;
void DATALINK_IntClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DATALINK_IntClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DATALINK_IntClock_StandbyPower(uint8 state) ;
void DATALINK_IntClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DATALINK_IntClock_GetDividerRegister(void) ;
void DATALINK_IntClock_SetModeRegister(uint8 modeBitMask) ;
void DATALINK_IntClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 DATALINK_IntClock_GetModeRegister(void) ;
void DATALINK_IntClock_SetSourceRegister(uint8 clkSource) ;
uint8 DATALINK_IntClock_GetSourceRegister(void) ;
#if defined(DATALINK_IntClock__CFG3)
void DATALINK_IntClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 DATALINK_IntClock_GetPhaseRegister(void) ;
#endif /* defined(DATALINK_IntClock__CFG3) */

#define DATALINK_IntClock_Enable()                       DATALINK_IntClock_Start()
#define DATALINK_IntClock_Disable()                      DATALINK_IntClock_Stop()
#define DATALINK_IntClock_SetDivider(clkDivider)         DATALINK_IntClock_SetDividerRegister(clkDivider, 1u)
#define DATALINK_IntClock_SetDividerValue(clkDivider)    DATALINK_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define DATALINK_IntClock_SetMode(clkMode)               DATALINK_IntClock_SetModeRegister(clkMode)
#define DATALINK_IntClock_SetSource(clkSource)           DATALINK_IntClock_SetSourceRegister(clkSource)
#if defined(DATALINK_IntClock__CFG3)
#define DATALINK_IntClock_SetPhase(clkPhase)             DATALINK_IntClock_SetPhaseRegister(clkPhase)
#define DATALINK_IntClock_SetPhaseValue(clkPhase)        DATALINK_IntClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DATALINK_IntClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DATALINK_IntClock_CLKEN              (* (reg8 *) DATALINK_IntClock__PM_ACT_CFG)
#define DATALINK_IntClock_CLKEN_PTR          ((reg8 *) DATALINK_IntClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DATALINK_IntClock_CLKSTBY            (* (reg8 *) DATALINK_IntClock__PM_STBY_CFG)
#define DATALINK_IntClock_CLKSTBY_PTR        ((reg8 *) DATALINK_IntClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DATALINK_IntClock_DIV_LSB            (* (reg8 *) DATALINK_IntClock__CFG0)
#define DATALINK_IntClock_DIV_LSB_PTR        ((reg8 *) DATALINK_IntClock__CFG0)
#define DATALINK_IntClock_DIV_PTR            ((reg16 *) DATALINK_IntClock__CFG0)

/* Clock MSB divider configuration register. */
#define DATALINK_IntClock_DIV_MSB            (* (reg8 *) DATALINK_IntClock__CFG1)
#define DATALINK_IntClock_DIV_MSB_PTR        ((reg8 *) DATALINK_IntClock__CFG1)

/* Mode and source configuration register */
#define DATALINK_IntClock_MOD_SRC            (* (reg8 *) DATALINK_IntClock__CFG2)
#define DATALINK_IntClock_MOD_SRC_PTR        ((reg8 *) DATALINK_IntClock__CFG2)

#if defined(DATALINK_IntClock__CFG3)
/* Analog clock phase configuration register */
#define DATALINK_IntClock_PHASE              (* (reg8 *) DATALINK_IntClock__CFG3)
#define DATALINK_IntClock_PHASE_PTR          ((reg8 *) DATALINK_IntClock__CFG3)
#endif /* defined(DATALINK_IntClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DATALINK_IntClock_CLKEN_MASK         DATALINK_IntClock__PM_ACT_MSK
#define DATALINK_IntClock_CLKSTBY_MASK       DATALINK_IntClock__PM_STBY_MSK

/* CFG2 field masks */
#define DATALINK_IntClock_SRC_SEL_MSK        DATALINK_IntClock__CFG2_SRC_SEL_MASK
#define DATALINK_IntClock_MODE_MASK          (~(DATALINK_IntClock_SRC_SEL_MSK))

#if defined(DATALINK_IntClock__CFG3)
/* CFG3 phase mask */
#define DATALINK_IntClock_PHASE_MASK         DATALINK_IntClock__CFG3_PHASE_DLY_MASK
#endif /* defined(DATALINK_IntClock__CFG3) */

#endif /* CY_CLOCK_DATALINK_IntClock_H */


/* [] END OF FILE */
