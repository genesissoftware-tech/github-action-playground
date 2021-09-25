# Works with 3.11 and tested through 3.18
cmake_minimum_required(VERSION 3.11...3.18)

# Project name and a few useful settings. Other commands can pick up the results
project(
  Dummy
  VERSION 0.0.1
  DESCRIPTION "Dummy project"
  LANGUAGES CXX C ASM)

set(CMAKE_CROSSCOMPILE OFF CACHE BOOL "is crosscompiled")
message(STATUS "CMAKE_CROSSCOMPILE ${CMAKE_CROSSCOMPILE}")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# The compiled library code is here
add_subdirectory(src)

IF(CMAKE_CROSSCOMPILING)
  message(STATUS "Cross-compiling so skipping unit tests.")
  add_subdirectory(apps)
ELSE(CMAKE_CROSSCOMPILING)
  include(CTest)
  if(BUILD_TESTING)
    # The testing code is here
    add_subdirectory(test)
  endif(BUILD_TESTING)
ENDIF()
