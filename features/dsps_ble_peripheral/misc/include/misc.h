/**
 ****************************************************************************************
 *
 * @file misc.h
 *
 * @brief Application code related to hardware
 *
 * Copyright (C) 2018-2023 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdio.h>
#include "hw_gpio.h"
#include "hw_wkup_da1469x.h"
#include "sys_timer.h"
#include "interrupts.h"

/*********************************************************************
 *
 *       Typedef
 *
 *********************************************************************
 */

typedef enum {
        SYS_TIMESTAMP_START  = 0x0,
        SYS_TIMESTAMP_STOP        ,
} SYS_TIMESTAMP;


/*********************************************************************
 *
 *       Defines
 *
 *********************************************************************
 */
#define KiB    1024

#if DBG_LOG_ENABLE
   #define DBG_LOG(_f, args...)   printf((_f), ## args)
#else
   #define DBG_LOG(_f, args...)
#endif /* DBG_LOG_ENABLE */

#if DBG_IO_ENABLE
   #define DBG_IO_ON(_port, _pin)                                                                    \
        {                                                                                          \
                hw_sys_pd_com_enable();                                                            \
                hw_gpio_set_pin_function((_port), (_pin), HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO); \
                hw_gpio_set_active((_port), (_pin));                                               \
                hw_gpio_pad_latch_enable((_port), (_pin));                                         \
                hw_gpio_pad_latch_disable((_port), (_pin));                                        \
                hw_sys_pd_com_disable();                                                           \
        }

   #define DBG_IO_OFF(_port, _pin)                                                                   \
        {                                                                                          \
                hw_sys_pd_com_enable();                                                            \
                hw_gpio_set_pin_function((_port), (_pin), HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO); \
                hw_gpio_set_inactive((_port), (_pin));                                             \
                hw_gpio_pad_latch_enable((_port), (_pin));                                         \
                hw_gpio_pad_latch_disable((_port), (_pin));                                        \
                hw_sys_pd_com_disable();                                                           \
        }

#else
   #define DBG_IO_ON(_port, _pin)
   #define DBG_IO_OFF(_port, _pin)
#endif /* DBG_IO_ENABLE */

/*********************************************************************
 *
 *       Static code
 *
 *********************************************************************
 */

/**
 * Wrapper function to get system's uptime in lp clocks. The function can also be called
 * from interrupt context.
 *
 * \return Number of lp clock elapsed from the beginning of system power-up.
 *
 */
__STATIC_INLINE uint64_t __sys_ticks_timestamp(void)
{
        return ((in_interrupt()) ? sys_timer_get_uptime_ticks_fromISR() : sys_timer_get_uptime_ticks());
}



/*********************************************************************
 *
 *       Functions prototype
 *
 *********************************************************************
 */

/**
 * Get time interval in milliseconds
 *
 * \param[in] state  Define the start or end of a timestamp operation.
 *
 * \return  0 if \p state is SYS_TIMESTAMP_START; Othewise, the time has elapsed between
 *          SYS_TIMESTAMP_START and SYS_TIMESTAMP_STOP in us.
 *
 * \note The routine is valid only when an OS is used.
 *
 * {code}
 * uint32_t timestamp;
 *
 * get_sys_timestamp_us(SYS_TIMESTAMP_START);
 * ...
 * timestamp = get_sys_timestamp_us(SYS_TIMESTAMP_STOP)
 *
 * DBG_LOG("Timestamp mS: %lu", timestamp / 1000)
 * {code}
 */
uint64_t get_sys_timestamp_us(SYS_TIMESTAMP state);

/**
 * Initialize GPIO pins not handled by adapters
 *
 * \param[in] gpio_list  Pointer to an array containing entries of type HW_GPIO_PINCONFIG.
 * \param[in] pin_power  Power level applied to all I/O pins defined in \p gpio_list.
 *
 * \warning The \p gpio_list must be terminated with HW_GPIO_PINCONFIG_END
 */
void app_gpio_pins_cfg(const gpio_config *gpio_list, HW_GPIO_POWER pin_power);

/**
 * Generate PDC entries for each GPIO pin in \p gpio_list. This is necessary, so that the
 * PDC can power on the application processor (CM33) once in the sleep state (completely
 * powered off).
 *
 * \param[in] gpio_list  Pointer to an array containing entries of type HW_GPIO_PINCONFIG.
 *
 * \warning The \p gpio_list must be terminated with HW_GPIO_PINCONFIG_END
 */
void app_gpio_pins_pdc_cfg(const gpio_config *gpio_list);

/**
 * Check the status of the K1 user button mounted on Pro or USB motherboards
 *
 * \return true if the user button is pressed; false otherwise.
 */
bool user_button_is_pressed(void);

#endif /* MISC_H_ */
