cmake_minimum_required(VERSION 3.5)
project(soem C)

# Find ament
find_package(ament_cmake REQUIRED)

# OS detection
if(WIN32)
  set(OS "win32")
  include_directories(oshw/win32/wpcap/Include)

  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    link_directories(${CMAKE_CURRENT_LIST_DIR}/oshw/win32/wpcap/Lib/x64)
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    link_directories(${CMAKE_CURRENT_LIST_DIR}/oshw/win32/wpcap/Lib)
  endif()

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D _CRT_SECURE_NO_WARNINGS /WX")
  set(OS_LIBS wpcap.lib Packet.lib Ws2_32.lib Winmm.lib)
elseif(UNIX AND NOT APPLE)
  set(OS "linux")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
  set(OS_LIBS pthread rt)
elseif(APPLE)
  set(OS "macosx")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
  set(OS_LIBS pthread pcap)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "rt-kernel")
  set(OS "rtk")
  include_directories(oshw/${OS}/${ARCH})
  file(GLOB OSHW_EXTRA_SOURCES oshw/${OS}/${ARCH}/*.c)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-function -Wno-format")
  set(OS_LIBS "-Wl,--start-group -l${BSP} -l${ARCH} -lkern -ldev -lsio -lblock -lfs -lusb -llwip -leth -li2c -lrtc -lcan -lnand -lspi -lnor -lpwm -ladc -ltrace -lc -lm -Wl,--end-group")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "rtems")
  set(OS "rtems")
endif()

message(STATUS "Target OS: ${OS}")

# Sources
file(GLOB soem_SOURCES soem/soem/*.c)
file(GLOB OSAL_SOURCES soem/osal/${OS}/*.c)
file(GLOB OSHW_SOURCES soem/oshw/${OS}/*.c)

file(GLOB soem_HEADERS soem/soem/*.h)
file(GLOB OSAL_HEADERS soem/osal/osal.h soem/osal/${OS}/*.h)
file(GLOB OSHW_HEADERS soem/oshw/${OS}/*.h)

# Library
add_library(soem STATIC
  ${soem_SOURCES}
  ${OSAL_SOURCES}
  ${OSHW_SOURCES}
  ${OSHW_EXTRA_SOURCES}
)

target_link_libraries(soem ${OS_LIBS})
set_target_properties(soem PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(soem PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/soem/soem>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/soem/osal>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/soem/osal/${OS}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/soem/oshw/${OS}>
  $<INSTALL_INTERFACE:include/soem/soem>
  $<INSTALL_INTERFACE:include/soem/osal>
  $<INSTALL_INTERFACE:include/soem/osal/${OS}>
  $<INSTALL_INTERFACE:include/soem/oshw/${OS}>
)

# Install targets
install(TARGETS soem
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install headers
install(
  FILES
  ${soem_HEADERS}
  ${OSAL_HEADERS}
  ${OSHW_HEADERS}
  DESTINATION include/soem
)

# Special ethercattype.h install
install(
  FILES
  ./soem/soem/ethercattype.h
  DESTINATION include
)

# Export CMake config
install(EXPORT export_${PROJECT_NAME}
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION share/${PROJECT_NAME}/cmake
)

# Export package
ament_export_include_directories(include)
ament_export_libraries(soem)

ament_package()

# Optional: Tests
option(BUILD_TESTS "Build SOEM tests" ON)

if(BUILD_TESTS)
  add_subdirectory(soem/test/linux/slaveinfo)
  add_subdirectory(soem/test/linux/eepromtool)
  add_subdirectory(soem/test/linux/simple_test)
endif()
