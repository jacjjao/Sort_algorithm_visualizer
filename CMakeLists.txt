cmake_minimum_required(VERSION 3.15)
project(SortAlgorithmVisualizer)

include(lib/Dependencies.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
	src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} 
	PRIVATE 
		sfml-system
		sfml-graphics
		sfml-window
		sfml-audio
		${OPENGL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		sfml-system 
		sfml-graphics 
		sfml-window
		sfml-audio
		${OPENGL_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} 
	PRIVATE 
		src
		src/imgui
)

if (WIN32)
	add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND_EXPAND_LISTS
	)
endif()
