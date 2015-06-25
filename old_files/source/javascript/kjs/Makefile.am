# Process this file with automake to produce Makefile.in

INCLUDES = -I./ \
		   -I../ \
		   -I../pcre \
		   -I../bindings \
		   -I../bindings/c \
		   -I../../ \
		   -I../../../ \
		   -I../../../include \
		   -I../../webcore/platform \
		   -I../../webcore/platform/unicode

NULL=

noinst_LTLIBRARIES = libjscore_kjs.la

libjscore_kjs_cpp_sources=\
	array_object.cpp \
	function_object.cpp \
	nodes2string.cpp \
	bool_object.cpp \
	identifier.cpp \
	nodes.cpp \
	collector.cpp \
	internal.cpp \
	number_object.cpp \
	regexp.cpp \
	date_object.cpp \
	interpreter.cpp \
	object.cpp \
	regexp_object.cpp \
	debugger.cpp \
	object_object.cpp \
	scope_chain.cpp \
	dtoa.cpp \
	lexer.cpp \
	Parser.cpp \
	JSImmediate.cpp \
	operations.cpp \
	string_object.cpp \
	error_object.cpp \
	list.cpp \
	property_map.cpp \
	fpconst.cpp \
	lookup.cpp \
	property_slot.cpp \
	ustring.cpp \
	function.cpp \
	math_object.cpp \
	value.cpp \
	JSLock.cpp \
	Context.cpp \
	DateMath.cpp \
	ExecState.cpp \
	JSWrapperObject.cpp \
	CommonIdentifiers.cpp \
	PropertyNameArray.cpp \
	../../wtf/Assertions.cpp \
	../../wtf/FastMalloc.cpp \
	../../wtf/HashTable.cpp \
	../../wtf/TCSystemAlloc.cpp\
	$(NULL)

libjscore_kjs_h_private_sources=\
	array_instance.h \
	array_object.h \
	bool_object.h \
	collector.h \
	completion.h \
	config.h \
	context.h \
	DateMath.h \
	date_object.h \
	debugger.h \
	dtoa.h \
	error_object.h \
	ExecState.h \
	function.h \
	function_object.h \
	identifier.h \
	internal.h \
	interpreter.h \
	JSImmediate.h \
	JSLock.h \
	JSType.h \
	JSWrapperObject.h \
	CommonIdentifiers.h \
	lexer.h \
	list.h \
	lookup.h \
	math_object.h \
	nodes.h \
	number_object.h \
	object.h \
	object_object.h \
	operations.h \
	Parser.h \
	property_map.h \
	PropertyNameArray.h \
	property_slot.h \
	protect.h \
	regexp.h \
	regexp_object.h \
	SavedBuiltins.h \
	scope_chain.h \
	string_object.h \
	types.h \
	ustring.h \
	value.h \
	../../wtf/ASCIICType.h \
	../../wtf/Platform.h \
	../../wtf/FastMalloc.h \
	../../wtf/Assertions.h \
	../../wtf/RefPtr.h \
	../../wtf/PassRefPtr.h \
	../../wtf/HashCountedSet.h \
	../../wtf/ListHashSet.h \
	../../wtf/OwnArrayPtr.h \
	../../wtf/AlwaysInline.h \
	../../wtf/Noncopyable.h \
	../../wtf/OwnPtr.h \
	../../wtf/GetPtr.h \
	../../wtf/Vector.h \
	../../wtf/HashMap.h \
	../../wtf/HashIterators.h \
	../../wtf/VectorTraits.h \
	../../wtf/HashSet.h \
	../../wtf/HashTable.h \
	../../wtf/HashTraits.h \
	../../wtf/HashFunctions.h \
	../../wtf/Forward.h \
	../../wtf/ListRefPtr.h \
	../../wtf/MathExtras.h \
	../../wtf/StringExtras.h \
	../../wtf/TCPageMap.h \
	../../wtf/TCSpinLock.h \
	../../wtf/TCSystemAlloc.h \
	../../wtf/unicode/Unicode.h \
	$(NULL)

libjscore_kjs_h_public_sources=\
	../../wtf/unicode/platform/UnicodePlat.h \
	$(NULL)

libjscore_API_cpp_sources=\
	../API/JSBase.cpp \
	../API/JSCallbackConstructor.cpp \
	../API/JSCallbackFunction.cpp \
	../API/JSCallbackObject.cpp \
	../API/JSClassRef.cpp \
	../API/JSContextRef.cpp \
	../API/JSObjectRef.cpp \
	../API/JSStringRef.cpp \
	../API/JSValueRef.cpp \
	$(NULL)

libjscore_API_h_sources=\
	../API/APICast.h \
	../API/JavaScriptCore.h \
	../API/JSCallbackConstructor.h \
	../API/JSCallbackFunction.h \
	../API/JSCallbackObject.h \
	../API/JSClassRef.h \
	$(NULL)

libjscore_bindings_cpp_sources=\
	../bindings/NP_jsobject.cpp \
	../bindings/npruntime.cpp \
	../bindings/npruntime_plugin.cpp \
	../bindings/runtime_array.cpp \
	../bindings/runtime.cpp \
	../bindings/runtime_method.cpp \
	../bindings/runtime_object.cpp \
	../bindings/runtime_root.cpp \
	../bindings/c/c_class.cpp \
	../bindings/c/c_instance.cpp \
	../bindings/c/c_runtime.cpp \
	../bindings/c/c_utility.cpp \
	$(NULL)


libjscore_bindings_h_sources=\
	../bindings/NP_jsobject.h \
	../bindings/npruntime_impl.h \
	../bindings/npruntime_priv.h \
	../bindings/runtime_array.h \
	../bindings/runtime.h \
	../bindings/runtime_method.h \
	../bindings/runtime_object.h \
	../bindings/runtime_root.h \
	../bindings/c/c_class.h \
	../bindings/c/c_instance.h \
	../bindings/c/c_runtime.h \
	../bindings/c/c_utility.h \
	$(NULL)
#global.h 
AM_CFLAGS = -DNDEBUG
AM_CXXFLAGS = -DNDEBUG -fno-exceptions -fno-rtti

LUT_FILES = math_object.lut.h lexer.lut.h array_object.lut.h date_object.lut.h string_object.lut.h number_object.lut.h regexp_object.lut.h
GRAMMAR_FILES = grammar.hpp grammar.cpp

YFLAGS = -d --file-prefix=grammar --name-prefix=kjsyy --output-file=grammar.cpp

$(GRAMMAR_FILES): 
	$(YACC) $(YFLAGS) grammar.y

CREATE_HASH_TABLE = $(srcdir)/create_hash_table

lexer.lut.h:  
	$(PERL) $(CREATE_HASH_TABLE) keywords.table -i > $@

%.lut.h: 
	$(PERL) $(CREATE_HASH_TABLE) `echo $@ | sed -e s/.lut.h/.cpp/` -i > $@

BUILT_SOURCES = $(GRAMMAR_FILES) $(LUT_FILES) 

libjscore_kjs_la_SOURCES = \
	$(libjscore_kjs_cpp_sources)\
	$(libjscore_kjs_h_private_sources)\
	$(libjscore_kjs_h_public_sources)\
	$(libjscore_bindings_cpp_sources)\
	$(libjscore_bindings_h_sources)\
	$(libjscore_API_cpp_sources)\
	$(libjscore_API_h_sources)\
	$(LUT_FILES)\
	$(GRAMMAR_FILES)\
	$(NULL)

EXTRA_DIST = grammar.y

