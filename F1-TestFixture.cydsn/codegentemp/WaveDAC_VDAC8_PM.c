/*******************************************************************************
* File Name: WaveDAC_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveDAC_VDAC8.h"

static WaveDAC_VDAC8_backupStruct WaveDAC_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveDAC_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void WaveDAC_VDAC8_SaveConfig(void) 
{
    if (!((WaveDAC_VDAC8_CR1 & WaveDAC_VDAC8_SRC_MASK) == WaveDAC_VDAC8_SRC_UDB))
    {
        WaveDAC_VDAC8_backup.data_value = WaveDAC_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveDAC_VDAC8_RestoreConfig
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
*******************************************************************************/
void WaveDAC_VDAC8_RestoreConfig(void) 
{
    if (!((WaveDAC_VDAC8_CR1 & WaveDAC_VDAC8_SRC_MASK) == WaveDAC_VDAC8_SRC_UDB))
    {
        if((WaveDAC_VDAC8_Strobe & WaveDAC_VDAC8_STRB_MASK) == WaveDAC_VDAC8_STRB_EN)
        {
            WaveDAC_VDAC8_Strobe &= (uint8)(~WaveDAC_VDAC8_STRB_MASK);
            WaveDAC_VDAC8_Data = WaveDAC_VDAC8_backup.data_value;
            WaveDAC_VDAC8_Strobe |= WaveDAC_VDAC8_STRB_EN;
        }
        else
        {
            WaveDAC_VDAC8_Data = WaveDAC_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveDAC_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  WaveDAC_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveDAC_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveDAC_VDAC8_ACT_PWR_EN == (WaveDAC_VDAC8_PWRMGR & WaveDAC_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveDAC_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveDAC_VDAC8_backup.enableState = 0u;
    }
    
    WaveDAC_VDAC8_Stop();
    WaveDAC_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveDAC_VDAC8_Wakeup
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
*  WaveDAC_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveDAC_VDAC8_Wakeup(void) 
{
    WaveDAC_VDAC8_RestoreConfig();
    
    if(WaveDAC_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveDAC_VDAC8_Enable();

        /* Restore the data register */
        WaveDAC_VDAC8_SetValue(WaveDAC_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
