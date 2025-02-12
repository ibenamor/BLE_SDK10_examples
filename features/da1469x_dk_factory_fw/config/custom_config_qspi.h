/**
 ****************************************************************************************
 *
 * @file custom_config_qspi.h
 *
 * @brief Board Support Package. User Configuration file for cached QSPI mode.
 *
 * Copyright (C) 2015-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
#ifndef CUSTOM_CONFIG_QSPI_H_
#define CUSTOM_CONFIG_QSPI_H_

#include "bsp_definitions.h"

#define dg_configUSE_SEGGER_FLASH_LOADER (1)
#define dg_configWDOG_MAX_TASKS_CNT (8)

#define CONFIG_USE_BLE

#define CONFIG_RETARGET

#define defaultBLE_ADDRESS_TYPE                 PRIVATE_ADDRESS

// disable bod as there's no battery
#define dg_configUSE_BOD                        ( 0 )
#define dg_configUSB_SUSPEND_MODE               USB_SUSPEND_MODE_IDLE
#define dg_configUSE_DCDC                       (0)
#define dg_configUSE_USB                        ( 1 )
#define dg_configUSE_HW_CHARGER                 ( 1 )
#define dg_configUSE_HW_USB_CHARGER             ( 1 )
#define dg_configUSE_USB_ENUMERATION            ( 1 )
#define dg_configDEFAULT_CLK                    (sysclk_XTAL32M)
#define dg_configQSPI_CODE_SIZE_AA              (420 * 1024)

// TODO
#define dg_configRF_ENABLE_RECALIBRATION        ( 0 )

/*************************************************************************************************\
 * System configuration
 */
#define dg_configUSE_LP_CLK                     ( LP_CLK_32768 )
#define dg_configEXEC_MODE                      ( MODE_IS_CACHED )
#define dg_configCODE_LOCATION                  ( NON_VOLATILE_IS_FLASH )

#define dg_configUSE_WDOG                       ( 1 )

#define dg_configFLASH_CONNECTED_TO             ( FLASH_CONNECTED_TO_1V8 )
#define dg_configFLASH_POWER_DOWN               ( 0 )
#define dg_configPOWER_1V8_ACTIVE               ( 1 )
#define dg_configPOWER_1V8_SLEEP                ( 1 )

/* Uncomment the following line to enable State-of-Charge debugging or performance test */
//#define DEBUG_SOC
#if defined(DEBUG_SOC)
        #define CONFIG_RETARGET
#endif


#define dg_configUSE_SYS_CHARGER                ( 1 )

#define dg_configUSE_SW_CURSOR                  ( 1 )

#define dg_configCACHEABLE_QSPI_AREA_LEN        ( NVMS_PARAM_PART_start - MEMORY_QSPIF_BASE )


/*************************************************************************************************\
 * FreeRTOS configuration
 */
#define OS_FREERTOS                             /* Define this to use FreeRTOS */

#define configTOTAL_HEAP_SIZE           ( 64000 )  /* FreeRTOS Total Heap Size */

/*************************************************************************************************\
 * Peripherals configuration
 */
 #define CONFIG_BLE_STORAGE

 
#define dg_configFLASH_ADAPTER                  ( 1 )
#define dg_configNVMS_ADAPTER                   ( 1 )
#define dg_configNVMS_VES                       ( 1 )
#define dg_configNVPARAM_ADAPTER                ( 1 )
#define dg_configNVPARAM_APP_AREA               ( 1 )
#define dg_configGPADC_ADAPTER                  ( 1 )
#define dg_configUSE_HW_SENSOR_NODE             ( 1 )
#define dg_configUSE_SNC_HW_GPADC               ( 1 )
#define dg_configSNC_ADAPTER                    ( 1 )


/*************************************************************************************************\
 * BLE configuration
 */
#define CONFIG_USE_BLE_SERVICES

#define dg_configBLE_CENTRAL                    ( 0 )
#define dg_configBLE_GATT_CLIENT                ( 0 )
#define dg_configBLE_OBSERVER                   ( 0 )
#define dg_configBLE_BROADCASTER                ( 0 )
#define dg_configBLE_L2CAP_COC                  ( 0 )

#define defaultBLE_ATT_DB_CONFIGURATION         ( 0x10 )  // Peripheral Pref. Conn. Param. attribute
#define defaultBLE_PPCP_INTERVAL_MIN            ( BLE_CONN_INTERVAL_FROM_MS( 500 ) )    // 500 ms
#define defaultBLE_PPCP_INTERVAL_MAX            ( BLE_CONN_INTERVAL_FROM_MS( 750 ) )    // 750 ms
#define defaultBLE_PPCP_SLAVE_LATENCY           ( 0 )                                   // 0 events
#define defaultBLE_PPCP_SUP_TIMEOUT             ( BLE_SUPERVISION_TMO_FROM_MS( 6000 ) ) // 6000 ms

/* Include bsp default values */
#include "bsp_defaults.h"
/* Include middleware default values */
#include "middleware_defaults.h"

#endif /* CUSTOM_CONFIG_QSPI_H_ */
