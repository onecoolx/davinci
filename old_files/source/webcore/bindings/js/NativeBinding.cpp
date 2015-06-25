
#include "config.h"
#include "Vector.h"
#include "NativeBinding.h"

#if ENABLE(JSNATIVEBINDING)

using namespace WTF;

namespace WebCore{

enum NativeType {
    NT_Class,
    NT_Function
};

struct ExtendedJSObjectEntry{
    NativeType     m_type;
    void *         m_native;
    JSClassRef     m_classRef;
    JSContextRef   m_context;
    JSObjectRef    m_globalObject;
    JSStringRef    m_propertyName;
    JSObjectRef    m_propertyValue;
};

typedef Vector<ExtendedJSObjectEntry*> JSClassRegisterTable;

static JSClassRegisterTable * jsClassTable()
{
    static JSClassRegisterTable *jsTable = new JSClassRegisterTable;
    return jsTable;
}

static int lookupExtendedJSObjectEntry(const char *name, ExtendedJSObjectEntry **entry)
{
    size_t size = jsClassTable()->size();
    for (size_t i=0; i<size; i++) {
        ExtendedJSObjectEntry *objectEntry = jsClassTable()->at(i);
        const char* objName = NULL;

        switch (objectEntry->m_type) {
            case NT_Class:
                objName = ((JSClassDefinition*)objectEntry->m_native)->className;
                break;
            case NT_Function:
                objName = ((JSNativeFunction *)objectEntry->m_native)->name;
                break;
        }

        if (objName) {
            if (! strcmp(name, objName)) {
                *entry = objectEntry;
                return i;
            }
        }
    }
    return -1;
}

static bool undefineExtendedJSObjectEntry(const char *name)
{
    ExtendedJSObjectEntry *entry = NULL;
    if (!name)
        return false;

    int i = lookupExtendedJSObjectEntry(name, &entry);
    if (entry) {
        JSStringRef propertyName = entry->m_propertyName;
        JSObjectRef globalObject = entry->m_globalObject;
        JSContextRef m_context = entry->m_context;

        if (JSObjectHasProperty(m_context, globalObject, propertyName))
            JSObjectDeleteProperty(m_context, globalObject, propertyName, 0);

        JSStringRelease(propertyName);
        jsClassTable()->remove(i);
        delete entry;
        return true;
    }
    return false;
}

bool DefineJSNativeClass(JSNativeClass *nativeClass)
{
    ExtendedJSObjectEntry *entry = NULL;
    if (! nativeClass || lookupExtendedJSObjectEntry(nativeClass->name, &entry) >= 0)
        return false;

    entry = new ExtendedJSObjectEntry();
    if (! entry)
        return false;

    JSClassDefinition *classDef = new JSClassDefinition; 
    if (! classDef) {
        delete entry;
        return false;
    }

    memset(classDef, 0x0, sizeof(*classDef));
    classDef->className = nativeClass->name;
    classDef->staticFunctions = static_cast<JSStaticFunction*>(nativeClass->method);
    classDef->staticValues = nativeClass->property;
    classDef->callAsConstructor = nativeClass->ctor;
    classDef->finalize = nativeClass->dtor;
    entry->m_type = NT_Class;
    entry->m_native = classDef;
    jsClassTable()->append(entry);
    return true;
}

bool UndefineJSNativeClass(JSNativeClass *nativeClass)
{
   if (! nativeClass)
       return false; 
   return undefineExtendedJSObjectEntry(nativeClass->name); 
}

const JSClassRef LookupJSNativeClass(const char * className)
{
    ExtendedJSObjectEntry *entry = NULL;
    lookupExtendedJSObjectEntry(className, &entry);
    if (entry)
        return entry->m_classRef;
    return NULL;
}

bool DefineJSNativeFunction(JSNativeFunction *nativeFunc)
{
    if (! (nativeFunc && nativeFunc->name))
        return false;

    ExtendedJSObjectEntry *entry = NULL;
    if (lookupExtendedJSObjectEntry(nativeFunc->name, &entry) >= 0) 
        return false;

    if (! (entry = new ExtendedJSObjectEntry()))
        return false;

    JSNativeFunction *funcDef = (JSNativeFunction*)fastMalloc(sizeof(JSNativeFunction));
    if (! funcDef) {
        delete entry;
        return false;
    }

    memcpy(funcDef, nativeFunc, sizeof(*funcDef));
    entry->m_type = NT_Function;
    entry->m_classRef = 0;
    entry->m_native = funcDef;
    jsClassTable()->append(entry);
    return true;
}

bool UndefineJSNativeFunction(JSNativeFunction *nativeFunc)
{
   if (! nativeFunc)
       return false;
    return undefineExtendedJSObjectEntry(nativeFunc->name); 
}

int initNativeJSObjects(RefPtr<ScriptInterpreter> script)
{
    JSContextRef context = reinterpret_cast<JSContextRef>(script->globalExec());
    JSObjectRef globalObject = JSContextGetGlobalObject(context);

    size_t size = jsClassTable()->size();
    for (size_t i=0; i<size; i++) {
        ExtendedJSObjectEntry * entry =  jsClassTable()->at(i);
        switch (entry->m_type) {
            case NT_Class:
            {
                JSClassDefinition *classDef = (JSClassDefinition*)entry->m_native;
                if (!entry->m_classRef)
                    entry->m_classRef = JSClassCreate(classDef);
                if (!entry->m_propertyName)
                    entry->m_propertyName = JSStringCreateWithUTF8CString(classDef->className);
                entry->m_propertyValue = JSObjectMakeConstructor(context,
                                            entry->m_classRef, classDef->callAsConstructor);
                break;
            }
            case NT_Function:
            {
                JSNativeFunction *functionDef = (JSNativeFunction*)entry->m_native;
                if (!entry->m_propertyName)
                    entry->m_propertyName = JSStringCreateWithUTF8CString(functionDef->name);
                entry->m_propertyValue = JSObjectMakeFunctionWithCallback(context,
                                            entry->m_propertyName, functionDef->callAsFunction);
                break;
            }
        }

        if (entry->m_propertyValue) {
            entry->m_globalObject = globalObject;
            entry->m_context = context;
            JSObjectSetProperty(
                    context,
                    globalObject,
                    entry->m_propertyName,
                    entry->m_propertyValue,
                    kJSPropertyAttributeDontEnum | kJSPropertyAttributeDontDelete, NULL);
        }
    }
    return 0;
}

} /* namespace WebCore */

#endif /* ENABLE(JSNATIVEBINDING) */
