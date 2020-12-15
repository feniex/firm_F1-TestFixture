/*******************************************************************************
* File Name: PWMtimer2_PM.c
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

#include "PWMtimer2.h"

static PWMtimer2_backupStruct PWMtimer2_backup;


/*******************************************************************************
* Function Name: PWMtimer2_SaveConfig
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
*  PWMtimer2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMtimer2_SaveConfig(void) 
{
    #if (!PWMtimer2_UsingFixedFunction)
        PWMtimer2_backup.TimerUdb = PWMtimer2_ReadCounter();
        PWMtimer2_backup.InterruptMaskValue = PWMtimer2_STATUS_MASK;
        #if (PWMtimer2_UsingHWCaptureCounter)
            PWMtimer2_backup.TimerCaptureCounter = PWMtimer2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PWMtimer2_UDB_CONTROL_REG_REMOVED)
            PWMtimer2_backup.TimerControlRegister = PWMtimer2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PWMtimer2_RestoreConfig
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
*  PWMtimer2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMtimer2_RestoreConfig(void) 
{   
    #if (!PWMtimer2_UsingFixedFunction)

        PWMtimer2_WriteCounter(PWMtimer2_backup.TimerUdb);
        PWMtimer2_STATUS_MASK =PWMtimer2_backup.InterruptMaskValue;
        #if (PWMtimer2_UsingHWCaptureCounter)
            PWMtimer2_SetCaptureCount(PWMtimer2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PWMtimer2_UDB_CONTROL_REG_REMOVED)
            PWMtimer2_WriteControlRegister(PWMtimer2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PWMtimer2_Sleep
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
*  PWMtimer2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMtimer2_Sleep(void) 
{
    #if(!PWMtimer2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PWMtimer2_CTRL_ENABLE == (PWMtimer2_CONTROL & PWMtimer2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PWMtimer2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PWMtimer2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PWMtimer2_Stop();
    PWMtimer2_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMtimer2_Wakeup
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
*  PWMtimer2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMtimer2_Wakeup(void) 
{
    PWMtimer2_RestoreConfig();
    #if(!PWMtimer2_UDB_CONTROL_REG_REMOVED)
        if(PWMtimer2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PWMtimer2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
