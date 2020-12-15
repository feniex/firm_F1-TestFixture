/*******************************************************************************
* File Name: QUAD_OBDII_AUDIO_PM.c
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

#include "QUAD_OBDII_AUDIO.h"


/***************************************
* Local data allocation
***************************************/

static QUAD_OBDII_AUDIO_BACKUP_STRUCT  QUAD_OBDII_AUDIO_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: QUAD_OBDII_AUDIO_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the QUAD_OBDII_AUDIO_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_OBDII_AUDIO_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_OBDII_AUDIO_SaveConfig(void)
{
    #if(QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED == 0u)
        QUAD_OBDII_AUDIO_backup.cr = QUAD_OBDII_AUDIO_CONTROL_REG;
    #endif /* End QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_OBDII_AUDIO_RestoreConfig
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
*  QUAD_OBDII_AUDIO_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling QUAD_OBDII_AUDIO_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void QUAD_OBDII_AUDIO_RestoreConfig(void)
{
    #if(QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED == 0u)
        QUAD_OBDII_AUDIO_CONTROL_REG = QUAD_OBDII_AUDIO_backup.cr;
    #endif /* End QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_OBDII_AUDIO_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The QUAD_OBDII_AUDIO_Sleep() API saves the current component state. Then it
*  calls the QUAD_OBDII_AUDIO_Stop() function and calls 
*  QUAD_OBDII_AUDIO_SaveConfig() to save the hardware configuration.
*  Call the QUAD_OBDII_AUDIO_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_OBDII_AUDIO_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_OBDII_AUDIO_Sleep(void)
{
    #if(QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED)
        if((QUAD_OBDII_AUDIO_RXSTATUS_ACTL_REG  & QUAD_OBDII_AUDIO_INT_ENABLE) != 0u)
        {
            QUAD_OBDII_AUDIO_backup.enableState = 1u;
        }
        else
        {
            QUAD_OBDII_AUDIO_backup.enableState = 0u;
        }
    #else
        if((QUAD_OBDII_AUDIO_TXSTATUS_ACTL_REG  & QUAD_OBDII_AUDIO_INT_ENABLE) !=0u)
        {
            QUAD_OBDII_AUDIO_backup.enableState = 1u;
        }
        else
        {
            QUAD_OBDII_AUDIO_backup.enableState = 0u;
        }
    #endif /* End QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED*/

    QUAD_OBDII_AUDIO_Stop();
    QUAD_OBDII_AUDIO_SaveConfig();
}


/*******************************************************************************
* Function Name: QUAD_OBDII_AUDIO_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  QUAD_OBDII_AUDIO_Sleep() was called. The QUAD_OBDII_AUDIO_Wakeup() function
*  calls the QUAD_OBDII_AUDIO_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  QUAD_OBDII_AUDIO_Sleep() function was called, the QUAD_OBDII_AUDIO_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_OBDII_AUDIO_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_OBDII_AUDIO_Wakeup(void)
{
    QUAD_OBDII_AUDIO_RestoreConfig();
    #if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
        QUAD_OBDII_AUDIO_ClearRxBuffer();
    #endif /* End (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */
    #if(QUAD_OBDII_AUDIO_TX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED)
        QUAD_OBDII_AUDIO_ClearTxBuffer();
    #endif /* End QUAD_OBDII_AUDIO_TX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED */

    if(QUAD_OBDII_AUDIO_backup.enableState != 0u)
    {
        QUAD_OBDII_AUDIO_Enable();
    }
}


/* [] END OF FILE */
