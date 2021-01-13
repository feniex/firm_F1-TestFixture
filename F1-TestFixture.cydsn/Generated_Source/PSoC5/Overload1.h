/*******************************************************************************
* File Name: Overload1.h  
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

#if !defined(CY_PINS_Overload1_H) /* Pins Overload1_H */
#define CY_PINS_Overload1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Overload1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Overload1__PORT == 15 && ((Overload1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Overload1_Write(uint8 value);
void    Overload1_SetDriveMode(uint8 mode);
uint8   Overload1_ReadDataReg(void);
uint8   Overload1_Read(void);
void    Overload1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Overload1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Overload1_SetDriveMode() function.
     *  @{
     */
        #define Overload1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Overload1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Overload1_DM_RES_UP          PIN_DM_RES_UP
        #define Overload1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Overload1_DM_OD_LO           PIN_DM_OD_LO
        #define Overload1_DM_OD_HI           PIN_DM_OD_HI
        #define Overload1_DM_STRONG          PIN_DM_STRONG
        #define Overload1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Overload1_MASK               Overload1__MASK
#define Overload1_SHIFT              Overload1__SHIFT
#define Overload1_WIDTH              1u

/* Interrupt constants */
#if defined(Overload1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Overload1_SetInterruptMode() function.
     *  @{
     */
        #define Overload1_INTR_NONE      (uint16)(0x0000u)
        #define Overload1_INTR_RISING    (uint16)(0x0001u)
        #define Overload1_INTR_FALLING   (uint16)(0x0002u)
        #define Overload1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Overload1_INTR_MASK      (0x01u) 
#endif /* (Overload1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Overload1_PS                     (* (reg8 *) Overload1__PS)
/* Data Register */
#define Overload1_DR                     (* (reg8 *) Overload1__DR)
/* Port Number */
#define Overload1_PRT_NUM                (* (reg8 *) Overload1__PRT) 
/* Connect to Analog Globals */                                                  
#define Overload1_AG                     (* (reg8 *) Overload1__AG)                       
/* Analog MUX bux enable */
#define Overload1_AMUX                   (* (reg8 *) Overload1__AMUX) 
/* Bidirectional Enable */                                                        
#define Overload1_BIE                    (* (reg8 *) Overload1__BIE)
/* Bit-mask for Aliased Register Access */
#define Overload1_BIT_MASK               (* (reg8 *) Overload1__BIT_MASK)
/* Bypass Enable */
#define Overload1_BYP                    (* (reg8 *) Overload1__BYP)
/* Port wide control signals */                                                   
#define Overload1_CTL                    (* (reg8 *) Overload1__CTL)
/* Drive Modes */
#define Overload1_DM0                    (* (reg8 *) Overload1__DM0) 
#define Overload1_DM1                    (* (reg8 *) Overload1__DM1)
#define Overload1_DM2                    (* (reg8 *) Overload1__DM2) 
/* Input Buffer Disable Override */
#define Overload1_INP_DIS                (* (reg8 *) Overload1__INP_DIS)
/* LCD Common or Segment Drive */
#define Overload1_LCD_COM_SEG            (* (reg8 *) Overload1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Overload1_LCD_EN                 (* (reg8 *) Overload1__LCD_EN)
/* Slew Rate Control */
#define Overload1_SLW                    (* (reg8 *) Overload1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Overload1_PRTDSI__CAPS_SEL       (* (reg8 *) Overload1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Overload1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Overload1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Overload1_PRTDSI__OE_SEL0        (* (reg8 *) Overload1__PRTDSI__OE_SEL0) 
#define Overload1_PRTDSI__OE_SEL1        (* (reg8 *) Overload1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Overload1_PRTDSI__OUT_SEL0       (* (reg8 *) Overload1__PRTDSI__OUT_SEL0) 
#define Overload1_PRTDSI__OUT_SEL1       (* (reg8 *) Overload1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Overload1_PRTDSI__SYNC_OUT       (* (reg8 *) Overload1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Overload1__SIO_CFG)
    #define Overload1_SIO_HYST_EN        (* (reg8 *) Overload1__SIO_HYST_EN)
    #define Overload1_SIO_REG_HIFREQ     (* (reg8 *) Overload1__SIO_REG_HIFREQ)
    #define Overload1_SIO_CFG            (* (reg8 *) Overload1__SIO_CFG)
    #define Overload1_SIO_DIFF           (* (reg8 *) Overload1__SIO_DIFF)
#endif /* (Overload1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Overload1__INTSTAT)
    #define Overload1_INTSTAT            (* (reg8 *) Overload1__INTSTAT)
    #define Overload1_SNAP               (* (reg8 *) Overload1__SNAP)
    
	#define Overload1_0_INTTYPE_REG 		(* (reg8 *) Overload1__0__INTTYPE)
#endif /* (Overload1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Overload1_H */


/* [] END OF FILE */
