#ifndef _NP_RUNTIME_H_
#define _NP_RUNTIME_H_

#include "mconfig.h"

#ifdef ENABLE_PLUGIN

#include "npapi.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
#else
#include "nptypes.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
    Objects (non-primitive data) passed between 'C' and script is
    always wrapped in an NPObject.  The 'interface' of an NPObject is
    described by an NPClass.
*/
typedef struct NPObject NPObject;
typedef struct NPClass NPClass;

typedef char NPUTF8;
typedef struct _NPString {
    const NPUTF8 *UTF8Characters;
    uint32_t UTF8Length;
} NPString;
  
typedef enum {
    NPVariantType_Void,
    NPVariantType_Null,
    NPVariantType_Bool,
    NPVariantType_Int32,
    NPVariantType_Double,
    NPVariantType_String,
    NPVariantType_Object
} NPVariantType;

typedef struct _NPVariant {
    NPVariantType type;
    union {
        bool boolValue;
        int32_t intValue;
        double doubleValue;
        NPString stringValue;
        NPObject *objectValue;
    } value;
} NPVariant;


void NPN_ReleaseVariantValue (NPVariant *variant);

#define NPVARIANT_IS_VOID(_v)    ((_v).type == NPVariantType_Void)
#define NPVARIANT_IS_NULL(_v)    ((_v).type == NPVariantType_Null)
#define NPVARIANT_IS_BOOLEAN(_v) ((_v).type == NPVariantType_Bool)
#define NPVARIANT_IS_INT32(_v)   ((_v).type == NPVariantType_Int32)
#define NPVARIANT_IS_DOUBLE(_v)  ((_v).type == NPVariantType_Double)
#define NPVARIANT_IS_STRING(_v)  ((_v).type == NPVariantType_String)
#define NPVARIANT_IS_OBJECT(_v)  ((_v).type == NPVariantType_Object)

#define NPVARIANT_TO_BOOLEAN(_v) ((_v).value.boolValue)
#define NPVARIANT_TO_INT32(_v)   ((_v).value.intValue)
#define NPVARIANT_TO_DOUBLE(_v)  ((_v).value.doubleValue)
#define NPVARIANT_TO_STRING(_v)  ((_v).value.stringValue)
#define NPVARIANT_TO_OBJECT(_v)  ((_v).value.objectValue)

#define NP_BEGIN_MACRO  do {
#define NP_END_MACRO    } while (0)

#define VOID_TO_NPVARIANT(_v)                NP_BEGIN_MACRO (_v).type = NPVariantType_Void; (_v).value.objectValue = NULL; NP_END_MACRO
#define NULL_TO_NPVARIANT(_v)                NP_BEGIN_MACRO (_v).type = NPVariantType_Null; (_v).value.objectValue = NULL; NP_END_MACRO
#define BOOLEAN_TO_NPVARIANT(_val, _v)       NP_BEGIN_MACRO (_v).type = NPVariantType_Bool; (_v).value.boolValue = !!(_val); NP_END_MACRO
#define INT32_TO_NPVARIANT(_val, _v)         NP_BEGIN_MACRO (_v).type = NPVariantType_Int32; (_v).value.intValue = _val; NP_END_MACRO
#define DOUBLE_TO_NPVARIANT(_val, _v)        NP_BEGIN_MACRO (_v).type = NPVariantType_Double; (_v).value.doubleValue = _val; NP_END_MACRO
#define STRINGZ_TO_NPVARIANT(_val, _v)       NP_BEGIN_MACRO (_v).type = NPVariantType_String; NPString str = { _val, strlen(_val) }; (_v).value.stringValue = str; NP_END_MACRO
#define STRINGN_TO_NPVARIANT(_val, _len, _v) NP_BEGIN_MACRO (_v).type = NPVariantType_String; NPString str = { _val, _len }; (_v).value.stringValue = str; NP_END_MACRO
#define OBJECT_TO_NPVARIANT(_val, _v)        NP_BEGIN_MACRO (_v).type = NPVariantType_Object; (_v).value.objectValue = _val; NP_END_MACRO

