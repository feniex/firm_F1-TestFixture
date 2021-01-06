/*******************************************************************************
* File Name: RS2.h  
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

#if !defined(CY_PINS_RS2_H) /* Pins RS2_H */
#define CY_PINS_RS2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RS2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RS2__PORT == 15 && ((RS2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RS2_Write(uint8 value);
void    RS2_SetDriveMode(uint8 mode);
uint8   RS2_ReadDataReg(void);
uint8   RS2_Read(void);
void    RS2_SetInterruptMode(uint16 position, uint16 mode);
uint8   RS2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RS2_SetDriveMode() function.
     *  @{
     */
        #define RS2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RS2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RS2_DM_RES_UP          PIN_DM_RES_UP
        #define RS2_DM_RES_DWN         PIN_DM_RES_DWN
        #define RS2_DM_OD_LO           PIN_DM_OD_LO
        #define RS2_DM_OD_HI           PIN_DM_OD_HI
        #define RS2_DM_STRONG          PIN_DM_STRONG
        #define RS2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RS2_MASK               RS2__MASK
#define RS2_SHIFT              RS2__SHIFT
#define RS2_WIDTH              1u

/* Interrupt constants */
#if defined(RS2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RS2_SetInterruptMode() function.
     *  @{
     */
        #define RS2_INTR_NONE      (uint16)(0x0000u)
        #define RS2_INTR_RISING    (uint16)(0x0001u)
        #define RS2_INTR_FALLING   (uint16)(0x0002u)
        #define RS2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RS2_INTR_MASK      (0x01u) 
#endif /* (RS2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RS2_PS                     (* (reg8 *) RS2__PS)
/* Data Register */
#define RS2_DR                     (* (reg8 *) RS2__DR)
/* Port Number */
#define RS2_PRT_NUM                (* (reg8 *) RS2__PRT) 
/* Connect to Analog Globals */                                                  
#define RS2_AG                     (* (reg8 *) RS2__AG)                       
/* Analog MUX bux enable */
#define RS2_AMUX                   (* (reg8 *) RS2__AMUX) 
/* Bidirectional Enable */                                                        
#define RS2_BIE                    (* (reg8 *) RS2__BIE)
/* Bit-mask for Aliased Register Access */
#define RS2_BIT_MASK               (* (reg8 *) RS2__BIT_MASK)
/* Bypass Enable */
#define RS2_BYP                    (* (reg8 *) RS2__BYP)
/* Port wide control signals */                                                   
#define RS2_CTL                    (* (reg8 *) RS2__CTL)
/* Drive Modes */
#define RS2_DM0                    (* (reg8 *) RS2__DM0) 
#define RS2_DM1                    (* (reg8 *) RS2__DM1)
#define RS2_DM2                    (* (reg8 *) RS2__DM2) 
/* Input Buffer Disable Override */
#define RS2_INP_DIS                (* (reg8 *) RS2__INP_DIS)
/* LCD Common or Segment Drive */
#define RS2_LCD_COM_SEG            (* (reg8 *) RS2__LCD_COM_SEG)
/* Enable Segment LCD */
#define RS2_LCD_EN                 (* (reg8 *) RS2__LCD_EN)
/* Slew Rate Control */
#define RS2_SLW                    (* (reg8 *) RS2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RS2_PRTDSI__CAPS_SEL       (* (reg8 *) RS2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RS2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RS2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RS2_PRTDSI__OE_SEL0        (* (reg8 *) RS2__PRTDSI__OE_SEL0) 
#define RS2_PRTDSI__OE_SEL1        (* (reg8 *) RS2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RS2_PRTDSI__OUT_SEL0       (* (reg8 *) RS2__PRTDSI__OUT_SEL0) 
#define RS2_PRTDSI__OUT_SEL1       (* (reg8 *) RS2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RS2_PRTDSI__SYNC_OUT       (* (reg8 *) RS2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RS2__SIO_CFG)
    #define RS2_SIO_HYST_EN        (* (reg8 *) RS2__SIO_HYST_EN)
    #define RS2_SIO_REG_HIFREQ     (* (reg8 *) RS2__SIO_REG_HIFREQ)
    #define RS2_SIO_CFG            (* (reg8 *) RS2__SIO_CFG)
    #define RS2_SIO_DIFF           (* (reg8 *) RS2__SIO_DIFF)
#endif /* (RS2__SIO_CFG) */

/* Interrupt Registers */
#if defined(RS2__INTSTAT)
    #define RS2_INTSTAT            (* (reg8 *) RS2__INTSTAT)
    #define RS2_SNAP               (* (reg8 *) RS2__SNAP)
    
	#define RS2_0_INTTYPE_REG 		(* (reg8 *) RS2__0__INTTYPE)
#endif /* (RS2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RS2_H */


/* [] END OF FILE */
