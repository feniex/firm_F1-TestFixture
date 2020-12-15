/*******************************************************************************
* File Name: HornInput.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_HornInput_H) /* Pins HornInput_H */
#define CY_PINS_HornInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HornInput_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HornInput__PORT == 15 && ((HornInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    HornInput_Write(uint8 value) ;
void    HornInput_SetDriveMode(uint8 mode) ;
uint8   HornInput_ReadDataReg(void) ;
uint8   HornInput_Read(void) ;
uint8   HornInput_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HornInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define HornInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define HornInput_DM_RES_UP          PIN_DM_RES_UP
#define HornInput_DM_RES_DWN         PIN_DM_RES_DWN
#define HornInput_DM_OD_LO           PIN_DM_OD_LO
#define HornInput_DM_OD_HI           PIN_DM_OD_HI
#define HornInput_DM_STRONG          PIN_DM_STRONG
#define HornInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define HornInput_MASK               HornInput__MASK
#define HornInput_SHIFT              HornInput__SHIFT
#define HornInput_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HornInput_PS                     (* (reg8 *) HornInput__PS)
/* Data Register */
#define HornInput_DR                     (* (reg8 *) HornInput__DR)
/* Port Number */
#define HornInput_PRT_NUM                (* (reg8 *) HornInput__PRT) 
/* Connect to Analog Globals */                                                  
#define HornInput_AG                     (* (reg8 *) HornInput__AG)                       
/* Analog MUX bux enable */
#define HornInput_AMUX                   (* (reg8 *) HornInput__AMUX) 
/* Bidirectional Enable */                                                        
#define HornInput_BIE                    (* (reg8 *) HornInput__BIE)
/* Bit-mask for Aliased Register Access */
#define HornInput_BIT_MASK               (* (reg8 *) HornInput__BIT_MASK)
/* Bypass Enable */
#define HornInput_BYP                    (* (reg8 *) HornInput__BYP)
/* Port wide control signals */                                                   
#define HornInput_CTL                    (* (reg8 *) HornInput__CTL)
/* Drive Modes */
#define HornInput_DM0                    (* (reg8 *) HornInput__DM0) 
#define HornInput_DM1                    (* (reg8 *) HornInput__DM1)
#define HornInput_DM2                    (* (reg8 *) HornInput__DM2) 
/* Input Buffer Disable Override */
#define HornInput_INP_DIS                (* (reg8 *) HornInput__INP_DIS)
/* LCD Common or Segment Drive */
#define HornInput_LCD_COM_SEG            (* (reg8 *) HornInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define HornInput_LCD_EN                 (* (reg8 *) HornInput__LCD_EN)
/* Slew Rate Control */
#define HornInput_SLW                    (* (reg8 *) HornInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HornInput_PRTDSI__CAPS_SEL       (* (reg8 *) HornInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HornInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HornInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HornInput_PRTDSI__OE_SEL0        (* (reg8 *) HornInput__PRTDSI__OE_SEL0) 
#define HornInput_PRTDSI__OE_SEL1        (* (reg8 *) HornInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HornInput_PRTDSI__OUT_SEL0       (* (reg8 *) HornInput__PRTDSI__OUT_SEL0) 
#define HornInput_PRTDSI__OUT_SEL1       (* (reg8 *) HornInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HornInput_PRTDSI__SYNC_OUT       (* (reg8 *) HornInput__PRTDSI__SYNC_OUT) 


#if defined(HornInput__INTSTAT)  /* Interrupt Registers */

    #define HornInput_INTSTAT                (* (reg8 *) HornInput__INTSTAT)
    #define HornInput_SNAP                   (* (reg8 *) HornInput__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HornInput_H */


/* [] END OF FILE */
