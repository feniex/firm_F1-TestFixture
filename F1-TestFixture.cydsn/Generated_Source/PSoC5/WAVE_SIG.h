/*******************************************************************************
* File Name: WAVE_SIG.h  
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

#if !defined(CY_PINS_WAVE_SIG_H) /* Pins WAVE_SIG_H */
#define CY_PINS_WAVE_SIG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WAVE_SIG_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WAVE_SIG__PORT == 15 && ((WAVE_SIG__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WAVE_SIG_Write(uint8 value);
void    WAVE_SIG_SetDriveMode(uint8 mode);
uint8   WAVE_SIG_ReadDataReg(void);
uint8   WAVE_SIG_Read(void);
void    WAVE_SIG_SetInterruptMode(uint16 position, uint16 mode);
uint8   WAVE_SIG_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WAVE_SIG_SetDriveMode() function.
     *  @{
     */
        #define WAVE_SIG_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WAVE_SIG_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WAVE_SIG_DM_RES_UP          PIN_DM_RES_UP
        #define WAVE_SIG_DM_RES_DWN         PIN_DM_RES_DWN
        #define WAVE_SIG_DM_OD_LO           PIN_DM_OD_LO
        #define WAVE_SIG_DM_OD_HI           PIN_DM_OD_HI
        #define WAVE_SIG_DM_STRONG          PIN_DM_STRONG
        #define WAVE_SIG_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WAVE_SIG_MASK               WAVE_SIG__MASK
#define WAVE_SIG_SHIFT              WAVE_SIG__SHIFT
#define WAVE_SIG_WIDTH              1u

/* Interrupt constants */
#if defined(WAVE_SIG__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WAVE_SIG_SetInterruptMode() function.
     *  @{
     */
        #define WAVE_SIG_INTR_NONE      (uint16)(0x0000u)
        #define WAVE_SIG_INTR_RISING    (uint16)(0x0001u)
        #define WAVE_SIG_INTR_FALLING   (uint16)(0x0002u)
        #define WAVE_SIG_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WAVE_SIG_INTR_MASK      (0x01u) 
#endif /* (WAVE_SIG__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WAVE_SIG_PS                     (* (reg8 *) WAVE_SIG__PS)
/* Data Register */
#define WAVE_SIG_DR                     (* (reg8 *) WAVE_SIG__DR)
/* Port Number */
#define WAVE_SIG_PRT_NUM                (* (reg8 *) WAVE_SIG__PRT) 
/* Connect to Analog Globals */                                                  
#define WAVE_SIG_AG                     (* (reg8 *) WAVE_SIG__AG)                       
/* Analog MUX bux enable */
#define WAVE_SIG_AMUX                   (* (reg8 *) WAVE_SIG__AMUX) 
/* Bidirectional Enable */                                                        
#define WAVE_SIG_BIE                    (* (reg8 *) WAVE_SIG__BIE)
/* Bit-mask for Aliased Register Access */
#define WAVE_SIG_BIT_MASK               (* (reg8 *) WAVE_SIG__BIT_MASK)
/* Bypass Enable */
#define WAVE_SIG_BYP                    (* (reg8 *) WAVE_SIG__BYP)
/* Port wide control signals */                                                   
#define WAVE_SIG_CTL                    (* (reg8 *) WAVE_SIG__CTL)
/* Drive Modes */
#define WAVE_SIG_DM0                    (* (reg8 *) WAVE_SIG__DM0) 
#define WAVE_SIG_DM1                    (* (reg8 *) WAVE_SIG__DM1)
#define WAVE_SIG_DM2                    (* (reg8 *) WAVE_SIG__DM2) 
/* Input Buffer Disable Override */
#define WAVE_SIG_INP_DIS                (* (reg8 *) WAVE_SIG__INP_DIS)
/* LCD Common or Segment Drive */
#define WAVE_SIG_LCD_COM_SEG            (* (reg8 *) WAVE_SIG__LCD_COM_SEG)
/* Enable Segment LCD */
#define WAVE_SIG_LCD_EN                 (* (reg8 *) WAVE_SIG__LCD_EN)
/* Slew Rate Control */
#define WAVE_SIG_SLW                    (* (reg8 *) WAVE_SIG__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WAVE_SIG_PRTDSI__CAPS_SEL       (* (reg8 *) WAVE_SIG__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WAVE_SIG_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WAVE_SIG__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WAVE_SIG_PRTDSI__OE_SEL0        (* (reg8 *) WAVE_SIG__PRTDSI__OE_SEL0) 
#define WAVE_SIG_PRTDSI__OE_SEL1        (* (reg8 *) WAVE_SIG__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WAVE_SIG_PRTDSI__OUT_SEL0       (* (reg8 *) WAVE_SIG__PRTDSI__OUT_SEL0) 
#define WAVE_SIG_PRTDSI__OUT_SEL1       (* (reg8 *) WAVE_SIG__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WAVE_SIG_PRTDSI__SYNC_OUT       (* (reg8 *) WAVE_SIG__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WAVE_SIG__SIO_CFG)
    #define WAVE_SIG_SIO_HYST_EN        (* (reg8 *) WAVE_SIG__SIO_HYST_EN)
    #define WAVE_SIG_SIO_REG_HIFREQ     (* (reg8 *) WAVE_SIG__SIO_REG_HIFREQ)
    #define WAVE_SIG_SIO_CFG            (* (reg8 *) WAVE_SIG__SIO_CFG)
    #define WAVE_SIG_SIO_DIFF           (* (reg8 *) WAVE_SIG__SIO_DIFF)
#endif /* (WAVE_SIG__SIO_CFG) */

/* Interrupt Registers */
#if defined(WAVE_SIG__INTSTAT)
    #define WAVE_SIG_INTSTAT            (* (reg8 *) WAVE_SIG__INTSTAT)
    #define WAVE_SIG_SNAP               (* (reg8 *) WAVE_SIG__SNAP)
    
	#define WAVE_SIG_0_INTTYPE_REG 		(* (reg8 *) WAVE_SIG__0__INTTYPE)
#endif /* (WAVE_SIG__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WAVE_SIG_H */


/* [] END OF FILE */
