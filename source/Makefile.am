
SUBDIRS = javascript webcore webview

lib_LTLIBRARIES = libmacross.la

libmacross_la_SOURCES = template.cpp template.h

libmacross_la_LIBADD = \
	javascript/libjscore.la \
	webcore/libwebcore.la \
	webview/libwebview.la 

libmacross_la_LDFLAGS= -no-undefined -release $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_MICRO)
