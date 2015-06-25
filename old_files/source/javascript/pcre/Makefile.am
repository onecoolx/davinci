# Process this file with automake to produce Makefile.in
NULL=

INCLUDES = -I./ -I../kjs/ -I../../ -I../../wtf -I../../../

noinst_LTLIBRARIES = libjscore_pcre.la

libjscore_pcre_cpp_sources=\
	pcre_compile.c \
	pcre_exec.c \
	pcre_fullinfo.c \
	pcre_get.c \
	pcre_maketables.c \
	pcre_ord2utf8.c \
	pcre_tables.c \
	pcre_ucp_searchfuncs.c \
	pcre_xclass.c \
	../../wtf/UnusedParam.h \
	../../wtf/FastMallocPCRE.cpp \
	$(NULL)


libjscore_pcre_h_private_sources=\
	pcre-config.h \
	pcre.h \
	pcre_internal.h \
	ucp.h \
	ucpinternal.h

chartables.c: 
	$(CC) $(INCLUDES) -o dftables dftables.c
	./dftables $(srcdir)/chartables.c


libjscore_pcre_la_SOURCES = \
	$(libjscore_pcre_cpp_sources)\
	$(libjscore_pcre_h_private_sources)

BUILT_SOURCES = chartables.c
EXTRA_DIST = chartables.c ucptable.c
MAINTAINERCLEANFILES = dftables
