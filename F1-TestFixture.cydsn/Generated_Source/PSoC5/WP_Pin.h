/*******************************************************************************
* File Name: WP_Pin.h  
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

#if !defined(CY_PINS_WP_Pin_H) /* Pins WP_Pin_H */
#define CY_PINS_WP_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WP_Pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WP_Pin__PORT == 15 && ((WP_Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WP_Pin_Write(uint8 value);
void    WP_Pin_SetDriveMode(uint8 mode);
uint8   WP_Pin_ReadDataReg(void);
uint8   WP_Pin_Read(void);
void    WP_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   WP_Pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WP_Pin_SetDriveMode() function.
     *  @{
     */
        #define WP_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WP_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WP_Pin_DM_RES_UP          PIN_DM_RES_UP
        #define WP_Pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define WP_Pin_DM_OD_LO           PIN_DM_OD_LO
        #define WP_Pin_DM_OD_HI           PIN_DM_OD_HI
        #define WP_Pin_DM_STRONG          PIN_DM_STRONG
        #define WP_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WP_Pin_MASK               WP_Pin__MASK
#define WP_Pin_SHIFT              WP_Pin__SHIFT
#define WP_Pin_WIDTH              1u

/* Interrupt constants */
#if defined(WP_Pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WP_Pin_SetInterruptMode() function.
     *  @{
     */
        #define WP_Pin_INTR_NONE      (uint16)(0x0000u)
        #define WP_Pin_INTR_RISING    (uint16)(0x0001u)
        #define WP_Pin_INTR_FALLING   (uint16)(0x0002u)
        #define WP_Pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WP_Pin_INTR_MASK      (0x01u) 
#endif /* (WP_Pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WP_Pin_PS                     (* (reg8 *) WP_Pin__PS)
/* Data Register */
#define WP_Pin_DR                     (* (reg8 *) WP_Pin__DR)
/* Port Number */
#define WP_Pin_PRT_NUM                (* (reg8 *) WP_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define WP_Pin_AG                     (* (reg8 *) WP_Pin__AG)                       
/* Analog MUX bux enable */
#define WP_Pin_AMUX                   (* (reg8 *) WP_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define WP_Pin_BIE                    (* (reg8 *) WP_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define WP_Pin_BIT_MASK               (* (reg8 *) WP_Pin__BIT_MASK)
/* Bypass Enable */
#define WP_Pin_BYP                    (* (reg8 *) WP_Pin__BYP)
/* Port wide control signals */                                                   
#define WP_Pin_CTL                    (* (reg8 *) WP_Pin__CTL)
/* Drive Modes */
#define WP_Pin_DM0                    (* (reg8 *) WP_Pin__DM0) 
#define WP_Pin_DM1                    (* (reg8 *) WP_Pin__DM1)
#define WP_Pin_DM2                    (* (reg8 *) WP_Pin__DM2) 
/* Input Buffer Disable Override */
#define WP_Pin_INP_DIS                (* (reg8 *) WP_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define WP_Pin_LCD_COM_SEG            (* (reg8 *) WP_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define WP_Pin_LCD_EN                 (* (reg8 *) WP_Pin__LCD_EN)
/* Slew Rate Control */
#define WP_Pin_SLW                    (* (reg8 *) WP_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WP_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) WP_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WP_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WP_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WP_Pin_PRTDSI__OE_SEL0        (* (reg8 *) WP_Pin__PRTDSI__OE_SEL0) 
#define WP_Pin_PRTDSI__OE_SEL1        (* (reg8 *) WP_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WP_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) WP_Pin__PRTDSI__OUT_SEL0) 
#define WP_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) WP_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WP_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) WP_Pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WP_Pin__SIO_CFG)
    #define WP_Pin_SIO_HYST_EN        (* (reg8 *) WP_Pin__SIO_HYST_EN)
    #define WP_Pin_SIO_REG_HIFREQ     (* (reg8 *) WP_Pin__SIO_REG_HIFREQ)
    #define WP_Pin_SIO_CFG            (* (reg8 *) WP_Pin__SIO_CFG)
    #define WP_Pin_SIO_DIFF           (* (reg8 *) WP_Pin__SIO_DIFF)
#endif /* (WP_Pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(WP_Pin__INTSTAT)
    #define WP_Pin_INTSTAT            (* (reg8 *) WP_Pin__INTSTAT)
    #define WP_Pin_SNAP               (* (reg8 *) WP_Pin__SNAP)
    
	#define WP_Pin_0_INTTYPE_REG 		(* (reg8 *) WP_Pin__0__INTTYPE)
#endif /* (WP_Pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WP_Pin_H */


/* [] END OF FILE */
