/*******************************************************************************
* File Name: PWMoutput1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PWMoutput1_H) /* Pins PWMoutput1_H */
#define CY_PINS_PWMoutput1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMoutput1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMoutput1__PORT == 15 && ((PWMoutput1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PWMoutput1_Write(uint8 value);
void    PWMoutput1_SetDriveMode(uint8 mode);
uint8   PWMoutput1_ReadDataReg(void);
uint8   PWMoutput1_Read(void);
void    PWMoutput1_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWMoutput1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PWMoutput1_SetDriveMode() function.
     *  @{
     */
        #define PWMoutput1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PWMoutput1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PWMoutput1_DM_RES_UP          PIN_DM_RES_UP
        #define PWMoutput1_DM_RES_DWN         PIN_DM_RES_DWN
        #define PWMoutput1_DM_OD_LO           PIN_DM_OD_LO
        #define PWMoutput1_DM_OD_HI           PIN_DM_OD_HI
        #define PWMoutput1_DM_STRONG          PIN_DM_STRONG
        #define PWMoutput1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PWMoutput1_MASK               PWMoutput1__MASK
#define PWMoutput1_SHIFT              PWMoutput1__SHIFT
#define PWMoutput1_WIDTH              1u

/* Interrupt constants */
#if defined(PWMoutput1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWMoutput1_SetInterruptMode() function.
     *  @{
     */
        #define PWMoutput1_INTR_NONE      (uint16)(0x0000u)
        #define PWMoutput1_INTR_RISING    (uint16)(0x0001u)
        #define PWMoutput1_INTR_FALLING   (uint16)(0x0002u)
        #define PWMoutput1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PWMoutput1_INTR_MASK      (0x01u) 
#endif /* (PWMoutput1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMoutput1_PS                     (* (reg8 *) PWMoutput1__PS)
/* Data Register */
#define PWMoutput1_DR                     (* (reg8 *) PWMoutput1__DR)
/* Port Number */
#define PWMoutput1_PRT_NUM                (* (reg8 *) PWMoutput1__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMoutput1_AG                     (* (reg8 *) PWMoutput1__AG)                       
/* Analog MUX bux enable */
#define PWMoutput1_AMUX                   (* (reg8 *) PWMoutput1__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMoutput1_BIE                    (* (reg8 *) PWMoutput1__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMoutput1_BIT_MASK               (* (reg8 *) PWMoutput1__BIT_MASK)
/* Bypass Enable */
#define PWMoutput1_BYP                    (* (reg8 *) PWMoutput1__BYP)
/* Port wide control signals */                                                   
#define PWMoutput1_CTL                    (* (reg8 *) PWMoutput1__CTL)
/* Drive Modes */
#define PWMoutput1_DM0                    (* (reg8 *) PWMoutput1__DM0) 
#define PWMoutput1_DM1                    (* (reg8 *) PWMoutput1__DM1)
#define PWMoutput1_DM2                    (* (reg8 *) PWMoutput1__DM2) 
/* Input Buffer Disable Override */
#define PWMoutput1_INP_DIS                (* (reg8 *) PWMoutput1__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMoutput1_LCD_COM_SEG            (* (reg8 *) PWMoutput1__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMoutput1_LCD_EN                 (* (reg8 *) PWMoutput1__LCD_EN)
/* Slew Rate Control */
#define PWMoutput1_SLW                    (* (reg8 *) PWMoutput1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMoutput1_PRTDSI__CAPS_SEL       (* (reg8 *) PWMoutput1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMoutput1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMoutput1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMoutput1_PRTDSI__OE_SEL0        (* (reg8 *) PWMoutput1__PRTDSI__OE_SEL0) 
#define PWMoutput1_PRTDSI__OE_SEL1        (* (reg8 *) PWMoutput1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMoutput1_PRTDSI__OUT_SEL0       (* (reg8 *) PWMoutput1__PRTDSI__OUT_SEL0) 
#define PWMoutput1_PRTDSI__OUT_SEL1       (* (reg8 *) PWMoutput1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMoutput1_PRTDSI__SYNC_OUT       (* (reg8 *) PWMoutput1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PWMoutput1__SIO_CFG)
    #define PWMoutput1_SIO_HYST_EN        (* (reg8 *) PWMoutput1__SIO_HYST_EN)
    #define PWMoutput1_SIO_REG_HIFREQ     (* (reg8 *) PWMoutput1__SIO_REG_HIFREQ)
    #define PWMoutput1_SIO_CFG            (* (reg8 *) PWMoutput1__SIO_CFG)
    #define PWMoutput1_SIO_DIFF           (* (reg8 *) PWMoutput1__SIO_DIFF)
#endif /* (PWMoutput1__SIO_CFG) */

/* Interrupt Registers */
#if defined(PWMoutput1__INTSTAT)
    #define PWMoutput1_INTSTAT            (* (reg8 *) PWMoutput1__INTSTAT)
    #define PWMoutput1_SNAP               (* (reg8 *) PWMoutput1__SNAP)
    
	#define PWMoutput1_0_INTTYPE_REG 		(* (reg8 *) PWMoutput1__0__INTTYPE)
#endif /* (PWMoutput1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMoutput1_H */


/* [] END OF FILE */
