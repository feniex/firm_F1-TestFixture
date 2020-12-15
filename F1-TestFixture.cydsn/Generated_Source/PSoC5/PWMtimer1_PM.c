/*******************************************************************************
* File Name: PWMtimer1_PM.c
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

#include "PWMtimer1.h"

static PWMtimer1_backupStruct PWMtimer1_backup;


/*******************************************************************************
* Function Name: PWMtimer1_SaveConfig
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
*  PWMtimer1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMtimer1_SaveConfig(void) 
{
    #if (!PWMtimer1_UsingFixedFunction)
        PWMtimer1_backup.TimerUdb = PWMtimer1_ReadCounter();
        PWMtimer1_backup.InterruptMaskValue = PWMtimer1_STATUS_MASK;
        #if (PWMtimer1_UsingHWCaptureCounter)
            PWMtimer1_backup.TimerCaptureCounter = PWMtimer1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PWMtimer1_UDB_CONTROL_REG_REMOVED)
            PWMtimer1_backup.TimerControlRegister = PWMtimer1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PWMtimer1_RestoreConfig
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
*  PWMtimer1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMtimer1_RestoreConfig(void) 
{   
    #if (!PWMtimer1_UsingFixedFunction)

        PWMtimer1_WriteCounter(PWMtimer1_backup.TimerUdb);
        PWMtimer1_STATUS_MASK =PWMtimer1_backup.InterruptMaskValue;
        #if (PWMtimer1_UsingHWCaptureCounter)
            PWMtimer1_SetCaptureCount(PWMtimer1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PWMtimer1_UDB_CONTROL_REG_REMOVED)
            PWMtimer1_WriteControlRegister(PWMtimer1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PWMtimer1_Sleep
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
*  PWMtimer1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMtimer1_Sleep(void) 
{
    #if(!PWMtimer1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PWMtimer1_CTRL_ENABLE == (PWMtimer1_CONTROL & PWMtimer1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PWMtimer1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PWMtimer1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PWMtimer1_Stop();
    PWMtimer1_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMtimer1_Wakeup
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
*  PWMtimer1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMtimer1_Wakeup(void) 
{
    PWMtimer1_RestoreConfig();
    #if(!PWMtimer1_UDB_CONTROL_REG_REMOVED)
        if(PWMtimer1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PWMtimer1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
