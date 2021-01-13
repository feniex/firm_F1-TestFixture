/*******************************************************************************
* File Name: Overload2.h  
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

#if !defined(CY_PINS_Overload2_H) /* Pins Overload2_H */
#define CY_PINS_Overload2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Overload2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Overload2__PORT == 15 && ((Overload2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Overload2_Write(uint8 value);
void    Overload2_SetDriveMode(uint8 mode);
uint8   Overload2_ReadDataReg(void);
uint8   Overload2_Read(void);
void    Overload2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Overload2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Overload2_SetDriveMode() function.
     *  @{
     */
        #define Overload2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Overload2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Overload2_DM_RES_UP          PIN_DM_RES_UP
        #define Overload2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Overload2_DM_OD_LO           PIN_DM_OD_LO
        #define Overload2_DM_OD_HI           PIN_DM_OD_HI
        #define Overload2_DM_STRONG          PIN_DM_STRONG
        #define Overload2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Overload2_MASK               Overload2__MASK
#define Overload2_SHIFT              Overload2__SHIFT
#define Overload2_WIDTH              1u

/* Interrupt constants */
#if defined(Overload2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Overload2_SetInterruptMode() function.
     *  @{
     */
        #define Overload2_INTR_NONE      (uint16)(0x0000u)
        #define Overload2_INTR_RISING    (uint16)(0x0001u)
        #define Overload2_INTR_FALLING   (uint16)(0x0002u)
        #define Overload2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Overload2_INTR_MASK      (0x01u) 
#endif /* (Overload2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Overload2_PS                     (* (reg8 *) Overload2__PS)
/* Data Register */
#define Overload2_DR                     (* (reg8 *) Overload2__DR)
/* Port Number */
#define Overload2_PRT_NUM                (* (reg8 *) Overload2__PRT) 
/* Connect to Analog Globals */                                                  
#define Overload2_AG                     (* (reg8 *) Overload2__AG)                       
/* Analog MUX bux enable */
#define Overload2_AMUX                   (* (reg8 *) Overload2__AMUX) 
/* Bidirectional Enable */                                                        
#define Overload2_BIE                    (* (reg8 *) Overload2__BIE)
/* Bit-mask for Aliased Register Access */
#define Overload2_BIT_MASK               (* (reg8 *) Overload2__BIT_MASK)
/* Bypass Enable */
#define Overload2_BYP                    (* (reg8 *) Overload2__BYP)
/* Port wide control signals */                                                   
#define Overload2_CTL                    (* (reg8 *) Overload2__CTL)
/* Drive Modes */
#define Overload2_DM0                    (* (reg8 *) Overload2__DM0) 
#define Overload2_DM1                    (* (reg8 *) Overload2__DM1)
#define Overload2_DM2                    (* (reg8 *) Overload2__DM2) 
/* Input Buffer Disable Override */
#define Overload2_INP_DIS                (* (reg8 *) Overload2__INP_DIS)
/* LCD Common or Segment Drive */
#define Overload2_LCD_COM_SEG            (* (reg8 *) Overload2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Overload2_LCD_EN                 (* (reg8 *) Overload2__LCD_EN)
/* Slew Rate Control */
#define Overload2_SLW                    (* (reg8 *) Overload2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Overload2_PRTDSI__CAPS_SEL       (* (reg8 *) Overload2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Overload2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Overload2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Overload2_PRTDSI__OE_SEL0        (* (reg8 *) Overload2__PRTDSI__OE_SEL0) 
#define Overload2_PRTDSI__OE_SEL1        (* (reg8 *) Overload2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Overload2_PRTDSI__OUT_SEL0       (* (reg8 *) Overload2__PRTDSI__OUT_SEL0) 
#define Overload2_PRTDSI__OUT_SEL1       (* (reg8 *) Overload2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Overload2_PRTDSI__SYNC_OUT       (* (reg8 *) Overload2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Overload2__SIO_CFG)
    #define Overload2_SIO_HYST_EN        (* (reg8 *) Overload2__SIO_HYST_EN)
    #define Overload2_SIO_REG_HIFREQ     (* (reg8 *) Overload2__SIO_REG_HIFREQ)
    #define Overload2_SIO_CFG            (* (reg8 *) Overload2__SIO_CFG)
    #define Overload2_SIO_DIFF           (* (reg8 *) Overload2__SIO_DIFF)
#endif /* (Overload2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Overload2__INTSTAT)
    #define Overload2_INTSTAT            (* (reg8 *) Overload2__INTSTAT)
    #define Overload2_SNAP               (* (reg8 *) Overload2__SNAP)
    
	#define Overload2_0_INTTYPE_REG 		(* (reg8 *) Overload2__0__INTTYPE)
#endif /* (Overload2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Overload2_H */


/* [] END OF FILE */
