/*******************************************************************************
* File Name: SecondsTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SecondsTimer.h"

static SecondsTimer_backupStruct SecondsTimer_backup;


/*******************************************************************************
* Function Name: SecondsTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SecondsTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SecondsTimer_SaveConfig(void) 
{
    #if (!SecondsTimer_UsingFixedFunction)
        SecondsTimer_backup.TimerUdb = SecondsTimer_ReadCounter();
        SecondsTimer_backup.InterruptMaskValue = SecondsTimer_STATUS_MASK;
        #if (SecondsTimer_UsingHWCaptureCounter)
            SecondsTimer_backup.TimerCaptureCounter = SecondsTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SecondsTimer_UDB_CONTROL_REG_REMOVED)
            SecondsTimer_backup.TimerControlRegister = SecondsTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SecondsTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SecondsTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SecondsTimer_RestoreConfig(void) 
{   
    #if (!SecondsTimer_UsingFixedFunction)

        SecondsTimer_WriteCounter(SecondsTimer_backup.TimerUdb);
        SecondsTimer_STATUS_MASK =SecondsTimer_backup.InterruptMaskValue;
        #if (SecondsTimer_UsingHWCaptureCounter)
            SecondsTimer_SetCaptureCount(SecondsTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SecondsTimer_UDB_CONTROL_REG_REMOVED)
            SecondsTimer_WriteControlRegister(SecondsTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SecondsTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SecondsTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SecondsTimer_Sleep(void) 
{
    #if(!SecondsTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SecondsTimer_CTRL_ENABLE == (SecondsTimer_CONTROL & SecondsTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SecondsTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SecondsTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SecondsTimer_Stop();
    SecondsTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SecondsTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SecondsTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SecondsTimer_Wakeup(void) 
{
    SecondsTimer_RestoreConfig();
    #if(!SecondsTimer_UDB_CONTROL_REG_REMOVED)
        if(SecondsTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SecondsTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
