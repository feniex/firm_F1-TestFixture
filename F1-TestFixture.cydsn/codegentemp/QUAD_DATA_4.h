/*******************************************************************************
* File Name: QUAD_DATA_4.h  
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

#if !defined(CY_PINS_QUAD_DATA_4_H) /* Pins QUAD_DATA_4_H */
#define CY_PINS_QUAD_DATA_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "QUAD_DATA_4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 QUAD_DATA_4__PORT == 15 && ((QUAD_DATA_4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    QUAD_DATA_4_Write(uint8 value);
void    QUAD_DATA_4_SetDriveMode(uint8 mode);
uint8   QUAD_DATA_4_ReadDataReg(void);
uint8   QUAD_DATA_4_Read(void);
void    QUAD_DATA_4_SetInterruptMode(uint16 position, uint16 mode);
uint8   QUAD_DATA_4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the QUAD_DATA_4_SetDriveMode() function.
     *  @{
     */
        #define QUAD_DATA_4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define QUAD_DATA_4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define QUAD_DATA_4_DM_RES_UP          PIN_DM_RES_UP
        #define QUAD_DATA_4_DM_RES_DWN         PIN_DM_RES_DWN
        #define QUAD_DATA_4_DM_OD_LO           PIN_DM_OD_LO
        #define QUAD_DATA_4_DM_OD_HI           PIN_DM_OD_HI
        #define QUAD_DATA_4_DM_STRONG          PIN_DM_STRONG
        #define QUAD_DATA_4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define QUAD_DATA_4_MASK               QUAD_DATA_4__MASK
#define QUAD_DATA_4_SHIFT              QUAD_DATA_4__SHIFT
#define QUAD_DATA_4_WIDTH              1u

/* Interrupt constants */
#if defined(QUAD_DATA_4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in QUAD_DATA_4_SetInterruptMode() function.
     *  @{
     */
        #define QUAD_DATA_4_INTR_NONE      (uint16)(0x0000u)
        #define QUAD_DATA_4_INTR_RISING    (uint16)(0x0001u)
        #define QUAD_DATA_4_INTR_FALLING   (uint16)(0x0002u)
        #define QUAD_DATA_4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define QUAD_DATA_4_INTR_MASK      (0x01u) 
#endif /* (QUAD_DATA_4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define QUAD_DATA_4_PS                     (* (reg8 *) QUAD_DATA_4__PS)
/* Data Register */
#define QUAD_DATA_4_DR                     (* (reg8 *) QUAD_DATA_4__DR)
/* Port Number */
#define QUAD_DATA_4_PRT_NUM                (* (reg8 *) QUAD_DATA_4__PRT) 
/* Connect to Analog Globals */                                                  
#define QUAD_DATA_4_AG                     (* (reg8 *) QUAD_DATA_4__AG)                       
/* Analog MUX bux enable */
#define QUAD_DATA_4_AMUX                   (* (reg8 *) QUAD_DATA_4__AMUX) 
/* Bidirectional Enable */                                                        
#define QUAD_DATA_4_BIE                    (* (reg8 *) QUAD_DATA_4__BIE)
/* Bit-mask for Aliased Register Access */
#define QUAD_DATA_4_BIT_MASK               (* (reg8 *) QUAD_DATA_4__BIT_MASK)
/* Bypass Enable */
#define QUAD_DATA_4_BYP                    (* (reg8 *) QUAD_DATA_4__BYP)
/* Port wide control signals */                                                   
#define QUAD_DATA_4_CTL                    (* (reg8 *) QUAD_DATA_4__CTL)
/* Drive Modes */
#define QUAD_DATA_4_DM0                    (* (reg8 *) QUAD_DATA_4__DM0) 
#define QUAD_DATA_4_DM1                    (* (reg8 *) QUAD_DATA_4__DM1)
#define QUAD_DATA_4_DM2                    (* (reg8 *) QUAD_DATA_4__DM2) 
/* Input Buffer Disable Override */
#define QUAD_DATA_4_INP_DIS                (* (reg8 *) QUAD_DATA_4__INP_DIS)
/* LCD Common or Segment Drive */
#define QUAD_DATA_4_LCD_COM_SEG            (* (reg8 *) QUAD_DATA_4__LCD_COM_SEG)
/* Enable Segment LCD */
#define QUAD_DATA_4_LCD_EN                 (* (reg8 *) QUAD_DATA_4__LCD_EN)
/* Slew Rate Control */
#define QUAD_DATA_4_SLW                    (* (reg8 *) QUAD_DATA_4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define QUAD_DATA_4_PRTDSI__CAPS_SEL       (* (reg8 *) QUAD_DATA_4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define QUAD_DATA_4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) QUAD_DATA_4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define QUAD_DATA_4_PRTDSI__OE_SEL0        (* (reg8 *) QUAD_DATA_4__PRTDSI__OE_SEL0) 
#define QUAD_DATA_4_PRTDSI__OE_SEL1        (* (reg8 *) QUAD_DATA_4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define QUAD_DATA_4_PRTDSI__OUT_SEL0       (* (reg8 *) QUAD_DATA_4__PRTDSI__OUT_SEL0) 
#define QUAD_DATA_4_PRTDSI__OUT_SEL1       (* (reg8 *) QUAD_DATA_4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define QUAD_DATA_4_PRTDSI__SYNC_OUT       (* (reg8 *) QUAD_DATA_4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(QUAD_DATA_4__SIO_CFG)
    #define QUAD_DATA_4_SIO_HYST_EN        (* (reg8 *) QUAD_DATA_4__SIO_HYST_EN)
    #define QUAD_DATA_4_SIO_REG_HIFREQ     (* (reg8 *) QUAD_DATA_4__SIO_REG_HIFREQ)
    #define QUAD_DATA_4_SIO_CFG            (* (reg8 *) QUAD_DATA_4__SIO_CFG)
    #define QUAD_DATA_4_SIO_DIFF           (* (reg8 *) QUAD_DATA_4__SIO_DIFF)
#endif /* (QUAD_DATA_4__SIO_CFG) */

/* Interrupt Registers */
#if defined(QUAD_DATA_4__INTSTAT)
    #define QUAD_DATA_4_INTSTAT            (* (reg8 *) QUAD_DATA_4__INTSTAT)
    #define QUAD_DATA_4_SNAP               (* (reg8 *) QUAD_DATA_4__SNAP)
    
	#define QUAD_DATA_4_0_INTTYPE_REG 		(* (reg8 *) QUAD_DATA_4__0__INTTYPE)
#endif /* (QUAD_DATA_4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_QUAD_DATA_4_H */


/* [] END OF FILE */
