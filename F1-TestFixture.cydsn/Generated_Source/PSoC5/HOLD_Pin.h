/*******************************************************************************
* File Name: HOLD_Pin.h  
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

#if !defined(CY_PINS_HOLD_Pin_H) /* Pins HOLD_Pin_H */
#define CY_PINS_HOLD_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HOLD_Pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HOLD_Pin__PORT == 15 && ((HOLD_Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HOLD_Pin_Write(uint8 value);
void    HOLD_Pin_SetDriveMode(uint8 mode);
uint8   HOLD_Pin_ReadDataReg(void);
uint8   HOLD_Pin_Read(void);
void    HOLD_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   HOLD_Pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HOLD_Pin_SetDriveMode() function.
     *  @{
     */
        #define HOLD_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HOLD_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HOLD_Pin_DM_RES_UP          PIN_DM_RES_UP
        #define HOLD_Pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define HOLD_Pin_DM_OD_LO           PIN_DM_OD_LO
        #define HOLD_Pin_DM_OD_HI           PIN_DM_OD_HI
        #define HOLD_Pin_DM_STRONG          PIN_DM_STRONG
        #define HOLD_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HOLD_Pin_MASK               HOLD_Pin__MASK
#define HOLD_Pin_SHIFT              HOLD_Pin__SHIFT
#define HOLD_Pin_WIDTH              1u

/* Interrupt constants */
#if defined(HOLD_Pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HOLD_Pin_SetInterruptMode() function.
     *  @{
     */
        #define HOLD_Pin_INTR_NONE      (uint16)(0x0000u)
        #define HOLD_Pin_INTR_RISING    (uint16)(0x0001u)
        #define HOLD_Pin_INTR_FALLING   (uint16)(0x0002u)
        #define HOLD_Pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HOLD_Pin_INTR_MASK      (0x01u) 
#endif /* (HOLD_Pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HOLD_Pin_PS                     (* (reg8 *) HOLD_Pin__PS)
/* Data Register */
#define HOLD_Pin_DR                     (* (reg8 *) HOLD_Pin__DR)
/* Port Number */
#define HOLD_Pin_PRT_NUM                (* (reg8 *) HOLD_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define HOLD_Pin_AG                     (* (reg8 *) HOLD_Pin__AG)                       
/* Analog MUX bux enable */
#define HOLD_Pin_AMUX                   (* (reg8 *) HOLD_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define HOLD_Pin_BIE                    (* (reg8 *) HOLD_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define HOLD_Pin_BIT_MASK               (* (reg8 *) HOLD_Pin__BIT_MASK)
/* Bypass Enable */
#define HOLD_Pin_BYP                    (* (reg8 *) HOLD_Pin__BYP)
/* Port wide control signals */                                                   
#define HOLD_Pin_CTL                    (* (reg8 *) HOLD_Pin__CTL)
/* Drive Modes */
#define HOLD_Pin_DM0                    (* (reg8 *) HOLD_Pin__DM0) 
#define HOLD_Pin_DM1                    (* (reg8 *) HOLD_Pin__DM1)
#define HOLD_Pin_DM2                    (* (reg8 *) HOLD_Pin__DM2) 
/* Input Buffer Disable Override */
#define HOLD_Pin_INP_DIS                (* (reg8 *) HOLD_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define HOLD_Pin_LCD_COM_SEG            (* (reg8 *) HOLD_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define HOLD_Pin_LCD_EN                 (* (reg8 *) HOLD_Pin__LCD_EN)
/* Slew Rate Control */
#define HOLD_Pin_SLW                    (* (reg8 *) HOLD_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HOLD_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) HOLD_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HOLD_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HOLD_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HOLD_Pin_PRTDSI__OE_SEL0        (* (reg8 *) HOLD_Pin__PRTDSI__OE_SEL0) 
#define HOLD_Pin_PRTDSI__OE_SEL1        (* (reg8 *) HOLD_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HOLD_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) HOLD_Pin__PRTDSI__OUT_SEL0) 
#define HOLD_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) HOLD_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HOLD_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) HOLD_Pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HOLD_Pin__SIO_CFG)
    #define HOLD_Pin_SIO_HYST_EN        (* (reg8 *) HOLD_Pin__SIO_HYST_EN)
    #define HOLD_Pin_SIO_REG_HIFREQ     (* (reg8 *) HOLD_Pin__SIO_REG_HIFREQ)
    #define HOLD_Pin_SIO_CFG            (* (reg8 *) HOLD_Pin__SIO_CFG)
    #define HOLD_Pin_SIO_DIFF           (* (reg8 *) HOLD_Pin__SIO_DIFF)
#endif /* (HOLD_Pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(HOLD_Pin__INTSTAT)
    #define HOLD_Pin_INTSTAT            (* (reg8 *) HOLD_Pin__INTSTAT)
    #define HOLD_Pin_SNAP               (* (reg8 *) HOLD_Pin__SNAP)
    
	#define HOLD_Pin_0_INTTYPE_REG 		(* (reg8 *) HOLD_Pin__0__INTTYPE)
#endif /* (HOLD_Pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HOLD_Pin_H */


/* [] END OF FILE */
