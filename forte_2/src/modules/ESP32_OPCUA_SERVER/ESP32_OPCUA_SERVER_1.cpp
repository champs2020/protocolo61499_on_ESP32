/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: ESP32_OPCUA_SERVER_1
 *** Description: Service Interface Function Block Type
 *** Version:
***     1.0: 2026-11-23/José Hélio -  - 
 *************************************************************************/

#include "ESP32_OPCUA_SERVER_1.h"
#include "opcua_server.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ESP32_OPCUA_SERVER_1_gen.cpp"
#endif

#include <esp_log.h>

DEFINE_FIRMWARE_FB(FORTE_ESP32_OPCUA_SERVER_1, g_nStringIdESP32_OPCUA_SERVER_1)

const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anDataInputNames[] = {g_nStringIdQI};

const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anDataInputTypeIds[] = {g_nStringIdBOOL};

const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS};

const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING};

const TDataIOID FORTE_ESP32_OPCUA_SERVER_1::scm_anEIWith[] = {0, 255, 0, 255};
const TForteInt16 FORTE_ESP32_OPCUA_SERVER_1::scm_anEIWithIndexes[] = {0, 2};
const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdSTART};

const TDataIOID FORTE_ESP32_OPCUA_SERVER_1::scm_anEOWith[] = {0, 1, 255, 0, 1, 255};
const TForteInt16 FORTE_ESP32_OPCUA_SERVER_1::scm_anEOWithIndexes[] = {0, 3};
const CStringDictionary::TStringId FORTE_ESP32_OPCUA_SERVER_1::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF};


const SFBInterfaceSpec FORTE_ESP32_OPCUA_SERVER_1::scm_stFBInterfaceSpec = {
  2, scm_anEventInputNames, scm_anEIWith, scm_anEIWithIndexes,
  2, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  1, scm_anDataInputNames, scm_anDataInputTypeIds,
  2, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

void FORTE_ESP32_OPCUA_SERVER_1::executeEvent(int pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventINITID:
      m_started = false;
      if (st_QI() == true) {
        st_QO() = true;
        st_STATUS() = "IDLE";
      } else {
        st_QO() = false;
        st_STATUS() = "DISABLED";
      }
      sendOutputEvent(scm_nEventINITOID);
      break;

    case scm_nEventSTARTID:
      if (st_QI() != true) {
        st_QO() = false;
        st_STATUS() = "DISABLED";
      } else if (m_started) {
        st_QO() = true;
        st_STATUS() = "ALREADY_STARTED";
      } else {
        esp_err_t result = opcua_server_start();
        if (result == ESP_OK) {
          m_started = true;
          st_QO() = true;
          st_STATUS() = "START_REQUESTED";
          ESP_LOGI("OPCUA_SERVER_FB", "OPC UA server start requested");
        } else {
          st_QO() = false;
          st_STATUS() = "START_FAILED";
          ESP_LOGE("OPCUA_SERVER_FB", "OPC UA server start failed");
        }
      }
      sendOutputEvent(scm_nEventCNFID);
      break;
  }
}


