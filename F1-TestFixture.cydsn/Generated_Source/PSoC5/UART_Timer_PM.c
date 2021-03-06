/*******************************************************************************
* File Name: UART_Timer_PM.c
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

#include "UART_Timer.h"

static UART_Timer_backupStruct UART_Timer_backup;


/*******************************************************************************
* Function Name: UART_Timer_SaveConfig
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
*  UART_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UART_Timer_SaveConfig(void) 
{
    #if (!UART_Timer_UsingFixedFunction)
        UART_Timer_backup.TimerUdb = UART_Timer_ReadCounter();
        UART_Timer_backup.InterruptMaskValue = UART_Timer_STATUS_MASK;
        #if (UART_Timer_UsingHWCaptureCounter)
            UART_Timer_backup.TimerCaptureCounter = UART_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!UART_Timer_UDB_CONTROL_REG_REMOVED)
            UART_Timer_backup.TimerControlRegister = UART_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: UART_Timer_RestoreConfig
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
*  UART_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UART_Timer_RestoreConfig(void) 
{   
    #if (!UART_Timer_UsingFixedFunction)

        UART_Timer_WriteCounter(UART_Timer_backup.TimerUdb);
        UART_Timer_STATUS_MASK =UART_Timer_backup.InterruptMaskValue;
        #if (UART_Timer_UsingHWCaptureCounter)
            UART_Timer_SetCaptureCount(UART_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!UART_Timer_UDB_CONTROL_REG_REMOVED)
            UART_Timer_WriteControlRegister(UART_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: UART_Timer_Sleep
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
*  UART_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void UART_Timer_Sleep(void) 
{
    #if(!UART_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(UART_Timer_CTRL_ENABLE == (UART_Timer_CONTROL & UART_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            UART_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            UART_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    UART_Timer_Stop();
    UART_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_Timer_Wakeup
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
*  UART_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UART_Timer_Wakeup(void) 
{
    UART_Timer_RestoreConfig();
    #if(!UART_Timer_UDB_CONTROL_REG_REMOVED)
        if(UART_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                UART_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
