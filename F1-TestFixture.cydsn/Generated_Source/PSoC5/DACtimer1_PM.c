/*******************************************************************************
* File Name: DACtimer1_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "DACtimer1.h"

static DACtimer1_backupStruct DACtimer1_backup;


/*******************************************************************************
* Function Name: DACtimer1_SaveConfig
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
*  DACtimer1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DACtimer1_SaveConfig(void) 
{
    #if (!DACtimer1_UsingFixedFunction)
        DACtimer1_backup.TimerUdb = DACtimer1_ReadCounter();
        DACtimer1_backup.InterruptMaskValue = DACtimer1_STATUS_MASK;
        #if (DACtimer1_UsingHWCaptureCounter)
            DACtimer1_backup.TimerCaptureCounter = DACtimer1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DACtimer1_UDB_CONTROL_REG_REMOVED)
            DACtimer1_backup.TimerControlRegister = DACtimer1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DACtimer1_RestoreConfig
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
*  DACtimer1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DACtimer1_RestoreConfig(void) 
{   
    #if (!DACtimer1_UsingFixedFunction)

        DACtimer1_WriteCounter(DACtimer1_backup.TimerUdb);
        DACtimer1_STATUS_MASK =DACtimer1_backup.InterruptMaskValue;
        #if (DACtimer1_UsingHWCaptureCounter)
            DACtimer1_SetCaptureCount(DACtimer1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DACtimer1_UDB_CONTROL_REG_REMOVED)
            DACtimer1_WriteControlRegister(DACtimer1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DACtimer1_Sleep
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
*  DACtimer1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DACtimer1_Sleep(void) 
{
    #if(!DACtimer1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DACtimer1_CTRL_ENABLE == (DACtimer1_CONTROL & DACtimer1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DACtimer1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DACtimer1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DACtimer1_Stop();
    DACtimer1_SaveConfig();
}


/*******************************************************************************
* Function Name: DACtimer1_Wakeup
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
*  DACtimer1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DACtimer1_Wakeup(void) 
{
    DACtimer1_RestoreConfig();
    #if(!DACtimer1_UDB_CONTROL_REG_REMOVED)
        if(DACtimer1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DACtimer1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
