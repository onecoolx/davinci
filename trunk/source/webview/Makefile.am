INCLUDES = -I../../include/ \
		   -I../ \
		   -I../wtf \
		   -I../webcore/ \
		   -I../webcore/buildsrc \
		   -I../webcore/plugin/ \
		   -I../webcore/page/ \
		   -I../webcore/editing/ \
		   -I../webcore/dom/ \
		   -I../webcore/css/ \
		   -I../webcore/loader/ \
		   -I../webcore/rendering/ \
		   -I../webcore/platform/ \
		   -I../webcore/bridge/ \
		   -I../webcore/bindings/js \
		   -I../webcore/html/ \
		   -I../webcore/history/ \
		   -I../webcore/platform/graphics/ \
		   -I../webcore/platform/picasso/ \
		   -I../webcore/platform/unicode/ \
		   -I../webcore/platform/network/curl/ \
		   -I../webcore/platform/network/ \
		   -I../javascript/

FLAGS= -DNDEBUG

AM_CFLAGS = $(FLAGS)
AM_CXXFLAGS = $(FLAGS) -fno-exceptions -fno-rtti
noinst_LTLIBRARIES = libwebview.la

libwebview_la_SOURCES= \
					  WebEngine.cpp \
					  WebEngine.h \
					  WebView.cpp \
					  WebView.h \
					  WebCallback.cpp \
					  WebCallback.h \
					  WebEncoding.cpp \
					  WebEncoding.h \
					  WebGlobal.h \
					  SchemeExtension.cpp \
					  SchemeExtension.h \
					  ScanCodeMap.h \
					  WidgetView.h \
					  \
					  CertificateMC.h \
					  CertificateMC.cpp \
					  ContextMenuMC.cpp \
					  EventHandleMC.cpp \
					  DragControllerMC.cpp \
					  PasteboardMC.cpp \
					  MouseEventMC.cpp \
					  WheelEventMC.cpp \
					  KeyEventMC.cpp \
					  SearchPopupMenuMC.cpp \
					  ScreenMC.cpp \
					  CursorMC.cpp \
					  FrameExtraMC.cpp \
					  ClipboardMC.cpp \
					  WidgetMC.cpp \
					  ScrollViewMC.cpp \
 					  PopupMenuMC.cpp \
					  FileChooserMC.cpp \
					  GlobalFunctions.cpp \
					  ChromeClientMC.cpp \
					  ChromeClientMC.h \
					  ContextMenuClientMC.cpp \
					  ContextMenuClientMC.h \
					  EditorClientMC.cpp \
					  EditorClientMC.h \
					  DragClientMC.cpp \
					  CookieJarMC.cpp \
					  DragClientMC.h \
					  InspectorClientMC.cpp \
					  InspectorClientMC.h \
					  FrameLoaderClientMC.cpp \
					  FrameLoaderClientMC.h 
