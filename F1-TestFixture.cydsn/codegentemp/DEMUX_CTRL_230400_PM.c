/*******************************************************************************
* File Name: DEMUX_CTRL_230400_PM.c
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

#include "DEMUX_CTRL_230400.h"

/* Check for removal by optimization */
#if !defined(DEMUX_CTRL_230400_Sync_ctrl_reg__REMOVED)

static DEMUX_CTRL_230400_BACKUP_STRUCT  DEMUX_CTRL_230400_backup = {0u};

    
/*******************************************************************************
* Function Name: DEMUX_CTRL_230400_SaveConfig
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
void DEMUX_CTRL_230400_SaveConfig(void) 
{
    DEMUX_CTRL_230400_backup.controlState = DEMUX_CTRL_230400_Control;
}


/*******************************************************************************
* Function Name: DEMUX_CTRL_230400_RestoreConfig
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
void DEMUX_CTRL_230400_RestoreConfig(void) 
{
     DEMUX_CTRL_230400_Control = DEMUX_CTRL_230400_backup.controlState;
}


/*******************************************************************************
* Function Name: DEMUX_CTRL_230400_Sleep
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
void DEMUX_CTRL_230400_Sleep(void) 
{
    DEMUX_CTRL_230400_SaveConfig();
}


/*******************************************************************************
* Function Name: DEMUX_CTRL_230400_Wakeup
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
void DEMUX_CTRL_230400_Wakeup(void)  
{
    DEMUX_CTRL_230400_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
