/*******************************************************************************
* File Name: DEBUG_PORT_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG_PORT.h"


/***************************************
* Local data allocation
***************************************/

static DEBUG_PORT_BACKUP_STRUCT  DEBUG_PORT_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: DEBUG_PORT_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the DEBUG_PORT_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_PORT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_PORT_SaveConfig(void)
{
    #if(DEBUG_PORT_CONTROL_REG_REMOVED == 0u)
        DEBUG_PORT_backup.cr = DEBUG_PORT_CONTROL_REG;
    #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: DEBUG_PORT_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_PORT_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling DEBUG_PORT_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void DEBUG_PORT_RestoreConfig(void)
{
    #if(DEBUG_PORT_CONTROL_REG_REMOVED == 0u)
        DEBUG_PORT_CONTROL_REG = DEBUG_PORT_backup.cr;
    #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: DEBUG_PORT_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The DEBUG_PORT_Sleep() API saves the current component state. Then it
*  calls the DEBUG_PORT_Stop() function and calls 
*  DEBUG_PORT_SaveConfig() to save the hardware configuration.
*  Call the DEBUG_PORT_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_PORT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_PORT_Sleep(void)
{
    #if(DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)
        if((DEBUG_PORT_RXSTATUS_ACTL_REG  & DEBUG_PORT_INT_ENABLE) != 0u)
        {
            DEBUG_PORT_backup.enableState = 1u;
        }
        else
        {
            DEBUG_PORT_backup.enableState = 0u;
        }
    #else
        if((DEBUG_PORT_TXSTATUS_ACTL_REG  & DEBUG_PORT_INT_ENABLE) !=0u)
        {
            DEBUG_PORT_backup.enableState = 1u;
        }
        else
        {
            DEBUG_PORT_backup.enableState = 0u;
        }
    #endif /* End DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED*/

    DEBUG_PORT_Stop();
    DEBUG_PORT_SaveConfig();
}


/*******************************************************************************
* Function Name: DEBUG_PORT_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  DEBUG_PORT_Sleep() was called. The DEBUG_PORT_Wakeup() function
*  calls the DEBUG_PORT_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  DEBUG_PORT_Sleep() function was called, the DEBUG_PORT_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_PORT_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_PORT_Wakeup(void)
{
    DEBUG_PORT_RestoreConfig();
    #if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
        DEBUG_PORT_ClearRxBuffer();
    #endif /* End (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */
    #if(DEBUG_PORT_TX_ENABLED || DEBUG_PORT_HD_ENABLED)
        DEBUG_PORT_ClearTxBuffer();
    #endif /* End DEBUG_PORT_TX_ENABLED || DEBUG_PORT_HD_ENABLED */

    if(DEBUG_PORT_backup.enableState != 0u)
    {
        DEBUG_PORT_Enable();
    }
}


/* [] END OF FILE */
