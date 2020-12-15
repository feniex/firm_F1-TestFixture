/*******************************************************************************
* File Name: OverloadInput1.h  
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

#if !defined(CY_PINS_OverloadInput1_H) /* Pins OverloadInput1_H */
#define CY_PINS_OverloadInput1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OverloadInput1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OverloadInput1__PORT == 15 && ((OverloadInput1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    OverloadInput1_Write(uint8 value);
void    OverloadInput1_SetDriveMode(uint8 mode);
uint8   OverloadInput1_ReadDataReg(void);
uint8   OverloadInput1_Read(void);
void    OverloadInput1_SetInterruptMode(uint16 position, uint16 mode);
uint8   OverloadInput1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the OverloadInput1_SetDriveMode() function.
     *  @{
     */
        #define OverloadInput1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define OverloadInput1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define OverloadInput1_DM_RES_UP          PIN_DM_RES_UP
        #define OverloadInput1_DM_RES_DWN         PIN_DM_RES_DWN
        #define OverloadInput1_DM_OD_LO           PIN_DM_OD_LO
        #define OverloadInput1_DM_OD_HI           PIN_DM_OD_HI
        #define OverloadInput1_DM_STRONG          PIN_DM_STRONG
        #define OverloadInput1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define OverloadInput1_MASK               OverloadInput1__MASK
#define OverloadInput1_SHIFT              OverloadInput1__SHIFT
#define OverloadInput1_WIDTH              1u

/* Interrupt constants */
#if defined(OverloadInput1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OverloadInput1_SetInterruptMode() function.
     *  @{
     */
        #define OverloadInput1_INTR_NONE      (uint16)(0x0000u)
        #define OverloadInput1_INTR_RISING    (uint16)(0x0001u)
        #define OverloadInput1_INTR_FALLING   (uint16)(0x0002u)
        #define OverloadInput1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define OverloadInput1_INTR_MASK      (0x01u) 
#endif /* (OverloadInput1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OverloadInput1_PS                     (* (reg8 *) OverloadInput1__PS)
/* Data Register */
#define OverloadInput1_DR                     (* (reg8 *) OverloadInput1__DR)
/* Port Number */
#define OverloadInput1_PRT_NUM                (* (reg8 *) OverloadInput1__PRT) 
/* Connect to Analog Globals */                                                  
#define OverloadInput1_AG                     (* (reg8 *) OverloadInput1__AG)                       
/* Analog MUX bux enable */
#define OverloadInput1_AMUX                   (* (reg8 *) OverloadInput1__AMUX) 
/* Bidirectional Enable */                                                        
#define OverloadInput1_BIE                    (* (reg8 *) OverloadInput1__BIE)
/* Bit-mask for Aliased Register Access */
#define OverloadInput1_BIT_MASK               (* (reg8 *) OverloadInput1__BIT_MASK)
/* Bypass Enable */
#define OverloadInput1_BYP                    (* (reg8 *) OverloadInput1__BYP)
/* Port wide control signals */                                                   
#define OverloadInput1_CTL                    (* (reg8 *) OverloadInput1__CTL)
/* Drive Modes */
#define OverloadInput1_DM0                    (* (reg8 *) OverloadInput1__DM0) 
#define OverloadInput1_DM1                    (* (reg8 *) OverloadInput1__DM1)
#define OverloadInput1_DM2                    (* (reg8 *) OverloadInput1__DM2) 
/* Input Buffer Disable Override */
#define OverloadInput1_INP_DIS                (* (reg8 *) OverloadInput1__INP_DIS)
/* LCD Common or Segment Drive */
#define OverloadInput1_LCD_COM_SEG            (* (reg8 *) OverloadInput1__LCD_COM_SEG)
/* Enable Segment LCD */
#define OverloadInput1_LCD_EN                 (* (reg8 *) OverloadInput1__LCD_EN)
/* Slew Rate Control */
#define OverloadInput1_SLW                    (* (reg8 *) OverloadInput1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OverloadInput1_PRTDSI__CAPS_SEL       (* (reg8 *) OverloadInput1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OverloadInput1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OverloadInput1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OverloadInput1_PRTDSI__OE_SEL0        (* (reg8 *) OverloadInput1__PRTDSI__OE_SEL0) 
#define OverloadInput1_PRTDSI__OE_SEL1        (* (reg8 *) OverloadInput1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OverloadInput1_PRTDSI__OUT_SEL0       (* (reg8 *) OverloadInput1__PRTDSI__OUT_SEL0) 
#define OverloadInput1_PRTDSI__OUT_SEL1       (* (reg8 *) OverloadInput1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OverloadInput1_PRTDSI__SYNC_OUT       (* (reg8 *) OverloadInput1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(OverloadInput1__SIO_CFG)
    #define OverloadInput1_SIO_HYST_EN        (* (reg8 *) OverloadInput1__SIO_HYST_EN)
    #define OverloadInput1_SIO_REG_HIFREQ     (* (reg8 *) OverloadInput1__SIO_REG_HIFREQ)
    #define OverloadInput1_SIO_CFG            (* (reg8 *) OverloadInput1__SIO_CFG)
    #define OverloadInput1_SIO_DIFF           (* (reg8 *) OverloadInput1__SIO_DIFF)
#endif /* (OverloadInput1__SIO_CFG) */

/* Interrupt Registers */
#if defined(OverloadInput1__INTSTAT)
    #define OverloadInput1_INTSTAT            (* (reg8 *) OverloadInput1__INTSTAT)
    #define OverloadInput1_SNAP               (* (reg8 *) OverloadInput1__SNAP)
    
	#define OverloadInput1_0_INTTYPE_REG 		(* (reg8 *) OverloadInput1__0__INTTYPE)
#endif /* (OverloadInput1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OverloadInput1_H */


/* [] END OF FILE */
