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

#ifndef _ESP32_OPCUA_SERVER_1_H_
#define _ESP32_OPCUA_SERVER_1_H_

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_wstring.h"
#include "forte_array_at.h"

class FORTE_ESP32_OPCUA_SERVER_1: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_ESP32_OPCUA_SERVER_1)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  
  static const TEventID scm_nEventINITID = 0;
  static const TEventID scm_nEventSTARTID = 1;
  
   static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  
  static const TEventID scm_nEventINITOID = 0;
  static const TEventID scm_nEventCNFID = 1;
  
   static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  bool m_started;

  CIEC_BOOL &st_QI() {
    return *static_cast<CIEC_BOOL*>(getDI(0));
  }
  
  CIEC_BOOL &st_QO() {
    return *static_cast<CIEC_BOOL*>(getDO(0));
  }
  
  CIEC_WSTRING &st_STATUS() {
    return *static_cast<CIEC_WSTRING*>(getDO(1));
  }
  

  FORTE_FB_DATA_ARRAY(2, 1, 2, 0);

  void executeEvent(int pa_nEIID);

public:
   FORTE_ESP32_OPCUA_SERVER_1(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
       CFunctionBlock( pa_poSrcRes, &scm_stFBInterfaceSpec, pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData),
       m_started(false) {
   };

  virtual ~FORTE_ESP32_OPCUA_SERVER_1() = default;
};

#endif // _ESP32_OPCUA_SERVER_1_H_


