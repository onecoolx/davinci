set(WEBCORE_IMP_DIR ${WORKSPACE_DIR}/source/WebCore)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_IMP_DIR}/page"
    "${WEBCORE_IMP_DIR}/editing"
)

list(APPEND WebCore_SOURCES
    ${WEBCORE_IMP_DIR}/page/DragController.cpp
    ${WEBCORE_IMP_DIR}/editing/Editor.cpp
)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
)

