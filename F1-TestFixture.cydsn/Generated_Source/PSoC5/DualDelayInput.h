/*******************************************************************************
* File Name: DualDelayInput.h  
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

#if !defined(CY_PINS_DualDelayInput_H) /* Pins DualDelayInput_H */
#define CY_PINS_DualDelayInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DualDelayInput_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DualDelayInput__PORT == 15 && ((DualDelayInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DualDelayInput_Write(uint8 value) ;
void    DualDelayInput_SetDriveMode(uint8 mode) ;
uint8   DualDelayInput_ReadDataReg(void) ;
uint8   DualDelayInput_Read(void) ;
uint8   DualDelayInput_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DualDelayInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DualDelayInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DualDelayInput_DM_RES_UP          PIN_DM_RES_UP
#define DualDelayInput_DM_RES_DWN         PIN_DM_RES_DWN
#define DualDelayInput_DM_OD_LO           PIN_DM_OD_LO
#define DualDelayInput_DM_OD_HI           PIN_DM_OD_HI
#define DualDelayInput_DM_STRONG          PIN_DM_STRONG
#define DualDelayInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DualDelayInput_MASK               DualDelayInput__MASK
#define DualDelayInput_SHIFT              DualDelayInput__SHIFT
#define DualDelayInput_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DualDelayInput_PS                     (* (reg8 *) DualDelayInput__PS)
/* Data Register */
#define DualDelayInput_DR                     (* (reg8 *) DualDelayInput__DR)
/* Port Number */
#define DualDelayInput_PRT_NUM                (* (reg8 *) DualDelayInput__PRT) 
/* Connect to Analog Globals */                                                  
#define DualDelayInput_AG                     (* (reg8 *) DualDelayInput__AG)                       
/* Analog MUX bux enable */
#define DualDelayInput_AMUX                   (* (reg8 *) DualDelayInput__AMUX) 
/* Bidirectional Enable */                                                        
#define DualDelayInput_BIE                    (* (reg8 *) DualDelayInput__BIE)
/* Bit-mask for Aliased Register Access */
#define DualDelayInput_BIT_MASK               (* (reg8 *) DualDelayInput__BIT_MASK)
/* Bypass Enable */
#define DualDelayInput_BYP                    (* (reg8 *) DualDelayInput__BYP)
/* Port wide control signals */                                                   
#define DualDelayInput_CTL                    (* (reg8 *) DualDelayInput__CTL)
/* Drive Modes */
#define DualDelayInput_DM0                    (* (reg8 *) DualDelayInput__DM0) 
#define DualDelayInput_DM1                    (* (reg8 *) DualDelayInput__DM1)
#define DualDelayInput_DM2                    (* (reg8 *) DualDelayInput__DM2) 
/* Input Buffer Disable Override */
#define DualDelayInput_INP_DIS                (* (reg8 *) DualDelayInput__INP_DIS)
/* LCD Common or Segment Drive */
#define DualDelayInput_LCD_COM_SEG            (* (reg8 *) DualDelayInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define DualDelayInput_LCD_EN                 (* (reg8 *) DualDelayInput__LCD_EN)
/* Slew Rate Control */
#define DualDelayInput_SLW                    (* (reg8 *) DualDelayInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DualDelayInput_PRTDSI__CAPS_SEL       (* (reg8 *) DualDelayInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DualDelayInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DualDelayInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DualDelayInput_PRTDSI__OE_SEL0        (* (reg8 *) DualDelayInput__PRTDSI__OE_SEL0) 
#define DualDelayInput_PRTDSI__OE_SEL1        (* (reg8 *) DualDelayInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DualDelayInput_PRTDSI__OUT_SEL0       (* (reg8 *) DualDelayInput__PRTDSI__OUT_SEL0) 
#define DualDelayInput_PRTDSI__OUT_SEL1       (* (reg8 *) DualDelayInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DualDelayInput_PRTDSI__SYNC_OUT       (* (reg8 *) DualDelayInput__PRTDSI__SYNC_OUT) 


#if defined(DualDelayInput__INTSTAT)  /* Interrupt Registers */

    #define DualDelayInput_INTSTAT                (* (reg8 *) DualDelayInput__INTSTAT)
    #define DualDelayInput_SNAP                   (* (reg8 *) DualDelayInput__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DualDelayInput_H */


/* [] END OF FILE */
