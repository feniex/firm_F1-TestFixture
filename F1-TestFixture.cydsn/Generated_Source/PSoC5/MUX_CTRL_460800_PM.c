/*******************************************************************************
* File Name: MUX_CTRL_460800_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "MUX_CTRL_460800.h"

/* Check for removal by optimization */
#if !defined(MUX_CTRL_460800_Sync_ctrl_reg__REMOVED)

static MUX_CTRL_460800_BACKUP_STRUCT  MUX_CTRL_460800_backup = {0u};

    
/*******************************************************************************
* Function Name: MUX_CTRL_460800_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MUX_CTRL_460800_SaveConfig(void) 
{
    MUX_CTRL_460800_backup.controlState = MUX_CTRL_460800_Control;
}


/*******************************************************************************
* Function Name: MUX_CTRL_460800_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void MUX_CTRL_460800_RestoreConfig(void) 
{
     MUX_CTRL_460800_Control = MUX_CTRL_460800_backup.controlState;
}


/*******************************************************************************
* Function Name: MUX_CTRL_460800_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MUX_CTRL_460800_Sleep(void) 
{
    MUX_CTRL_460800_SaveConfig();
}


/*******************************************************************************
* Function Name: MUX_CTRL_460800_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MUX_CTRL_460800_Wakeup(void)  
{
    MUX_CTRL_460800_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
