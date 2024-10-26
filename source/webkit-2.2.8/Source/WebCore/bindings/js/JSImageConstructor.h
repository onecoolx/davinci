/*
 *  Copyright (C) 1999 Harri Porten (porten@kde.org)
 *  Copyright (C) 2004, 2006, 2007, 2008 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef JSImageConstructor_h
#define JSImageConstructor_h

#include "JSDOMBinding.h"
#include "JSDocument.h"

namespace WebCore {

    class JSImageConstructor : public DOMConstructorWithDocument {
    public:
        typedef DOMConstructorWithDocument Base;

        static JSImageConstructor* create(JSC::ExecState* exec, JSC::Structure* structure, JSDOMGlobalObject* globalObject)
        {
            JSImageConstructor* constructor = new (NotNull, JSC::allocateCell<JSImageConstructor>(*exec->heap())) JSImageConstructor(structure, globalObject);
            constructor->finishCreation(exec, globalObject);
            return constructor;
        }

        static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
        {
            return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
        }

        DECLARE_INFO;

    private:
        JSImageConstructor(JSC::Structure*, JSDOMGlobalObject*);
        void finishCreation(JSC::ExecState*, JSDOMGlobalObject*);
        static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&);
    };

} // namespace WebCore

#endif // JSImageConstructor_h
