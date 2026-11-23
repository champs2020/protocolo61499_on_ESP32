# ESP32 4diac FORTE OPC UA Server

This project runs 4diac FORTE and an open62541 OPC UA server on an ESP32 with ESP-IDF 5.5.
The OPC UA server is started by the IEC 61499 function block `ESP32_OPCUA_SERVER_1` instead
of automatically from `app_main()`.

## Project purpose

The application provides:

- A 4diac FORTE runtime on port `61499`.
- An OPC UA server on port `4840`.
- An OPC UA temperature data source at `ns=1;s=temperature`.
- An ESP32 LED control example for 4diac monitoring.
- A 4diac SIFB that requests OPC UA server startup.

The DHT22 implementation reads the temperature from GPIO 4. Failed DHT22 reads currently
return a random fallback value and should not be interpreted as valid sensor data until
the fallback behavior is replaced with an error status.

## Repository layout

- [main/main.c](main/main.c): ESP-IDF startup and Wi-Fi/FORTE initialization.
- [components/forte_main/](components/forte_main/): FORTE integration and static archive.
- [components/opcua_server/](components/opcua_server/): open62541 server task.
- [components/model/](components/model/): OPC UA temperature data source and DHT22 driver.
- [components/open62541lib/](components/open62541lib/): vendored open62541 library.
- [components/forte_main/step_by_step_problem_solving.txt](components/forte_main/step_by_step_problem_solving.txt):
  chronological troubleshooting record.

FORTE custom function-block sources are under [ESP32_OPCUA_SERVER](../forte_2/src/modules/ESP32_OPCUA_SERVER):

- [ESP32_OPCUA_SERVER_1.cpp](../forte_2/src/modules/ESP32_OPCUA_SERVER/ESP32_OPCUA_SERVER_1.cpp)
- [ESP32_OPCUA_SERVER_1.h](../forte_2/src/modules/ESP32_OPCUA_SERVER/ESP32_OPCUA_SERVER_1.h)
- [ESP32_OPCUA_SERVER.fbt](../forte_2/src/modules/ESP32_OPCUA_SERVER/ESP32_OPCUA_SERVER.fbt)

## Firmware architecture

The startup sequence is:

```text
ESP-IDF app_main
  -> initialize Wi-Fi
  -> start FORTE task
  -> 4diac executes START/COLD or WARM
  -> ESP32_OPCUA_SERVER_1.INIT
  -> ESP32_OPCUA_SERVER_1.INITO
  -> ESP32_OPCUA_SERVER_1.START
  -> opcua_server_start()
  -> create FreeRTOS OPC UA task
  -> configure open62541
  -> create temperature data source
  -> UA_Server_run_startup()
  -> UA_Server_run_iterate()
```

The server task is on FreeRTOS core 1. FORTE and Wi-Fi continue to run alongside it.
Wi-Fi, FORTE, management monitoring, open62541, network buffers, sessions, subscriptions,
and monitored items share the ESP32 internal RAM.

## `ESP32_OPCUA_SERVER_1`

### Interface

| Direction | Name | IEC 61499 type | Purpose |
|---|---|---|---|
| Event input | `INIT` | Event | Initialize the SIFB state |
| Event input | `START` | Event | Request OPC UA server startup |
| Event output | `INITO` | Event | Initialization confirmation |
| Event output | `CNF` | Event | Start confirmation |
| Data input | `QI` | `BOOL` | Enable or disable the service |
| Data output | `QO` | `BOOL` | Last operation result |
| Data output | `STATUS` | `WSTRING` | Status text |

### Event behavior

- `INIT`
  - `QI = TRUE`: sets `QO = TRUE`, `STATUS = "IDLE"`, and sends `INITO`.
  - `QI = FALSE`: sets `QO = FALSE`, `STATUS = "DISABLED"`, and sends `INITO`.
- `START`
  - `QI = FALSE`: `QO = FALSE`, `STATUS = "DISABLED"`.
  - First enabled call: calls `opcua_server_start()`.
  - Success: `QO = TRUE`, `STATUS = "START_REQUESTED"`.
  - Task allocation failure: `QO = FALSE`, `STATUS = "START_FAILED"`.
  - Repeated call: `QO = TRUE`, `STATUS = "ALREADY_STARTED"`.
  - Every call sends `CNF`.

