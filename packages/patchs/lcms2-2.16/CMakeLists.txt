cmake_minimum_required(VERSION 3.16)

project(Little-CMS LANGUAGES C)

file(GLOB LCMS_SRCS "src/*.c" "src/*.def")
add_library(lcms2 STATIC ${LCMS_SRCS})

include_directories(include)

file(GLOB LCMS_HEADERS "include/*.h")

install(TARGETS lcms2 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
install(FILES ${LCMS_HEADERS} DESTINATION include/)

