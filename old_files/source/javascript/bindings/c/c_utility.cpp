/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2006 Alexey Proskuryakov (ap@nypop.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"

#if USE(NPOBJECT)
#include "c_utility.h"

#include "NP_jsobject.h"
#include "c_instance.h" 
#include "npruntime_impl.h"
#include "npruntime_priv.h"
#include "runtime_object.h"
#include "runtime_root.h"
#include "UChar.h"

namespace KJS { namespace Bindings {

// Requires free() of returned UTF16Chars.
void convertNPStringToUTF16(const NPString *string, NPUTF16 **UTF16Chars, unsigned int *UTF16Length)
{
    convertUTF8ToUTF16(string->UTF8Characters, string->UTF8Length, UTF16Chars, UTF16Length);
}

// Requires free() of returned UTF16Chars.
void convertUTF8ToUTF16(const NPUTF8 *UTF8Chars, int UTF8Length, NPUTF16 **UTF16Chars, unsigned int *UTF16Length)
{
    int n, t;
    USChar32 wc;
	UChar16 w1, w2;
    NPUTF8 *ResourceS, *ResourceE;
    NPUTF16  *DestiS, *DestiE;

    ASSERT(UTF8Chars || UTF8Length == 0);
    ASSERT(UTF16Chars);
    
    if (UTF8Length == -1)
        UTF8Length = static_cast<int>(strlen(UTF8Chars));

    ResourceS =const_cast<NPUTF8*>(UTF8Chars);
    ResourceE =ResourceS +UTF8Length;
        
    // UTF16Length maximum length is the length of the UTF8 string, plus one to include terminator
    // Without the plus one, it will convert ok, but a warning is generated from the converter as
    // there is not enough room for a terminating character.
    *UTF16Length = UTF8Length + 1; 
        
    *UTF16Chars = 0;
    *UTF16Chars = (NPUTF16 *)malloc(sizeof(NPUTF16) * (*UTF16Length));
    if(!UTF16Chars)
		return ;
	DestiS =*UTF16Chars;
    DestiE =DestiS +*UTF16Length;
    
    while(ResourceS <ResourceE)
    {
		wc = *(ResourceS++);
		
		if (wc & 0x80) {
			n = 1;
			while (wc & (0x80 >> n))
				n++;
			
			if(ResourceS +n >ResourceE)
				return ;       //error, the source data has wrong data,   malin
			wc &= (1 << (8-n)) - 1;
			while (--n > 0) {
				t = *((unsigned char *)(ResourceS++));
			
				wc = (wc << 6) | (t & 0x3F);
			}
		}

		if (wc > 0x10FFFF) {
			continue;
		}
	
		if (wc < 0x10000) {
            if(DestiS >DestiE)
				return ;       //there is not enough space to write,is an error    malin
			*DestiS =(NPUTF16)wc;
			DestiS +=1;
			continue;
		}
	
		wc -= 0x10000;
		w1 = 0xD800;
		w2 = 0xDC00;
	
		w1 |= (wc >> 10);
		w2 |= (wc & 0x03FF);
		if(DestiS +1 <DestiE)
		{
			*DestiS++ =(NPUTF16)w1;
			*DestiS++ =(NPUTF16)w2;
		}
		else
		{
			return ;     //there is not enough space to write,is an error    malin
		}
    }

	*UTF16Length =DestiS -(*UTF16Chars);     //the real long of Destination data
}


// Variant value must be released with NPReleaseVariantValue()
void convertValueToNPVariant(ExecState *exec, JSValue *value, NPVariant *result)
{
    JSLock lock;
    
    JSType type = value->type();
    
    VOID_TO_NPVARIANT(*result);

    if (type == StringType) {
        UString ustring = value->toString(exec);
        CString cstring = ustring.UTF8String();
        NPString string = { (const NPUTF8 *)cstring.c_str(), static_cast<uint32_t>(cstring.size()) };
        NPN_InitializeVariantWithStringCopy(result, &string);
    } else if (type == NumberType) {
        DOUBLE_TO_NPVARIANT(value->toNumber(exec), *result);
    } else if (type == BooleanType) {
        BOOLEAN_TO_NPVARIANT(value->toBoolean(exec), *result);
    } else if (type == UnspecifiedType) {
        VOID_TO_NPVARIANT(*result);
    } else if (type == NullType) {
        NULL_TO_NPVARIANT(*result);
    } else if (type == ObjectType) {
        JSObject* object = static_cast<JSObject*>(value);
        if (object->classInfo() == &RuntimeObjectImp::info) {
            RuntimeObjectImp* imp = static_cast<RuntimeObjectImp *>(value);
            CInstance* instance = static_cast<CInstance*>(imp->getInternalInstance());
            if (instance) {
                NPObject* obj = instance->getObject();
                _NPN_RetainObject(obj);
                OBJECT_TO_NPVARIANT(obj, *result);
            }
        } else {
            Interpreter* originInterpreter = exec->dynamicInterpreter();
            RootObject* originRootObject = findRootObject(originInterpreter);

            Interpreter* interpreter = 0;
            if (originInterpreter->isGlobalObject(value)) {
                interpreter = originInterpreter->interpreterForGlobalObject(value);
            }

            if (!interpreter)
                interpreter = originInterpreter;

            RootObject* rootObject = findRootObject(interpreter);
            if (rootObject) {
                NPObject* npObject = _NPN_CreateScriptObject(0, object, originRootObject, rootObject);
                OBJECT_TO_NPVARIANT(npObject, *result);
            }
        }
    }
}

JSValue *convertNPVariantToValue(ExecState*, const NPVariant* variant, RootObject* rootObject)
{
    JSLock lock;
    
    NPVariantType type = variant->type;

    if (type == NPVariantType_Bool)
        return jsBoolean(NPVARIANT_TO_BOOLEAN(*variant));
    if (type == NPVariantType_Null)
        return jsNull();
    if (type == NPVariantType_Void)
        return jsUndefined();
    if (type == NPVariantType_Int32)
        return jsNumber(NPVARIANT_TO_INT32(*variant));
    if (type == NPVariantType_Double)
        return jsNumber(NPVARIANT_TO_DOUBLE(*variant));
    if (type == NPVariantType_String) {
        NPUTF16 *stringValue;
        unsigned int UTF16Length;
        convertNPStringToUTF16(&variant->value.stringValue, &stringValue, &UTF16Length); // requires free() of returned memory
        UString resultString((const UChar *)stringValue,UTF16Length);
        free(stringValue);
        return jsString(resultString);
    }
    if (type == NPVariantType_Object) {
        NPObject *obj = variant->value.objectValue;
        
        if (obj->_class == NPScriptObjectClass)
            // Get JSObject from NP_JavaScriptObject.
            return ((JavaScriptObject *)obj)->imp;

        // Wrap NPObject in a CInstance.
        return Instance::createRuntimeObject(Instance::CLanguage, obj, rootObject);
    }
    
    return jsUndefined();
}

Identifier identifierFromNPIdentifier(const NPUTF8* name)
{
    NPUTF16 *methodName;
    unsigned UTF16Length;
    convertUTF8ToUTF16(name, -1, &methodName, &UTF16Length); // requires free() of returned memory.
    Identifier identifier((const KJS::UChar*)methodName, UTF16Length);
    free(methodName);
    return identifier;
}

} }
#endif //USE(NPOBJECT)
