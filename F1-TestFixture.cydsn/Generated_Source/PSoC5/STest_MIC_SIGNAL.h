/*******************************************************************************
* File Name: STest_MIC_SIGNAL.h  
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

#if !defined(CY_PINS_STest_MIC_SIGNAL_H) /* Pins STest_MIC_SIGNAL_H */
#define CY_PINS_STest_MIC_SIGNAL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "STest_MIC_SIGNAL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 STest_MIC_SIGNAL__PORT == 15 && ((STest_MIC_SIGNAL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    STest_MIC_SIGNAL_Write(uint8 value);
void    STest_MIC_SIGNAL_SetDriveMode(uint8 mode);
uint8   STest_MIC_SIGNAL_ReadDataReg(void);
uint8   STest_MIC_SIGNAL_Read(void);
void    STest_MIC_SIGNAL_SetInterruptMode(uint16 position, uint16 mode);
uint8   STest_MIC_SIGNAL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the STest_MIC_SIGNAL_SetDriveMode() function.
     *  @{
     */
        #define STest_MIC_SIGNAL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define STest_MIC_SIGNAL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define STest_MIC_SIGNAL_DM_RES_UP          PIN_DM_RES_UP
        #define STest_MIC_SIGNAL_DM_RES_DWN         PIN_DM_RES_DWN
        #define STest_MIC_SIGNAL_DM_OD_LO           PIN_DM_OD_LO
        #define STest_MIC_SIGNAL_DM_OD_HI           PIN_DM_OD_HI
        #define STest_MIC_SIGNAL_DM_STRONG          PIN_DM_STRONG
        #define STest_MIC_SIGNAL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define STest_MIC_SIGNAL_MASK               STest_MIC_SIGNAL__MASK
#define STest_MIC_SIGNAL_SHIFT              STest_MIC_SIGNAL__SHIFT
#define STest_MIC_SIGNAL_WIDTH              1u

/* Interrupt constants */
#if defined(STest_MIC_SIGNAL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in STest_MIC_SIGNAL_SetInterruptMode() function.
     *  @{
     */
        #define STest_MIC_SIGNAL_INTR_NONE      (uint16)(0x0000u)
        #define STest_MIC_SIGNAL_INTR_RISING    (uint16)(0x0001u)
        #define STest_MIC_SIGNAL_INTR_FALLING   (uint16)(0x0002u)
        #define STest_MIC_SIGNAL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define STest_MIC_SIGNAL_INTR_MASK      (0x01u) 
#endif /* (STest_MIC_SIGNAL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define STest_MIC_SIGNAL_PS                     (* (reg8 *) STest_MIC_SIGNAL__PS)
/* Data Register */
#define STest_MIC_SIGNAL_DR                     (* (reg8 *) STest_MIC_SIGNAL__DR)
/* Port Number */
#define STest_MIC_SIGNAL_PRT_NUM                (* (reg8 *) STest_MIC_SIGNAL__PRT) 
/* Connect to Analog Globals */                                                  
#define STest_MIC_SIGNAL_AG                     (* (reg8 *) STest_MIC_SIGNAL__AG)                       
/* Analog MUX bux enable */
#define STest_MIC_SIGNAL_AMUX                   (* (reg8 *) STest_MIC_SIGNAL__AMUX) 
/* Bidirectional Enable */                                                        
#define STest_MIC_SIGNAL_BIE                    (* (reg8 *) STest_MIC_SIGNAL__BIE)
/* Bit-mask for Aliased Register Access */
#define STest_MIC_SIGNAL_BIT_MASK               (* (reg8 *) STest_MIC_SIGNAL__BIT_MASK)
/* Bypass Enable */
#define STest_MIC_SIGNAL_BYP                    (* (reg8 *) STest_MIC_SIGNAL__BYP)
/* Port wide control signals */                                                   
#define STest_MIC_SIGNAL_CTL                    (* (reg8 *) STest_MIC_SIGNAL__CTL)
/* Drive Modes */
#define STest_MIC_SIGNAL_DM0                    (* (reg8 *) STest_MIC_SIGNAL__DM0) 
#define STest_MIC_SIGNAL_DM1                    (* (reg8 *) STest_MIC_SIGNAL__DM1)
#define STest_MIC_SIGNAL_DM2                    (* (reg8 *) STest_MIC_SIGNAL__DM2) 
/* Input Buffer Disable Override */
#define STest_MIC_SIGNAL_INP_DIS                (* (reg8 *) STest_MIC_SIGNAL__INP_DIS)
/* LCD Common or Segment Drive */
#define STest_MIC_SIGNAL_LCD_COM_SEG            (* (reg8 *) STest_MIC_SIGNAL__LCD_COM_SEG)
/* Enable Segment LCD */
#define STest_MIC_SIGNAL_LCD_EN                 (* (reg8 *) STest_MIC_SIGNAL__LCD_EN)
/* Slew Rate Control */
#define STest_MIC_SIGNAL_SLW                    (* (reg8 *) STest_MIC_SIGNAL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define STest_MIC_SIGNAL_PRTDSI__CAPS_SEL       (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define STest_MIC_SIGNAL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define STest_MIC_SIGNAL_PRTDSI__OE_SEL0        (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__OE_SEL0) 
#define STest_MIC_SIGNAL_PRTDSI__OE_SEL1        (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define STest_MIC_SIGNAL_PRTDSI__OUT_SEL0       (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__OUT_SEL0) 
#define STest_MIC_SIGNAL_PRTDSI__OUT_SEL1       (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define STest_MIC_SIGNAL_PRTDSI__SYNC_OUT       (* (reg8 *) STest_MIC_SIGNAL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(STest_MIC_SIGNAL__SIO_CFG)
    #define STest_MIC_SIGNAL_SIO_HYST_EN        (* (reg8 *) STest_MIC_SIGNAL__SIO_HYST_EN)
    #define STest_MIC_SIGNAL_SIO_REG_HIFREQ     (* (reg8 *) STest_MIC_SIGNAL__SIO_REG_HIFREQ)
    #define STest_MIC_SIGNAL_SIO_CFG            (* (reg8 *) STest_MIC_SIGNAL__SIO_CFG)
    #define STest_MIC_SIGNAL_SIO_DIFF           (* (reg8 *) STest_MIC_SIGNAL__SIO_DIFF)
#endif /* (STest_MIC_SIGNAL__SIO_CFG) */

/* Interrupt Registers */
#if defined(STest_MIC_SIGNAL__INTSTAT)
    #define STest_MIC_SIGNAL_INTSTAT            (* (reg8 *) STest_MIC_SIGNAL__INTSTAT)
    #define STest_MIC_SIGNAL_SNAP               (* (reg8 *) STest_MIC_SIGNAL__SNAP)
    
	#define STest_MIC_SIGNAL_0_INTTYPE_REG 		(* (reg8 *) STest_MIC_SIGNAL__0__INTTYPE)
#endif /* (STest_MIC_SIGNAL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_STest_MIC_SIGNAL_H */


/* [] END OF FILE */
