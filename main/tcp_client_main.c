/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include "nvs_flash.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_event.h"
#include "esp_random.h"

extern void tcp_client(char *);
extern void tcp_client_2(void);
extern int send_data(char *);

// some comment because I forgot to make branch for this before !
void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    tcp_client_2();
    
    while(1){
    uint32_t rand_from_esp = esp_random();
    char text1[255];
    sprintf(text1,"%lu",rand_from_esp);
    int ret = send_data(text1);
    }
}


//tcp_client(text1);