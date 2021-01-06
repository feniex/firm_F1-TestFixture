/*******************************************************************************
* File Name: RS1.h  
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

#if !defined(CY_PINS_RS1_H) /* Pins RS1_H */
#define CY_PINS_RS1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RS1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RS1__PORT == 15 && ((RS1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RS1_Write(uint8 value);
void    RS1_SetDriveMode(uint8 mode);
uint8   RS1_ReadDataReg(void);
uint8   RS1_Read(void);
void    RS1_SetInterruptMode(uint16 position, uint16 mode);
uint8   RS1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RS1_SetDriveMode() function.
     *  @{
     */
        #define RS1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RS1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RS1_DM_RES_UP          PIN_DM_RES_UP
        #define RS1_DM_RES_DWN         PIN_DM_RES_DWN
        #define RS1_DM_OD_LO           PIN_DM_OD_LO
        #define RS1_DM_OD_HI           PIN_DM_OD_HI
        #define RS1_DM_STRONG          PIN_DM_STRONG
        #define RS1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RS1_MASK               RS1__MASK
#define RS1_SHIFT              RS1__SHIFT
#define RS1_WIDTH              1u

/* Interrupt constants */
#if defined(RS1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RS1_SetInterruptMode() function.
     *  @{
     */
        #define RS1_INTR_NONE      (uint16)(0x0000u)
        #define RS1_INTR_RISING    (uint16)(0x0001u)
        #define RS1_INTR_FALLING   (uint16)(0x0002u)
        #define RS1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RS1_INTR_MASK      (0x01u) 
#endif /* (RS1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RS1_PS                     (* (reg8 *) RS1__PS)
/* Data Register */
#define RS1_DR                     (* (reg8 *) RS1__DR)
/* Port Number */
#define RS1_PRT_NUM                (* (reg8 *) RS1__PRT) 
/* Connect to Analog Globals */                                                  
#define RS1_AG                     (* (reg8 *) RS1__AG)                       
/* Analog MUX bux enable */
#define RS1_AMUX                   (* (reg8 *) RS1__AMUX) 
/* Bidirectional Enable */                                                        
#define RS1_BIE                    (* (reg8 *) RS1__BIE)
/* Bit-mask for Aliased Register Access */
#define RS1_BIT_MASK               (* (reg8 *) RS1__BIT_MASK)
/* Bypass Enable */
#define RS1_BYP                    (* (reg8 *) RS1__BYP)
/* Port wide control signals */                                                   
#define RS1_CTL                    (* (reg8 *) RS1__CTL)
/* Drive Modes */
#define RS1_DM0                    (* (reg8 *) RS1__DM0) 
#define RS1_DM1                    (* (reg8 *) RS1__DM1)
#define RS1_DM2                    (* (reg8 *) RS1__DM2) 
/* Input Buffer Disable Override */
#define RS1_INP_DIS                (* (reg8 *) RS1__INP_DIS)
/* LCD Common or Segment Drive */
#define RS1_LCD_COM_SEG            (* (reg8 *) RS1__LCD_COM_SEG)
/* Enable Segment LCD */
#define RS1_LCD_EN                 (* (reg8 *) RS1__LCD_EN)
/* Slew Rate Control */
#define RS1_SLW                    (* (reg8 *) RS1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RS1_PRTDSI__CAPS_SEL       (* (reg8 *) RS1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RS1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RS1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RS1_PRTDSI__OE_SEL0        (* (reg8 *) RS1__PRTDSI__OE_SEL0) 
#define RS1_PRTDSI__OE_SEL1        (* (reg8 *) RS1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RS1_PRTDSI__OUT_SEL0       (* (reg8 *) RS1__PRTDSI__OUT_SEL0) 
#define RS1_PRTDSI__OUT_SEL1       (* (reg8 *) RS1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RS1_PRTDSI__SYNC_OUT       (* (reg8 *) RS1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RS1__SIO_CFG)
    #define RS1_SIO_HYST_EN        (* (reg8 *) RS1__SIO_HYST_EN)
    #define RS1_SIO_REG_HIFREQ     (* (reg8 *) RS1__SIO_REG_HIFREQ)
    #define RS1_SIO_CFG            (* (reg8 *) RS1__SIO_CFG)
    #define RS1_SIO_DIFF           (* (reg8 *) RS1__SIO_DIFF)
#endif /* (RS1__SIO_CFG) */

/* Interrupt Registers */
#if defined(RS1__INTSTAT)
    #define RS1_INTSTAT            (* (reg8 *) RS1__INTSTAT)
    #define RS1_SNAP               (* (reg8 *) RS1__SNAP)
    
	#define RS1_0_INTTYPE_REG 		(* (reg8 *) RS1__0__INTTYPE)
#endif /* (RS1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RS1_H */


/* [] END OF FILE */
