
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Halp2)


set(CMAKE_PREFIX_PATH /home/renat/Documents/geant4.10.4-build)

option(WITH_GEANT4_UIVIS "Build project with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(Halp2 main.cc ${sources} ${headers} include/PrimaryGenMessenger.hh src/PrimaryGenMessenger.cc)
target_link_libraries(Halp2 ${Geant4_LIBRARIES})



set(EXAMPLEB1_SCRIPTS
  init_vis.mac
  vis.mac
        run.mac
        )

foreach(_script ${EXAMPLEB1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


install(TARGETS Halp2 DESTINATION bin)


