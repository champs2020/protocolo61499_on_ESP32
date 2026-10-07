# 🚀 Eclipse 4diac FORTE for ESP32 (IEC 61499 Runtime & Custom SIFBs)

Repository dedicated to integrating the **Eclipse 4diac FORTE (FORTE_LITE)** real-time execution engine with the **ESP32** microcontroller, implementing distributed control logic based on the **IEC 61499** standard.

---

## 📌 Main Achievements and Features

### 1. FORTE Engine Update & Optimization for ESP32
* **FORTE Engine Update:** Synchronization and optimization of the core FORTE source code for stable execution on 32-bit ESP-IDF-based architectures.
* **Custom CMake:** Advanced cross-compilation configuration (`CMakeLists.txt`) tailored specifically for the ESP32 firmware, isolating I/O modules and ensuring a reduced memory footprint (`FORTE_LITE`).

### 2. Custom Service Interface Function Blocks (SIFBs) Development
* **`ESP32_LOGGER` (Custom SIFB):** Service interface block developed from scratch and integrated as a native firmware component in the runtime (`DEFINE_FIRMWARE_FB`).
  * Direct mapping of the ESP32 **GPIO 2** pin for physical LED actuation triggered by cyclic events.
  * Advanced synchronization between the event flow (`INIT`, `REQ`, `CNF`) and data flows (`SD`, `STATUS`, `RD`).
  * Native logging integration using ESP-IDF operating system macros (`ESP_LOGI`).
* **`ESP32_IO` (Multi-Channel SIFB):** Modular structure designed to manage multiple digital I/O channels (8 inputs and 8 outputs) with parameterizable timing (`UpdateInterval` in Hz).

### 3. Resolution of Critical Compilation and Runtime Issues
* **C++ Scope and Signature Alignment:** Fixed scope errors (`was not declared in this scope`) by properly unifying getters/setters in both the header (`.h`) and implementation (`.cpp`) files.
* **4DIAC IDE Object Fix (`NO_SUCH_OBJECT`):** Precise synchronization between C++ string dictionaries (`CStringDictionary`) and graphical pin names drawn in the 4diac IDE (`SD`, `RD`, `STATUS`).
* **Data Type Management:** Resolved static and polymorphic type conflicts (`CIEC_BOOL`, `CIEC_WSTRING`, and `ANY` containers) to ensure safe memory assignments on the microcontroller.

---

## 📂 Repository Structure

```text
├── src/
│   ├── modules/
│   │   └── ESP_LOGGER/        # Custom SIFB source code for ESP32_LOGGER (.h / .cpp)
│   ├── core/                  # Updated FORTE runtime core
│   └── CMakeLists.txt         # Custom build configuration for ESP-IDF
├── 4diac_models/              # Block files and tests exported from 4diac IDE (.fbt)
└── README.md                  # Project documentation
