/*******************************************************************************
* File Name: RELAY_DATALINK_2_RS485_RX.h  
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

#if !defined(CY_PINS_RELAY_DATALINK_2_RS485_RX_H) /* Pins RELAY_DATALINK_2_RS485_RX_H */
#define CY_PINS_RELAY_DATALINK_2_RS485_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RELAY_DATALINK_2_RS485_RX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RELAY_DATALINK_2_RS485_RX__PORT == 15 && ((RELAY_DATALINK_2_RS485_RX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RELAY_DATALINK_2_RS485_RX_Write(uint8 value);
void    RELAY_DATALINK_2_RS485_RX_SetDriveMode(uint8 mode);
uint8   RELAY_DATALINK_2_RS485_RX_ReadDataReg(void);
uint8   RELAY_DATALINK_2_RS485_RX_Read(void);
void    RELAY_DATALINK_2_RS485_RX_SetInterruptMode(uint16 position, uint16 mode);
uint8   RELAY_DATALINK_2_RS485_RX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RELAY_DATALINK_2_RS485_RX_SetDriveMode() function.
     *  @{
     */
        #define RELAY_DATALINK_2_RS485_RX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RELAY_DATALINK_2_RS485_RX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RELAY_DATALINK_2_RS485_RX_DM_RES_UP          PIN_DM_RES_UP
        #define RELAY_DATALINK_2_RS485_RX_DM_RES_DWN         PIN_DM_RES_DWN
        #define RELAY_DATALINK_2_RS485_RX_DM_OD_LO           PIN_DM_OD_LO
        #define RELAY_DATALINK_2_RS485_RX_DM_OD_HI           PIN_DM_OD_HI
        #define RELAY_DATALINK_2_RS485_RX_DM_STRONG          PIN_DM_STRONG
        #define RELAY_DATALINK_2_RS485_RX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RELAY_DATALINK_2_RS485_RX_MASK               RELAY_DATALINK_2_RS485_RX__MASK
#define RELAY_DATALINK_2_RS485_RX_SHIFT              RELAY_DATALINK_2_RS485_RX__SHIFT
#define RELAY_DATALINK_2_RS485_RX_WIDTH              1u

/* Interrupt constants */
#if defined(RELAY_DATALINK_2_RS485_RX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RELAY_DATALINK_2_RS485_RX_SetInterruptMode() function.
     *  @{
     */
        #define RELAY_DATALINK_2_RS485_RX_INTR_NONE      (uint16)(0x0000u)
        #define RELAY_DATALINK_2_RS485_RX_INTR_RISING    (uint16)(0x0001u)
        #define RELAY_DATALINK_2_RS485_RX_INTR_FALLING   (uint16)(0x0002u)
        #define RELAY_DATALINK_2_RS485_RX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RELAY_DATALINK_2_RS485_RX_INTR_MASK      (0x01u) 
#endif /* (RELAY_DATALINK_2_RS485_RX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RELAY_DATALINK_2_RS485_RX_PS                     (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PS)
/* Data Register */
#define RELAY_DATALINK_2_RS485_RX_DR                     (* (reg8 *) RELAY_DATALINK_2_RS485_RX__DR)
/* Port Number */
#define RELAY_DATALINK_2_RS485_RX_PRT_NUM                (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRT) 
/* Connect to Analog Globals */                                                  
#define RELAY_DATALINK_2_RS485_RX_AG                     (* (reg8 *) RELAY_DATALINK_2_RS485_RX__AG)                       
/* Analog MUX bux enable */
#define RELAY_DATALINK_2_RS485_RX_AMUX                   (* (reg8 *) RELAY_DATALINK_2_RS485_RX__AMUX) 
/* Bidirectional Enable */                                                        
#define RELAY_DATALINK_2_RS485_RX_BIE                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__BIE)
/* Bit-mask for Aliased Register Access */
#define RELAY_DATALINK_2_RS485_RX_BIT_MASK               (* (reg8 *) RELAY_DATALINK_2_RS485_RX__BIT_MASK)
/* Bypass Enable */
#define RELAY_DATALINK_2_RS485_RX_BYP                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__BYP)
/* Port wide control signals */                                                   
#define RELAY_DATALINK_2_RS485_RX_CTL                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__CTL)
/* Drive Modes */
#define RELAY_DATALINK_2_RS485_RX_DM0                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__DM0) 
#define RELAY_DATALINK_2_RS485_RX_DM1                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__DM1)
#define RELAY_DATALINK_2_RS485_RX_DM2                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__DM2) 
/* Input Buffer Disable Override */
#define RELAY_DATALINK_2_RS485_RX_INP_DIS                (* (reg8 *) RELAY_DATALINK_2_RS485_RX__INP_DIS)
/* LCD Common or Segment Drive */
#define RELAY_DATALINK_2_RS485_RX_LCD_COM_SEG            (* (reg8 *) RELAY_DATALINK_2_RS485_RX__LCD_COM_SEG)
/* Enable Segment LCD */
#define RELAY_DATALINK_2_RS485_RX_LCD_EN                 (* (reg8 *) RELAY_DATALINK_2_RS485_RX__LCD_EN)
/* Slew Rate Control */
#define RELAY_DATALINK_2_RS485_RX_SLW                    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__CAPS_SEL       (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__OE_SEL0        (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__OE_SEL0) 
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__OE_SEL1        (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__OUT_SEL0       (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__OUT_SEL0) 
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__OUT_SEL1       (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RELAY_DATALINK_2_RS485_RX_PRTDSI__SYNC_OUT       (* (reg8 *) RELAY_DATALINK_2_RS485_RX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RELAY_DATALINK_2_RS485_RX__SIO_CFG)
    #define RELAY_DATALINK_2_RS485_RX_SIO_HYST_EN        (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SIO_HYST_EN)
    #define RELAY_DATALINK_2_RS485_RX_SIO_REG_HIFREQ     (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SIO_REG_HIFREQ)
    #define RELAY_DATALINK_2_RS485_RX_SIO_CFG            (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SIO_CFG)
    #define RELAY_DATALINK_2_RS485_RX_SIO_DIFF           (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SIO_DIFF)
#endif /* (RELAY_DATALINK_2_RS485_RX__SIO_CFG) */

/* Interrupt Registers */
#if defined(RELAY_DATALINK_2_RS485_RX__INTSTAT)
    #define RELAY_DATALINK_2_RS485_RX_INTSTAT            (* (reg8 *) RELAY_DATALINK_2_RS485_RX__INTSTAT)
    #define RELAY_DATALINK_2_RS485_RX_SNAP               (* (reg8 *) RELAY_DATALINK_2_RS485_RX__SNAP)
    
	#define RELAY_DATALINK_2_RS485_RX_0_INTTYPE_REG 		(* (reg8 *) RELAY_DATALINK_2_RS485_RX__0__INTTYPE)
#endif /* (RELAY_DATALINK_2_RS485_RX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RELAY_DATALINK_2_RS485_RX_H */


/* [] END OF FILE */
