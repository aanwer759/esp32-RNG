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
#include "bootloader_random.h"
#include "esp_log.h"
#include <string.h>
#include <unistd.h>
#include <esp_random.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/cpu_hal.h"
#include "esp_timer.h"
#include "esp_flash.h"



extern void tcp_client(char *);
extern void tcp_client_2(void);
extern int send_data(char *);


static  char* TAG = "PRNG test";

void app_main(void)
{
    int sample_size = 100;
    uint32_t rand_from_PRNG ;
    uint64_t before_time ;
    uint64_t after_time ;
    uint32_t random_number_collected [sample_size];
    

    
    

    ESP_LOGI(TAG,"Enabling bootloader random entropy");
    bootloader_random_enable();
    
      //  ESP_LOGI(TAG,"%d",esp_flash_get_size());
    for (int i=0;i <=sample_size-1 ; i ++){

        
        before_time = esp_timer_get_time();
        rand_from_PRNG = esp_random();
        random_number_collected[i] = rand_from_PRNG;
        after_time = esp_timer_get_time();
        
        ESP_LOGI(TAG,"%llu",before_time);
        ESP_LOGI(TAG,"%lu",rand_from_PRNG);
        ESP_LOGI(TAG,"%llu",after_time);
        ESP_LOGI(TAG,"%d",i);
        vTaskDelay(1);

}
    bootloader_random_disable();
    ESP_LOGI(TAG,"Bootloader entropy disabled:");
    //ESP_LOGI(TAG,"%d",esp_flash_get_size());
    vTaskDelay(1);

    // safe side to give time for disabling of bootloader entropy
    // Enabling RF subsystem to transfer data to TCP server
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    tcp_client_2();
    
    for (int j =0 ; j <=sample_size-1 ; j++){
    
    char text1[255];
    sprintf(text1,"%lu",random_number_collected[j]);
    int ret = send_data(text1);
    vTaskDelay(10);
    }
}


