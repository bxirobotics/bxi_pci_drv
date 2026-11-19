cmake_minimum_required(VERSION 3.16)
project(bxi_pci_drv_test LANGUAGES C)

find_package(Threads REQUIRED)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" BXI_PROCESSOR)
if(BXI_PROCESSOR MATCHES "^(x86_64|amd64)$")
  set(BXI_PCI_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/libbxi_pci_drv.a")
elseif(BXI_PROCESSOR MATCHES "^(aarch64|arm64)$")
  set(BXI_PCI_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/lib/libbxi_pci_drv_arm.a")
else()
  message(FATAL_ERROR "Unsupported PCI architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

add_library(bxi_pci_drv STATIC IMPORTED)
set_target_properties(bxi_pci_drv PROPERTIES
  IMPORTED_LOCATION "${BXI_PCI_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/lib")
foreach(TOOL drv_test motor_test)
  add_executable(${TOOL} src/${TOOL}.c)
  target_compile_options(${TOOL} PRIVATE -Wall -fPIC -Wno-unused-function)
  target_link_libraries(${TOOL} PRIVATE bxi_pci_drv Threads::Threads)
  install(TARGETS ${TOOL} DESTINATION lib/bxi_pci_drv)
endforeach()
