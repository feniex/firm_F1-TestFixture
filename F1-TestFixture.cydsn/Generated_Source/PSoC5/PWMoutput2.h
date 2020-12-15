/*******************************************************************************
* File Name: PWMoutput2.h  
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

#if !defined(CY_PINS_PWMoutput2_H) /* Pins PWMoutput2_H */
#define CY_PINS_PWMoutput2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMoutput2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMoutput2__PORT == 15 && ((PWMoutput2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PWMoutput2_Write(uint8 value);
void    PWMoutput2_SetDriveMode(uint8 mode);
uint8   PWMoutput2_ReadDataReg(void);
uint8   PWMoutput2_Read(void);
void    PWMoutput2_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWMoutput2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PWMoutput2_SetDriveMode() function.
     *  @{
     */
        #define PWMoutput2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PWMoutput2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PWMoutput2_DM_RES_UP          PIN_DM_RES_UP
        #define PWMoutput2_DM_RES_DWN         PIN_DM_RES_DWN
        #define PWMoutput2_DM_OD_LO           PIN_DM_OD_LO
        #define PWMoutput2_DM_OD_HI           PIN_DM_OD_HI
        #define PWMoutput2_DM_STRONG          PIN_DM_STRONG
        #define PWMoutput2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PWMoutput2_MASK               PWMoutput2__MASK
#define PWMoutput2_SHIFT              PWMoutput2__SHIFT
#define PWMoutput2_WIDTH              1u

/* Interrupt constants */
#if defined(PWMoutput2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWMoutput2_SetInterruptMode() function.
     *  @{
     */
        #define PWMoutput2_INTR_NONE      (uint16)(0x0000u)
        #define PWMoutput2_INTR_RISING    (uint16)(0x0001u)
        #define PWMoutput2_INTR_FALLING   (uint16)(0x0002u)
        #define PWMoutput2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PWMoutput2_INTR_MASK      (0x01u) 
#endif /* (PWMoutput2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMoutput2_PS                     (* (reg8 *) PWMoutput2__PS)
/* Data Register */
#define PWMoutput2_DR                     (* (reg8 *) PWMoutput2__DR)
/* Port Number */
#define PWMoutput2_PRT_NUM                (* (reg8 *) PWMoutput2__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMoutput2_AG                     (* (reg8 *) PWMoutput2__AG)                       
/* Analog MUX bux enable */
#define PWMoutput2_AMUX                   (* (reg8 *) PWMoutput2__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMoutput2_BIE                    (* (reg8 *) PWMoutput2__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMoutput2_BIT_MASK               (* (reg8 *) PWMoutput2__BIT_MASK)
/* Bypass Enable */
#define PWMoutput2_BYP                    (* (reg8 *) PWMoutput2__BYP)
/* Port wide control signals */                                                   
#define PWMoutput2_CTL                    (* (reg8 *) PWMoutput2__CTL)
/* Drive Modes */
#define PWMoutput2_DM0                    (* (reg8 *) PWMoutput2__DM0) 
#define PWMoutput2_DM1                    (* (reg8 *) PWMoutput2__DM1)
#define PWMoutput2_DM2                    (* (reg8 *) PWMoutput2__DM2) 
/* Input Buffer Disable Override */
#define PWMoutput2_INP_DIS                (* (reg8 *) PWMoutput2__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMoutput2_LCD_COM_SEG            (* (reg8 *) PWMoutput2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMoutput2_LCD_EN                 (* (reg8 *) PWMoutput2__LCD_EN)
/* Slew Rate Control */
#define PWMoutput2_SLW                    (* (reg8 *) PWMoutput2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMoutput2_PRTDSI__CAPS_SEL       (* (reg8 *) PWMoutput2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMoutput2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMoutput2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMoutput2_PRTDSI__OE_SEL0        (* (reg8 *) PWMoutput2__PRTDSI__OE_SEL0) 
#define PWMoutput2_PRTDSI__OE_SEL1        (* (reg8 *) PWMoutput2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMoutput2_PRTDSI__OUT_SEL0       (* (reg8 *) PWMoutput2__PRTDSI__OUT_SEL0) 
#define PWMoutput2_PRTDSI__OUT_SEL1       (* (reg8 *) PWMoutput2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMoutput2_PRTDSI__SYNC_OUT       (* (reg8 *) PWMoutput2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PWMoutput2__SIO_CFG)
    #define PWMoutput2_SIO_HYST_EN        (* (reg8 *) PWMoutput2__SIO_HYST_EN)
    #define PWMoutput2_SIO_REG_HIFREQ     (* (reg8 *) PWMoutput2__SIO_REG_HIFREQ)
    #define PWMoutput2_SIO_CFG            (* (reg8 *) PWMoutput2__SIO_CFG)
    #define PWMoutput2_SIO_DIFF           (* (reg8 *) PWMoutput2__SIO_DIFF)
#endif /* (PWMoutput2__SIO_CFG) */

/* Interrupt Registers */
#if defined(PWMoutput2__INTSTAT)
    #define PWMoutput2_INTSTAT            (* (reg8 *) PWMoutput2__INTSTAT)
    #define PWMoutput2_SNAP               (* (reg8 *) PWMoutput2__SNAP)
    
	#define PWMoutput2_0_INTTYPE_REG 		(* (reg8 *) PWMoutput2__0__INTTYPE)
#endif /* (PWMoutput2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMoutput2_H */


/* [] END OF FILE */
