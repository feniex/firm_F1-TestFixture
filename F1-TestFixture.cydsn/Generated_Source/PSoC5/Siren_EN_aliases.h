/*******************************************************************************
* File Name: Siren_EN.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Siren_EN_ALIASES_H) /* Pins Siren_EN_ALIASES_H */
#define CY_PINS_Siren_EN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Siren_EN_0			(Siren_EN__0__PC)
#define Siren_EN_0_INTR	((uint16)((uint16)0x0001u << Siren_EN__0__SHIFT))

#define Siren_EN_INTR_ALL	 ((uint16)(Siren_EN_0_INTR))

#endif /* End Pins Siren_EN_ALIASES_H */


/* [] END OF FILE */
