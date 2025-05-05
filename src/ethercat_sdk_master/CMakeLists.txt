cmake_minimum_required(VERSION 3.16)
project(ethercat_sdk_master)

# Use ccache if available
find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
  message(STATUS "Using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(soem_interface REQUIRED)
find_package(message_logger REQUIRED)

# ##########
# # Build ##
# ##########
include_directories(
  include
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/EthercatMaster.cpp
  src/${PROJECT_NAME}/EthercatDevice.cpp
)

target_link_libraries(${PROJECT_NAME}
  yaml-cpp
  Threads::Threads
)

ament_target_dependencies(${PROJECT_NAME} soem_interface message_logger)

# ############
# # Install ##
# ############
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_dependencies(Threads soem_interface)
ament_export_libraries(${PROJECT_NAME})

ament_package()
