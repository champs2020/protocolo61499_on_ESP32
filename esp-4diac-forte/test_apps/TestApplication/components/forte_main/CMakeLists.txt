# No arquivo CMakeLists.txt do seu COMPONENTE

# Importante: Garanta que SRCS contenha APENAS o seu código de inicialização do ESP32.
# Se o FORTE reclamar de duplicatas em 'initForte' ou 'stringlist', 
# verifique se esses arquivos .cpp não estão na mesma pasta que este CMakeLists.
idf_component_register(
    SRCS "forte_main.cpp" 
)
 