`START_REQUESTED` means only that the FreeRTOS task was created. It does not prove that
`UA_Server_run_startup()` completed. Confirm listening with the serial logs.

### 4diac event connections

Use this event chain:

```text
START.COLD  ─┐
START.WARM  ─┴─> ESP32_OPCUA_SERVER_1.INIT
                         |
                      INITO
                         |
                         └─> ESP32_OPCUA_SERVER_1.START
                                    |
                                   CNF
```

Set `QI = TRUE`. Do not connect `COLD` or `WARM` directly to both `INIT` and `START`.
Do not connect `CNF` back to `START`; that would create repeated start requests.

## OPC UA address space

```text
Endpoint: opc.tcp://<ESP32-IP>:4840
Node: ns=1;s=temperature
Type: UA_Float
Access: Read
Display name: Temperature
```

The temperature callback calls `ReadTemperature(DHT22_GPIO)` each time the node is read
or sampled. There is no separate sensor-polling task for this node.

## Memory configuration

Current staged limits for an ESP32 DevKit without PSRAM:

- OPC UA send buffer: `8192` bytes.
- OPC UA receive buffer: `8192` bytes.
- OPC UA SecureChannels: maximum `1`.
- OPC UA Sessions: maximum `1`.
- OPC UA Subscriptions: maximum `1`.
- OPC UA Subscriptions per Session: maximum `1`.
- OPC UA task stack: staged at `6144` bytes.
- OPC UA loop delay: `50 ms`.
- FORTE task stack: `10000` words.

Do not reduce the open62541 network buffers below `8192` bytes. Open62541 rejects or
cannot safely process SecureChannel operations below this minimum in the tested build.

The 6144-byte task stack is a staged test. Restore `8192` bytes if:

- UaExpert or 4diac requests trigger stack overflow.
- The ESP32 task watchdog reports `opcua_server`.
- `OPC UA stack high` falls below approximately `1 KB`.
- SecureChannel, session, browse, or subscription operations become unstable.

## Heap diagnostics

The OPC UA task logs heap information every three seconds:

```text
Heap: free=<bytes> largest=<bytes> minimum=<bytes>; OPC UA stack high=<bytes>
```

Meaning:

- `free`: current free internal heap.
- `largest`: largest currently contiguous allocation.
- `minimum`: lowest free heap observed since boot.
- `OPC UA stack high`: unused OPC UA task stack converted to bytes.

Use `free` and `largest` together. Heap may exist but remain too fragmented for a large
open62541 allocation.

Observed examples:

- Startup could leave approximately `17 KB` free and `11 KB` contiguous, while Namespace 0
  initialization still exhausted memory.
- A successful startup left approximately `11–11.5 KB` free.
- UaExpert session/subscription activity temporarily reduced free heap to approximately
  `7.8 KB` and the largest block to approximately `5 KB`.
- Disconnecting UaExpert recovered free heap to approximately `10 KB`.
- 4diac Watch could reduce free heap to approximately `2.8 KB` and the largest block to
  approximately `1.5 KB`, followed by a 4diac socket close.

## Build instructions

Use the ESP-IDF 5.5.4 environment and Python environment installed for this project.

### Configure and build FORTE

```powershell
cmake -S C:\esp\projects\forte_2 `
  -B C:\esp\projects\forte_2\build `
  -DFORTE_MODULE_ESP_LOGGER=ON `
  -DFORTE_MODULE_ESP32_OPCUA_SERVER_1=ON `
  -DFORTE_COM_OPC_UA_INCLUDE_DIR=C:/esp/projects/esp_forte_opca-ua_server/components/open62541lib `
  -DFORTE_COM_OPC_UA_LIB_DIR=C:/esp/projects/esp_forte_opca-ua_server/components/open62541lib `
  "-DFORTE_COM_OPC_UA_LIB=C:/esp/projects/esp_forte_opca-ua_server/components/open62541lib/open62541.c"

cmake --build C:\esp\projects\forte_2\build --target forte-static -j4
```

Copy the rebuilt archive:

```powershell
Copy-Item `
  C:\esp\projects\forte_2\build\src\libforte-static.a `
  C:\esp\projects\esp_forte_opca-ua_server\components\forte_main\libforte-static.a `
  -Force
