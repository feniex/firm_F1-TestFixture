/*******************************************************************************
* File Name: PB_NextAction.h  
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

#if !defined(CY_PINS_PB_NextAction_H) /* Pins PB_NextAction_H */
#define CY_PINS_PB_NextAction_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PB_NextAction_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PB_NextAction__PORT == 15 && ((PB_NextAction__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PB_NextAction_Write(uint8 value);
void    PB_NextAction_SetDriveMode(uint8 mode);
uint8   PB_NextAction_ReadDataReg(void);
uint8   PB_NextAction_Read(void);
void    PB_NextAction_SetInterruptMode(uint16 position, uint16 mode);
uint8   PB_NextAction_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PB_NextAction_SetDriveMode() function.
     *  @{
     */
        #define PB_NextAction_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PB_NextAction_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PB_NextAction_DM_RES_UP          PIN_DM_RES_UP
        #define PB_NextAction_DM_RES_DWN         PIN_DM_RES_DWN
        #define PB_NextAction_DM_OD_LO           PIN_DM_OD_LO
        #define PB_NextAction_DM_OD_HI           PIN_DM_OD_HI
        #define PB_NextAction_DM_STRONG          PIN_DM_STRONG
        #define PB_NextAction_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PB_NextAction_MASK               PB_NextAction__MASK
#define PB_NextAction_SHIFT              PB_NextAction__SHIFT
#define PB_NextAction_WIDTH              1u

/* Interrupt constants */
#if defined(PB_NextAction__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PB_NextAction_SetInterruptMode() function.
     *  @{
     */
        #define PB_NextAction_INTR_NONE      (uint16)(0x0000u)
        #define PB_NextAction_INTR_RISING    (uint16)(0x0001u)
        #define PB_NextAction_INTR_FALLING   (uint16)(0x0002u)
        #define PB_NextAction_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PB_NextAction_INTR_MASK      (0x01u) 
#endif /* (PB_NextAction__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PB_NextAction_PS                     (* (reg8 *) PB_NextAction__PS)
/* Data Register */
#define PB_NextAction_DR                     (* (reg8 *) PB_NextAction__DR)
/* Port Number */
#define PB_NextAction_PRT_NUM                (* (reg8 *) PB_NextAction__PRT) 
/* Connect to Analog Globals */                                                  
#define PB_NextAction_AG                     (* (reg8 *) PB_NextAction__AG)                       
/* Analog MUX bux enable */
#define PB_NextAction_AMUX                   (* (reg8 *) PB_NextAction__AMUX) 
/* Bidirectional Enable */                                                        
#define PB_NextAction_BIE                    (* (reg8 *) PB_NextAction__BIE)
/* Bit-mask for Aliased Register Access */
#define PB_NextAction_BIT_MASK               (* (reg8 *) PB_NextAction__BIT_MASK)
/* Bypass Enable */
#define PB_NextAction_BYP                    (* (reg8 *) PB_NextAction__BYP)
/* Port wide control signals */                                                   
#define PB_NextAction_CTL                    (* (reg8 *) PB_NextAction__CTL)
/* Drive Modes */
#define PB_NextAction_DM0                    (* (reg8 *) PB_NextAction__DM0) 
#define PB_NextAction_DM1                    (* (reg8 *) PB_NextAction__DM1)
#define PB_NextAction_DM2                    (* (reg8 *) PB_NextAction__DM2) 
/* Input Buffer Disable Override */
#define PB_NextAction_INP_DIS                (* (reg8 *) PB_NextAction__INP_DIS)
/* LCD Common or Segment Drive */
#define PB_NextAction_LCD_COM_SEG            (* (reg8 *) PB_NextAction__LCD_COM_SEG)
/* Enable Segment LCD */
#define PB_NextAction_LCD_EN                 (* (reg8 *) PB_NextAction__LCD_EN)
/* Slew Rate Control */
#define PB_NextAction_SLW                    (* (reg8 *) PB_NextAction__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PB_NextAction_PRTDSI__CAPS_SEL       (* (reg8 *) PB_NextAction__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PB_NextAction_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PB_NextAction__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PB_NextAction_PRTDSI__OE_SEL0        (* (reg8 *) PB_NextAction__PRTDSI__OE_SEL0) 
#define PB_NextAction_PRTDSI__OE_SEL1        (* (reg8 *) PB_NextAction__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PB_NextAction_PRTDSI__OUT_SEL0       (* (reg8 *) PB_NextAction__PRTDSI__OUT_SEL0) 
#define PB_NextAction_PRTDSI__OUT_SEL1       (* (reg8 *) PB_NextAction__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PB_NextAction_PRTDSI__SYNC_OUT       (* (reg8 *) PB_NextAction__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PB_NextAction__SIO_CFG)
    #define PB_NextAction_SIO_HYST_EN        (* (reg8 *) PB_NextAction__SIO_HYST_EN)
    #define PB_NextAction_SIO_REG_HIFREQ     (* (reg8 *) PB_NextAction__SIO_REG_HIFREQ)
    #define PB_NextAction_SIO_CFG            (* (reg8 *) PB_NextAction__SIO_CFG)
    #define PB_NextAction_SIO_DIFF           (* (reg8 *) PB_NextAction__SIO_DIFF)
#endif /* (PB_NextAction__SIO_CFG) */

/* Interrupt Registers */
#if defined(PB_NextAction__INTSTAT)
    #define PB_NextAction_INTSTAT            (* (reg8 *) PB_NextAction__INTSTAT)
    #define PB_NextAction_SNAP               (* (reg8 *) PB_NextAction__SNAP)
    
	#define PB_NextAction_0_INTTYPE_REG 		(* (reg8 *) PB_NextAction__0__INTTYPE)
#endif /* (PB_NextAction__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PB_NextAction_H */


/* [] END OF FILE */
