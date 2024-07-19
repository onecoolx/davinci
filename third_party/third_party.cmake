# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include (${CMAKE_CURRENT_LIST_DIR}/zlib.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/png.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/jpeg.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/sqlite.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/mbedtls.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/curl.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/uv.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/xml2.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/xslt.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/freetype2.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/harfbuzz.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/icu.cmake)

if (OPT_UNITTEST)
include (${CMAKE_CURRENT_LIST_DIR}/gtest.cmake)
endif(OPT_UNITTEST)
