/*******************************************************************************
* File Name: MUX_CTRL_230400.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MUX_CTRL_230400.h"

/* Check for removal by optimization */
#if !defined(MUX_CTRL_230400_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: MUX_CTRL_230400_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void MUX_CTRL_230400_Write(uint8 control) 
{
    MUX_CTRL_230400_Control = control;
}


/*******************************************************************************
* Function Name: MUX_CTRL_230400_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 MUX_CTRL_230400_Read(void) 
{
    return MUX_CTRL_230400_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
