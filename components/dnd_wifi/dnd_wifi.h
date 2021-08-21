/*
 * @file dnd_wifi.h
 * @brief WiFi Controls
 */

#ifndef DND_WIFI_H_INCLUDED
#define DND_WIFI_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/event_groups.h"

// Wifi Events 
typedef enum _dnd_wifi_events {
    WIFI_CONNECTED_BIT = BIT0,
    WIFI_FAIL_BIT = BIT1,
} dnd_wifi_events_t;

// Init AWS
void dnd_wifi_initialize();

// Return wifi event group 
EventGroupHandle_t dnd_wifi_event_group();

#ifdef __cplusplus
extern }
#endif

#endif // DND_WIFI_H_INCLUDED