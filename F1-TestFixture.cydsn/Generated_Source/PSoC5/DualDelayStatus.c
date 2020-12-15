/*******************************************************************************
* File Name: DualDelayStatus.c  
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

#include "DualDelayStatus.h"

#if !defined(DualDelayStatus_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: DualDelayStatus_Read
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
uint8 DualDelayStatus_Read(void) 
{ 
    return DualDelayStatus_Status;
}


/*******************************************************************************
* Function Name: DualDelayStatus_InterruptEnable
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
void DualDelayStatus_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    DualDelayStatus_Status_Aux_Ctrl |= DualDelayStatus_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: DualDelayStatus_InterruptDisable
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
void DualDelayStatus_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    DualDelayStatus_Status_Aux_Ctrl &= (uint8)(~DualDelayStatus_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: DualDelayStatus_WriteMask
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
void DualDelayStatus_WriteMask(uint8 mask) 
{
    #if(DualDelayStatus_INPUTS < 8u)
    	mask &= ((uint8)(1u << DualDelayStatus_INPUTS) - 1u);
	#endif /* End DualDelayStatus_INPUTS < 8u */
    DualDelayStatus_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: DualDelayStatus_ReadMask
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
uint8 DualDelayStatus_ReadMask(void) 
{
    return DualDelayStatus_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
