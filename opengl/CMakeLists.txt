# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (recolic-hust-opengl)

find_package(OpenGL REQUIRED)
# Use header-only rlib.

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# hw1
add_executable(hw1 
	hw1/hw1.cc
	common/shader.cc
	common/shader.hpp
	
	hw1/SimpleFragmentShader.fragmentshader
	hw1/SimpleVertexShader.vertexshader
)
target_link_libraries(hw1
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(hw1 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hw1/")
create_target_launcher(hw1 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/hw1/")
create_default_target_launcher(hw1 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/hw1/") # tut 1 is not the default or people would complain that tut 2 doesn't work


# hw2
add_executable(hw2
	hw2/hw2.cc
	common/shader.cc
	common/shader.hpp
	common/controls.cc
	common/controls.hpp
	common/texture.cc
	common/texture.hpp
	common/objloader.cc
	common/objloader.hpp
	
	hw2/StandardShading.vertexshader
	hw2/StandardShading.fragmentshader
)
target_link_libraries(hw2
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(hw2 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hw2/")
create_target_launcher(hw2 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/hw2/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET hw1 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/hw1${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/hw1/"
)
add_custom_command(
   TARGET hw2 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/hw2${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/hw2/"
)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

