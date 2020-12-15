/*******************************************************************************
* File Name: TackSwitchInput.h  
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

#if !defined(CY_PINS_TackSwitchInput_H) /* Pins TackSwitchInput_H */
#define CY_PINS_TackSwitchInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TackSwitchInput_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TackSwitchInput__PORT == 15 && ((TackSwitchInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TackSwitchInput_Write(uint8 value) ;
void    TackSwitchInput_SetDriveMode(uint8 mode) ;
uint8   TackSwitchInput_ReadDataReg(void) ;
uint8   TackSwitchInput_Read(void) ;
uint8   TackSwitchInput_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TackSwitchInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TackSwitchInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TackSwitchInput_DM_RES_UP          PIN_DM_RES_UP
#define TackSwitchInput_DM_RES_DWN         PIN_DM_RES_DWN
#define TackSwitchInput_DM_OD_LO           PIN_DM_OD_LO
#define TackSwitchInput_DM_OD_HI           PIN_DM_OD_HI
#define TackSwitchInput_DM_STRONG          PIN_DM_STRONG
#define TackSwitchInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TackSwitchInput_MASK               TackSwitchInput__MASK
#define TackSwitchInput_SHIFT              TackSwitchInput__SHIFT
#define TackSwitchInput_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TackSwitchInput_PS                     (* (reg8 *) TackSwitchInput__PS)
/* Data Register */
#define TackSwitchInput_DR                     (* (reg8 *) TackSwitchInput__DR)
/* Port Number */
#define TackSwitchInput_PRT_NUM                (* (reg8 *) TackSwitchInput__PRT) 
/* Connect to Analog Globals */                                                  
#define TackSwitchInput_AG                     (* (reg8 *) TackSwitchInput__AG)                       
/* Analog MUX bux enable */
#define TackSwitchInput_AMUX                   (* (reg8 *) TackSwitchInput__AMUX) 
/* Bidirectional Enable */                                                        
#define TackSwitchInput_BIE                    (* (reg8 *) TackSwitchInput__BIE)
/* Bit-mask for Aliased Register Access */
#define TackSwitchInput_BIT_MASK               (* (reg8 *) TackSwitchInput__BIT_MASK)
/* Bypass Enable */
#define TackSwitchInput_BYP                    (* (reg8 *) TackSwitchInput__BYP)
/* Port wide control signals */                                                   
#define TackSwitchInput_CTL                    (* (reg8 *) TackSwitchInput__CTL)
/* Drive Modes */
#define TackSwitchInput_DM0                    (* (reg8 *) TackSwitchInput__DM0) 
#define TackSwitchInput_DM1                    (* (reg8 *) TackSwitchInput__DM1)
#define TackSwitchInput_DM2                    (* (reg8 *) TackSwitchInput__DM2) 
/* Input Buffer Disable Override */
#define TackSwitchInput_INP_DIS                (* (reg8 *) TackSwitchInput__INP_DIS)
/* LCD Common or Segment Drive */
#define TackSwitchInput_LCD_COM_SEG            (* (reg8 *) TackSwitchInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define TackSwitchInput_LCD_EN                 (* (reg8 *) TackSwitchInput__LCD_EN)
/* Slew Rate Control */
#define TackSwitchInput_SLW                    (* (reg8 *) TackSwitchInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TackSwitchInput_PRTDSI__CAPS_SEL       (* (reg8 *) TackSwitchInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TackSwitchInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TackSwitchInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TackSwitchInput_PRTDSI__OE_SEL0        (* (reg8 *) TackSwitchInput__PRTDSI__OE_SEL0) 
#define TackSwitchInput_PRTDSI__OE_SEL1        (* (reg8 *) TackSwitchInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TackSwitchInput_PRTDSI__OUT_SEL0       (* (reg8 *) TackSwitchInput__PRTDSI__OUT_SEL0) 
#define TackSwitchInput_PRTDSI__OUT_SEL1       (* (reg8 *) TackSwitchInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TackSwitchInput_PRTDSI__SYNC_OUT       (* (reg8 *) TackSwitchInput__PRTDSI__SYNC_OUT) 


#if defined(TackSwitchInput__INTSTAT)  /* Interrupt Registers */

    #define TackSwitchInput_INTSTAT                (* (reg8 *) TackSwitchInput__INTSTAT)
    #define TackSwitchInput_SNAP                   (* (reg8 *) TackSwitchInput__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TackSwitchInput_H */


/* [] END OF FILE */
