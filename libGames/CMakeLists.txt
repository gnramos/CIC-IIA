cmake_minimum_required (VERSION 2.8)

# Descrição do projeto:
project (libGames CXX)
set (LIB_NAME Games)
set (VERSION_MAJOR 0)
set (VERSION_MINOR 4)

# Funções auxiliares
include (../utils.cmake)

# Definir jogo(s):
set (GAMES Pub TicTacToe)

# Arquivos fonte:
include_directories (include)
include_directories (include/statistics)
include_directories (include/tournaments)
set (SOURCES src/libGames.cpp)

# Incluir jogos:
foreach (GAME ${GAMES})
	file (GLOB ${GAME}_SRC games/${GAME}/*.cpp)
	include_directories (games/${GAME})
	
	# Remover o arquivo de teste
	foreach (GAME_FILE ${${GAME}_SRC})
		if (${GAME_FILE} MATCHES "Test${GAME}.cpp")
			list (REMOVE_ITEM ${GAME}_SRC ${GAME_FILE})
		endif ()
	endforeach ()
	set (SOURCES ${SOURCES} ${${GAME}_SRC})
endforeach ()

# Flags de compilação:
add_definitions (-g -Wall -std=c++0x -O0 -Wno-sign-compare)

# Definir onde os arquivos serão gerados:
set (LIBRARY_OUTPUT_PATH    ${CMAKE_SOURCE_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set (DOC_OUTPUT_PATH        $ENV{HOME}/docs)

# Bibliotecas necessárias:
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../libIIA libIIA)
include_directories_recursive ("h*" ../libIIA/include)

# Gerar a bilioteca:
add_library (${LIB_NAME} SHARED ${SOURCES})
target_link_libraries (${LIB_NAME} IIA)
add_dependencies (${LIB_NAME} IIA)

check_GXX_version (4.1 4.7)
add_tests_in_dir (test ${LIB_NAME})
foreach (GAME ${GAMES})
	add_custom_test(games/${GAME} Test${GAME} ${LIB_NAME})
endforeach ()
add_doc_target (libIIA)

# Informações adicionais para o usuário:
add_to_list (Autor "Guilherme N. Ramos (gnramos@unb.br)")
add_to_list (Objetivo "Criar uma biblioteca com funções de jogos (com adversários).")
add_to_list (Objetivo "Exemplificar o uso destas funções.")
add_to_list (Dependencia "Biblioteca libIIA.")
add_to_list (Comando "\"make\" para gerar todos os arquivos.")
add_to_list (Comando "\"make test\" para executar testes na biblioteca.")
if (DOXYGEN_FOUND)
	add_to_list (Comando "\"make ${DOC_TARGET}\" para gerar documentação.\n\t\t(arquivos serão gerados em ${DOC_OUTPUT_PATH})")
endif ()
show_intro (Autor Objetivo Dependencia Comando)