/*******************************************************************************
* File Name: ParkKillInput.h  
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

#if !defined(CY_PINS_ParkKillInput_H) /* Pins ParkKillInput_H */
#define CY_PINS_ParkKillInput_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ParkKillInput_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ParkKillInput__PORT == 15 && ((ParkKillInput__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ParkKillInput_Write(uint8 value) ;
void    ParkKillInput_SetDriveMode(uint8 mode) ;
uint8   ParkKillInput_ReadDataReg(void) ;
uint8   ParkKillInput_Read(void) ;
uint8   ParkKillInput_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ParkKillInput_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ParkKillInput_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ParkKillInput_DM_RES_UP          PIN_DM_RES_UP
#define ParkKillInput_DM_RES_DWN         PIN_DM_RES_DWN
#define ParkKillInput_DM_OD_LO           PIN_DM_OD_LO
#define ParkKillInput_DM_OD_HI           PIN_DM_OD_HI
#define ParkKillInput_DM_STRONG          PIN_DM_STRONG
#define ParkKillInput_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ParkKillInput_MASK               ParkKillInput__MASK
#define ParkKillInput_SHIFT              ParkKillInput__SHIFT
#define ParkKillInput_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ParkKillInput_PS                     (* (reg8 *) ParkKillInput__PS)
/* Data Register */
#define ParkKillInput_DR                     (* (reg8 *) ParkKillInput__DR)
/* Port Number */
#define ParkKillInput_PRT_NUM                (* (reg8 *) ParkKillInput__PRT) 
/* Connect to Analog Globals */                                                  
#define ParkKillInput_AG                     (* (reg8 *) ParkKillInput__AG)                       
/* Analog MUX bux enable */
#define ParkKillInput_AMUX                   (* (reg8 *) ParkKillInput__AMUX) 
/* Bidirectional Enable */                                                        
#define ParkKillInput_BIE                    (* (reg8 *) ParkKillInput__BIE)
/* Bit-mask for Aliased Register Access */
#define ParkKillInput_BIT_MASK               (* (reg8 *) ParkKillInput__BIT_MASK)
/* Bypass Enable */
#define ParkKillInput_BYP                    (* (reg8 *) ParkKillInput__BYP)
/* Port wide control signals */                                                   
#define ParkKillInput_CTL                    (* (reg8 *) ParkKillInput__CTL)
/* Drive Modes */
#define ParkKillInput_DM0                    (* (reg8 *) ParkKillInput__DM0) 
#define ParkKillInput_DM1                    (* (reg8 *) ParkKillInput__DM1)
#define ParkKillInput_DM2                    (* (reg8 *) ParkKillInput__DM2) 
/* Input Buffer Disable Override */
#define ParkKillInput_INP_DIS                (* (reg8 *) ParkKillInput__INP_DIS)
/* LCD Common or Segment Drive */
#define ParkKillInput_LCD_COM_SEG            (* (reg8 *) ParkKillInput__LCD_COM_SEG)
/* Enable Segment LCD */
#define ParkKillInput_LCD_EN                 (* (reg8 *) ParkKillInput__LCD_EN)
/* Slew Rate Control */
#define ParkKillInput_SLW                    (* (reg8 *) ParkKillInput__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ParkKillInput_PRTDSI__CAPS_SEL       (* (reg8 *) ParkKillInput__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ParkKillInput_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ParkKillInput__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ParkKillInput_PRTDSI__OE_SEL0        (* (reg8 *) ParkKillInput__PRTDSI__OE_SEL0) 
#define ParkKillInput_PRTDSI__OE_SEL1        (* (reg8 *) ParkKillInput__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ParkKillInput_PRTDSI__OUT_SEL0       (* (reg8 *) ParkKillInput__PRTDSI__OUT_SEL0) 
#define ParkKillInput_PRTDSI__OUT_SEL1       (* (reg8 *) ParkKillInput__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ParkKillInput_PRTDSI__SYNC_OUT       (* (reg8 *) ParkKillInput__PRTDSI__SYNC_OUT) 


#if defined(ParkKillInput__INTSTAT)  /* Interrupt Registers */

    #define ParkKillInput_INTSTAT                (* (reg8 *) ParkKillInput__INTSTAT)
    #define ParkKillInput_SNAP                   (* (reg8 *) ParkKillInput__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ParkKillInput_H */


/* [] END OF FILE */
