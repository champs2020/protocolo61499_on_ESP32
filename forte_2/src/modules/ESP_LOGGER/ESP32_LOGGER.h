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

#ifndef _ESP32_LOGGER_H_
#define _ESP32_LOGGER_H_

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "forte_array_at.h"


class FORTE_ESP32_LOGGER: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ESP32_LOGGER)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  
  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventREQID = 1;
  
   static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  
  static const TEventID scm_nEventCNFID = 0;
  
   static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  CIEC_BOOL &st_SD() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  }
  
  CIEC_WSTRING &st_STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(0));
  }
  
  CIEC_BOOL &st_RD() {
    return *static_cast<CIEC_BOOL*>(getDO(1));
  }
  

  FORTE_FB_DATA_ARRAY(1, 1, 2, 0);

  void executeEvent(int pa_nEIID);

public:
   FORTE_ESP32_LOGGER(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
       CFunctionBlock( pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData) {
   };

  virtual ~FORTE_ESP32_LOGGER() = default;
};

#endif // _ESP32_LOGGER_H_


