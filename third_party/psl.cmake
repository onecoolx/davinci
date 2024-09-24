# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(PSL_NAME "libpsl")
set(PSL_VERSION "0.21.5")
set(PSL_PACKAGE "${PROJECT_ROOT}/packages/${PSL_NAME}-${PSL_VERSION}.tar.gz")
set(PSL_HASH "d6717685a5f221403041907cca98ae9f72aef163b9d813d40d417c2663373a32")

ExternalProject_Add(
  ${PSL_NAME}
  PREFIX "${PROJECT_OUT}/${PSL_NAME}"
  URL "${PSL_PACKAGE}"
  URL_HASH SHA256=${PSL_HASH}
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${PSL_NAME}-${PSL_VERSION}/CMakeLists.txt" "${PROJECT_OUT}/${PSL_NAME}/src/${PSL_NAME}/"
  && ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${PSL_NAME}-${PSL_VERSION}/public_suffix_list.dat" "${PROJECT_OUT}/${PSL_NAME}/src/${PSL_NAME}/list/"
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)

add_dependencies(
    ${PSL_NAME}
    ${ICU_NAME}
)

