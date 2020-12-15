/*******************************************************************************
* File Name: GPS_TX.h  
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

#if !defined(CY_PINS_GPS_TX_H) /* Pins GPS_TX_H */
#define CY_PINS_GPS_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "GPS_TX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 GPS_TX__PORT == 15 && ((GPS_TX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    GPS_TX_Write(uint8 value);
void    GPS_TX_SetDriveMode(uint8 mode);
uint8   GPS_TX_ReadDataReg(void);
uint8   GPS_TX_Read(void);
void    GPS_TX_SetInterruptMode(uint16 position, uint16 mode);
uint8   GPS_TX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the GPS_TX_SetDriveMode() function.
     *  @{
     */
        #define GPS_TX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define GPS_TX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define GPS_TX_DM_RES_UP          PIN_DM_RES_UP
        #define GPS_TX_DM_RES_DWN         PIN_DM_RES_DWN
        #define GPS_TX_DM_OD_LO           PIN_DM_OD_LO
        #define GPS_TX_DM_OD_HI           PIN_DM_OD_HI
        #define GPS_TX_DM_STRONG          PIN_DM_STRONG
        #define GPS_TX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define GPS_TX_MASK               GPS_TX__MASK
#define GPS_TX_SHIFT              GPS_TX__SHIFT
#define GPS_TX_WIDTH              1u

/* Interrupt constants */
#if defined(GPS_TX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GPS_TX_SetInterruptMode() function.
     *  @{
     */
        #define GPS_TX_INTR_NONE      (uint16)(0x0000u)
        #define GPS_TX_INTR_RISING    (uint16)(0x0001u)
        #define GPS_TX_INTR_FALLING   (uint16)(0x0002u)
        #define GPS_TX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define GPS_TX_INTR_MASK      (0x01u) 
#endif /* (GPS_TX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GPS_TX_PS                     (* (reg8 *) GPS_TX__PS)
/* Data Register */
#define GPS_TX_DR                     (* (reg8 *) GPS_TX__DR)
/* Port Number */
#define GPS_TX_PRT_NUM                (* (reg8 *) GPS_TX__PRT) 
/* Connect to Analog Globals */                                                  
#define GPS_TX_AG                     (* (reg8 *) GPS_TX__AG)                       
/* Analog MUX bux enable */
#define GPS_TX_AMUX                   (* (reg8 *) GPS_TX__AMUX) 
/* Bidirectional Enable */                                                        
#define GPS_TX_BIE                    (* (reg8 *) GPS_TX__BIE)
/* Bit-mask for Aliased Register Access */
#define GPS_TX_BIT_MASK               (* (reg8 *) GPS_TX__BIT_MASK)
/* Bypass Enable */
#define GPS_TX_BYP                    (* (reg8 *) GPS_TX__BYP)
/* Port wide control signals */                                                   
#define GPS_TX_CTL                    (* (reg8 *) GPS_TX__CTL)
/* Drive Modes */
#define GPS_TX_DM0                    (* (reg8 *) GPS_TX__DM0) 
#define GPS_TX_DM1                    (* (reg8 *) GPS_TX__DM1)
#define GPS_TX_DM2                    (* (reg8 *) GPS_TX__DM2) 
/* Input Buffer Disable Override */
#define GPS_TX_INP_DIS                (* (reg8 *) GPS_TX__INP_DIS)
/* LCD Common or Segment Drive */
#define GPS_TX_LCD_COM_SEG            (* (reg8 *) GPS_TX__LCD_COM_SEG)
/* Enable Segment LCD */
#define GPS_TX_LCD_EN                 (* (reg8 *) GPS_TX__LCD_EN)
/* Slew Rate Control */
#define GPS_TX_SLW                    (* (reg8 *) GPS_TX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define GPS_TX_PRTDSI__CAPS_SEL       (* (reg8 *) GPS_TX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define GPS_TX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) GPS_TX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define GPS_TX_PRTDSI__OE_SEL0        (* (reg8 *) GPS_TX__PRTDSI__OE_SEL0) 
#define GPS_TX_PRTDSI__OE_SEL1        (* (reg8 *) GPS_TX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define GPS_TX_PRTDSI__OUT_SEL0       (* (reg8 *) GPS_TX__PRTDSI__OUT_SEL0) 
#define GPS_TX_PRTDSI__OUT_SEL1       (* (reg8 *) GPS_TX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define GPS_TX_PRTDSI__SYNC_OUT       (* (reg8 *) GPS_TX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(GPS_TX__SIO_CFG)
    #define GPS_TX_SIO_HYST_EN        (* (reg8 *) GPS_TX__SIO_HYST_EN)
    #define GPS_TX_SIO_REG_HIFREQ     (* (reg8 *) GPS_TX__SIO_REG_HIFREQ)
    #define GPS_TX_SIO_CFG            (* (reg8 *) GPS_TX__SIO_CFG)
    #define GPS_TX_SIO_DIFF           (* (reg8 *) GPS_TX__SIO_DIFF)
#endif /* (GPS_TX__SIO_CFG) */

/* Interrupt Registers */
#if defined(GPS_TX__INTSTAT)
    #define GPS_TX_INTSTAT            (* (reg8 *) GPS_TX__INTSTAT)
    #define GPS_TX_SNAP               (* (reg8 *) GPS_TX__SNAP)
    
	#define GPS_TX_0_INTTYPE_REG 		(* (reg8 *) GPS_TX__0__INTTYPE)
#endif /* (GPS_TX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_GPS_TX_H */


/* [] END OF FILE */
