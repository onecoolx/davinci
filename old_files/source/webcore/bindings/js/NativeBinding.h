
#ifndef NativeBinding_h
#define NativeBinding_h

#include "kjs_binding.h"

#if ENABLE(JSNATIVEBINDING)

#include "JSBase.h"
#include "JSContextRef.h"
#include "JSStringRef.h"
#include "JSObjectRef.h"
#include "JSValueRef.h"
#include "JSBinding.h"


namespace WebCore {

using namespace KJS;

bool DefineJSNativeClass(JSNativeClass *nativeClass);
const JSClassRef LookupJSNativeClass(const char * name);
bool UndefineJSNativeClass(JSNativeClass *nativeClass);

bool DefineJSNativeFunction(JSNativeFunction *nativeFunc);
bool UndefineJSNativeFunction(JSNativeFunction *nativeFunc);

int initNativeJSObjects(RefPtr<ScriptInterpreter> script);

} /* namespace WebCore */

#endif /* ENABLE(JSNATIVEBINDING) */
#endif /* NativeBinding_h */

