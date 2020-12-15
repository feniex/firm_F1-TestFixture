/*******************************************************************************
* File Name: AMux2.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMux2_H)
#define CY_AMUX_AMux2_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void AMux2_Start(void) ;
#define AMux2_Init() AMux2_Start()
void AMux2_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux2_Stop(void); */
/* void AMux2_Select(uint8 channel); */
/* void AMux2_Connect(uint8 channel); */
/* void AMux2_Disconnect(uint8 channel); */
/* void AMux2_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux2_CHANNELS  2u
#define AMux2_MUXTYPE   1
#define AMux2_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define AMux2_NULL_CHANNEL 0xFFu
#define AMux2_MUX_SINGLE   1
#define AMux2_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux2_MUXTYPE == AMux2_MUX_SINGLE
# if !AMux2_ATMOSTONE
#  define AMux2_Connect(channel) AMux2_Set(channel)
# endif
# define AMux2_Disconnect(channel) AMux2_Unset(channel)
#else
# if !AMux2_ATMOSTONE
void AMux2_Connect(uint8 channel) ;
# endif
void AMux2_Disconnect(uint8 channel) ;
#endif

#if AMux2_ATMOSTONE
# define AMux2_Stop() AMux2_DisconnectAll()
# define AMux2_Select(channel) AMux2_FastSelect(channel)
void AMux2_DisconnectAll(void) ;
#else
# define AMux2_Stop() AMux2_Start()
void AMux2_Select(uint8 channel) ;
# define AMux2_DisconnectAll() AMux2_Start()
#endif

#endif /* CY_AMUX_AMux2_H */


/* [] END OF FILE */
