/*******************************************************************************
* File Name: RadioRebroadcast_EN.h  
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

#if !defined(CY_PINS_RadioRebroadcast_EN_H) /* Pins RadioRebroadcast_EN_H */
#define CY_PINS_RadioRebroadcast_EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RadioRebroadcast_EN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RadioRebroadcast_EN__PORT == 15 && ((RadioRebroadcast_EN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RadioRebroadcast_EN_Write(uint8 value);
void    RadioRebroadcast_EN_SetDriveMode(uint8 mode);
uint8   RadioRebroadcast_EN_ReadDataReg(void);
uint8   RadioRebroadcast_EN_Read(void);
void    RadioRebroadcast_EN_SetInterruptMode(uint16 position, uint16 mode);
uint8   RadioRebroadcast_EN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RadioRebroadcast_EN_SetDriveMode() function.
     *  @{
     */
        #define RadioRebroadcast_EN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RadioRebroadcast_EN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RadioRebroadcast_EN_DM_RES_UP          PIN_DM_RES_UP
        #define RadioRebroadcast_EN_DM_RES_DWN         PIN_DM_RES_DWN
        #define RadioRebroadcast_EN_DM_OD_LO           PIN_DM_OD_LO
        #define RadioRebroadcast_EN_DM_OD_HI           PIN_DM_OD_HI
        #define RadioRebroadcast_EN_DM_STRONG          PIN_DM_STRONG
        #define RadioRebroadcast_EN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RadioRebroadcast_EN_MASK               RadioRebroadcast_EN__MASK
#define RadioRebroadcast_EN_SHIFT              RadioRebroadcast_EN__SHIFT
#define RadioRebroadcast_EN_WIDTH              1u

/* Interrupt constants */
#if defined(RadioRebroadcast_EN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RadioRebroadcast_EN_SetInterruptMode() function.
     *  @{
     */
        #define RadioRebroadcast_EN_INTR_NONE      (uint16)(0x0000u)
        #define RadioRebroadcast_EN_INTR_RISING    (uint16)(0x0001u)
        #define RadioRebroadcast_EN_INTR_FALLING   (uint16)(0x0002u)
        #define RadioRebroadcast_EN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RadioRebroadcast_EN_INTR_MASK      (0x01u) 
#endif /* (RadioRebroadcast_EN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RadioRebroadcast_EN_PS                     (* (reg8 *) RadioRebroadcast_EN__PS)
/* Data Register */
#define RadioRebroadcast_EN_DR                     (* (reg8 *) RadioRebroadcast_EN__DR)
/* Port Number */
#define RadioRebroadcast_EN_PRT_NUM                (* (reg8 *) RadioRebroadcast_EN__PRT) 
/* Connect to Analog Globals */                                                  
#define RadioRebroadcast_EN_AG                     (* (reg8 *) RadioRebroadcast_EN__AG)                       
/* Analog MUX bux enable */
#define RadioRebroadcast_EN_AMUX                   (* (reg8 *) RadioRebroadcast_EN__AMUX) 
/* Bidirectional Enable */                                                        
#define RadioRebroadcast_EN_BIE                    (* (reg8 *) RadioRebroadcast_EN__BIE)
/* Bit-mask for Aliased Register Access */
#define RadioRebroadcast_EN_BIT_MASK               (* (reg8 *) RadioRebroadcast_EN__BIT_MASK)
/* Bypass Enable */
#define RadioRebroadcast_EN_BYP                    (* (reg8 *) RadioRebroadcast_EN__BYP)
/* Port wide control signals */                                                   
#define RadioRebroadcast_EN_CTL                    (* (reg8 *) RadioRebroadcast_EN__CTL)
/* Drive Modes */
#define RadioRebroadcast_EN_DM0                    (* (reg8 *) RadioRebroadcast_EN__DM0) 
#define RadioRebroadcast_EN_DM1                    (* (reg8 *) RadioRebroadcast_EN__DM1)
#define RadioRebroadcast_EN_DM2                    (* (reg8 *) RadioRebroadcast_EN__DM2) 
/* Input Buffer Disable Override */
#define RadioRebroadcast_EN_INP_DIS                (* (reg8 *) RadioRebroadcast_EN__INP_DIS)
/* LCD Common or Segment Drive */
#define RadioRebroadcast_EN_LCD_COM_SEG            (* (reg8 *) RadioRebroadcast_EN__LCD_COM_SEG)
/* Enable Segment LCD */
#define RadioRebroadcast_EN_LCD_EN                 (* (reg8 *) RadioRebroadcast_EN__LCD_EN)
/* Slew Rate Control */
#define RadioRebroadcast_EN_SLW                    (* (reg8 *) RadioRebroadcast_EN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RadioRebroadcast_EN_PRTDSI__CAPS_SEL       (* (reg8 *) RadioRebroadcast_EN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RadioRebroadcast_EN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RadioRebroadcast_EN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RadioRebroadcast_EN_PRTDSI__OE_SEL0        (* (reg8 *) RadioRebroadcast_EN__PRTDSI__OE_SEL0) 
#define RadioRebroadcast_EN_PRTDSI__OE_SEL1        (* (reg8 *) RadioRebroadcast_EN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RadioRebroadcast_EN_PRTDSI__OUT_SEL0       (* (reg8 *) RadioRebroadcast_EN__PRTDSI__OUT_SEL0) 
#define RadioRebroadcast_EN_PRTDSI__OUT_SEL1       (* (reg8 *) RadioRebroadcast_EN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RadioRebroadcast_EN_PRTDSI__SYNC_OUT       (* (reg8 *) RadioRebroadcast_EN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RadioRebroadcast_EN__SIO_CFG)
    #define RadioRebroadcast_EN_SIO_HYST_EN        (* (reg8 *) RadioRebroadcast_EN__SIO_HYST_EN)
    #define RadioRebroadcast_EN_SIO_REG_HIFREQ     (* (reg8 *) RadioRebroadcast_EN__SIO_REG_HIFREQ)
    #define RadioRebroadcast_EN_SIO_CFG            (* (reg8 *) RadioRebroadcast_EN__SIO_CFG)
    #define RadioRebroadcast_EN_SIO_DIFF           (* (reg8 *) RadioRebroadcast_EN__SIO_DIFF)
#endif /* (RadioRebroadcast_EN__SIO_CFG) */

/* Interrupt Registers */
#if defined(RadioRebroadcast_EN__INTSTAT)
    #define RadioRebroadcast_EN_INTSTAT            (* (reg8 *) RadioRebroadcast_EN__INTSTAT)
    #define RadioRebroadcast_EN_SNAP               (* (reg8 *) RadioRebroadcast_EN__SNAP)
    
	#define RadioRebroadcast_EN_0_INTTYPE_REG 		(* (reg8 *) RadioRebroadcast_EN__0__INTTYPE)
#endif /* (RadioRebroadcast_EN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RadioRebroadcast_EN_H */


/* [] END OF FILE */
