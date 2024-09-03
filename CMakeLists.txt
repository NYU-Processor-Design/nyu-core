cmake_minimum_required(VERSION 3.27)

include(cmake/BootstrapVcpkg.cmake)

project(nyu-core VERSION 1.0.0)

find_package(nyu-cmake CONFIG REQUIRED)

add_library(core INTERFACE)

add_subdirectory(rtl)

if(NYU_BUILD_TESTS)
  enable_testing()
  add_subdirectory(dv)
endif()

# include(CMakePackageConfigHelpers)
# include(GNUInstallDirs)
#
# nyu_install_sv(
#   EXPORT projectTargets
#   TARGETS
#   NAMESPACE nyu::
#   EXPORT_DEST ${CMAKE_INSTALL_DATADIR}/project
#   SV_DEST ${CMAKE_INSTALL_DATADIR}/project/rtl
# )
#
# write_basic_package_version_file(
#   ${CMAKE_CURRENT_BINARY_DIR}/project-config-version.cmake
#   COMPATIBILITY ExactVersion
#   ARCH_INDEPENDENT
# )
#
# install(FILES
#   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/project-config.cmake
#   ${CMAKE_CURRENT_BINARY_DIR}/project-config-version.cmake
#   DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/project
# )
