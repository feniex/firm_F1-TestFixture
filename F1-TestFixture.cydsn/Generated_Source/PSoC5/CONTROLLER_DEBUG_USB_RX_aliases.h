/*******************************************************************************
* File Name: CONTROLLER_DEBUG_USB_RX.h  
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

#if !defined(CY_PINS_CONTROLLER_DEBUG_USB_RX_ALIASES_H) /* Pins CONTROLLER_DEBUG_USB_RX_ALIASES_H */
#define CY_PINS_CONTROLLER_DEBUG_USB_RX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define CONTROLLER_DEBUG_USB_RX_0			(CONTROLLER_DEBUG_USB_RX__0__PC)
#define CONTROLLER_DEBUG_USB_RX_0_INTR	((uint16)((uint16)0x0001u << CONTROLLER_DEBUG_USB_RX__0__SHIFT))

#define CONTROLLER_DEBUG_USB_RX_INTR_ALL	 ((uint16)(CONTROLLER_DEBUG_USB_RX_0_INTR))

#endif /* End Pins CONTROLLER_DEBUG_USB_RX_ALIASES_H */


/* [] END OF FILE */
