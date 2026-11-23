#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "esp_log.h"
#include "esp_task_wdt.h"
#include "esp_heap_caps.h"
#include "esp_sntp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "open62541.h"
#include "model.h"
#include "opcua_server.h"

#define TAG "OPCUA_SERVER"
#define SNTP_TAG "SNTP"

static void
time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(SNTP_TAG, "System time synchronized");
}

static bool
synchronize_time(void)
{
    ESP_LOGI(SNTP_TAG, "Starting SNTP time synchronization");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_setservername(1, "time.google.com");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_init();

    for (int retry = 1;
         sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && retry <= 10;
         ++retry)
    {
        ESP_LOGI(SNTP_TAG, "Waiting for time synchronization (%d/10)", retry);
        vTaskDelay(pdMS_TO_TICKS(2000));
        ESP_ERROR_CHECK(esp_task_wdt_reset());
    }

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    ESP_LOGI(SNTP_TAG, "Current year: %d", timeinfo.tm_year + 1900);
    return timeinfo.tm_year > (2016 - 1900);
}

static void
opcua_server_task(void *arg)
{
    (void)arg;
    ESP_ERROR_CHECK(esp_task_wdt_add(NULL));

    if (!synchronize_time())
        ESP_LOGW(SNTP_TAG, "Time synchronization failed; starting with current system time");

    ESP_LOGI(TAG, "Free heap before UA_Server_new: %lu bytes",
             (unsigned long)esp_get_free_heap_size());
    ESP_LOGI(TAG, "Largest free block before UA_Server_new: %lu bytes",
             (unsigned long)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    UA_Server *server = UA_Server_new();
    if (server == NULL)
    {
        ESP_LOGE(TAG, "Failed to create OPC UA server");
        ESP_ERROR_CHECK(esp_task_wdt_delete(NULL));
        vTaskDelete(NULL);
        return;
    }

    UA_ServerConfig *serverConfig = UA_Server_getConfig(server);
    UA_StatusCode status = UA_ServerConfig_setMinimalCustomBuffer(
        serverConfig, 4840, NULL, 8192, 8192);
    if (status != UA_STATUSCODE_GOOD)
    {
        ESP_LOGE(TAG, "Failed to configure OPC UA server: 0x%08lx",
                 (unsigned long)status);
        UA_Server_delete(server);
        ESP_ERROR_CHECK(esp_task_wdt_delete(NULL));
        vTaskDelete(NULL);
        return;
    }

    serverConfig->maxSecureChannels = 1;
    serverConfig->maxSessions = 1;
    serverConfig->maxSubscriptions = 1;
    serverConfig->maxSubscriptionsPerSession = 1;

    serverConfig->maxSecureChannels = 1;
    serverConfig->maxSessions = 1;
    serverConfig->maxSubscriptions = 1;
    serverConfig->maxSubscriptionsPerSession = 1;

    ESP_LOGI(TAG, "Free heap after OPC UA configuration: %lu bytes",
             (unsigned long)esp_get_free_heap_size());

    addCurrentTemperatureDataSourceVariable(server);

    status = UA_Server_run_startup(server);
    if (status != UA_STATUSCODE_GOOD)
    {
        ESP_LOGE(TAG, "Failed to start OPC UA server: 0x%08lx",
                 (unsigned long)status);
        UA_Server_delete(server);
        ESP_ERROR_CHECK(esp_task_wdt_delete(NULL));
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "OPC UA temperature server listening on port 4840");
    TickType_t lastHeapLog = xTaskGetTickCount();
    while (true)
    {
        ESP_ERROR_CHECK(esp_task_wdt_reset());
        UA_Server_run_iterate(server, false);
        ESP_ERROR_CHECK(esp_task_wdt_reset());
        vTaskDelay(pdMS_TO_TICKS(50));

        TickType_t now = xTaskGetTickCount();
        if ((now - lastHeapLog) >= pdMS_TO_TICKS(3000))
        {
            ESP_LOGI(TAG,
                     "Heap: free=%lu largest=%lu minimum=%lu bytes; OPC UA stack high=%u bytes",
                     (unsigned long)esp_get_free_heap_size(),
                     (unsigned long)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT),
                     (unsigned long)esp_get_minimum_free_heap_size(),
                     (unsigned int)(uxTaskGetStackHighWaterMark(NULL) * sizeof(StackType_t)));
            lastHeapLog = now;
        }
    }
}

esp_err_t
opcua_server_start(void)
{
    BaseType_t result = xTaskCreatePinnedToCore(
        opcua_server_task, "opcua_server", 6144, NULL, 10, NULL, 1);
    return result == pdPASS ? ESP_OK : ESP_ERR_NO_MEM;
}
