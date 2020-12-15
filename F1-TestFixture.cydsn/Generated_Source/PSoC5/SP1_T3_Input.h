/*******************************************************************************
* File Name: SP1_T3_Input.h  
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

#if !defined(CY_PINS_SP1_T3_Input_H) /* Pins SP1_T3_Input_H */
#define CY_PINS_SP1_T3_Input_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SP1_T3_Input_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SP1_T3_Input__PORT == 15 && ((SP1_T3_Input__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SP1_T3_Input_Write(uint8 value) ;
void    SP1_T3_Input_SetDriveMode(uint8 mode) ;
uint8   SP1_T3_Input_ReadDataReg(void) ;
uint8   SP1_T3_Input_Read(void) ;
uint8   SP1_T3_Input_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SP1_T3_Input_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SP1_T3_Input_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SP1_T3_Input_DM_RES_UP          PIN_DM_RES_UP
#define SP1_T3_Input_DM_RES_DWN         PIN_DM_RES_DWN
#define SP1_T3_Input_DM_OD_LO           PIN_DM_OD_LO
#define SP1_T3_Input_DM_OD_HI           PIN_DM_OD_HI
#define SP1_T3_Input_DM_STRONG          PIN_DM_STRONG
#define SP1_T3_Input_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SP1_T3_Input_MASK               SP1_T3_Input__MASK
#define SP1_T3_Input_SHIFT              SP1_T3_Input__SHIFT
#define SP1_T3_Input_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SP1_T3_Input_PS                     (* (reg8 *) SP1_T3_Input__PS)
/* Data Register */
#define SP1_T3_Input_DR                     (* (reg8 *) SP1_T3_Input__DR)
/* Port Number */
#define SP1_T3_Input_PRT_NUM                (* (reg8 *) SP1_T3_Input__PRT) 
/* Connect to Analog Globals */                                                  
#define SP1_T3_Input_AG                     (* (reg8 *) SP1_T3_Input__AG)                       
/* Analog MUX bux enable */
#define SP1_T3_Input_AMUX                   (* (reg8 *) SP1_T3_Input__AMUX) 
/* Bidirectional Enable */                                                        
#define SP1_T3_Input_BIE                    (* (reg8 *) SP1_T3_Input__BIE)
/* Bit-mask for Aliased Register Access */
#define SP1_T3_Input_BIT_MASK               (* (reg8 *) SP1_T3_Input__BIT_MASK)
/* Bypass Enable */
#define SP1_T3_Input_BYP                    (* (reg8 *) SP1_T3_Input__BYP)
/* Port wide control signals */                                                   
#define SP1_T3_Input_CTL                    (* (reg8 *) SP1_T3_Input__CTL)
/* Drive Modes */
#define SP1_T3_Input_DM0                    (* (reg8 *) SP1_T3_Input__DM0) 
#define SP1_T3_Input_DM1                    (* (reg8 *) SP1_T3_Input__DM1)
#define SP1_T3_Input_DM2                    (* (reg8 *) SP1_T3_Input__DM2) 
/* Input Buffer Disable Override */
#define SP1_T3_Input_INP_DIS                (* (reg8 *) SP1_T3_Input__INP_DIS)
/* LCD Common or Segment Drive */
#define SP1_T3_Input_LCD_COM_SEG            (* (reg8 *) SP1_T3_Input__LCD_COM_SEG)
/* Enable Segment LCD */
#define SP1_T3_Input_LCD_EN                 (* (reg8 *) SP1_T3_Input__LCD_EN)
/* Slew Rate Control */
#define SP1_T3_Input_SLW                    (* (reg8 *) SP1_T3_Input__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SP1_T3_Input_PRTDSI__CAPS_SEL       (* (reg8 *) SP1_T3_Input__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SP1_T3_Input_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SP1_T3_Input__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SP1_T3_Input_PRTDSI__OE_SEL0        (* (reg8 *) SP1_T3_Input__PRTDSI__OE_SEL0) 
#define SP1_T3_Input_PRTDSI__OE_SEL1        (* (reg8 *) SP1_T3_Input__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SP1_T3_Input_PRTDSI__OUT_SEL0       (* (reg8 *) SP1_T3_Input__PRTDSI__OUT_SEL0) 
#define SP1_T3_Input_PRTDSI__OUT_SEL1       (* (reg8 *) SP1_T3_Input__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SP1_T3_Input_PRTDSI__SYNC_OUT       (* (reg8 *) SP1_T3_Input__PRTDSI__SYNC_OUT) 


#if defined(SP1_T3_Input__INTSTAT)  /* Interrupt Registers */

    #define SP1_T3_Input_INTSTAT                (* (reg8 *) SP1_T3_Input__INTSTAT)
    #define SP1_T3_Input_SNAP                   (* (reg8 *) SP1_T3_Input__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SP1_T3_Input_H */


/* [] END OF FILE */
