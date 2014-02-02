# Definição de macros úteis.
#
# @author Guilherme N. Ramos (gnramos@unb.br)
# @date 2013/05/14



		##############
		# Compilação #
		##############

# Verificar versão mínima do compilador
macro (CHECK_GXX_VERSION GXX_MIN_VERSION GXX_MAX_VERSION)  
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion 
	                OUTPUT_VARIABLE GXX_VERSION)
	if (${GXX_VERSION} VERSION_LESS ${GXX_MIN_VERSION})
		message (FATAL_ERROR "É necessário um compilador com versão >= ${GXX_MIN_VERSION}.")
	endif ()
	if (${GXX_VERSION} VERSION_GREATER ${GXX_MAX_VERSION})
		message (FATAL_ERROR "É necessário um compilador com versão <= ${GXX_MAX_VERSION}.")
	endif ()
endmacro ()





		##############
		# Diretórios #
		##############

# Define a lista de subdiretórios (nomes apenas) do diretório dado.
macro (GET_SUBDIR_NAME_LIST DIR TARGET_LIST)
	file (GLOB SUBDIRS RELATIVE ${PROJECT_SOURCE_DIR}/${DIR} ${DIR}/*)
	foreach(SUBDIR ${SUBDIRS})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${DIR}/${SUBDIR})
			set (${TARGET_LIST} ${${TARGET_LIST}} ${SUBDIR})
		endif()
	endforeach()
endmacro ()

# Incluir, recursivamente, os diretórios com arquivos dos tipos dados a partir 
# do diretório base fornecido. Os tipos devem serão usados como parte da 
# "globbing expression" *.[TIPOS], e devem ser separados pelo caracter '|'.
macro (INCLUDE_DIRECTORIES_RECURSIVE FILE_TYPES BASE_DIRECTORY)
	file (GLOB_RECURSE FILE_LIST ${BASE_DIRECTORY}/*.${FILE_TYPES})
	foreach (FILE_PATH ${FILE_LIST})
		get_filename_component (DIR_PATH ${FILE_PATH} PATH)
		set (DIR_LIST ${DIR_LIST} ${DIR_PATH})
	endforeach ()
	list (REMOVE_DUPLICATES DIR_LIST)
	foreach (DIR_NAME ${DIR_LIST})
		include_directories (${DIR_NAME})
	endforeach ()
endmacro ()




		################
		# Documentação #
		################

# Configurações extras: o arquivo de configuração pode ser gerado a partir de um 
# template de nome Doxygen.in, que é configurado com as seguintes variáveis:
# PROJECT_NAME, VERSION, DOC_OUTPUT_DIR, DOC_INCLUDE_DIRS, DOC_EXCLUDE_DIRS, 
# DOC_EXCLUDE_PATTERN, e DOC_TAG_FILES

find_package(Doxygen QUIET)
if (NOT DOC_OUTPUT_PATH)
	set (DOC_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/docs)
endif ()
if (NOT DOC_TEMPLATE_FILE)
	get_filename_component (PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
	set (DOC_TEMPLATE_FILE ${PARENT_DIR}/Doxyfile.in)
endif ()
if (NOT DOC_INCLUDE_DIRS)
	set (DOC_INCLUDE_DIRS .)
endif ()
if (NOT DOC_RECURSIVE)
	set (DOC_RECURSIVE YES)
endif ()

# Adiciona a opção para gerar documentação. Se DOC_TEMPLATE_FILE não existir, cria automaticamente.
macro (ADD_DOC_TARGET)
	if (DOXYGEN_FOUND)
		if (NOT EXISTS ${DOC_TEMPLATE_FILE})
			execute_process(COMMAND ${DOXYGEN_EXECUTABLE} -g ${DOC_TEMPLATE_FILE} OUTPUT_QUIET)
		endif ()

		set (DOXYFILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.Doxyfile)
		set (DOC_OUTPUT_DIR ${DOC_OUTPUT_PATH}/${PROJECT_NAME})
		set (DOC_TARGET ${PROJECT_NAME}-doc)

		if (NOT EXISTS ${DOC_OUTPUT_PATH})
			add_custom_target (${DOC_TARGET}
								COMMAND mkdir ${DOC_OUTPUT_PATH}
								COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
								COMMENT "Gerando documentação em \"${DOC_OUTPUT_DIR}\"..."
								WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
		else ()
			add_custom_target (${DOC_TARGET}
								COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
								COMMENT "Gerando documentação em \"${DOC_OUTPUT_DIR}\"..."
								WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
		endif ()

		
		foreach (EXTERNAL_DOC ${ARGN})
			set (${EXTERNAL_DOC}_DOC_TARGET ${EXTERNAL_DOC}-doc)
			set (DOC_TAG_FILES "${DOC_TAG_FILES} ${DOC_OUTPUT_PATH}/${EXTERNAL_DOC}/${EXTERNAL_DOC}.tag=${DOC_OUTPUT_PATH}/${EXTERNAL_DOC}/html")
			add_dependencies (${DOC_TARGET} ${${EXTERNAL_DOC}_DOC_TARGET})
		endforeach ()

		configure_file (${DOC_TEMPLATE_FILE} ${DOXYFILE} @ONLY IMMEDIATE)
	endif()
endmacro ()





		############
		# Exemplos #
		############

# Gerar um exemplo a partir de todos os arquivos dentro do diretório dado. Bibliotecas 
# necessárias são fornecidas como argumentos adicionais.
macro (ADD_CUSTOM_EXAMPLE EXAMPLE_DIR EXAMPLE_NAME)
	file (GLOB ${EXAMPLE_NAME}_SRC ${EXAMPLE_DIR}/${EXAMPLE_NAME}/*.cpp)	
	add_executable (${EXAMPLE_NAME} ${${EXAMPLE_NAME}_SRC})
	target_link_libraries (${EXAMPLE_NAME} ${ARGN})
endmacro ()

# Gerar exemplos a partir de um diretório. Supõe-se que cada exemplo está organizado
# em seu próprio subdiretório. Bibliotecas necessárias são fornecidas como argumentos 
# adicionais.
macro (ADD_EXAMPLES_IN_DIR EXAMPLE_DIR)
	if (NOT EXISTS ${EXECUTABLE_OUTPUT_PATH}/${EXAMPLE_DIR})
		file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${EXAMPLE_DIR})
	endif ()

	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${EXAMPLE_DIR})

	include_directories_recursive ("h*" ${EXAMPLE_DIR})
	get_subdir_name_list (${EXAMPLE_DIR} EXAMPLES)
	foreach (EXAMPLE ${EXAMPLES})
		add_custom_example (${EXAMPLE_DIR} ${EXAMPLE} ${ARGN})
	endforeach ()

	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endmacro ()





		#############
		# Mensagens #
		#############

# Exibir mensagens do projeto.
macro(show)
	message ("[${PROJECT_NAME}] ${ARGN}")
endmacro()

# Adiciona um item a lista.
macro (ADD_TO_LIST LIST_NAME ITEM)
	set (${PROJECT_NAME}_${LIST_NAME}S ${${PROJECT_NAME}_${LIST_NAME}S} ${ITEM})
endmacro ()

# Mostrar mensagem de apresentação do projeto identificando o nome do projeto e
# os autores
macro (SHOW_INTRO)
	message ("")
	show ("Projeto: <[ ${PROJECT_NAME} v${VERSION_MAJOR}.${VERSION_MINOR} ]>")
	foreach (LIST_NAME ${ARGN})
		message ("")
		show ("${LIST_NAME}(s)")
		foreach (ITEM ${${PROJECT_NAME}_${LIST_NAME}S})
			show ("  - ${ITEM}")
		endforeach ()
	endforeach ()
	message ("")
endmacro ()



		##########
		# Testes #
		##########
enable_testing ()

# Adicionar executável específico para teste. Recebe como entrada o diretório 
# em que estão os arquivos de teste, o nome do teste (deve ser parte do nome 
# de cada arquivo a ser incluído). Bibliotecas necessárias são fornecidas como 
# argumentos adicionais.
macro (ADD_CUSTOM_TEST TEST_DIR TEST_NAME)
	file (GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*${TEST_NAME}*.cpp)
	add_executable (${TEST_NAME} ${TEST_SOURCES})
	add_dependencies (${TEST_NAME} ${ARGN})
	target_link_libraries (${TEST_NAME} ${ARGN})
	add_test (NAME ${TEST_NAME} 
			  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
			  COMMAND ${TEST_NAME})
endmacro ()

# Gerar testes a partir dos arquivos .cpp encontrados no diretório dado. 
# Bibliotecas necessárias são fornecidas como argumentos adicionais.
macro (ADD_TESTS_IN_DIR TEST_DIR)
	if (NOT EXISTS ${EXECUTABLE_OUTPUT_PATH}/${TEST_DIR})
		file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${TEST_DIR})
	endif ()

	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/${TEST_DIR})

	file (GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cpp)
	foreach (TEST_FILE ${TEST_SOURCES})
		get_filename_component (TEST_NAME ${TEST_FILE} NAME_WE)
		add_custom_test (${TEST_DIR} ${TEST_NAME} ${ARGN})
	endforeach ()

	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endmacro ()