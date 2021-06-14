#----------------------------------------------------------------------------
# Setup the project

cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(g4_py8_decayer)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find Pythia8 (required package)
#
# Ideally, should be done via find_package:
#
# ---> find_package(Pythia8 REQUIRED)

find_library( PYTHIA8_LIBRARIES NAMES pythia8 
			     HINTS $ENV{PYTHIA8} $ENV{PYTHIA8}/lib)
if(NOT PYTHIA8_LIBRARIES)
  message(FATAL_ERROR "pythia8 library not found")
endif()

find_path( PYTHIA8_INCLUDES Pythia8/Pythia.h
           HINTS $ENV{PYTHIA8} $ENV{PYTHIA8}/include $ENV{PYTHIA8}/include/Pythia8 )
if (NOT PYTHIA8_INCLUDES )
  message(FATAL_ERROR "pythia8 include directory not found")
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
		    ${PYTHIA8_INCLUDES})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(g4_py8_decayer g4_py8_decayer.cc ${sources} ${headers})
target_link_libraries(g4_py8_decayer  ${Geant4_LIBRARIES} ${PYTHIA8_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build decayer6. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
# ---> NO NEED SO FAR !!!
#
#set(decayer6_SCRIPTS
#    init_vis.mac pythia6_decayer.in pythia6_decayer.out vis.mac
#  )

#foreach(_script ${decayer6_SCRIPTS})
#  configure_file(
#    ${PROJECT_SOURCE_DIR}/${_script}
#    ${PROJECT_BINARY_DIR}/${_script}
#    COPYONLY
#    )
#endforeach()


