/*******************************************************************************
* File Name: HornRingStatus.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HornRingStatus.h"

#if !defined(HornRingStatus_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: HornRingStatus_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 HornRingStatus_Read(void) 
{ 
    return HornRingStatus_Status;
}


/*******************************************************************************
* Function Name: HornRingStatus_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void HornRingStatus_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    HornRingStatus_Status_Aux_Ctrl |= HornRingStatus_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: HornRingStatus_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void HornRingStatus_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    HornRingStatus_Status_Aux_Ctrl &= (uint8)(~HornRingStatus_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: HornRingStatus_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void HornRingStatus_WriteMask(uint8 mask) 
{
    #if(HornRingStatus_INPUTS < 8u)
    	mask &= ((uint8)(1u << HornRingStatus_INPUTS) - 1u);
	#endif /* End HornRingStatus_INPUTS < 8u */
    HornRingStatus_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: HornRingStatus_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 HornRingStatus_ReadMask(void) 
{
    return HornRingStatus_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
