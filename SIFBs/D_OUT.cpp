/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: D_OUT
 *** Description: Service Interface Function Block Type
 *** Version:
***     1.0: 2026-07-17/José Hélio -  - 
 *************************************************************************/

#include "D_OUT.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "D_OUT_gen.cpp"
#endif


DEFINE_FIRMWARE_FB(FORTE_D_OUT, g_nStringIdD_OUT)

const CStringDictionary::TStringId FORTE_D_OUT::scm_anDataInputNames[] = {g_nStringIdQI, g_nStringIdPARAMS, g_nStringIdSD};

const CStringDictionary::TStringId FORTE_D_OUT::scm_anDataInputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdANY};

const CStringDictionary::TStringId FORTE_D_OUT::scm_anDataOutputNames[] = {g_nStringIdQO, g_nStringIdSTATUS, g_nStringIdRD};

const CStringDictionary::TStringId FORTE_D_OUT::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdWSTRING, g_nStringIdANY};

const TDataIOID FORTE_D_OUT::scm_anEIWith[] = {0, 1, 255, 0, 2, 255, 0, 255};
const TForteInt16 FORTE_D_OUT::scm_anEIWithIndexes[] = {0, 3, 6};
const CStringDictionary::TStringId FORTE_D_OUT::scm_anEventInputNames[] = {g_nStringIdINIT, g_nStringIdREQ, g_nStringIdRSP};

const TDataIOID FORTE_D_OUT::scm_anEOWith[] = {0, 1, 255, 0, 1, 255, 0, 1, 2, 255};
const TForteInt16 FORTE_D_OUT::scm_anEOWithIndexes[] = {0, 3, 6};
const CStringDictionary::TStringId FORTE_D_OUT::scm_anEventOutputNames[] = {g_nStringIdINITO, g_nStringIdCNF, g_nStringIdIND};


const SFBInterfaceSpec FORTE_D_OUT::scm_stFBInterfaceSpec = {
  3, scm_anEventInputNames, scm_anEIWith, scm_anEIWithIndexes,
  3, scm_anEventOutputNames, scm_anEOWith, scm_anEOWithIndexes,
  3, scm_anDataInputNames, scm_anDataInputTypeIds,
  3, scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, nullptr
};

void FORTE_D_OUT::executeEvent(int pa_nEIID) {
  switch(pa_nEIID) {
    case scm_nEventINITID:
      #error add code for INIT event!
      /*
        do not forget to send output event, calling e.g.
          sendOutputEvent(scm_nEventCNFID);
      */
      break;
    case scm_nEventREQID:
      #error add code for REQ event!
      /*
        do not forget to send output event, calling e.g.
          sendOutputEvent(scm_nEventCNFID);
      */
      break;
    case scm_nEventRSPID:
      #error add code for RSP event!
      /*
        do not forget to send output event, calling e.g.
          sendOutputEvent(scm_nEventCNFID);
      */
      break;
  }
}


