/*******************************************************************************
* File Name: FrequencyTimer1_PM.c
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

#include "FrequencyTimer1.h"

static FrequencyTimer1_backupStruct FrequencyTimer1_backup;


/*******************************************************************************
* Function Name: FrequencyTimer1_SaveConfig
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
*  FrequencyTimer1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FrequencyTimer1_SaveConfig(void) 
{
    #if (!FrequencyTimer1_UsingFixedFunction)
        FrequencyTimer1_backup.TimerUdb = FrequencyTimer1_ReadCounter();
        FrequencyTimer1_backup.InterruptMaskValue = FrequencyTimer1_STATUS_MASK;
        #if (FrequencyTimer1_UsingHWCaptureCounter)
            FrequencyTimer1_backup.TimerCaptureCounter = FrequencyTimer1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!FrequencyTimer1_UDB_CONTROL_REG_REMOVED)
            FrequencyTimer1_backup.TimerControlRegister = FrequencyTimer1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: FrequencyTimer1_RestoreConfig
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
*  FrequencyTimer1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FrequencyTimer1_RestoreConfig(void) 
{   
    #if (!FrequencyTimer1_UsingFixedFunction)

        FrequencyTimer1_WriteCounter(FrequencyTimer1_backup.TimerUdb);
        FrequencyTimer1_STATUS_MASK =FrequencyTimer1_backup.InterruptMaskValue;
        #if (FrequencyTimer1_UsingHWCaptureCounter)
            FrequencyTimer1_SetCaptureCount(FrequencyTimer1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!FrequencyTimer1_UDB_CONTROL_REG_REMOVED)
            FrequencyTimer1_WriteControlRegister(FrequencyTimer1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: FrequencyTimer1_Sleep
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
*  FrequencyTimer1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void FrequencyTimer1_Sleep(void) 
{
    #if(!FrequencyTimer1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(FrequencyTimer1_CTRL_ENABLE == (FrequencyTimer1_CONTROL & FrequencyTimer1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            FrequencyTimer1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            FrequencyTimer1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    FrequencyTimer1_Stop();
    FrequencyTimer1_SaveConfig();
}


/*******************************************************************************
* Function Name: FrequencyTimer1_Wakeup
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
*  FrequencyTimer1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FrequencyTimer1_Wakeup(void) 
{
    FrequencyTimer1_RestoreConfig();
    #if(!FrequencyTimer1_UDB_CONTROL_REG_REMOVED)
        if(FrequencyTimer1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                FrequencyTimer1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
