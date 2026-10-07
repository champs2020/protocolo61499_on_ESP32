/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ESP32_LOGGER
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     1.0: 2026-09-28/José Hélio -  -
 *************************************************************************/

#include "ESP32_LOGGER.h"
#include <esp_log.h>
#include <driver/gpio.h>

#define LED_GPIO GPIO_NUM_2 // Pino padrão do LED na placa ESP32

#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ESP32_LOGGER_gen.cpp"
#endif


DEFINE_FIRMWARE_FB(FORTE_ESP32_LOGGER, g_nStringIdESP32_LOGGER)

const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anDataInputNames[] = { g_nStringIdSD };

const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anDataInputTypeIds[] = { g_nStringIdBOOL };

const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anDataOutputNames[] = { g_nStringIdSTATUS, g_nStringIdRD };

const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anDataOutputTypeIds[] = { g_nStringIdWSTRING, g_nStringIdBOOL };

const TDataIOID FORTE_ESP32_LOGGER::scm_anEIWith[] = { 0, 255 };
const TForteInt16 FORTE_ESP32_LOGGER::scm_anEIWithIndexes[] = { -1, 0 };
const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anEventInputNames[] = { g_nStringIdINIT, g_nStringIdREQ };

const TDataIOID FORTE_ESP32_LOGGER::scm_anEOWith[] = { 0, 1, 255 };
const TForteInt16 FORTE_ESP32_LOGGER::scm_anEOWithIndexes[] = { 0 };
const CStringDictionary::TStringId FORTE_ESP32_LOGGER::scm_anEventOutputNames[] = { g_nStringIdCNF };


const SFBInterfaceSpec FORTE_ESP32_LOGGER::scm_stFBInterfaceSpec = {
  2, scm_anEventInputNames, scm_anEIWith, scm_anEIWithIndexes,
  1, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  1, scm_anDataInputNames, scm_anDataInputTypeIds,
  2, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

void FORTE_ESP32_LOGGER::executeEvent(int pa_nEIID) {
    switch (pa_nEIID) {
    case scm_nEventINITID:
        // Configura o pino GPIO 2 do LED como saída digital física
        gpio_reset_pin(LED_GPIO);
        gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

        st_STATUS() = "INIT_OK";
        st_RD() = false;

        ESP_LOGI("ESP32_LOGGER", "GPIO 2 inicializado com sucesso!");
        sendOutputEvent(scm_nEventCNFID);
        break;

    case scm_nEventREQID:
        // Lê o estado booleano do pino SD vindo da lógica (ex: Q do E_SR)
        if (st_SD() == true) {
            gpio_set_level(LED_GPIO, 1); // Liga o LED físico
            ESP_LOGI("4DIAC_ESP32", "LED ON (SD = TRUE)");
        }
        else {
            gpio_set_level(LED_GPIO, 0); // Desliga o LED físico
            ESP_LOGI("4DIAC_ESP32", "LED OFF (SD = FALSE)");
        }

        st_RD() = st_SD();     // Espelha o valor no pino de saída RD
        st_STATUS() = "LOG_OK"; // Define a mensagem de estado

        sendOutputEvent(scm_nEventCNFID);
        break;
    }
}