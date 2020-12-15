/*******************************************************************************
* File Name: ModeStatus2.c  
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

#include "ModeStatus2.h"

#if !defined(ModeStatus2_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: ModeStatus2_Read
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
uint8 ModeStatus2_Read(void) 
{ 
    return ModeStatus2_Status;
}


/*******************************************************************************
* Function Name: ModeStatus2_InterruptEnable
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
void ModeStatus2_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ModeStatus2_Status_Aux_Ctrl |= ModeStatus2_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ModeStatus2_InterruptDisable
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
void ModeStatus2_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    ModeStatus2_Status_Aux_Ctrl &= (uint8)(~ModeStatus2_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ModeStatus2_WriteMask
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
void ModeStatus2_WriteMask(uint8 mask) 
{
    #if(ModeStatus2_INPUTS < 8u)
    	mask &= ((uint8)(1u << ModeStatus2_INPUTS) - 1u);
	#endif /* End ModeStatus2_INPUTS < 8u */
    ModeStatus2_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: ModeStatus2_ReadMask
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
uint8 ModeStatus2_ReadMask(void) 
{
    return ModeStatus2_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
