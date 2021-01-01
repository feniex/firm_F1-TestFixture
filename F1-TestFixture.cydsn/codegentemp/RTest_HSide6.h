/*******************************************************************************
* File Name: RTest_HSide6.h  
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

#if !defined(CY_PINS_RTest_HSide6_H) /* Pins RTest_HSide6_H */
#define CY_PINS_RTest_HSide6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTest_HSide6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTest_HSide6__PORT == 15 && ((RTest_HSide6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTest_HSide6_Write(uint8 value);
void    RTest_HSide6_SetDriveMode(uint8 mode);
uint8   RTest_HSide6_ReadDataReg(void);
uint8   RTest_HSide6_Read(void);
void    RTest_HSide6_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTest_HSide6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTest_HSide6_SetDriveMode() function.
     *  @{
     */
        #define RTest_HSide6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTest_HSide6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTest_HSide6_DM_RES_UP          PIN_DM_RES_UP
        #define RTest_HSide6_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTest_HSide6_DM_OD_LO           PIN_DM_OD_LO
        #define RTest_HSide6_DM_OD_HI           PIN_DM_OD_HI
        #define RTest_HSide6_DM_STRONG          PIN_DM_STRONG
        #define RTest_HSide6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTest_HSide6_MASK               RTest_HSide6__MASK
#define RTest_HSide6_SHIFT              RTest_HSide6__SHIFT
#define RTest_HSide6_WIDTH              1u

/* Interrupt constants */
#if defined(RTest_HSide6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTest_HSide6_SetInterruptMode() function.
     *  @{
     */
        #define RTest_HSide6_INTR_NONE      (uint16)(0x0000u)
        #define RTest_HSide6_INTR_RISING    (uint16)(0x0001u)
        #define RTest_HSide6_INTR_FALLING   (uint16)(0x0002u)
        #define RTest_HSide6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTest_HSide6_INTR_MASK      (0x01u) 
#endif /* (RTest_HSide6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTest_HSide6_PS                     (* (reg8 *) RTest_HSide6__PS)
/* Data Register */
#define RTest_HSide6_DR                     (* (reg8 *) RTest_HSide6__DR)
/* Port Number */
#define RTest_HSide6_PRT_NUM                (* (reg8 *) RTest_HSide6__PRT) 
/* Connect to Analog Globals */                                                  
#define RTest_HSide6_AG                     (* (reg8 *) RTest_HSide6__AG)                       
/* Analog MUX bux enable */
#define RTest_HSide6_AMUX                   (* (reg8 *) RTest_HSide6__AMUX) 
/* Bidirectional Enable */                                                        
#define RTest_HSide6_BIE                    (* (reg8 *) RTest_HSide6__BIE)
/* Bit-mask for Aliased Register Access */
#define RTest_HSide6_BIT_MASK               (* (reg8 *) RTest_HSide6__BIT_MASK)
/* Bypass Enable */
#define RTest_HSide6_BYP                    (* (reg8 *) RTest_HSide6__BYP)
/* Port wide control signals */                                                   
#define RTest_HSide6_CTL                    (* (reg8 *) RTest_HSide6__CTL)
/* Drive Modes */
#define RTest_HSide6_DM0                    (* (reg8 *) RTest_HSide6__DM0) 
#define RTest_HSide6_DM1                    (* (reg8 *) RTest_HSide6__DM1)
#define RTest_HSide6_DM2                    (* (reg8 *) RTest_HSide6__DM2) 
/* Input Buffer Disable Override */
#define RTest_HSide6_INP_DIS                (* (reg8 *) RTest_HSide6__INP_DIS)
/* LCD Common or Segment Drive */
#define RTest_HSide6_LCD_COM_SEG            (* (reg8 *) RTest_HSide6__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTest_HSide6_LCD_EN                 (* (reg8 *) RTest_HSide6__LCD_EN)
/* Slew Rate Control */
#define RTest_HSide6_SLW                    (* (reg8 *) RTest_HSide6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTest_HSide6_PRTDSI__CAPS_SEL       (* (reg8 *) RTest_HSide6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTest_HSide6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTest_HSide6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTest_HSide6_PRTDSI__OE_SEL0        (* (reg8 *) RTest_HSide6__PRTDSI__OE_SEL0) 
#define RTest_HSide6_PRTDSI__OE_SEL1        (* (reg8 *) RTest_HSide6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTest_HSide6_PRTDSI__OUT_SEL0       (* (reg8 *) RTest_HSide6__PRTDSI__OUT_SEL0) 
#define RTest_HSide6_PRTDSI__OUT_SEL1       (* (reg8 *) RTest_HSide6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTest_HSide6_PRTDSI__SYNC_OUT       (* (reg8 *) RTest_HSide6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTest_HSide6__SIO_CFG)
    #define RTest_HSide6_SIO_HYST_EN        (* (reg8 *) RTest_HSide6__SIO_HYST_EN)
    #define RTest_HSide6_SIO_REG_HIFREQ     (* (reg8 *) RTest_HSide6__SIO_REG_HIFREQ)
    #define RTest_HSide6_SIO_CFG            (* (reg8 *) RTest_HSide6__SIO_CFG)
    #define RTest_HSide6_SIO_DIFF           (* (reg8 *) RTest_HSide6__SIO_DIFF)
#endif /* (RTest_HSide6__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTest_HSide6__INTSTAT)
    #define RTest_HSide6_INTSTAT            (* (reg8 *) RTest_HSide6__INTSTAT)
    #define RTest_HSide6_SNAP               (* (reg8 *) RTest_HSide6__SNAP)
    
	#define RTest_HSide6_0_INTTYPE_REG 		(* (reg8 *) RTest_HSide6__0__INTTYPE)
#endif /* (RTest_HSide6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTest_HSide6_H */


/* [] END OF FILE */
