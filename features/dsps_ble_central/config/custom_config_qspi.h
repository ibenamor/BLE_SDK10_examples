/**
 ****************************************************************************************
 *
 * @file custom_config_qspi.h
 *
 * @brief Board Support Package. User Configuration file for cached QSPI mode.
 *
 * Copyright (C) 2015-2022 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
#ifndef CUSTOM_CONFIG_QSPI_H_
#define CUSTOM_CONFIG_QSPI_H_

#include "bsp_definitions.h"

#define CONFIG_USE_BLE

/*************************************************************************************************\
 * DSPS specific config
 *
 *************************************************************************************************/
/* Enable the log on SEGGER RTT, or printf will be empty function */
#define DBG_LOG_ENABLE          ( 1 )

#if DBG_LOG_ENABLE
   #define CONFIG_RTT
#endif

/* Set one UART flow control mode */
#define CFG_UART_HW_FLOW_CTRL

/* Enable circular DMA so no data are overwritten in the RX HW FIFOs upon file transfers. */
#define dg_configUART_RX_CIRCULAR_DMA                ( 1 )
/* This value has been adjusted so that no data loss is encountered in file transfer operations. */
#define dg_configUART2_RX_CIRCULAR_DMA_BUF_SIZE      1024

/* Set UART baudrate */
#define CFG_UART_SPS_BAUDRATE                   HW_UART_BAUDRATE_1000000

/* Necessary for the external MCU UART communication */
#define CONFIG_UART_IGNORE_BUSY_DETECT

/*
 * When the CPU runs @32MHz and the selected serial interface supports flow control signaling (DSPS_UART)
 * and a device receives and transmits data simultaneously a deadlock should occur. The series of events
 * is as follows:
 *
 * a. Device A reads data from the UART interface and the RX queue reaches the high WM and so the UART
 *    flow control is enabled.
 * b. At the same time device B TX queue (where the received data are pushed into) reaches the high WM
 *    and it sends an SPS notification to device A to stop sending further data.
 * c. Device A receives that notification and so the RX queue cannot be offloaded
 * d. The same situation happens to device B as it also reads data from its serial interface and the
 *    UART flow control is activated (RX queue is filled).
 * e. Device A/B cannot offload their TX queues as the UART flow has already been activated and so does
 *    the SPS flow control. ==> deadlock!
 *
 * Workaround: To achieve the max. throughput just do not print the received data on the serial interface
 * (SERIAL_PORT_WRITE_DATA should be empty).
 *
 * When the selected serial interface does not support or exhibit flow control (e.g. USB device porting)
 * it might happen that some data are lost (especially if the device receives and transmits data
 * simultaneously).
 *
 */
#define CUSTOM_SYS_CLK                          sysclk_PLL96

#define GENERATE_RANDOM_DEVICE_ADDRESS          ( 1 )

/* Default connection parameter */
#define defaultBLE_PPCP_INTERVAL_MIN            (BLE_CONN_INTERVAL_FROM_MS(15))
#define defaultBLE_PPCP_INTERVAL_MAX            (BLE_CONN_INTERVAL_FROM_MS(15))
#define defaultBLE_PPCP_SLAVE_LATENCY           (0)
#define defaultBLE_PPCP_SUP_TIMEOUT             (BLE_SUPERVISION_TMO_FROM_MS(1000))
/* Min. connection event length decides number of packets/connection
 * increase this value will increase throughput if device is master */
#define defaultBLE_CONN_EVENT_LENGTH_MIN        BLE_CONN_EVENT_LENGTH_FROM_MS(10)

/*************************************************************************************************\
 * System configuration
 */
#define dg_configUSE_LP_CLK                     ( LP_CLK_32768 )
#define dg_configEXEC_MODE                      ( MODE_IS_CACHED )
#define dg_configCODE_LOCATION                  ( NON_VOLATILE_IS_FLASH )
#define dg_configEMULATE_OTP_COPY               ( 0 )

#define dg_configUSE_WDOG                       ( 1 )
#define dg_configWDOG_RESET_VALUE               ( 0x1FF )

#define dg_configFLASH_CONNECTED_TO             ( FLASH_CONNECTED_TO_1V8P )
#define dg_configFLASH_POWER_DOWN               ( 1 )
#define dg_configPOWER_1V8P_ACTIVE              ( 1 )
#define dg_configPOWER_1V8P_SLEEP               ( 1 )

#if defined(DSPS_USBD)
# undef dg_configUSE_USB_ENUMERATION
# undef dg_configUSB_DMA_SUPPORT
# undef dg_configUSE_SYS_CHARGER
# define dg_configUSE_USB_ENUMERATION           ( 1 )
# define dg_configUSB_DMA_SUPPORT               ( 1 )
# define dg_configUSE_SYS_CHARGER               ( 0 )
#endif

#define dg_configWDOG_MAX_TASKS_CNT             ( 9 )

#define dg_configUSE_SW_CURSOR                  ( 1 )

#define dg_configCACHEABLE_QSPI_AREA_LEN        ( NVMS_PARAM_PART_start - MEMORY_QSPIF_BASE )

/*************************************************************************************************\
 * FreeRTOS configuration
 */
#define OS_FREERTOS                              /* Define this to use FreeRTOS */
#define configTOTAL_HEAP_SIZE                   ( 38000 )   /* FreeRTOS Total Heap Size */

/*************************************************************************************************\
 * Peripherals configuration
 */
#define dg_configFLASH_ADAPTER                  ( 1 )
#define dg_configNVMS_ADAPTER                   ( 1 )
#define dg_configNVMS_VES                       ( 1 )
#define dg_configNVPARAM_ADAPTER                ( 1 )
#define dg_configGPADC_ADAPTER                  ( 1 )
#define dg_configUSE_HW_SENSOR_NODE             ( 1 )
#define dg_configUSE_SNC_HW_GPADC               ( 1 )
#define dg_configSNC_ADAPTER                    ( 1 )
#define dg_configUSE_SYS_ADC                    ( 1 )
#if defined(DSPS_UART)
# undef dg_configUART_ADAPTER
# define dg_configUART_ADAPTER                  ( 1 )
#endif

/*************************************************************************************************\
 * BLE configuration
 */
#define dg_configBLE_PERIPHERAL                 ( 0 )
#define dg_configBLE_GATT_SERVER                ( 0 )
#define dg_configBLE_OBSERVER                   ( 0 )
#define dg_configBLE_BROADCASTER                ( 0 )
#define dg_configBLE_L2CAP_COC                  ( 0 )

/* Include bsp default values */
#include "bsp_defaults.h"
/* Include middleware default values */
#include "middleware_defaults.h"

#endif /* CUSTOM_CONFIG_QSPI_H_ */
