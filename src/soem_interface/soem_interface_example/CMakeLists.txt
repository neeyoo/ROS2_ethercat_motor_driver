cmake_minimum_required(VERSION 3.15)
project(soem_interface_example)

# Default C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror)

# Definitions
add_definitions(-DMELO_USE_COUT)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(message_logger REQUIRED)
find_package(soem REQUIRED)
find_package(soem_interface REQUIRED)

set(PACKAGE_DEPENDENCIES
  message_logger
  soem
  soem_interface
)

# Include directories
include_directories(
  include
)

# Library
add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/ExampleSlave.cpp
)
ament_target_dependencies(${PROJECT_NAME} message_logger soem soem_interface)

# Executable
add_executable(${PROJECT_NAME}_1
  src/example_slave.cpp
)
target_link_libraries(${PROJECT_NAME}_1
  ${PROJECT_NAME}
)
ament_target_dependencies(${PROJECT_NAME}_1 message_logger soem soem_interface)

# Install targets
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_1
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

# Export package
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${PACKAGE_DEPENDENCIES})

# Install CMake export targets
install(EXPORT export_${PROJECT_NAME}
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION share/${PROJECT_NAME}/cmake
)

ament_package()
