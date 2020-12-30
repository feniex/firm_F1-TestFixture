/*******************************************************************************
* File Name: RTest_DEMUX_COM.h  
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

#if !defined(CY_PINS_RTest_DEMUX_COM_H) /* Pins RTest_DEMUX_COM_H */
#define CY_PINS_RTest_DEMUX_COM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTest_DEMUX_COM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTest_DEMUX_COM__PORT == 15 && ((RTest_DEMUX_COM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTest_DEMUX_COM_Write(uint8 value);
void    RTest_DEMUX_COM_SetDriveMode(uint8 mode);
uint8   RTest_DEMUX_COM_ReadDataReg(void);
uint8   RTest_DEMUX_COM_Read(void);
void    RTest_DEMUX_COM_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTest_DEMUX_COM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTest_DEMUX_COM_SetDriveMode() function.
     *  @{
     */
        #define RTest_DEMUX_COM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTest_DEMUX_COM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTest_DEMUX_COM_DM_RES_UP          PIN_DM_RES_UP
        #define RTest_DEMUX_COM_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTest_DEMUX_COM_DM_OD_LO           PIN_DM_OD_LO
        #define RTest_DEMUX_COM_DM_OD_HI           PIN_DM_OD_HI
        #define RTest_DEMUX_COM_DM_STRONG          PIN_DM_STRONG
        #define RTest_DEMUX_COM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTest_DEMUX_COM_MASK               RTest_DEMUX_COM__MASK
#define RTest_DEMUX_COM_SHIFT              RTest_DEMUX_COM__SHIFT
#define RTest_DEMUX_COM_WIDTH              1u

/* Interrupt constants */
#if defined(RTest_DEMUX_COM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTest_DEMUX_COM_SetInterruptMode() function.
     *  @{
     */
        #define RTest_DEMUX_COM_INTR_NONE      (uint16)(0x0000u)
        #define RTest_DEMUX_COM_INTR_RISING    (uint16)(0x0001u)
        #define RTest_DEMUX_COM_INTR_FALLING   (uint16)(0x0002u)
        #define RTest_DEMUX_COM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTest_DEMUX_COM_INTR_MASK      (0x01u) 
#endif /* (RTest_DEMUX_COM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTest_DEMUX_COM_PS                     (* (reg8 *) RTest_DEMUX_COM__PS)
/* Data Register */
#define RTest_DEMUX_COM_DR                     (* (reg8 *) RTest_DEMUX_COM__DR)
/* Port Number */
#define RTest_DEMUX_COM_PRT_NUM                (* (reg8 *) RTest_DEMUX_COM__PRT) 
/* Connect to Analog Globals */                                                  
#define RTest_DEMUX_COM_AG                     (* (reg8 *) RTest_DEMUX_COM__AG)                       
/* Analog MUX bux enable */
#define RTest_DEMUX_COM_AMUX                   (* (reg8 *) RTest_DEMUX_COM__AMUX) 
/* Bidirectional Enable */                                                        
#define RTest_DEMUX_COM_BIE                    (* (reg8 *) RTest_DEMUX_COM__BIE)
/* Bit-mask for Aliased Register Access */
#define RTest_DEMUX_COM_BIT_MASK               (* (reg8 *) RTest_DEMUX_COM__BIT_MASK)
/* Bypass Enable */
#define RTest_DEMUX_COM_BYP                    (* (reg8 *) RTest_DEMUX_COM__BYP)
/* Port wide control signals */                                                   
#define RTest_DEMUX_COM_CTL                    (* (reg8 *) RTest_DEMUX_COM__CTL)
/* Drive Modes */
#define RTest_DEMUX_COM_DM0                    (* (reg8 *) RTest_DEMUX_COM__DM0) 
#define RTest_DEMUX_COM_DM1                    (* (reg8 *) RTest_DEMUX_COM__DM1)
#define RTest_DEMUX_COM_DM2                    (* (reg8 *) RTest_DEMUX_COM__DM2) 
/* Input Buffer Disable Override */
#define RTest_DEMUX_COM_INP_DIS                (* (reg8 *) RTest_DEMUX_COM__INP_DIS)
/* LCD Common or Segment Drive */
#define RTest_DEMUX_COM_LCD_COM_SEG            (* (reg8 *) RTest_DEMUX_COM__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTest_DEMUX_COM_LCD_EN                 (* (reg8 *) RTest_DEMUX_COM__LCD_EN)
/* Slew Rate Control */
#define RTest_DEMUX_COM_SLW                    (* (reg8 *) RTest_DEMUX_COM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTest_DEMUX_COM_PRTDSI__CAPS_SEL       (* (reg8 *) RTest_DEMUX_COM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTest_DEMUX_COM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTest_DEMUX_COM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTest_DEMUX_COM_PRTDSI__OE_SEL0        (* (reg8 *) RTest_DEMUX_COM__PRTDSI__OE_SEL0) 
#define RTest_DEMUX_COM_PRTDSI__OE_SEL1        (* (reg8 *) RTest_DEMUX_COM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTest_DEMUX_COM_PRTDSI__OUT_SEL0       (* (reg8 *) RTest_DEMUX_COM__PRTDSI__OUT_SEL0) 
#define RTest_DEMUX_COM_PRTDSI__OUT_SEL1       (* (reg8 *) RTest_DEMUX_COM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTest_DEMUX_COM_PRTDSI__SYNC_OUT       (* (reg8 *) RTest_DEMUX_COM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTest_DEMUX_COM__SIO_CFG)
    #define RTest_DEMUX_COM_SIO_HYST_EN        (* (reg8 *) RTest_DEMUX_COM__SIO_HYST_EN)
    #define RTest_DEMUX_COM_SIO_REG_HIFREQ     (* (reg8 *) RTest_DEMUX_COM__SIO_REG_HIFREQ)
    #define RTest_DEMUX_COM_SIO_CFG            (* (reg8 *) RTest_DEMUX_COM__SIO_CFG)
    #define RTest_DEMUX_COM_SIO_DIFF           (* (reg8 *) RTest_DEMUX_COM__SIO_DIFF)
#endif /* (RTest_DEMUX_COM__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTest_DEMUX_COM__INTSTAT)
    #define RTest_DEMUX_COM_INTSTAT            (* (reg8 *) RTest_DEMUX_COM__INTSTAT)
    #define RTest_DEMUX_COM_SNAP               (* (reg8 *) RTest_DEMUX_COM__SNAP)
    
	#define RTest_DEMUX_COM_0_INTTYPE_REG 		(* (reg8 *) RTest_DEMUX_COM__0__INTTYPE)
#endif /* (RTest_DEMUX_COM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTest_DEMUX_COM_H */


/* [] END OF FILE */
