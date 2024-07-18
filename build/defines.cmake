# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

if (WIN32)
    add_compile_definitions(WIN32)
    add_compile_definitions(_WIN32)
    add_compile_definitions(DLL_EXPORT)
    add_compile_definitions(_UNICODE=1)
    add_compile_definitions(UNICODE=1)
    add_compile_definitions(_HAS_EXCEPTIONS=0)
    add_compile_definitions(_USE_MATH_DEFINES)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
    add_compile_definitions(_CRT_NONSTDC_NO_WARNINGS)
    add_compile_definitions(_SCL_SECURE_NO_WARNINGS)
    add_compile_definitions(_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)
endif()
