cmake_minimum_required (VERSION 2.8)

# Descrição do projeto:
project (libIIA CXX)
set (LIB_NAME IIA)
set (VERSION_MAJOR 0)
set (VERSION_MINOR 4)

# Funções auxiliares
include (../utils.cmake)

# Arquivos fonte:
include_directories_recursive ("h*" include)
set (SOURCES src/libIIA.cpp)

# Flags de compilação:
add_definitions (-g -Wall -std=c++0x) #-O0 -Wno-sign-compare

# Definir onde os arquivos serão gerados:
set (LIBRARY_OUTPUT_PATH    ${CMAKE_SOURCE_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set (DOC_OUTPUT_PATH        $ENV{HOME}/docs)

# Gerar a bilioteca:
add_library (${LIB_NAME} SHARED ${SOURCES})
if (NOT UNIX)
	message (FATAL_ERROR "O sistema operacional deve ser Unix.")
elseif (NOT APPLE)
	target_link_libraries (${LIB_NAME} rt)
endif ()

check_GXX_version (4.1 4.7)
add_tests_in_dir (test ${LIB_NAME})
add_examples_in_dir (examples ${LIB_NAME})
add_doc_target ()

# Informações adicionais para o usuário:
add_to_list (Autor "Guilherme N. Ramos (gnramos@unb.br)")
add_to_list (Objetivo "Criar uma biblioteca com funções de IA.")
add_to_list (Objetivo "Exemplificar o uso destas funções.")
add_to_list (Comando "\"make\" para gerar todos os arquivos.")
add_to_list (Comando "\"make test\" para executar testes na biblioteca.")
if (DOXYGEN_FOUND)
	add_to_list (Comando "\"make ${DOC_TARGET}\" para gerar documentação.\n\t\t(arquivos serão gerados em ${DOC_OUTPUT_PATH})")
endif ()
foreach (EXAMPLE ${EXAMPLES}) # EXAMPLES é gerado em "add_examples_in_dir ()"
	add_to_list (Exemplo ${EXAMPLE})
endforeach ()
show_intro (Autor Objetivo Comando Exemplo)