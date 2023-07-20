# File generated at : 02:47:01, Sat 20 Apr 
# Converted Project : D:\Smash\Smash-Engine\SmashEngine\SmashEngine.vcxproj
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME SmashEngine)


# Outputs
set(OUTPUT_DEBUG ${PROJECT_DIR}/bin)
set(OUTPUT_RELEASE ${PROJECT_DIR}/bin)

################# CMake Project ############################
# The main options of project                              #
############################################################

project(${PROJECT_NAME} CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

############## Artefacts Output ############################
# Defines outputs , depending BUILD TYPE                   #
############################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
endif()

# Messages
message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

# Source Files
Set(FILTER_COMPONENT
	./Camera.cpp 
	./Camera.h 
	./Component.h 
	./ComponentCreator.h 
	./ComponentType.h 
	./Transform.cpp 
	./Transform.h
	)

source_group("Component" FILES ${FILTER_COMPONENT})

set(FILTER_EDITOR
	./imconfig.h
	./imconfig.cpp
	./imgui.h 
	./imgui.ini 
	./imgui_draw.cpp 
	./imgui_impl_glfw_gl3.cpp 
	./imgui_internal.h
	)
	
source_group("Editor" FILES ${FILTER_EDITOR})

set(FILTER_ENGINE
	./Engine.h 
	./EngineType.h 
	./MainEngine.cpp 
	./MainEngine.h
	)

source_group("Engine" FILES ${FILTER_ENGINE})

set(FILTER_GRAPHICS
	./Graphics.cpp 
	./Graphics.h 
	./Render.h 
	./Render.cpp
	)

source_group("Graphics" FILES ${FILTER_GRAPHICS})

set(FILTER_GRAPHICS_PRIMITIVES
	./Cube.cpp 
	./Cube.h 
	./Model.cpp 
	./Model.h 
	./Primitive.cpp 
	./Primitive.h 
	./Sphere.cpp 
	./Sphere.h 
	./Wireframe.cpp 
	./Wireframe.h
	)

source_group("Graphics//Primitives" FILES ${FILTER_GRAPHICS_PRIMITIVES})

set(FILTER_INPUT
	./InputSignal.cpp 
	./InputSignal.h 
	./InputType.h
	)

source_group("Input" FILES ${FILTER_INPUT})

set(FILTER_MEMORYMANAGER
	./MemoryPool.cpp 
	./MemoryPool.h 
	./StandardMemoryPool.cpp 
	./StandardMemoryPool.h
	)

source_group("Memory Manager" FILES ${FILTER_MEMORYMANAGER})

set(FILTER_OBJECTS
	./Gameobject.cpp 
	./Gameobject.h
	)

source_group("Object" FILES ${FILTER_OBJECTS})

set(FILTER_PHYSICS
	./Body.cpp 
	./Body.h 
	./Physics.cpp 
	./Physics.h 
	./PhysicsState.h 
	)

source_group("Physics" FILES ${FILTER_PHYSICS})

set(FILTER_PRECOMPILEDHEADER
	./stdafx.h 
	./stdafx.cpp
	)

SOURCE_GROUP("Precompiled Header" FILES ${FILTER_PRECOMPILEDHEADER})

set(FILTER_RESOURCEFILES
	./tinyxml2.cpp
	./tinyxml2.h
	)

source_group("Resource Files" FILES ${FILTER_RESOURCEFILES})

set(FILTER_RESOURCEMANAGER
	./PrimitiveManager.h 
	./PrimitiveManager.cpp 
	./ShaderManager.h 
	./ShaderManager.cpp 
	./TextureManager.h 
	./TextureManager.cpp
	)

source_group("Resource Managers" FILES ${FILTER_RESOURCEMANAGER})

set(FILTER_RESOURCES
	./ResourcePath.cpp 
	./ResourcePath.h 
	./ResourceType.h 
	./Shader.cpp 
	./Shader.h 
	./Texture.cpp 
	./Texture.h 
	./VertexBufferObject.cpp 
	./VertexBufferObject.h
	)

source_group("Resources" FILES ${FILTER_RESOURCES})

set(FILTER_SHADERS
	./normal.frag 
	./normal.vert
	)

source_group("Shaders" FILES ${FILTER_SHADERS})

set(FILTER_SIGNAL_SIGNALCHANNELS
	./CameraSignal.h 
	./DebugSignal.h
	)

source_group("Signal//SignalChanels" FILES ${FILTER_SIGNAL_SIGNALCHANNELS})

set(FILTER_SIGNAL
	./EngineState.h 
	./SignalHandler.h 
	./SignalManager.h 
	./SignalManager.cpp 
	./SignalSource.h 
	./sigslot.h
	)

source_group("Signal" FILES ${FILTER_SIGNAL})

set(FILTER_SYSTEMS
	./EditorSystem.cpp 
	./EditorSystem.h 
	./GameLogicSystem.cpp 
	./GameLogicSystem.h 
	./ObjectFactory.cpp 
	./ObjectFactory.h 
	./ObjectManager.h 
	./ObjectManager.cpp 
	./System.h 
	./System.cpp 
	./Watch.h 
	./Watch.cpp 
	./WindowSystem.cpp 
	./WindowSystem.h
	)

source_group("Systems" FILES ${FILTER_SYSTEMS})

# Add executable to build.
add_executable(${PROJECT_NAME} 
   ${FILTER_SYSTEMS} ${FILTER_SYSTEMS} ${FILTER_SIGNAL_SIGNALCHANNELS} ${FILTER_SHADERS} ${FILTER_RESOURCES} ${FILTER_RESOURCEMANAGER} ${FILTER_RESOURCEFILES} ${FILTER_PRECOMPILEDHEADER} ${FILTER_PHYSICS} ${FILTER_COMPONENT} ${FILTER_EDITOR} ${FILTER_ENGINE} ${FILTER_GRAPHICS} ${FILTER_GRAPHICS_PRIMITIVES} ${FILTER_INPUT} ${FILTER_MEMORYMANAGER} ${FILTER_OBJECTS}
)

######################### Flags ############################
# Defines Flags for Windows and Linux                      #
############################################################

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

# Preprocessor definitions
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /GL /Oi /Gy /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /MD /Od /Zi /EHsc)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

if(MSVC)
   target_link_libraries(${PROJECT_NAME} opengl32.lib glew32s.lib glfw3.lib glew32.lib SOIL.lib assimp.lib glfw3dll.lib )
endif(MSVC)
