/*******************************************************************************
* File Name: RadioRebroadcastInput.h  
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

#if !defined(CY_PINS_RadioRebroadcastInput_H) /* Pins RadioRebroadcastInput_H */
#define CY_PINS_RadioRebroadcastInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RadioRebroadcastInput_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RadioRebroadcastInput__PORT == 15 && ((RadioRebroadcastInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RadioRebroadcastInput_Write(uint8 value);
void    RadioRebroadcastInput_SetDriveMode(uint8 mode);
uint8   RadioRebroadcastInput_ReadDataReg(void);
uint8   RadioRebroadcastInput_Read(void);
void    RadioRebroadcastInput_SetInterruptMode(uint16 position, uint16 mode);
uint8   RadioRebroadcastInput_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RadioRebroadcastInput_SetDriveMode() function.
     *  @{
     */
        #define RadioRebroadcastInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RadioRebroadcastInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RadioRebroadcastInput_DM_RES_UP          PIN_DM_RES_UP
        #define RadioRebroadcastInput_DM_RES_DWN         PIN_DM_RES_DWN
        #define RadioRebroadcastInput_DM_OD_LO           PIN_DM_OD_LO
        #define RadioRebroadcastInput_DM_OD_HI           PIN_DM_OD_HI
        #define RadioRebroadcastInput_DM_STRONG          PIN_DM_STRONG
        #define RadioRebroadcastInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RadioRebroadcastInput_MASK               RadioRebroadcastInput__MASK
#define RadioRebroadcastInput_SHIFT              RadioRebroadcastInput__SHIFT
#define RadioRebroadcastInput_WIDTH              1u

/* Interrupt constants */
#if defined(RadioRebroadcastInput__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RadioRebroadcastInput_SetInterruptMode() function.
     *  @{
     */
        #define RadioRebroadcastInput_INTR_NONE      (uint16)(0x0000u)
        #define RadioRebroadcastInput_INTR_RISING    (uint16)(0x0001u)
        #define RadioRebroadcastInput_INTR_FALLING   (uint16)(0x0002u)
        #define RadioRebroadcastInput_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RadioRebroadcastInput_INTR_MASK      (0x01u) 
#endif /* (RadioRebroadcastInput__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RadioRebroadcastInput_PS                     (* (reg8 *) RadioRebroadcastInput__PS)
/* Data Register */
#define RadioRebroadcastInput_DR                     (* (reg8 *) RadioRebroadcastInput__DR)
/* Port Number */
#define RadioRebroadcastInput_PRT_NUM                (* (reg8 *) RadioRebroadcastInput__PRT) 
/* Connect to Analog Globals */                                                  
#define RadioRebroadcastInput_AG                     (* (reg8 *) RadioRebroadcastInput__AG)                       
/* Analog MUX bux enable */
#define RadioRebroadcastInput_AMUX                   (* (reg8 *) RadioRebroadcastInput__AMUX) 
/* Bidirectional Enable */                                                        
#define RadioRebroadcastInput_BIE                    (* (reg8 *) RadioRebroadcastInput__BIE)
/* Bit-mask for Aliased Register Access */
#define RadioRebroadcastInput_BIT_MASK               (* (reg8 *) RadioRebroadcastInput__BIT_MASK)
/* Bypass Enable */
#define RadioRebroadcastInput_BYP                    (* (reg8 *) RadioRebroadcastInput__BYP)
/* Port wide control signals */                                                   
#define RadioRebroadcastInput_CTL                    (* (reg8 *) RadioRebroadcastInput__CTL)
/* Drive Modes */
#define RadioRebroadcastInput_DM0                    (* (reg8 *) RadioRebroadcastInput__DM0) 
#define RadioRebroadcastInput_DM1                    (* (reg8 *) RadioRebroadcastInput__DM1)
#define RadioRebroadcastInput_DM2                    (* (reg8 *) RadioRebroadcastInput__DM2) 
/* Input Buffer Disable Override */
#define RadioRebroadcastInput_INP_DIS                (* (reg8 *) RadioRebroadcastInput__INP_DIS)
/* LCD Common or Segment Drive */
#define RadioRebroadcastInput_LCD_COM_SEG            (* (reg8 *) RadioRebroadcastInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define RadioRebroadcastInput_LCD_EN                 (* (reg8 *) RadioRebroadcastInput__LCD_EN)
/* Slew Rate Control */
#define RadioRebroadcastInput_SLW                    (* (reg8 *) RadioRebroadcastInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RadioRebroadcastInput_PRTDSI__CAPS_SEL       (* (reg8 *) RadioRebroadcastInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RadioRebroadcastInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RadioRebroadcastInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RadioRebroadcastInput_PRTDSI__OE_SEL0        (* (reg8 *) RadioRebroadcastInput__PRTDSI__OE_SEL0) 
#define RadioRebroadcastInput_PRTDSI__OE_SEL1        (* (reg8 *) RadioRebroadcastInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RadioRebroadcastInput_PRTDSI__OUT_SEL0       (* (reg8 *) RadioRebroadcastInput__PRTDSI__OUT_SEL0) 
#define RadioRebroadcastInput_PRTDSI__OUT_SEL1       (* (reg8 *) RadioRebroadcastInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RadioRebroadcastInput_PRTDSI__SYNC_OUT       (* (reg8 *) RadioRebroadcastInput__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RadioRebroadcastInput__SIO_CFG)
    #define RadioRebroadcastInput_SIO_HYST_EN        (* (reg8 *) RadioRebroadcastInput__SIO_HYST_EN)
    #define RadioRebroadcastInput_SIO_REG_HIFREQ     (* (reg8 *) RadioRebroadcastInput__SIO_REG_HIFREQ)
    #define RadioRebroadcastInput_SIO_CFG            (* (reg8 *) RadioRebroadcastInput__SIO_CFG)
    #define RadioRebroadcastInput_SIO_DIFF           (* (reg8 *) RadioRebroadcastInput__SIO_DIFF)
#endif /* (RadioRebroadcastInput__SIO_CFG) */

/* Interrupt Registers */
#if defined(RadioRebroadcastInput__INTSTAT)
    #define RadioRebroadcastInput_INTSTAT            (* (reg8 *) RadioRebroadcastInput__INTSTAT)
    #define RadioRebroadcastInput_SNAP               (* (reg8 *) RadioRebroadcastInput__SNAP)
    
	#define RadioRebroadcastInput_0_INTTYPE_REG 		(* (reg8 *) RadioRebroadcastInput__0__INTTYPE)
#endif /* (RadioRebroadcastInput__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RadioRebroadcastInput_H */


/* [] END OF FILE */
