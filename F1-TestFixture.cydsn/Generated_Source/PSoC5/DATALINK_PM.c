/*******************************************************************************
* File Name: DATALINK_PM.c
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

#include "DATALINK.h"


/***************************************
* Local data allocation
***************************************/

static DATALINK_BACKUP_STRUCT  DATALINK_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: DATALINK_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the DATALINK_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DATALINK_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DATALINK_SaveConfig(void)
{
    #if(DATALINK_CONTROL_REG_REMOVED == 0u)
        DATALINK_backup.cr = DATALINK_CONTROL_REG;
    #endif /* End DATALINK_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: DATALINK_RestoreConfig
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
*  DATALINK_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling DATALINK_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void DATALINK_RestoreConfig(void)
{
    #if(DATALINK_CONTROL_REG_REMOVED == 0u)
        DATALINK_CONTROL_REG = DATALINK_backup.cr;
    #endif /* End DATALINK_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: DATALINK_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The DATALINK_Sleep() API saves the current component state. Then it
*  calls the DATALINK_Stop() function and calls 
*  DATALINK_SaveConfig() to save the hardware configuration.
*  Call the DATALINK_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DATALINK_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DATALINK_Sleep(void)
{
    #if(DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)
        if((DATALINK_RXSTATUS_ACTL_REG  & DATALINK_INT_ENABLE) != 0u)
        {
            DATALINK_backup.enableState = 1u;
        }
        else
        {
            DATALINK_backup.enableState = 0u;
        }
    #else
        if((DATALINK_TXSTATUS_ACTL_REG  & DATALINK_INT_ENABLE) !=0u)
        {
            DATALINK_backup.enableState = 1u;
        }
        else
        {
            DATALINK_backup.enableState = 0u;
        }
    #endif /* End DATALINK_RX_ENABLED || DATALINK_HD_ENABLED*/

    DATALINK_Stop();
    DATALINK_SaveConfig();
}


/*******************************************************************************
* Function Name: DATALINK_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  DATALINK_Sleep() was called. The DATALINK_Wakeup() function
*  calls the DATALINK_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  DATALINK_Sleep() function was called, the DATALINK_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DATALINK_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DATALINK_Wakeup(void)
{
    DATALINK_RestoreConfig();
    #if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )
        DATALINK_ClearRxBuffer();
    #endif /* End (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */
    #if(DATALINK_TX_ENABLED || DATALINK_HD_ENABLED)
        DATALINK_ClearTxBuffer();
    #endif /* End DATALINK_TX_ENABLED || DATALINK_HD_ENABLED */

    if(DATALINK_backup.enableState != 0u)
    {
        DATALINK_Enable();
    }
}


/* [] END OF FILE */
