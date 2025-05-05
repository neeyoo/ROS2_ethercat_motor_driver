cmake_minimum_required(VERSION 3.16)
project(maxon_epos_ethercat_sdk)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(message_logger REQUIRED)
find_package(soem_interface REQUIRED)
find_package(ethercat_sdk_master REQUIRED)

# Include directories
include_directories(include)

# Source files
file(GLOB CPPSources src/${PROJECT_NAME}/*.cpp)

add_library(${PROJECT_NAME} SHARED
  ${CPPSources}
)
target_link_libraries(${PROJECT_NAME}
  yaml-cpp
)

ament_target_dependencies(${PROJECT_NAME} soem_interface message_logger ethercat_sdk_master)

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
ament_export_libraries(${PROJECT_NAME})

ament_package()
