/*******************************************************************************
* File Name: Amp2_Current.h  
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

#if !defined(CY_PINS_Amp2_Current_H) /* Pins Amp2_Current_H */
#define CY_PINS_Amp2_Current_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Amp2_Current_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Amp2_Current__PORT == 15 && ((Amp2_Current__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Amp2_Current_Write(uint8 value);
void    Amp2_Current_SetDriveMode(uint8 mode);
uint8   Amp2_Current_ReadDataReg(void);
uint8   Amp2_Current_Read(void);
void    Amp2_Current_SetInterruptMode(uint16 position, uint16 mode);
uint8   Amp2_Current_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Amp2_Current_SetDriveMode() function.
     *  @{
     */
        #define Amp2_Current_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Amp2_Current_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Amp2_Current_DM_RES_UP          PIN_DM_RES_UP
        #define Amp2_Current_DM_RES_DWN         PIN_DM_RES_DWN
        #define Amp2_Current_DM_OD_LO           PIN_DM_OD_LO
        #define Amp2_Current_DM_OD_HI           PIN_DM_OD_HI
        #define Amp2_Current_DM_STRONG          PIN_DM_STRONG
        #define Amp2_Current_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Amp2_Current_MASK               Amp2_Current__MASK
#define Amp2_Current_SHIFT              Amp2_Current__SHIFT
#define Amp2_Current_WIDTH              1u

/* Interrupt constants */
#if defined(Amp2_Current__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Amp2_Current_SetInterruptMode() function.
     *  @{
     */
        #define Amp2_Current_INTR_NONE      (uint16)(0x0000u)
        #define Amp2_Current_INTR_RISING    (uint16)(0x0001u)
        #define Amp2_Current_INTR_FALLING   (uint16)(0x0002u)
        #define Amp2_Current_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Amp2_Current_INTR_MASK      (0x01u) 
#endif /* (Amp2_Current__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Amp2_Current_PS                     (* (reg8 *) Amp2_Current__PS)
/* Data Register */
#define Amp2_Current_DR                     (* (reg8 *) Amp2_Current__DR)
/* Port Number */
#define Amp2_Current_PRT_NUM                (* (reg8 *) Amp2_Current__PRT) 
/* Connect to Analog Globals */                                                  
#define Amp2_Current_AG                     (* (reg8 *) Amp2_Current__AG)                       
/* Analog MUX bux enable */
#define Amp2_Current_AMUX                   (* (reg8 *) Amp2_Current__AMUX) 
/* Bidirectional Enable */                                                        
#define Amp2_Current_BIE                    (* (reg8 *) Amp2_Current__BIE)
/* Bit-mask for Aliased Register Access */
#define Amp2_Current_BIT_MASK               (* (reg8 *) Amp2_Current__BIT_MASK)
/* Bypass Enable */
#define Amp2_Current_BYP                    (* (reg8 *) Amp2_Current__BYP)
/* Port wide control signals */                                                   
#define Amp2_Current_CTL                    (* (reg8 *) Amp2_Current__CTL)
/* Drive Modes */
#define Amp2_Current_DM0                    (* (reg8 *) Amp2_Current__DM0) 
#define Amp2_Current_DM1                    (* (reg8 *) Amp2_Current__DM1)
#define Amp2_Current_DM2                    (* (reg8 *) Amp2_Current__DM2) 
/* Input Buffer Disable Override */
#define Amp2_Current_INP_DIS                (* (reg8 *) Amp2_Current__INP_DIS)
/* LCD Common or Segment Drive */
#define Amp2_Current_LCD_COM_SEG            (* (reg8 *) Amp2_Current__LCD_COM_SEG)
/* Enable Segment LCD */
#define Amp2_Current_LCD_EN                 (* (reg8 *) Amp2_Current__LCD_EN)
/* Slew Rate Control */
#define Amp2_Current_SLW                    (* (reg8 *) Amp2_Current__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Amp2_Current_PRTDSI__CAPS_SEL       (* (reg8 *) Amp2_Current__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Amp2_Current_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Amp2_Current__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Amp2_Current_PRTDSI__OE_SEL0        (* (reg8 *) Amp2_Current__PRTDSI__OE_SEL0) 
#define Amp2_Current_PRTDSI__OE_SEL1        (* (reg8 *) Amp2_Current__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Amp2_Current_PRTDSI__OUT_SEL0       (* (reg8 *) Amp2_Current__PRTDSI__OUT_SEL0) 
#define Amp2_Current_PRTDSI__OUT_SEL1       (* (reg8 *) Amp2_Current__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Amp2_Current_PRTDSI__SYNC_OUT       (* (reg8 *) Amp2_Current__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Amp2_Current__SIO_CFG)
    #define Amp2_Current_SIO_HYST_EN        (* (reg8 *) Amp2_Current__SIO_HYST_EN)
    #define Amp2_Current_SIO_REG_HIFREQ     (* (reg8 *) Amp2_Current__SIO_REG_HIFREQ)
    #define Amp2_Current_SIO_CFG            (* (reg8 *) Amp2_Current__SIO_CFG)
    #define Amp2_Current_SIO_DIFF           (* (reg8 *) Amp2_Current__SIO_DIFF)
#endif /* (Amp2_Current__SIO_CFG) */

/* Interrupt Registers */
#if defined(Amp2_Current__INTSTAT)
    #define Amp2_Current_INTSTAT            (* (reg8 *) Amp2_Current__INTSTAT)
    #define Amp2_Current_SNAP               (* (reg8 *) Amp2_Current__SNAP)
    
	#define Amp2_Current_0_INTTYPE_REG 		(* (reg8 *) Amp2_Current__0__INTTYPE)
#endif /* (Amp2_Current__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Amp2_Current_H */


/* [] END OF FILE */
