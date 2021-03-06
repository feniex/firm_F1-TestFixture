/*******************************************************************************
* File Name: STest_RRB_SIGNAL.h  
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

#if !defined(CY_PINS_STest_RRB_SIGNAL_ALIASES_H) /* Pins STest_RRB_SIGNAL_ALIASES_H */
#define CY_PINS_STest_RRB_SIGNAL_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define STest_RRB_SIGNAL_0			(STest_RRB_SIGNAL__0__PC)
#define STest_RRB_SIGNAL_0_INTR	((uint16)((uint16)0x0001u << STest_RRB_SIGNAL__0__SHIFT))

#define STest_RRB_SIGNAL_INTR_ALL	 ((uint16)(STest_RRB_SIGNAL_0_INTR))

#endif /* End Pins STest_RRB_SIGNAL_ALIASES_H */


/* [] END OF FILE */
