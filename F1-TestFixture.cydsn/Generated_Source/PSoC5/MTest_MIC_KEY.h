/*******************************************************************************
* File Name: MTest_MIC_KEY.h  
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

#if !defined(CY_PINS_MTest_MIC_KEY_H) /* Pins MTest_MIC_KEY_H */
#define CY_PINS_MTest_MIC_KEY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MTest_MIC_KEY_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MTest_MIC_KEY__PORT == 15 && ((MTest_MIC_KEY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MTest_MIC_KEY_Write(uint8 value);
void    MTest_MIC_KEY_SetDriveMode(uint8 mode);
uint8   MTest_MIC_KEY_ReadDataReg(void);
uint8   MTest_MIC_KEY_Read(void);
void    MTest_MIC_KEY_SetInterruptMode(uint16 position, uint16 mode);
uint8   MTest_MIC_KEY_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MTest_MIC_KEY_SetDriveMode() function.
     *  @{
     */
        #define MTest_MIC_KEY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MTest_MIC_KEY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MTest_MIC_KEY_DM_RES_UP          PIN_DM_RES_UP
        #define MTest_MIC_KEY_DM_RES_DWN         PIN_DM_RES_DWN
        #define MTest_MIC_KEY_DM_OD_LO           PIN_DM_OD_LO
        #define MTest_MIC_KEY_DM_OD_HI           PIN_DM_OD_HI
        #define MTest_MIC_KEY_DM_STRONG          PIN_DM_STRONG
        #define MTest_MIC_KEY_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MTest_MIC_KEY_MASK               MTest_MIC_KEY__MASK
#define MTest_MIC_KEY_SHIFT              MTest_MIC_KEY__SHIFT
#define MTest_MIC_KEY_WIDTH              1u

/* Interrupt constants */
#if defined(MTest_MIC_KEY__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MTest_MIC_KEY_SetInterruptMode() function.
     *  @{
     */
        #define MTest_MIC_KEY_INTR_NONE      (uint16)(0x0000u)
        #define MTest_MIC_KEY_INTR_RISING    (uint16)(0x0001u)
        #define MTest_MIC_KEY_INTR_FALLING   (uint16)(0x0002u)
        #define MTest_MIC_KEY_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MTest_MIC_KEY_INTR_MASK      (0x01u) 
#endif /* (MTest_MIC_KEY__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MTest_MIC_KEY_PS                     (* (reg8 *) MTest_MIC_KEY__PS)
/* Data Register */
#define MTest_MIC_KEY_DR                     (* (reg8 *) MTest_MIC_KEY__DR)
/* Port Number */
#define MTest_MIC_KEY_PRT_NUM                (* (reg8 *) MTest_MIC_KEY__PRT) 
/* Connect to Analog Globals */                                                  
#define MTest_MIC_KEY_AG                     (* (reg8 *) MTest_MIC_KEY__AG)                       
/* Analog MUX bux enable */
#define MTest_MIC_KEY_AMUX                   (* (reg8 *) MTest_MIC_KEY__AMUX) 
/* Bidirectional Enable */                                                        
#define MTest_MIC_KEY_BIE                    (* (reg8 *) MTest_MIC_KEY__BIE)
/* Bit-mask for Aliased Register Access */
#define MTest_MIC_KEY_BIT_MASK               (* (reg8 *) MTest_MIC_KEY__BIT_MASK)
/* Bypass Enable */
#define MTest_MIC_KEY_BYP                    (* (reg8 *) MTest_MIC_KEY__BYP)
/* Port wide control signals */                                                   
#define MTest_MIC_KEY_CTL                    (* (reg8 *) MTest_MIC_KEY__CTL)
/* Drive Modes */
#define MTest_MIC_KEY_DM0                    (* (reg8 *) MTest_MIC_KEY__DM0) 
#define MTest_MIC_KEY_DM1                    (* (reg8 *) MTest_MIC_KEY__DM1)
#define MTest_MIC_KEY_DM2                    (* (reg8 *) MTest_MIC_KEY__DM2) 
/* Input Buffer Disable Override */
#define MTest_MIC_KEY_INP_DIS                (* (reg8 *) MTest_MIC_KEY__INP_DIS)
/* LCD Common or Segment Drive */
#define MTest_MIC_KEY_LCD_COM_SEG            (* (reg8 *) MTest_MIC_KEY__LCD_COM_SEG)
/* Enable Segment LCD */
#define MTest_MIC_KEY_LCD_EN                 (* (reg8 *) MTest_MIC_KEY__LCD_EN)
/* Slew Rate Control */
#define MTest_MIC_KEY_SLW                    (* (reg8 *) MTest_MIC_KEY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MTest_MIC_KEY_PRTDSI__CAPS_SEL       (* (reg8 *) MTest_MIC_KEY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MTest_MIC_KEY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MTest_MIC_KEY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MTest_MIC_KEY_PRTDSI__OE_SEL0        (* (reg8 *) MTest_MIC_KEY__PRTDSI__OE_SEL0) 
#define MTest_MIC_KEY_PRTDSI__OE_SEL1        (* (reg8 *) MTest_MIC_KEY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MTest_MIC_KEY_PRTDSI__OUT_SEL0       (* (reg8 *) MTest_MIC_KEY__PRTDSI__OUT_SEL0) 
#define MTest_MIC_KEY_PRTDSI__OUT_SEL1       (* (reg8 *) MTest_MIC_KEY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MTest_MIC_KEY_PRTDSI__SYNC_OUT       (* (reg8 *) MTest_MIC_KEY__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MTest_MIC_KEY__SIO_CFG)
    #define MTest_MIC_KEY_SIO_HYST_EN        (* (reg8 *) MTest_MIC_KEY__SIO_HYST_EN)
    #define MTest_MIC_KEY_SIO_REG_HIFREQ     (* (reg8 *) MTest_MIC_KEY__SIO_REG_HIFREQ)
    #define MTest_MIC_KEY_SIO_CFG            (* (reg8 *) MTest_MIC_KEY__SIO_CFG)
    #define MTest_MIC_KEY_SIO_DIFF           (* (reg8 *) MTest_MIC_KEY__SIO_DIFF)
#endif /* (MTest_MIC_KEY__SIO_CFG) */

/* Interrupt Registers */
#if defined(MTest_MIC_KEY__INTSTAT)
    #define MTest_MIC_KEY_INTSTAT            (* (reg8 *) MTest_MIC_KEY__INTSTAT)
    #define MTest_MIC_KEY_SNAP               (* (reg8 *) MTest_MIC_KEY__SNAP)
    
	#define MTest_MIC_KEY_0_INTTYPE_REG 		(* (reg8 *) MTest_MIC_KEY__0__INTTYPE)
#endif /* (MTest_MIC_KEY__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MTest_MIC_KEY_H */


/* [] END OF FILE */
