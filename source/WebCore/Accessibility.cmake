set(WEBCORE_IMP_DIR ${WORKSPACE_DIR}/source/WebCore)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_IMP_DIR}/platform/accessibility"
)

list(APPEND WebCore_SOURCES
    ${WEBCORE_IMP_DIR}/accessibility/AXObjectCache.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMenuList.cpp

)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS

)

list(APPEND WebCore_LIBRARIES
)
