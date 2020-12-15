/*******************************************************************************
* File Name: MicKeyInput.h  
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

#if !defined(CY_PINS_MicKeyInput_H) /* Pins MicKeyInput_H */
#define CY_PINS_MicKeyInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MicKeyInput_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MicKeyInput__PORT == 15 && ((MicKeyInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MicKeyInput_Write(uint8 value);
void    MicKeyInput_SetDriveMode(uint8 mode);
uint8   MicKeyInput_ReadDataReg(void);
uint8   MicKeyInput_Read(void);
void    MicKeyInput_SetInterruptMode(uint16 position, uint16 mode);
uint8   MicKeyInput_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MicKeyInput_SetDriveMode() function.
     *  @{
     */
        #define MicKeyInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MicKeyInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MicKeyInput_DM_RES_UP          PIN_DM_RES_UP
        #define MicKeyInput_DM_RES_DWN         PIN_DM_RES_DWN
        #define MicKeyInput_DM_OD_LO           PIN_DM_OD_LO
        #define MicKeyInput_DM_OD_HI           PIN_DM_OD_HI
        #define MicKeyInput_DM_STRONG          PIN_DM_STRONG
        #define MicKeyInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MicKeyInput_MASK               MicKeyInput__MASK
#define MicKeyInput_SHIFT              MicKeyInput__SHIFT
#define MicKeyInput_WIDTH              1u

/* Interrupt constants */
#if defined(MicKeyInput__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MicKeyInput_SetInterruptMode() function.
     *  @{
     */
        #define MicKeyInput_INTR_NONE      (uint16)(0x0000u)
        #define MicKeyInput_INTR_RISING    (uint16)(0x0001u)
        #define MicKeyInput_INTR_FALLING   (uint16)(0x0002u)
        #define MicKeyInput_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MicKeyInput_INTR_MASK      (0x01u) 
#endif /* (MicKeyInput__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MicKeyInput_PS                     (* (reg8 *) MicKeyInput__PS)
/* Data Register */
#define MicKeyInput_DR                     (* (reg8 *) MicKeyInput__DR)
/* Port Number */
#define MicKeyInput_PRT_NUM                (* (reg8 *) MicKeyInput__PRT) 
/* Connect to Analog Globals */                                                  
#define MicKeyInput_AG                     (* (reg8 *) MicKeyInput__AG)                       
/* Analog MUX bux enable */
#define MicKeyInput_AMUX                   (* (reg8 *) MicKeyInput__AMUX) 
/* Bidirectional Enable */                                                        
#define MicKeyInput_BIE                    (* (reg8 *) MicKeyInput__BIE)
/* Bit-mask for Aliased Register Access */
#define MicKeyInput_BIT_MASK               (* (reg8 *) MicKeyInput__BIT_MASK)
/* Bypass Enable */
#define MicKeyInput_BYP                    (* (reg8 *) MicKeyInput__BYP)
/* Port wide control signals */                                                   
#define MicKeyInput_CTL                    (* (reg8 *) MicKeyInput__CTL)
/* Drive Modes */
#define MicKeyInput_DM0                    (* (reg8 *) MicKeyInput__DM0) 
#define MicKeyInput_DM1                    (* (reg8 *) MicKeyInput__DM1)
#define MicKeyInput_DM2                    (* (reg8 *) MicKeyInput__DM2) 
/* Input Buffer Disable Override */
#define MicKeyInput_INP_DIS                (* (reg8 *) MicKeyInput__INP_DIS)
/* LCD Common or Segment Drive */
#define MicKeyInput_LCD_COM_SEG            (* (reg8 *) MicKeyInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define MicKeyInput_LCD_EN                 (* (reg8 *) MicKeyInput__LCD_EN)
/* Slew Rate Control */
#define MicKeyInput_SLW                    (* (reg8 *) MicKeyInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MicKeyInput_PRTDSI__CAPS_SEL       (* (reg8 *) MicKeyInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MicKeyInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MicKeyInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MicKeyInput_PRTDSI__OE_SEL0        (* (reg8 *) MicKeyInput__PRTDSI__OE_SEL0) 
#define MicKeyInput_PRTDSI__OE_SEL1        (* (reg8 *) MicKeyInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MicKeyInput_PRTDSI__OUT_SEL0       (* (reg8 *) MicKeyInput__PRTDSI__OUT_SEL0) 
#define MicKeyInput_PRTDSI__OUT_SEL1       (* (reg8 *) MicKeyInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MicKeyInput_PRTDSI__SYNC_OUT       (* (reg8 *) MicKeyInput__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MicKeyInput__SIO_CFG)
    #define MicKeyInput_SIO_HYST_EN        (* (reg8 *) MicKeyInput__SIO_HYST_EN)
    #define MicKeyInput_SIO_REG_HIFREQ     (* (reg8 *) MicKeyInput__SIO_REG_HIFREQ)
    #define MicKeyInput_SIO_CFG            (* (reg8 *) MicKeyInput__SIO_CFG)
    #define MicKeyInput_SIO_DIFF           (* (reg8 *) MicKeyInput__SIO_DIFF)
#endif /* (MicKeyInput__SIO_CFG) */

/* Interrupt Registers */
#if defined(MicKeyInput__INTSTAT)
    #define MicKeyInput_INTSTAT            (* (reg8 *) MicKeyInput__INTSTAT)
    #define MicKeyInput_SNAP               (* (reg8 *) MicKeyInput__SNAP)
    
	#define MicKeyInput_0_INTTYPE_REG 		(* (reg8 *) MicKeyInput__0__INTTYPE)
#endif /* (MicKeyInput__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MicKeyInput_H */


/* [] END OF FILE */
