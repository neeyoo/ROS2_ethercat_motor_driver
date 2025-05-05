cmake_minimum_required(VERSION 3.16)
project(elmo_ethercat_sdk)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(ethercat_sdk_master REQUIRED)
find_package(message_logger REQUIRED)
find_package(yaml-cpp REQUIRED)

# Include directories
include_directories(
  include
)

# Source files
set(SOURCES
  src/elmo_ethercat_sdk/Elmo.cpp
  src/elmo_ethercat_sdk/Configuration.cpp
  src/elmo_ethercat_sdk/ConfigurationParser.cpp
  src/elmo_ethercat_sdk/Reading.cpp
  src/elmo_ethercat_sdk/Command.cpp
  src/elmo_ethercat_sdk/Controlword.cpp
  src/elmo_ethercat_sdk/Statusword.cpp
  src/elmo_ethercat_sdk/DriveState.cpp
  src/elmo_ethercat_sdk/PdoTypeEnum.cpp
)

# Library target
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
  yaml-cpp
)

ament_target_dependencies(${PROJECT_NAME}
  ethercat_sdk_master
  message_logger
)

# Install targets
install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

# Export the library and include directories for downstream packages
ament_export_targets(export_${PROJECT_NAME})
ament_export_include_directories(include)
ament_export_dependencies(ethercat_sdk_master message_logger yaml-cpp)

# Finalize package
ament_package()
