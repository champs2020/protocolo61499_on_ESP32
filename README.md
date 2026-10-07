# 🚀 Eclipse 4diac FORTE for ESP32 (IEC 61499 Runtime & Custom SIFBs)

Repositório dedicado à integração do motor de execução em tempo real **Eclipse 4diac FORTE (FORTE_LITE)** com o microcontrolador **ESP32**, implementando lógica de controlo distribuída baseada na norma **IEC 61499**.

---

## 📌 Principais Realizações e Funcionalidades

### 1. Atualização e Otimização do FORTE para ESP32
* **FORTE Engine Update:** Sincronização e otimização do código-fonte base do FORTE para funcionamento estável em arquiteturas de 32 bits baseadas no ESP-IDF.
* **CMake Customizado:** Configuração avançada de compilação cruzada (`CMakeLists.txt`) adaptada especificamente para o firmware do ESP32, isolando os módulos de I/O e garantindo uma footprint de memória reduzida (`FORTE_LITE`).

### 2. Desenvolvimento de Service Interface Function Blocks (SIFBs) Nativos
* **`ESP32_LOGGER` (Custom SIFB):** Bloco de interface de serviço desenvolvido de raiz e integrado como firmware nativo no runtime (`DEFINE_FIRMWARE_FB`).
  * Mapeamento direto do pino **GPIO 2** do ESP32 para atuação física de LEDs baseada em eventos cíclicos.
  * Sincronização avançada entre o fluxo de eventos (`INIT`, `REQ`, `CNF`) e os fluxos de dados (`SD`, `STATUS`, `RD`).
  * Tratamento de logs nativos utilizando as macros do sistema operativo do ESP32 (`ESP_LOGI`).
* **`ESP32_IO` (Multi-Channel SIFB):** Estrutura modular concebida para gerir múltiplos canais de E/S digitais (8 entradas e 8 saídas) com temporização parametrizável (`UpdateInterval` em Hz).

### 3. Resolução de Problemas Críticos de Compilação e Runtime
* **Alinhamento de Escopo e Assinaturas C++:** Correção de erros de escopo (`was not declared in this scope`) através da unificação correta dos métodos *getters/setters* no cabeçalho (`.h`) e na implementação (`.cpp`).
* **Correção de Objetos no 4diac IDE (`NO_SUCH_OBJECT`):** Sincronização precisa entre os dicionários de strings do C++ (`CStringDictionary`) e os nomes gráficos dos pinos desenhados no 4diac IDE (`SD`, `RD`, `STATUS`).
* **Gestão de Tipos de Dados:** Resolução de conflitos de tipagem estática e polimórfica (`CIEC_BOOL`, `CIEC_WSTRING` e contentores `ANY`) para garantir atribuições seguras na memória do microcontrolador.

---

## 📂 Estrutura do Repositório

```text
├── src/
│   ├── modules/
│   │   └── ESP_LOGGER/        # Código-fonte customizado do SIFB ESP32_LOGGER (.h / .cpp)
│   ├── core/                  # Núcleo atualizado do FORTE runtime
│   └── CMakeLists.txt         # Configuração de build customizada para ESP-IDF
├── 4diac_models/              # Ficheiros de blocos e testes exportados do 4diac IDE (.fbt)
└── README.md                  # Documentação do projeto
