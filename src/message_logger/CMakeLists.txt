cmake_minimum_required(VERSION 3.8)
project(message_logger)

find_package(ament_cmake REQUIRED)
add_definitions(-std=c++11 -fPIC -Wall)

# Options
option(MELO_FUNCTION_PRINTS "Enable function print macros" OFF)

# Configure backend config header
configure_file(
  include/message_logger/log/log_messages_backend_config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/message_logger/log/log_messages_backend_config.hpp @ONLY
)

# Add include directories
include_directories(
  include
  ${CMAKE_CURRENT_BINARY_DIR}/include # for the generated config header
)

# Define the library
add_library(${PROJECT_NAME} SHARED
  src/time/Time.cpp
  src/time/TimeStd.cpp
)

# Define compile definitions
# target_compile_definitions(${PROJECT_NAME} PRIVATE -fPIC -Wall)
if(MELO_FUNCTION_PRINTS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE MELO_FUNCTION_PRINTS)
endif()

# Install the include and library
install(
  DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h" PATTERN "*.in" EXCLUDE
)

install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Package
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_package()
