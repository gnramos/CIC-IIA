cmake_minimum_required (VERSION 2.8)

# Descrição do projeto:
project (CampeonatoIIA CXX)
set (VERSION_MAJOR 0)
set (VERSION_MINOR 4)

# Funções auxiliares
include (utils.cmake)

# Arquivos fonte:
set (SOURCES CampeonatoPub.cpp)

# Flags de compilação:
add_definitions (-g -Wall -std=c++0x) #-O0 -Wno-sign-compare

# Definir onde os arquivos serão gerados:
set (LIBRARY_OUTPUT_PATH    ${CMAKE_SOURCE_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set (DOC_OUTPUT_PATH        $ENV{HOME}/docs)
set (DOC_TEMPLATE_FILE      ${CMAKE_SOURCE_DIR}/Doxyfile.in)

# Bibliotecas/headers
include_directories_recursive ("h*" ${CMAKE_CURRENT_SOURCE_DIR}/libIIA/include)
include_directories_recursive ("h*" ${CMAKE_CURRENT_SOURCE_DIR}/libGames/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/libGames/games/Pub)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/libGames libGames)

# Criar o executável
add_executable (${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} Games)
add_dependencies (${PROJECT_NAME} Games)

check_GXX_version (4.1 4.7)
set (DOC_RECURSIVE NO)
add_doc_target (libGames)

# Informações adicionais para o usuário:
add_to_list (Autor "Guilherme N. Ramos (gnramos@unb.br)")
add_to_list (Objetivo "Executar um campeonato.")
add_to_list (Dependencia "Biblioteca libGames.")
add_to_list (Comando "\"make\" para gerar todos os arquivos.")
add_to_list (Comando "\"make test\" para executar testes na biblioteca.")
if (DOXYGEN_FOUND)
	add_to_list (Comando "\"make ${DOC_TARGET}\" para gerar documentação.\n\t\t(arquivos serão gerados em ${DOC_OUTPUT_PATH})")
endif ()
show_intro (Autor Objetivo Dependencia Comando)