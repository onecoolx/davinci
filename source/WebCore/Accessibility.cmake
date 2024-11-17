set(WEBCORE_IMP_DIR ${WORKSPACE_DIR}/source/WebCore)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_IMP_DIR}/platform/accessibility"
)

list(APPEND WebCore_SOURCES
    ${WEBCORE_IMP_DIR}/accessibility/AXCoreObject.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AXObjectCache.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMenuList.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityObject.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityRenderObject.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityNodeObject.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMockObject.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityImageMapLink.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityList.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySVGRoot.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySVGElement.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityScrollView.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityScrollbar.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySlider.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySpinButton.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTable.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableCell.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableColumn.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableHeaderContainer.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableRow.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTree.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTreeItem.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibleSetValueEvent.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityARIATable.cpp
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMathMLElement.cpp
    ${WEBCORE_IMP_DIR}/accessibility/playstation/AXObjectCachePlayStation.cpp

)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
    ${WEBCORE_IMP_DIR}/accessibility/AXCoreObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AXGeometryManager.h
    ${WEBCORE_IMP_DIR}/accessibility/AXImage.h
    ${WEBCORE_IMP_DIR}/accessibility/AXLogger.h
    ${WEBCORE_IMP_DIR}/accessibility/AXObjectCache.h
    ${WEBCORE_IMP_DIR}/accessibility/AXRemoteFrame.h
    ${WEBCORE_IMP_DIR}/accessibility/AXSearchManager.h
    ${WEBCORE_IMP_DIR}/accessibility/AXTextMarker.h
    ${WEBCORE_IMP_DIR}/accessibility/AXTextRun.h
    ${WEBCORE_IMP_DIR}/accessibility/AXTextStateChangeIntent.h
    ${WEBCORE_IMP_DIR}/accessibility/AXTreeStore.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityARIAGridCell.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityARIAGridRow.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityARIATable.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityAttachment.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityImageMapLink.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityLabel.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityList.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityListBox.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityListBoxOption.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMathMLElement.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMediaObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMenuList.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMenuListOption.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMenuListPopup.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityMockObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityNodeObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityProgressIndicator.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityRenderObject.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySVGElement.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySVGRoot.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityScrollView.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityScrollbar.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySlider.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilitySpinButton.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTable.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableCell.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableColumn.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableHeaderContainer.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTableRow.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTree.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibilityTreeItem.h
    ${WEBCORE_IMP_DIR}/accessibility/AccessibleSetValueEvent.h
    ${WEBCORE_IMP_DIR}/accessibility/ForcedAccessibilityValue.h
)

list(APPEND WebCore_LIBRARIES
)
