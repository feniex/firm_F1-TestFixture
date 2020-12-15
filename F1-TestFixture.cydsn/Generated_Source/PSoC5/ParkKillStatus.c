/*******************************************************************************
* File Name: ParkKillStatus.c  
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

#include "ParkKillStatus.h"

#if !defined(ParkKillStatus_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: ParkKillStatus_Read
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
uint8 ParkKillStatus_Read(void) 
{ 
    return ParkKillStatus_Status;
}


/*******************************************************************************
* Function Name: ParkKillStatus_InterruptEnable
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
void ParkKillStatus_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ParkKillStatus_Status_Aux_Ctrl |= ParkKillStatus_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ParkKillStatus_InterruptDisable
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
void ParkKillStatus_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ParkKillStatus_Status_Aux_Ctrl &= (uint8)(~ParkKillStatus_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ParkKillStatus_WriteMask
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
void ParkKillStatus_WriteMask(uint8 mask) 
{
    #if(ParkKillStatus_INPUTS < 8u)
    	mask &= ((uint8)(1u << ParkKillStatus_INPUTS) - 1u);
	#endif /* End ParkKillStatus_INPUTS < 8u */
    ParkKillStatus_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: ParkKillStatus_ReadMask
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
uint8 ParkKillStatus_ReadMask(void) 
{
    return ParkKillStatus_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
