/*******************************************************************************
* File Name: DACtimer2_PM.c
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

#include "DACtimer2.h"

static DACtimer2_backupStruct DACtimer2_backup;


/*******************************************************************************
* Function Name: DACtimer2_SaveConfig
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
*  DACtimer2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DACtimer2_SaveConfig(void) 
{
    #if (!DACtimer2_UsingFixedFunction)
        DACtimer2_backup.TimerUdb = DACtimer2_ReadCounter();
        DACtimer2_backup.InterruptMaskValue = DACtimer2_STATUS_MASK;
        #if (DACtimer2_UsingHWCaptureCounter)
            DACtimer2_backup.TimerCaptureCounter = DACtimer2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DACtimer2_UDB_CONTROL_REG_REMOVED)
            DACtimer2_backup.TimerControlRegister = DACtimer2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DACtimer2_RestoreConfig
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
*  DACtimer2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DACtimer2_RestoreConfig(void) 
{   
    #if (!DACtimer2_UsingFixedFunction)

        DACtimer2_WriteCounter(DACtimer2_backup.TimerUdb);
        DACtimer2_STATUS_MASK =DACtimer2_backup.InterruptMaskValue;
        #if (DACtimer2_UsingHWCaptureCounter)
            DACtimer2_SetCaptureCount(DACtimer2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DACtimer2_UDB_CONTROL_REG_REMOVED)
            DACtimer2_WriteControlRegister(DACtimer2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DACtimer2_Sleep
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
*  DACtimer2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DACtimer2_Sleep(void) 
{
    #if(!DACtimer2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DACtimer2_CTRL_ENABLE == (DACtimer2_CONTROL & DACtimer2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DACtimer2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DACtimer2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DACtimer2_Stop();
    DACtimer2_SaveConfig();
}


/*******************************************************************************
* Function Name: DACtimer2_Wakeup
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
*  DACtimer2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DACtimer2_Wakeup(void) 
{
    DACtimer2_RestoreConfig();
    #if(!DACtimer2_UDB_CONTROL_REG_REMOVED)
        if(DACtimer2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DACtimer2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
