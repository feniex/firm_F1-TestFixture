/*******************************************************************************
* File Name: MUX_CTRL_115200.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_MUX_CTRL_115200_H) /* CY_CONTROL_REG_MUX_CTRL_115200_H */
#define CY_CONTROL_REG_MUX_CTRL_115200_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} MUX_CTRL_115200_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    MUX_CTRL_115200_Write(uint8 control) ;
uint8   MUX_CTRL_115200_Read(void) ;

void MUX_CTRL_115200_SaveConfig(void) ;
void MUX_CTRL_115200_RestoreConfig(void) ;
void MUX_CTRL_115200_Sleep(void) ; 
void MUX_CTRL_115200_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define MUX_CTRL_115200_Control        (* (reg8 *) MUX_CTRL_115200_Sync_ctrl_reg__CONTROL_REG )
#define MUX_CTRL_115200_Control_PTR    (  (reg8 *) MUX_CTRL_115200_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_MUX_CTRL_115200_H */


/* [] END OF FILE */
