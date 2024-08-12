# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(ICU_NAME "icu4c")
set(ICU_VERSION "75_1-src")
set(ICU_PACKAGE "${PROJECT_ROOT}/packages/${ICU_NAME}-${ICU_VERSION}.zip")
set(ICU_HASH "930f37db1a423c3db9482fdc7932247e9a7ffd6330895bff41977fe2af8f8a1a")

ExternalProject_Add(
  ${ICU_NAME}
  PREFIX "${PROJECT_OUT}/${ICU_NAME}"
  URL "${ICU_PACKAGE}"
  URL_HASH SHA256=${ICU_HASH}
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_ROOT}/packages/patchs/icu/" "${PROJECT_OUT}/${ICU_NAME}/src/${ICU_NAME}/"
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)

