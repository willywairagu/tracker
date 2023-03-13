/*
 * ets_sys.h
 *
 *  Created on: Dec 13, 2022
 *      Author: Wilberforce
 */

#ifndef COMPONENTS_ESP_IDF_LIB_HELPERS_ETS_SYS_H_
#define COMPONENTS_ESP_IDF_LIB_HELPERS_ETS_SYS_H_

#if CONFIG_IDF_TARGET_ESP32
#include <esp32/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C2
#include <esp32c2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C3
#include <esp32c3/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32C6
#include <esp32c6/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32H2
#include <esp32h2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32H4
#include <esp32h4/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32S2
#include <esp32s2/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP32S3
#include <esp32s3/rom/ets_sys.h>
#elif CONFIG_IDF_TARGET_ESP8266
#include <rom/ets_sys.h>
#else
#error "ets_sys: Unknown target"
#endif

#endif /* COMPONENTS_ESP_IDF_LIB_HELPERS_ETS_SYS_H_ */
