/*******************************************************************************
* File Name: RTest_INPUTS_5.h  
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

#if !defined(CY_PINS_RTest_INPUTS_5_H) /* Pins RTest_INPUTS_5_H */
#define CY_PINS_RTest_INPUTS_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTest_INPUTS_5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTest_INPUTS_5__PORT == 15 && ((RTest_INPUTS_5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTest_INPUTS_5_Write(uint8 value);
void    RTest_INPUTS_5_SetDriveMode(uint8 mode);
uint8   RTest_INPUTS_5_ReadDataReg(void);
uint8   RTest_INPUTS_5_Read(void);
void    RTest_INPUTS_5_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTest_INPUTS_5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTest_INPUTS_5_SetDriveMode() function.
     *  @{
     */
        #define RTest_INPUTS_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTest_INPUTS_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTest_INPUTS_5_DM_RES_UP          PIN_DM_RES_UP
        #define RTest_INPUTS_5_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTest_INPUTS_5_DM_OD_LO           PIN_DM_OD_LO
        #define RTest_INPUTS_5_DM_OD_HI           PIN_DM_OD_HI
        #define RTest_INPUTS_5_DM_STRONG          PIN_DM_STRONG
        #define RTest_INPUTS_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTest_INPUTS_5_MASK               RTest_INPUTS_5__MASK
#define RTest_INPUTS_5_SHIFT              RTest_INPUTS_5__SHIFT
#define RTest_INPUTS_5_WIDTH              1u

/* Interrupt constants */
#if defined(RTest_INPUTS_5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTest_INPUTS_5_SetInterruptMode() function.
     *  @{
     */
        #define RTest_INPUTS_5_INTR_NONE      (uint16)(0x0000u)
        #define RTest_INPUTS_5_INTR_RISING    (uint16)(0x0001u)
        #define RTest_INPUTS_5_INTR_FALLING   (uint16)(0x0002u)
        #define RTest_INPUTS_5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTest_INPUTS_5_INTR_MASK      (0x01u) 
#endif /* (RTest_INPUTS_5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTest_INPUTS_5_PS                     (* (reg8 *) RTest_INPUTS_5__PS)
/* Data Register */
#define RTest_INPUTS_5_DR                     (* (reg8 *) RTest_INPUTS_5__DR)
/* Port Number */
#define RTest_INPUTS_5_PRT_NUM                (* (reg8 *) RTest_INPUTS_5__PRT) 
/* Connect to Analog Globals */                                                  
#define RTest_INPUTS_5_AG                     (* (reg8 *) RTest_INPUTS_5__AG)                       
/* Analog MUX bux enable */
#define RTest_INPUTS_5_AMUX                   (* (reg8 *) RTest_INPUTS_5__AMUX) 
/* Bidirectional Enable */                                                        
#define RTest_INPUTS_5_BIE                    (* (reg8 *) RTest_INPUTS_5__BIE)
/* Bit-mask for Aliased Register Access */
#define RTest_INPUTS_5_BIT_MASK               (* (reg8 *) RTest_INPUTS_5__BIT_MASK)
/* Bypass Enable */
#define RTest_INPUTS_5_BYP                    (* (reg8 *) RTest_INPUTS_5__BYP)
/* Port wide control signals */                                                   
#define RTest_INPUTS_5_CTL                    (* (reg8 *) RTest_INPUTS_5__CTL)
/* Drive Modes */
#define RTest_INPUTS_5_DM0                    (* (reg8 *) RTest_INPUTS_5__DM0) 
#define RTest_INPUTS_5_DM1                    (* (reg8 *) RTest_INPUTS_5__DM1)
#define RTest_INPUTS_5_DM2                    (* (reg8 *) RTest_INPUTS_5__DM2) 
/* Input Buffer Disable Override */
#define RTest_INPUTS_5_INP_DIS                (* (reg8 *) RTest_INPUTS_5__INP_DIS)
/* LCD Common or Segment Drive */
#define RTest_INPUTS_5_LCD_COM_SEG            (* (reg8 *) RTest_INPUTS_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTest_INPUTS_5_LCD_EN                 (* (reg8 *) RTest_INPUTS_5__LCD_EN)
/* Slew Rate Control */
#define RTest_INPUTS_5_SLW                    (* (reg8 *) RTest_INPUTS_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTest_INPUTS_5_PRTDSI__CAPS_SEL       (* (reg8 *) RTest_INPUTS_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTest_INPUTS_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTest_INPUTS_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTest_INPUTS_5_PRTDSI__OE_SEL0        (* (reg8 *) RTest_INPUTS_5__PRTDSI__OE_SEL0) 
#define RTest_INPUTS_5_PRTDSI__OE_SEL1        (* (reg8 *) RTest_INPUTS_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTest_INPUTS_5_PRTDSI__OUT_SEL0       (* (reg8 *) RTest_INPUTS_5__PRTDSI__OUT_SEL0) 
#define RTest_INPUTS_5_PRTDSI__OUT_SEL1       (* (reg8 *) RTest_INPUTS_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTest_INPUTS_5_PRTDSI__SYNC_OUT       (* (reg8 *) RTest_INPUTS_5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTest_INPUTS_5__SIO_CFG)
    #define RTest_INPUTS_5_SIO_HYST_EN        (* (reg8 *) RTest_INPUTS_5__SIO_HYST_EN)
    #define RTest_INPUTS_5_SIO_REG_HIFREQ     (* (reg8 *) RTest_INPUTS_5__SIO_REG_HIFREQ)
    #define RTest_INPUTS_5_SIO_CFG            (* (reg8 *) RTest_INPUTS_5__SIO_CFG)
    #define RTest_INPUTS_5_SIO_DIFF           (* (reg8 *) RTest_INPUTS_5__SIO_DIFF)
#endif /* (RTest_INPUTS_5__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTest_INPUTS_5__INTSTAT)
    #define RTest_INPUTS_5_INTSTAT            (* (reg8 *) RTest_INPUTS_5__INTSTAT)
    #define RTest_INPUTS_5_SNAP               (* (reg8 *) RTest_INPUTS_5__SNAP)
    
	#define RTest_INPUTS_5_0_INTTYPE_REG 		(* (reg8 *) RTest_INPUTS_5__0__INTTYPE)
#endif /* (RTest_INPUTS_5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTest_INPUTS_5_H */


/* [] END OF FILE */
