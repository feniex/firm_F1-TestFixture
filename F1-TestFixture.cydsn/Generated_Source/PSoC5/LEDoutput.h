/*******************************************************************************
* File Name: LEDoutput.h  
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

#if !defined(CY_PINS_LEDoutput_H) /* Pins LEDoutput_H */
#define CY_PINS_LEDoutput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDoutput_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDoutput__PORT == 15 && ((LEDoutput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDoutput_Write(uint8 value);
void    LEDoutput_SetDriveMode(uint8 mode);
uint8   LEDoutput_ReadDataReg(void);
uint8   LEDoutput_Read(void);
void    LEDoutput_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDoutput_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDoutput_SetDriveMode() function.
     *  @{
     */
        #define LEDoutput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDoutput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDoutput_DM_RES_UP          PIN_DM_RES_UP
        #define LEDoutput_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDoutput_DM_OD_LO           PIN_DM_OD_LO
        #define LEDoutput_DM_OD_HI           PIN_DM_OD_HI
        #define LEDoutput_DM_STRONG          PIN_DM_STRONG
        #define LEDoutput_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDoutput_MASK               LEDoutput__MASK
#define LEDoutput_SHIFT              LEDoutput__SHIFT
#define LEDoutput_WIDTH              1u

/* Interrupt constants */
#if defined(LEDoutput__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDoutput_SetInterruptMode() function.
     *  @{
     */
        #define LEDoutput_INTR_NONE      (uint16)(0x0000u)
        #define LEDoutput_INTR_RISING    (uint16)(0x0001u)
        #define LEDoutput_INTR_FALLING   (uint16)(0x0002u)
        #define LEDoutput_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDoutput_INTR_MASK      (0x01u) 
#endif /* (LEDoutput__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDoutput_PS                     (* (reg8 *) LEDoutput__PS)
/* Data Register */
#define LEDoutput_DR                     (* (reg8 *) LEDoutput__DR)
/* Port Number */
#define LEDoutput_PRT_NUM                (* (reg8 *) LEDoutput__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDoutput_AG                     (* (reg8 *) LEDoutput__AG)                       
/* Analog MUX bux enable */
#define LEDoutput_AMUX                   (* (reg8 *) LEDoutput__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDoutput_BIE                    (* (reg8 *) LEDoutput__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDoutput_BIT_MASK               (* (reg8 *) LEDoutput__BIT_MASK)
/* Bypass Enable */
#define LEDoutput_BYP                    (* (reg8 *) LEDoutput__BYP)
/* Port wide control signals */                                                   
#define LEDoutput_CTL                    (* (reg8 *) LEDoutput__CTL)
/* Drive Modes */
#define LEDoutput_DM0                    (* (reg8 *) LEDoutput__DM0) 
#define LEDoutput_DM1                    (* (reg8 *) LEDoutput__DM1)
#define LEDoutput_DM2                    (* (reg8 *) LEDoutput__DM2) 
/* Input Buffer Disable Override */
#define LEDoutput_INP_DIS                (* (reg8 *) LEDoutput__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDoutput_LCD_COM_SEG            (* (reg8 *) LEDoutput__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDoutput_LCD_EN                 (* (reg8 *) LEDoutput__LCD_EN)
/* Slew Rate Control */
#define LEDoutput_SLW                    (* (reg8 *) LEDoutput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDoutput_PRTDSI__CAPS_SEL       (* (reg8 *) LEDoutput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDoutput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDoutput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDoutput_PRTDSI__OE_SEL0        (* (reg8 *) LEDoutput__PRTDSI__OE_SEL0) 
#define LEDoutput_PRTDSI__OE_SEL1        (* (reg8 *) LEDoutput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDoutput_PRTDSI__OUT_SEL0       (* (reg8 *) LEDoutput__PRTDSI__OUT_SEL0) 
#define LEDoutput_PRTDSI__OUT_SEL1       (* (reg8 *) LEDoutput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDoutput_PRTDSI__SYNC_OUT       (* (reg8 *) LEDoutput__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDoutput__SIO_CFG)
    #define LEDoutput_SIO_HYST_EN        (* (reg8 *) LEDoutput__SIO_HYST_EN)
    #define LEDoutput_SIO_REG_HIFREQ     (* (reg8 *) LEDoutput__SIO_REG_HIFREQ)
    #define LEDoutput_SIO_CFG            (* (reg8 *) LEDoutput__SIO_CFG)
    #define LEDoutput_SIO_DIFF           (* (reg8 *) LEDoutput__SIO_DIFF)
#endif /* (LEDoutput__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDoutput__INTSTAT)
    #define LEDoutput_INTSTAT            (* (reg8 *) LEDoutput__INTSTAT)
    #define LEDoutput_SNAP               (* (reg8 *) LEDoutput__SNAP)
    
	#define LEDoutput_0_INTTYPE_REG 		(* (reg8 *) LEDoutput__0__INTTYPE)
#endif /* (LEDoutput__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDoutput_H */


/* [] END OF FILE */
