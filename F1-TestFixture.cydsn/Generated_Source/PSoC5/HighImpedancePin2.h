/*******************************************************************************
* File Name: HighImpedancePin2.h  
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

#if !defined(CY_PINS_HighImpedancePin2_H) /* Pins HighImpedancePin2_H */
#define CY_PINS_HighImpedancePin2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighImpedancePin2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighImpedancePin2__PORT == 15 && ((HighImpedancePin2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighImpedancePin2_Write(uint8 value);
void    HighImpedancePin2_SetDriveMode(uint8 mode);
uint8   HighImpedancePin2_ReadDataReg(void);
uint8   HighImpedancePin2_Read(void);
void    HighImpedancePin2_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighImpedancePin2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighImpedancePin2_SetDriveMode() function.
     *  @{
     */
        #define HighImpedancePin2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighImpedancePin2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighImpedancePin2_DM_RES_UP          PIN_DM_RES_UP
        #define HighImpedancePin2_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighImpedancePin2_DM_OD_LO           PIN_DM_OD_LO
        #define HighImpedancePin2_DM_OD_HI           PIN_DM_OD_HI
        #define HighImpedancePin2_DM_STRONG          PIN_DM_STRONG
        #define HighImpedancePin2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighImpedancePin2_MASK               HighImpedancePin2__MASK
#define HighImpedancePin2_SHIFT              HighImpedancePin2__SHIFT
#define HighImpedancePin2_WIDTH              1u

/* Interrupt constants */
#if defined(HighImpedancePin2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighImpedancePin2_SetInterruptMode() function.
     *  @{
     */
        #define HighImpedancePin2_INTR_NONE      (uint16)(0x0000u)
        #define HighImpedancePin2_INTR_RISING    (uint16)(0x0001u)
        #define HighImpedancePin2_INTR_FALLING   (uint16)(0x0002u)
        #define HighImpedancePin2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighImpedancePin2_INTR_MASK      (0x01u) 
#endif /* (HighImpedancePin2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighImpedancePin2_PS                     (* (reg8 *) HighImpedancePin2__PS)
/* Data Register */
#define HighImpedancePin2_DR                     (* (reg8 *) HighImpedancePin2__DR)
/* Port Number */
#define HighImpedancePin2_PRT_NUM                (* (reg8 *) HighImpedancePin2__PRT) 
/* Connect to Analog Globals */                                                  
#define HighImpedancePin2_AG                     (* (reg8 *) HighImpedancePin2__AG)                       
/* Analog MUX bux enable */
#define HighImpedancePin2_AMUX                   (* (reg8 *) HighImpedancePin2__AMUX) 
/* Bidirectional Enable */                                                        
#define HighImpedancePin2_BIE                    (* (reg8 *) HighImpedancePin2__BIE)
/* Bit-mask for Aliased Register Access */
#define HighImpedancePin2_BIT_MASK               (* (reg8 *) HighImpedancePin2__BIT_MASK)
/* Bypass Enable */
#define HighImpedancePin2_BYP                    (* (reg8 *) HighImpedancePin2__BYP)
/* Port wide control signals */                                                   
#define HighImpedancePin2_CTL                    (* (reg8 *) HighImpedancePin2__CTL)
/* Drive Modes */
#define HighImpedancePin2_DM0                    (* (reg8 *) HighImpedancePin2__DM0) 
#define HighImpedancePin2_DM1                    (* (reg8 *) HighImpedancePin2__DM1)
#define HighImpedancePin2_DM2                    (* (reg8 *) HighImpedancePin2__DM2) 
/* Input Buffer Disable Override */
#define HighImpedancePin2_INP_DIS                (* (reg8 *) HighImpedancePin2__INP_DIS)
/* LCD Common or Segment Drive */
#define HighImpedancePin2_LCD_COM_SEG            (* (reg8 *) HighImpedancePin2__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighImpedancePin2_LCD_EN                 (* (reg8 *) HighImpedancePin2__LCD_EN)
/* Slew Rate Control */
#define HighImpedancePin2_SLW                    (* (reg8 *) HighImpedancePin2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighImpedancePin2_PRTDSI__CAPS_SEL       (* (reg8 *) HighImpedancePin2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighImpedancePin2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighImpedancePin2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighImpedancePin2_PRTDSI__OE_SEL0        (* (reg8 *) HighImpedancePin2__PRTDSI__OE_SEL0) 
#define HighImpedancePin2_PRTDSI__OE_SEL1        (* (reg8 *) HighImpedancePin2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighImpedancePin2_PRTDSI__OUT_SEL0       (* (reg8 *) HighImpedancePin2__PRTDSI__OUT_SEL0) 
#define HighImpedancePin2_PRTDSI__OUT_SEL1       (* (reg8 *) HighImpedancePin2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighImpedancePin2_PRTDSI__SYNC_OUT       (* (reg8 *) HighImpedancePin2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighImpedancePin2__SIO_CFG)
    #define HighImpedancePin2_SIO_HYST_EN        (* (reg8 *) HighImpedancePin2__SIO_HYST_EN)
    #define HighImpedancePin2_SIO_REG_HIFREQ     (* (reg8 *) HighImpedancePin2__SIO_REG_HIFREQ)
    #define HighImpedancePin2_SIO_CFG            (* (reg8 *) HighImpedancePin2__SIO_CFG)
    #define HighImpedancePin2_SIO_DIFF           (* (reg8 *) HighImpedancePin2__SIO_DIFF)
#endif /* (HighImpedancePin2__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighImpedancePin2__INTSTAT)
    #define HighImpedancePin2_INTSTAT            (* (reg8 *) HighImpedancePin2__INTSTAT)
    #define HighImpedancePin2_SNAP               (* (reg8 *) HighImpedancePin2__SNAP)
    
	#define HighImpedancePin2_0_INTTYPE_REG 		(* (reg8 *) HighImpedancePin2__0__INTTYPE)
#endif /* (HighImpedancePin2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighImpedancePin2_H */


/* [] END OF FILE */
