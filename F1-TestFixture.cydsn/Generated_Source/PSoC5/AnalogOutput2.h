/*******************************************************************************
* File Name: AnalogOutput2.h  
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

#if !defined(CY_PINS_AnalogOutput2_H) /* Pins AnalogOutput2_H */
#define CY_PINS_AnalogOutput2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AnalogOutput2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AnalogOutput2__PORT == 15 && ((AnalogOutput2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AnalogOutput2_Write(uint8 value);
void    AnalogOutput2_SetDriveMode(uint8 mode);
uint8   AnalogOutput2_ReadDataReg(void);
uint8   AnalogOutput2_Read(void);
void    AnalogOutput2_SetInterruptMode(uint16 position, uint16 mode);
uint8   AnalogOutput2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AnalogOutput2_SetDriveMode() function.
     *  @{
     */
        #define AnalogOutput2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AnalogOutput2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AnalogOutput2_DM_RES_UP          PIN_DM_RES_UP
        #define AnalogOutput2_DM_RES_DWN         PIN_DM_RES_DWN
        #define AnalogOutput2_DM_OD_LO           PIN_DM_OD_LO
        #define AnalogOutput2_DM_OD_HI           PIN_DM_OD_HI
        #define AnalogOutput2_DM_STRONG          PIN_DM_STRONG
        #define AnalogOutput2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AnalogOutput2_MASK               AnalogOutput2__MASK
#define AnalogOutput2_SHIFT              AnalogOutput2__SHIFT
#define AnalogOutput2_WIDTH              1u

/* Interrupt constants */
#if defined(AnalogOutput2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AnalogOutput2_SetInterruptMode() function.
     *  @{
     */
        #define AnalogOutput2_INTR_NONE      (uint16)(0x0000u)
        #define AnalogOutput2_INTR_RISING    (uint16)(0x0001u)
        #define AnalogOutput2_INTR_FALLING   (uint16)(0x0002u)
        #define AnalogOutput2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AnalogOutput2_INTR_MASK      (0x01u) 
#endif /* (AnalogOutput2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AnalogOutput2_PS                     (* (reg8 *) AnalogOutput2__PS)
/* Data Register */
#define AnalogOutput2_DR                     (* (reg8 *) AnalogOutput2__DR)
/* Port Number */
#define AnalogOutput2_PRT_NUM                (* (reg8 *) AnalogOutput2__PRT) 
/* Connect to Analog Globals */                                                  
#define AnalogOutput2_AG                     (* (reg8 *) AnalogOutput2__AG)                       
/* Analog MUX bux enable */
#define AnalogOutput2_AMUX                   (* (reg8 *) AnalogOutput2__AMUX) 
/* Bidirectional Enable */                                                        
#define AnalogOutput2_BIE                    (* (reg8 *) AnalogOutput2__BIE)
/* Bit-mask for Aliased Register Access */
#define AnalogOutput2_BIT_MASK               (* (reg8 *) AnalogOutput2__BIT_MASK)
/* Bypass Enable */
#define AnalogOutput2_BYP                    (* (reg8 *) AnalogOutput2__BYP)
/* Port wide control signals */                                                   
#define AnalogOutput2_CTL                    (* (reg8 *) AnalogOutput2__CTL)
/* Drive Modes */
#define AnalogOutput2_DM0                    (* (reg8 *) AnalogOutput2__DM0) 
#define AnalogOutput2_DM1                    (* (reg8 *) AnalogOutput2__DM1)
#define AnalogOutput2_DM2                    (* (reg8 *) AnalogOutput2__DM2) 
/* Input Buffer Disable Override */
#define AnalogOutput2_INP_DIS                (* (reg8 *) AnalogOutput2__INP_DIS)
/* LCD Common or Segment Drive */
#define AnalogOutput2_LCD_COM_SEG            (* (reg8 *) AnalogOutput2__LCD_COM_SEG)
/* Enable Segment LCD */
#define AnalogOutput2_LCD_EN                 (* (reg8 *) AnalogOutput2__LCD_EN)
/* Slew Rate Control */
#define AnalogOutput2_SLW                    (* (reg8 *) AnalogOutput2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AnalogOutput2_PRTDSI__CAPS_SEL       (* (reg8 *) AnalogOutput2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AnalogOutput2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AnalogOutput2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AnalogOutput2_PRTDSI__OE_SEL0        (* (reg8 *) AnalogOutput2__PRTDSI__OE_SEL0) 
#define AnalogOutput2_PRTDSI__OE_SEL1        (* (reg8 *) AnalogOutput2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AnalogOutput2_PRTDSI__OUT_SEL0       (* (reg8 *) AnalogOutput2__PRTDSI__OUT_SEL0) 
#define AnalogOutput2_PRTDSI__OUT_SEL1       (* (reg8 *) AnalogOutput2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AnalogOutput2_PRTDSI__SYNC_OUT       (* (reg8 *) AnalogOutput2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AnalogOutput2__SIO_CFG)
    #define AnalogOutput2_SIO_HYST_EN        (* (reg8 *) AnalogOutput2__SIO_HYST_EN)
    #define AnalogOutput2_SIO_REG_HIFREQ     (* (reg8 *) AnalogOutput2__SIO_REG_HIFREQ)
    #define AnalogOutput2_SIO_CFG            (* (reg8 *) AnalogOutput2__SIO_CFG)
    #define AnalogOutput2_SIO_DIFF           (* (reg8 *) AnalogOutput2__SIO_DIFF)
#endif /* (AnalogOutput2__SIO_CFG) */

/* Interrupt Registers */
#if defined(AnalogOutput2__INTSTAT)
    #define AnalogOutput2_INTSTAT            (* (reg8 *) AnalogOutput2__INTSTAT)
    #define AnalogOutput2_SNAP               (* (reg8 *) AnalogOutput2__SNAP)
    
	#define AnalogOutput2_0_INTTYPE_REG 		(* (reg8 *) AnalogOutput2__0__INTTYPE)
#endif /* (AnalogOutput2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AnalogOutput2_H */


/* [] END OF FILE */