/*
        Type mappings (JavaScript types have been used for illustration
    purposes):

        JavaScript       to             C (NPVariant with type:)
        undefined                       NPVariantType_Void
        null                            NPVariantType_Null
        Boolean                         NPVariantType_Bool
        Number                          NPVariantType_Double or NPVariantType_Int32
        String                          NPVariantType_String
        Object                          NPVariantType_Object

        C (NPVariant with type:)   to   JavaScript
        NPVariantType_Void              undefined
        NPVariantType_Null              null
        NPVariantType_Bool              Boolean 
        NPVariantType_Int32             Number
        NPVariantType_Double            Number
        NPVariantType_String            String
        NPVariantType_Object            Object
*/

typedef void *NPIdentifier;

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name);
void NPN_GetStringIdentifiers(const NPUTF8 **names, int32_t nameCount, NPIdentifier *identifiers);
NPIdentifier NPN_GetIntIdentifier(int32_t intid);
bool NPN_IdentifierIsString(NPIdentifier identifier);

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier);
int32_t NPN_IntFromIdentifier(NPIdentifier identifier);

/*
    NPObject behavior is implemented using the following set of
    callback functions.

    The NPVariant *result argument of these functions (where
    applicable) should be released using NPN_ReleaseVariantValue().
*/
typedef NPObject *(*NPAllocateFunctionPtr)(NPP npp, NPClass *aClass);
typedef void (*NPDeallocateFunctionPtr)(NPObject *obj);
typedef void (*NPInvalidateFunctionPtr)(NPObject *obj);
typedef bool (*NPHasMethodFunctionPtr)(NPObject *obj, NPIdentifier name);
typedef bool (*NPInvokeFunctionPtr)(NPObject *obj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
typedef bool (*NPInvokeDefaultFunctionPtr)(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);
typedef bool (*NPHasPropertyFunctionPtr)(NPObject *obj, NPIdentifier name);
typedef bool (*NPGetPropertyFunctionPtr)(NPObject *obj, NPIdentifier name, NPVariant *result);
typedef bool (*NPSetPropertyFunctionPtr)(NPObject *obj, NPIdentifier name, const NPVariant *value);
typedef bool (*NPRemovePropertyFunctionPtr)(NPObject *npobj, NPIdentifier name);
typedef bool (*NPEnumerationFunctionPtr)(NPObject *npobj, NPIdentifier **value, uint32_t *count);

/*
    NPObjects returned by create have a reference count of one.  It is the caller's responsibility
    to release the returned object.

    NPInvokeFunctionPtr function may return false to indicate a the method could not be invoked.
    
    NPGetPropertyFunctionPtr and NPSetPropertyFunctionPtr may return false to indicate a property doesn't
    exist.
    
    NPInvalidateFunctionPtr is called by the scripting environment when the native code is
    shutdown.  Any attempt to message a NPObject instance after the invalidate
    callback has been called will result in undefined behavior, even if the
    native code is still retaining those NPObject instances.
    (The runtime will typically return immediately, with 0 or NULL, from an attempt to
    dispatch to a NPObject, but this behavior should not be depended upon.)
    
    The NPEnumerationFunctionPtr function may pass an array of                  
    NPIdentifiers back to the caller. The callee allocs the memory of           
    the array using NPN_MemAlloc(), and it's the caller's responsibility        
    to release it using NPN_MemFree().           
*/
struct NPClass
{
    uint32_t structVersion;
    NPAllocateFunctionPtr allocate;
    NPDeallocateFunctionPtr deallocate;
    NPInvalidateFunctionPtr invalidate;
    NPHasMethodFunctionPtr hasMethod;
    NPInvokeFunctionPtr invoke;
    NPInvokeDefaultFunctionPtr invokeDefault;
    NPHasPropertyFunctionPtr hasProperty;
    NPGetPropertyFunctionPtr getProperty;
    NPSetPropertyFunctionPtr setProperty;
    NPRemovePropertyFunctionPtr removeProperty;
    NPEnumerationFunctionPtr enumerate;
};

#define NP_CLASS_STRUCT_VERSION      2
#define NP_CLASS_STRUCT_VERSION_ENUM 2                           
#define NP_CLASS_STRUCT_VERSION_HAS_ENUM(npclass)   \
    ((npclass)->structVersion >= NP_CLASS_STRUCT_VERSION_ENUM)

struct NPObject {
    NPClass *_class;
    uint32_t referenceCount;
    /* Additional space may be allocated here by types of NPObjects */
};

/*
    If the class has an allocate function, NPN_CreateObject invokes that function,
    otherwise a NPObject is allocated and returned.  If a class has an allocate
    function it is the responsibility of that implementation to set the initial retain
    count to 1.
*/
NPObject *NPN_CreateObject(NPP npp, NPClass *aClass);

/*
    Increment the NPObject's reference count.
*/
NPObject *NPN_RetainObject (NPObject *obj);

/*
    Decremented the NPObject's reference count.  If the reference
    count goes to zero, the class's destroy function is invoke if
    specified, otherwise the object is freed directly.
*/
void NPN_ReleaseObject (NPObject *obj);

/*
    Functions to access script objects represented by NPObject.

    Calls to script objects are synchronous.  If a function returns a
    value, it will be supplied via the result NPVariant
    argument. Successful calls will return true, false will be
    returned in case of an error.
    
    Calls made from plugin code to script must be made from the thread
    on which the plugin was initialized.
*/
bool NPN_Invoke(NPP npp, NPObject *npobj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result);
bool NPN_InvokeDefault(NPP npp, NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);
bool NPN_Evaluate(NPP npp, NPObject *npobj, NPString *script, NPVariant *result);
bool NPN_GetProperty(NPP npp, NPObject *npobj, NPIdentifier propertyName, NPVariant *result);
bool NPN_SetProperty(NPP npp, NPObject *npobj, NPIdentifier propertyName, const NPVariant *value);
bool NPN_RemoveProperty(NPP npp, NPObject *npobj, NPIdentifier propertyName);
bool NPN_HasProperty(NPP npp, NPObject *npobj, NPIdentifier propertyName);
bool NPN_HasMethod(NPP npp, NPObject *npobj, NPIdentifier methodName);
bool NPN_Enumerate(NPP npp, NPObject *npobj, NPIdentifier **identifier, uint32_t *count);

/*
    NPN_SetException may be called to trigger a script exception upon return
    from entry points into NPObjects.
*/
void NPN_SetException (NPObject *obj, const NPUTF8 *message);


typedef NPError (*NPN_GetURLNotifyProcPtr)(NPP instance, const char* URL, const char* target, void* notifyData);
typedef NPError (*NPN_PostURLNotifyProcPtr)(NPP instance, const char* URL, const char* target, uint32 len, 
                                                                const char* buf, NPBool file, void* notifyData);
typedef NPError (*NPN_RequestReadProcPtr)(NPStream* stream, NPByteRange* rangeList);
typedef NPError (*NPN_NewStreamProcPtr)(NPP instance, NPMIMEType type, const char* target, NPStream** stream);
typedef int32 (*NPN_WriteProcPtr)(NPP instance, NPStream* stream, int32 len, void* buffer);
typedef NPError (*NPN_DestroyStreamProcPtr)(NPP instance, NPStream* stream, NPReason reason);
typedef void (*NPN_StatusProcPtr)(NPP instance, const char* message);
typedef const char*(*NPN_UserAgentProcPtr)(NPP instance);
typedef void* (*NPN_MemAllocProcPtr)(uint32 size);
typedef void (*NPN_MemFreeProcPtr)(void* ptr);
typedef uint32 (*NPN_MemFlushProcPtr)(uint32 size);
typedef void (*NPN_ReloadPluginsProcPtr)(NPBool reloadPages);
typedef NPError (*NPN_GetValueProcPtr)(NPP instance, NPNVariable variable, void *ret_value);
typedef NPError (*NPN_SetValueProcPtr)(NPP instance, NPPVariable variable, void *value);
typedef void (*NPN_InvalidateRectProcPtr)(NPP instance, NPRect *rect);
typedef void (*NPN_InvalidateRegionProcPtr)(NPP instance, NPRegion region);
typedef void (*NPN_ForceRedrawProcPtr)(NPP instance);
typedef NPError (*NPN_GetURLProcPtr)(NPP instance, const char* URL, const char* target);
typedef NPError (*NPN_PostURLProcPtr)(NPP instance, const char* URL, const char* target, uint32 len, const char* buf, NPBool file);
typedef JRIEnv* (*NPN_GetJavaEnvProcPtr)(void);
typedef jref (*NPN_GetJavaPeerProcPtr)(NPP instance);
typedef void (*NPN_PushPopupsEnabledStateProcPtr)(NPP instance, NPBool enabled);
typedef void (*NPN_PopPopupsEnabledStateProcPtr)(NPP instance);
typedef void (*NPN_ReleaseVariantValueProcPtr) (NPVariant *variant);
typedef NPIdentifier (*NPN_GetStringIdentifierProcPtr) (const NPUTF8 *name);
typedef void (*NPN_GetStringIdentifiersProcPtr) (const NPUTF8 **names, int32_t nameCount, NPIdentifier *identifiers);
typedef NPIdentifier (*NPN_GetIntIdentifierProcPtr) (int32_t intid);
typedef int32_t (*NPN_IntFromIdentifierProcPtr) (NPIdentifier identifier);
typedef bool (*NPN_IdentifierIsStringProcPtr) (NPIdentifier identifier);
typedef NPUTF8 *(*NPN_UTF8FromIdentifierProcPtr) (NPIdentifier identifier);
typedef NPObject* (*NPN_CreateObjectProcPtr) (NPP, NPClass *aClass);
typedef NPObject* (*NPN_RetainObjectProcPtr) (NPObject *obj);
typedef void (*NPN_ReleaseObjectProcPtr) (NPObject *obj);
typedef bool (*NPN_InvokeProcPtr) (NPP npp, NPObject *obj, NPIdentifier methodName, const NPVariant *args,
                                                                         unsigned argCount, NPVariant *result);
typedef bool (*NPN_InvokeDefaultProcPtr) (NPP npp, NPObject *obj, const NPVariant *args, unsigned argCount, NPVariant *result);
typedef bool (*NPN_EvaluateProcPtr) (NPP npp, NPObject *obj, NPString *script, NPVariant *result);
typedef bool (*NPN_GetPropertyProcPtr) (NPP npp, NPObject *obj, NPIdentifier  propertyName, NPVariant *result);
typedef bool (*NPN_SetPropertyProcPtr) (NPP npp, NPObject *obj, NPIdentifier  propertyName, const NPVariant *value);
typedef bool (*NPN_HasPropertyProcPtr) (NPP, NPObject *npobj, NPIdentifier propertyName);
typedef bool (*NPN_HasMethodProcPtr) (NPP npp, NPObject *npobj, NPIdentifier methodName);
typedef bool (*NPN_RemovePropertyProcPtr) (NPP npp, NPObject *obj, NPIdentifier propertyName);
typedef void (*NPN_SetExceptionProcPtr) (NPObject *obj, const NPUTF8 *message);
typedef bool (*NPN_EnumerateProcPtr) (NPP npp, NPObject *npobj, NPIdentifier **identifier, uint32_t *count);



typedef NPError (*NPP_NewProcPtr)(NPMIMEType pluginType, NPP instance, uint16 mode, int16 argc, 
                                                char* argn[], char* argv[], NPSavedData* saved);
typedef NPError (*NPP_DestroyProcPtr)(NPP instance, NPSavedData** save);
typedef NPError (*NPP_SetWindowProcPtr)(NPP instance, NPWindow* window);
typedef NPError (*NPP_NewStreamProcPtr)(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype);
typedef NPError (*NPP_DestroyStreamProcPtr)(NPP instance, NPStream* stream, NPReason reason);
typedef void (*NPP_StreamAsFileProcPtr)(NPP instance, NPStream* stream, const char* fname);
typedef int32 (*NPP_WriteReadyProcPtr)(NPP instance, NPStream* stream);
typedef int32 (*NPP_WriteProcPtr)(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer);
typedef void (*NPP_PrintProcPtr)(NPP instance, NPPrint* platformPrint);
typedef int16 (*NPP_HandleEventProcPtr)(NPP instance, NPEvent* event);
typedef void (*NPP_URLNotifyProcPtr)(NPP instance, const char* URL, NPReason reason, void* notifyData);
typedef NPError (*NPP_GetValueProcPtr)(NPP instance, NPPVariable variable, void *ret_value);
typedef NPError (*NPP_SetValueProcPtr)(NPP instance, NPNVariable variable, void *value);
typedef jref *(*NPP_GetJavaClassProcPtr)(void);


typedef struct _NPNetscapeFuncs {
    uint16 size;
    uint16 version;
    NPN_GetURLProcPtr geturl;
    NPN_PostURLProcPtr posturl;
    NPN_RequestReadProcPtr requestread;
    NPN_NewStreamProcPtr newstream;
    NPN_WriteProcPtr write;
    NPN_DestroyStreamProcPtr destroystream;
    NPN_StatusProcPtr status;
    NPN_UserAgentProcPtr uagent;
    NPN_MemAllocProcPtr memalloc;
    NPN_MemFreeProcPtr memfree;
    NPN_MemFlushProcPtr memflush;
    NPN_ReloadPluginsProcPtr reloadplugins;
    NPN_GetJavaEnvProcPtr getJavaEnv;
    NPN_GetJavaPeerProcPtr getJavaPeer;
    NPN_GetURLNotifyProcPtr geturlnotify;
    NPN_PostURLNotifyProcPtr posturlnotify;
    NPN_GetValueProcPtr getvalue;
    NPN_SetValueProcPtr setvalue;
    NPN_InvalidateRectProcPtr invalidaterect;
    NPN_InvalidateRegionProcPtr invalidateregion;
    NPN_ForceRedrawProcPtr forceredraw;
    NPN_GetStringIdentifierProcPtr getstringidentifier;
    NPN_GetStringIdentifiersProcPtr getstringidentifiers;
    NPN_GetIntIdentifierProcPtr getintidentifier;
    NPN_IdentifierIsStringProcPtr identifierisstring;
    NPN_UTF8FromIdentifierProcPtr utf8fromidentifier;
    NPN_IntFromIdentifierProcPtr intfromidentifier;
    NPN_CreateObjectProcPtr createobject;
    NPN_RetainObjectProcPtr retainobject;
    NPN_ReleaseObjectProcPtr releaseobject;
    NPN_InvokeProcPtr invoke;
    NPN_InvokeDefaultProcPtr invokeDefault;
    NPN_EvaluateProcPtr evaluate;
    NPN_GetPropertyProcPtr getproperty;
    NPN_SetPropertyProcPtr setproperty;
    NPN_RemovePropertyProcPtr removeproperty;
    NPN_HasPropertyProcPtr hasproperty;
    NPN_HasMethodProcPtr hasmethod;
    NPN_ReleaseVariantValueProcPtr releasevariantvalue;
    NPN_SetExceptionProcPtr setexception;
    NPN_PushPopupsEnabledStateProcPtr pushpopupsenabledstate;
    NPN_PopPopupsEnabledStateProcPtr poppopupsenabledstate;
    NPN_EnumerateProcPtr enumerate;
} NPNetscapeFuncs;

typedef struct _NPPluginFuncs {
    uint16 size;
    uint16 version;
    NPP_NewProcPtr newp;
    NPP_DestroyProcPtr destroy;
    NPP_SetWindowProcPtr setwindow;
    NPP_NewStreamProcPtr newstream;
    NPP_DestroyStreamProcPtr destroystream;
    NPP_StreamAsFileProcPtr asfile;
    NPP_WriteReadyProcPtr writeready;
    NPP_WriteProcPtr write;
    NPP_PrintProcPtr print;
    NPP_HandleEventProcPtr event;
    NPP_URLNotifyProcPtr urlnotify;
    NPP_GetJavaClassProcPtr javaclass;
    NPP_GetValueProcPtr getvalue;
    NPP_SetValueProcPtr setvalue;
} NPPluginFuncs;

#ifdef XP_UNIX
typedef const char* (*NP_GetMIMEDescriptionProcPtr)(void);
typedef NPError (*NP_InitializeProcPtr)(NPNetscapeFuncs*, NPPluginFuncs*);
typedef void (*NP_ShutdownProcPtr)(void);
#endif /* XP_UNIX */

#ifdef XP_WIN32
typedef NPError (*NP_GetEntryPointsProcPtr)(NPPluginFuncs*);
typedef NPError (*NP_InitializeProcPtr)(NPNetscapeFuncs*);
typedef void (*NP_ShutdownProcPtr)(void);
#endif /* XP_WIN32 */

#ifdef __cplusplus
}
#endif

#endif /* ENABLE_PLUGIN */

#endif
