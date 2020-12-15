/*******************************************************************************
* File Name: GPS_PM.c
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

#include "GPS.h"


/***************************************
* Local data allocation
***************************************/

static GPS_BACKUP_STRUCT  GPS_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: GPS_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the GPS_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  GPS_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GPS_SaveConfig(void)
{
    #if(GPS_CONTROL_REG_REMOVED == 0u)
        GPS_backup.cr = GPS_CONTROL_REG;
    #endif /* End GPS_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: GPS_RestoreConfig
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
*  GPS_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling GPS_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void GPS_RestoreConfig(void)
{
    #if(GPS_CONTROL_REG_REMOVED == 0u)
        GPS_CONTROL_REG = GPS_backup.cr;
    #endif /* End GPS_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: GPS_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The GPS_Sleep() API saves the current component state. Then it
*  calls the GPS_Stop() function and calls 
*  GPS_SaveConfig() to save the hardware configuration.
*  Call the GPS_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  GPS_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GPS_Sleep(void)
{
    #if(GPS_RX_ENABLED || GPS_HD_ENABLED)
        if((GPS_RXSTATUS_ACTL_REG  & GPS_INT_ENABLE) != 0u)
        {
            GPS_backup.enableState = 1u;
        }
        else
        {
            GPS_backup.enableState = 0u;
        }
    #else
        if((GPS_TXSTATUS_ACTL_REG  & GPS_INT_ENABLE) !=0u)
        {
            GPS_backup.enableState = 1u;
        }
        else
        {
            GPS_backup.enableState = 0u;
        }
    #endif /* End GPS_RX_ENABLED || GPS_HD_ENABLED*/

    GPS_Stop();
    GPS_SaveConfig();
}


/*******************************************************************************
* Function Name: GPS_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  GPS_Sleep() was called. The GPS_Wakeup() function
*  calls the GPS_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  GPS_Sleep() function was called, the GPS_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  GPS_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GPS_Wakeup(void)
{
    GPS_RestoreConfig();
    #if( (GPS_RX_ENABLED) || (GPS_HD_ENABLED) )
        GPS_ClearRxBuffer();
    #endif /* End (GPS_RX_ENABLED) || (GPS_HD_ENABLED) */
    #if(GPS_TX_ENABLED || GPS_HD_ENABLED)
        GPS_ClearTxBuffer();
    #endif /* End GPS_TX_ENABLED || GPS_HD_ENABLED */

    if(GPS_backup.enableState != 0u)
    {
        GPS_Enable();
    }
}


/* [] END OF FILE */
