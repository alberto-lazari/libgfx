cmake_minimum_required(VERSION 3.16)
project(libgfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# Automatically scan for sources
file(GLOB GFX_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create shared library
add_library(gfx SHARED ${GFX_SOURCES})

# On Windows, export symbols automatically (generate .lib)
if(WIN32)
  target_compile_definitions(gfx PRIVATE GFX_EXPORTS)
endif()

add_executable(gfx_test tests/test.cpp)
target_link_libraries(gfx_test PRIVATE gfx)

# macOS RPATH
if(APPLE)
  set_target_properties(gfx_test PROPERTIES
    BUILD_RPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  )
endif()

# Cross-platform test target
add_custom_target(test
  COMMAND gfx_test
  DEPENDS gfx_test
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

install(TARGETS gfx
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)
