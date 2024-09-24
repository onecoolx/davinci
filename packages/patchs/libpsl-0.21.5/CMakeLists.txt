cmake_minimum_required(VERSION 3.16)

project(libpsl LANGUAGES C)

set(LIBPSL_VERSION 0.21.5)
set(LIBPSL_VERSION_MAJOR 0)
set(LIBPSL_VERSION_MINOR 21)
set(LIBPSL_VERSION_PATCH 5)
set(LIBPSL_VERSION_NUMBER 0x001505)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(PSL_SRCS 
    ${SRC_DIR}/src/lookup_string_in_fixed_set.c 
    ${SRC_DIR}/src/psl.c
)

set(PSL_FILE ${SRC_DIR}/list/public_suffix_list.dat)

set(SUFFIXES_HEADER ${OUT_DIR}/include/suffixes_dafsa.h)
add_custom_command(
    OUTPUT ${SUFFIXES_HEADER}
    COMMAND python ${SRC_DIR}/src/psl-make-dafsa --output-format=cxx+ "${PSL_FILE}" ${SUFFIXES_HEADER}
    DEPENDS ${PSL_FILE}
)

add_library(psl STATIC ${PSL_SRCS} ${SUFFIXES_HEADER})

include_directories(${OUT_DIR}/include)

target_compile_definitions(psl PRIVATE PACKAGE_VERSION="${LIBPSL_VERSION}")
target_compile_definitions(psl PRIVATE ENABLE_BUILTIN)
target_compile_definitions(psl PRIVATE WITH_LIBICU)

set(PSL_HEADERS include/libpsl.h)

configure_file(
    ${PSL_HEADERS}.in
    ${PSL_HEADERS}
)

install(TARGETS psl LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PSL_HEADERS} DESTINATION include/)

