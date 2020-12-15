/*******************************************************************************
* File Name: PowerAmpOutput2.h  
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

#if !defined(CY_PINS_PowerAmpOutput2_H) /* Pins PowerAmpOutput2_H */
#define CY_PINS_PowerAmpOutput2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PowerAmpOutput2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PowerAmpOutput2__PORT == 15 && ((PowerAmpOutput2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PowerAmpOutput1_Write(uint8 value) ;
void    PowerAmpOutput2_SetDriveMode(uint8 mode) ;
uint8   PowerAmpOutput2_ReadDataReg(void) ;
uint8   PowerAmpOutput2_Read(void) ;
uint8   PowerAmpOutput2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PowerAmpOutput2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PowerAmpOutput2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PowerAmpOutput2_DM_RES_UP          PIN_DM_RES_UP
#define PowerAmpOutput2_DM_RES_DWN         PIN_DM_RES_DWN
#define PowerAmpOutput2_DM_OD_LO           PIN_DM_OD_LO
#define PowerAmpOutput2_DM_OD_HI           PIN_DM_OD_HI
#define PowerAmpOutput2_DM_STRONG          PIN_DM_STRONG
#define PowerAmpOutput2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PowerAmpOutput2_MASK               PowerAmpOutput2__MASK
#define PowerAmpOutput2_SHIFT              PowerAmpOutput2__SHIFT
#define PowerAmpOutput2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PowerAmpOutput2_PS                     (* (reg8 *) PowerAmpOutput2__PS)
/* Data Register */
#define PowerAmpOutput2_DR                     (* (reg8 *) PowerAmpOutput2__DR)
/* Port Number */
#define PowerAmpOutput2_PRT_NUM                (* (reg8 *) PowerAmpOutput2__PRT) 
/* Connect to Analog Globals */                                                  
#define PowerAmpOutput2_AG                     (* (reg8 *) PowerAmpOutput2__AG)                       
/* Analog MUX bux enable */
#define PowerAmpOutput2_AMUX                   (* (reg8 *) PowerAmpOutput2__AMUX) 
/* Bidirectional Enable */                                                        
#define PowerAmpOutput2_BIE                    (* (reg8 *) PowerAmpOutput2__BIE)
/* Bit-mask for Aliased Register Access */
#define PowerAmpOutput2_BIT_MASK               (* (reg8 *) PowerAmpOutput2__BIT_MASK)
/* Bypass Enable */
#define PowerAmpOutput2_BYP                    (* (reg8 *) PowerAmpOutput2__BYP)
/* Port wide control signals */                                                   
#define PowerAmpOutput2_CTL                    (* (reg8 *) PowerAmpOutput2__CTL)
/* Drive Modes */
#define PowerAmpOutput2_DM0                    (* (reg8 *) PowerAmpOutput2__DM0) 
#define PowerAmpOutput2_DM1                    (* (reg8 *) PowerAmpOutput2__DM1)
#define PowerAmpOutput2_DM2                    (* (reg8 *) PowerAmpOutput2__DM2) 
/* Input Buffer Disable Override */
#define PowerAmpOutput2_INP_DIS                (* (reg8 *) PowerAmpOutput2__INP_DIS)
/* LCD Common or Segment Drive */
#define PowerAmpOutput2_LCD_COM_SEG            (* (reg8 *) PowerAmpOutput2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PowerAmpOutput2_LCD_EN                 (* (reg8 *) PowerAmpOutput2__LCD_EN)
/* Slew Rate Control */
#define PowerAmpOutput2_SLW                    (* (reg8 *) PowerAmpOutput2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PowerAmpOutput2_PRTDSI__CAPS_SEL       (* (reg8 *) PowerAmpOutput2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PowerAmpOutput2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PowerAmpOutput2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PowerAmpOutput2_PRTDSI__OE_SEL0        (* (reg8 *) PowerAmpOutput2__PRTDSI__OE_SEL0) 
#define PowerAmpOutput2_PRTDSI__OE_SEL1        (* (reg8 *) PowerAmpOutput2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PowerAmpOutput2_PRTDSI__OUT_SEL0       (* (reg8 *) PowerAmpOutput2__PRTDSI__OUT_SEL0) 
#define PowerAmpOutput2_PRTDSI__OUT_SEL1       (* (reg8 *) PowerAmpOutput2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PowerAmpOutput2_PRTDSI__SYNC_OUT       (* (reg8 *) PowerAmpOutput2__PRTDSI__SYNC_OUT) 


#if defined(PowerAmpOutput2__INTSTAT)  /* Interrupt Registers */

    #define PowerAmpOutput2_INTSTAT                (* (reg8 *) PowerAmpOutput2__INTSTAT)
    #define PowerAmpOutput2_SNAP                   (* (reg8 *) PowerAmpOutput2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PowerAmpOutput2_H */


/* [] END OF FILE */
