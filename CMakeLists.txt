cmake_minimum_required(VERSION 2.8)
project(bxi_pci_drv_test)

add_compile_options(-Wall -fdiagnostics-color=auto -fPIC -Wno-unused-function)

include_directories(./src ./lib)

aux_source_directory(./src DIR_SRC)

set(BXI_PCI_CTL_LIB "${CMAKE_SOURCE_DIR}/lib/libbxi_pci_drv.a")

add_executable(${PROJECT_NAME} ${DIR_SRC})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  pthread
  "${BXI_PCI_CTL_LIB}"  # 直接链接库的绝对路径
)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
  OBJECT_DEPENDS "${BXI_PCI_CTL_LIB}"
)
