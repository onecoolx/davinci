set(ICUDT_DIR ${CMAKE_CURRENT_LIST_DIR}/source/data)

set(LIB_ICUDT icudt)

set(OUTTMPDIR ${CMAKE_CURRENT_BINARY_DIR})

set(ICUDT_CHAR ${U_ENDIAN_CHAR})

file(GLOB ICUDT_ARCHIVE_FILES LIST_DIRECTORIES false
    ${ICUDT_DIR}/in/*.dat
)
list(GET ICUDT_ARCHIVE_FILES 0 ICUDT_ARCHIVE)

if(MSVC)
    set(LOCAL_BIN_DIR ${CMAKE_BUILD_TYPE})
endif(MSVC)

set(ICUPKG ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_BIN_DIR}/${TOOL_ICUPKG})

set(ICUDT_SOURCE_ARCHIVE_FILE_NAME ${LIB_ICUDT}${VERSION_INFO}${ICUDT_CHAR}.dat)
set(ICUDT_SOURCE_ARCHIVE ${OUTTMPDIR}/${ICUDT_SOURCE_ARCHIVE_FILE_NAME})
set(icudt_source_archive_STAMP "${OUTTMPDIR}/icudt_source_archive_stamp")

add_custom_command(
    OUTPUT ${ICUDT_SOURCE_ARCHIVE} ${icudt_source_archive_STAMP}
    COMMAND ${ICUPKG} -t${ICUDT_CHAR}
        ${ICUDT_ARCHIVE} ${ICUDT_SOURCE_ARCHIVE}
    COMMAND ${CMAKE_COMMAND} -E touch ${icudt_source_archive_STAMP}
    DEPENDS ${TOOL_ICUPKG} ${ICUDT_ARCHIVE}
    COMMENT
        "Convert ${ICUDT_ARCHIVE} to ${ICUDT_SOURCE_ARCHIVE}"
)

set(PKGDATA_LIST ${OUTTMPDIR}/icudata.lst)
set(pkgdata_list_STAMP "${OUTTMPDIR}/pkgdata_list_stamp")

if(MSVC)
  set(extract_pattern *)
  set(PKGDATA_VERSIONING "")
  set(ICUDT_SOURCES ${OUTTMPDIR}/${LIB_ICUDT}${VERSION_INFO}${ICUDT_CHAR}_dat.obj)
  set(LDFLAGS_ICUDT "-NOENTRY")
else()
  set(extract_pattern \\*)
  set(PKGDATA_VERSIONING "")
  set(ICUDT_SOURCES ${OUTTMPDIR}/${LIB_ICUDT}${VERSION_INFO}${ICUDT_CHAR}_dat.S)
  set(LDFLAGS_ICUDT "-nodefaultlibs -nostdlib")
endif(MSVC)

add_custom_command(
    OUTPUT ${PKGDATA_LIST} ${pkgdata_list_STAMP}
    COMMAND ${CMAKE_COMMAND} -E remove -f ${PKGDATA_LIST}
    COMMAND ${ICUPKG}
        -d ${OUTTMPDIR}  # --destdir
        --list
        -x ${extract_pattern}  # --extract
        ${ICUDT_SOURCE_ARCHIVE}
        -o ${PKGDATA_LIST}  # --outlist
    COMMAND ${CMAKE_COMMAND} -E touch ${pkgdata_list_STAMP}
    DEPENDS ${TOOL_ICUPKG} ${ICUDT_SOURCE_ARCHIVE} ${icudt_source_archive_STAMP}
    COMMENT
        "Unpacking ${ICUDT_SOURCE_ARCHIVE} and generating ${PKGDATA_LIST} (list of data files)"
)

set(PKGDATA ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_BIN_DIR}/${TOOL_PKGDATA})
set(icudt_asm_file_STAMP "${OUTTMPDIR}/icudt_asm_file_stamp")

set(ICUDT_ENTRY_POINT ${LIB_ICUDT}${VERSION_INFO})
set(ICUDT_NAME ${LIB_ICUDT}${VERSION_INFO}${ICUDT_CHAR})
set(asm_PKGDATA_MODE dll)
set(asm_PKGDATA_LIBNAME -L ${LIB_ICUDT})

add_custom_command(
    OUTPUT ${ICUDT_SOURCES} ${icudt_asm_file_STAMP}
    COMMAND ${PKGDATA}
        -e ${ICUDT_ENTRY_POINT}  # --entrypoint
        -T ${OUTTMPDIR}            # --tempdir
        -p ${ICUDT_NAME}         # --name
        -m ${asm_PKGDATA_MODE}     # --mode
        ${PKGDATA_VERSIONING}
        ${asm_PKGDATA_LIBNAME}
        ${PKGDATA_LIST}
    COMMAND ${CMAKE_COMMAND} -E touch ${icudt_asm_file_STAMP}
    DEPENDS ${TOOL_PKGDATA} ${PKGDATA_LIST} ${pkgdata_list_STAMP}
    COMMENT
        "Packing data to the asm file ${ICUDT_SOURCES}"
)

add_custom_target(icudt_asm_target
    DEPENDS ${ICUDT_SOURCES} ${icudt_asm_file_STAMP}
)

add_library(${LIB_ICUDT} "")

set_target_properties(${LIB_ICUDT} PROPERTIES
    LINKER_LANGUAGE C
    OUTPUT_NAME ${LIB_ICUDT}
    VERSION ${VERSION_INFO}.${VERSION_MICRO} SOVERSION 1)

add_dependencies(${LIB_ICUDT} icudt_asm_target)

target_sources(${LIB_ICUDT} PRIVATE ${ICUDT_SOURCES})

set_property(TARGET ${LIB_ICUDT} APPEND_STRING PROPERTY
    LINK_FLAGS ${LDFLAGS_ICUDT}
)

install(TARGETS ${LIB_ICUDT} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
