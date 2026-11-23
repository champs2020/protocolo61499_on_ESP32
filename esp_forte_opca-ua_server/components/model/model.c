#include "open62541.h"
#include "model.h"
#include "DHT22.h"
#include "esp_log.h"

#define TAG "OPCUA_DATA"

// /* LED Method */

// UA_StatusCode
// ledProcessCallBack(UA_Server *server,
//                    const UA_NodeId *sessionId, void *sessionHandle,
//                    const UA_NodeId *methodId, void *methodContext,
//                    const UA_NodeId *objectId, void *objectContext,
//                    size_t inputSize, const UA_Variant *input,
//                    size_t outputSize, UA_Variant *output)
// {
//     UA_Int32 i = 0;
//     UA_Int32 *inputVal = (UA_Int32 *)input->data;
//     UA_String tmp = UA_STRING_ALLOC("Data Received");
//     if (*inputVal > 0)
//     {
//         tmp.data = (UA_Byte *)UA_realloc(tmp.data, tmp.length);
//         while (i < *inputVal + 1)
//         {
//             gpio_pad_select_gpio(BLINK_GPIO);
//             gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
//             gpio_set_level(BLINK_GPIO, 1);
//             vTaskDelay(500 / portTICK_PERIOD_MS);
//             gpio_set_level(BLINK_GPIO, 0);
//             vTaskDelay(500 / portTICK_PERIOD_MS);
//             i++;
//         }
//     }
//     UA_String_clear(&tmp);
//     return UA_STATUSCODE_GOOD;
// }

// void
// addLEDMethod(UA_Server *server)
// {

//     UA_NodeId createdNodeId;
//     UA_ObjectAttributes object_attr = UA_ObjectAttributes_default;

//     object_attr.description = UA_LOCALIZEDTEXT("en-US", "A pump!");
//     object_attr.displayName = UA_LOCALIZEDTEXT("en-US", "Pump1");

//     UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1, 0),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
//                             UA_QUALIFIEDNAME(1, "Pump1"),
//                             UA_NODEID_NUMERIC(2, 1002),
//                             object_attr, NULL, &createdNodeId);

//     UA_Argument inputArgument;
//     UA_Argument_init(&inputArgument);
//     inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Number of times to blink LED!");
//     inputArgument.name = UA_STRING("Blink Count");
//     inputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//     inputArgument.valueRank = -1; /* scalar */

//     /* And output argument for a void method is not logical, check here !!! */
//     UA_Argument outputArgument;
//     UA_Argument_init(&outputArgument);
//     outputArgument.description = UA_LOCALIZEDTEXT("en-US", "LED Blinked");
//     outputArgument.name = UA_STRING("Led Blink Method Output");
//     outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//     outputArgument.valueRank = UA_VALUERANK_ONE_DIMENSION;

//     UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
//     helloAttr.description = UA_LOCALIZEDTEXT("en-US", "Enter the number of times you want LED to blin!");
//     helloAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Blink");
//     helloAttr.executable = true;
//     helloAttr.userExecutable = true;
//     UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                             UA_QUALIFIEDNAME(1, "Blink"),
//                             helloAttr, &ledProcessCallBack,
//                             1, &inputArgument, 1, &outputArgument, NULL, &createdNodeId);
// }


/* Temperature */

UA_StatusCode
readCurrentTemperature(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {
    UA_Float temperature = ReadTemperature(DHT22_GPIO);
    ESP_LOGI(TAG, "Temperature read: %.1f C", temperature);
    UA_Variant_setScalarCopy(&dataValue->value, &temperature,
                             &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


void
addCurrentTemperatureDataSourceVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Temperature");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;
    attr.minimumSamplingInterval = 3000.0;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "temperature");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Ambient Temperature");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentTemperature;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}