```

### Build ESP-IDF firmware

```powershell
cd C:\esp\projects\esp_forte_opca-ua_server
idf.py build
```

The firmware output is:

```text
build\esp_forte_opca-ua_server.bin
```

### Flash and monitor

Close any existing serial monitor using COM13:

```powershell
idf.py -C C:\esp\projects\esp_forte_opca-ua_server -p COM13 flash monitor
```

Replace `COM13` with the board port reported in Windows.

## Flashing and 4diac deployment

Flashing restarts the ESP32 and closes existing TCP management and OPC UA connections.

After every flash:

1. Wait for Wi-Fi and FORTE startup.
2. Confirm `FORTE is up and running` appears in the serial log.
3. Reconnect 4diac IDE to `192.168.0.108:61499`.
4. Verify the ESP32 IP in the serial log or router lease table.
5. Download/restart the 4diac application.
6. Trigger `ESP32_OPCUA_SERVER_1.START`.

The address `192.168.0.108:61499` is only an observed example. It can change after DHCP.

## OPC UA testing

1. Start the server through 4diac.
2. Confirm:

   ```text
   OPC UA temperature server listening on port 4840
   ```

3. Connect UaExpert to:

   ```text
   opc.tcp://<ESP32-IP>:4840
   ```

4. Browse or read:

   ```text
   ns=1;s=temperature
   ```

5. Prefer a direct read before creating a subscription.
6. Use at most one subscription and monitored item.
7. Use a monitored sampling interval of at least `3000 ms`.

## Testing 4diac Watch safely

Do not keep all of these active at once:

```text
UaExpert
+ 4diac Watch
+ OPC UA subscription
+ 4diac server management
```

Use separate test phases:

1. Disconnect UaExpert.
2. Start 4diac Watch.
3. Add one watch element at a time.
4. Remove or stop Watch after inspection.
5. Disconnect 4diac Watch.
6. Start or reconnect UaExpert alone.

Do not increase the watchdog timeout to hide a stall. A watchdog reset or socket close
is a downstream symptom of heap exhaustion, task starvation, or a board reset.

## Known limitations

### ESP32 heap

No simultaneous-activity guarantee is provided for:

- 4diac management
- 4diac monitoring
- UaExpert
- OPC UA subscriptions
- Wi-Fi
- FORTE
- open62541

This is the current branch's main limitation.

### ESP32 DevKit without PSRAM

An ESP32-WROOM/DevKit board with only internal RAM is suitable for sequential testing but
not reliable simultaneous testing of all clients and monitors.

Recommended improvements:

- Use an ESP32 module with PSRAM.
- Move large network/send buffers to PSRAM if open62541 and ESP-IDF support it.
- Add static task stacks where measured stack high-water is safe.
- Reduce 4diac and Wi-Fi task footprints.
- Disable unused OPC UA features.
- Keep only one session and subscription.
- Avoid continuous DHT22 polling.
- Consider moving OPC UA monitoring or FORTE management to a PC/Raspberry Pi host and
  exposing one lightweight data interface to the ESP32.

### DHT22 fallback

The DHT22 driver currently returns a random `20–30 C` value when a sensor read fails.
This is not valid sensor data. Replace the fallback with a sensor status or OPC UA
`BadOutOfMemory`/sensor error value before production use.

### 4diac socket closure

The 4diac IDE `Could not add watch` and `Socket closed` messages do not prove that the
`ESP32_OPCUA_SERVER_1.CNF` event or `CNF` port is faulty.

Correlate those messages with the ESP32 serial log. Look for:

- `BadOutOfMemory`
- `Heap`
- `Largest`
- Task watchdog
- Stack overflow
- Socket closed
- Board reset
- `Failed to create OPC UA server`
- `Failed to start OPC UA server`

## Optional boot application

A generated boot file is available at:

[ESP32_blinky_ESP32.fboot](../forte_2/ESP32_blinky_ESP32.fboot)

It creates `Blinky_RES`, `ESP32_LOGGER`, and `ESP32_OPCUA_SERVER_1`, and starts the server
after `INITO`.

It is not currently embedded in the ESP32 flash filesystem. To make it run without a
4diac download:

1. Copy it as `spiffs/forte.fboot`.
2. Configure a SPIFFS partition.
3. Mount the partition from `app_main`.
4. Set `FORTE_BootfileLocation=/spiffs/forte.fboot`.
5. Rebuild FORTE and ESP-IDF.
6. Erase and flash the SPIFFS partition with the application.