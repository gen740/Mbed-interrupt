# Install script for directory: /Users/fujimotogen/home/Mbed/Interrupt/mbed-os/storage/kvstore

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "develop")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/local/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/tdbstore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/filesystemstore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/securestore/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/kv_config/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/direct_access_devicekey/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/fujimotogen/home/Mbed/Interrupt/cmake_build/NUCLEO_F401RE/develop/GCC_ARM/mbed-os/storage/kvstore/kvstore_global_api/cmake_install.cmake")
endif()
