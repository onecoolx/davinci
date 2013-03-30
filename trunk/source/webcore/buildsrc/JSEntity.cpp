/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#include "JSEntity.h"

#include <wtf/GetPtr.h>

#include "Entity.h"
#include "PlatformString.h"

using namespace KJS;

namespace WebCore {

/* Hash table */

static const HashEntry JSEntityTableEntries[] =
{
    { 0, 0, 0, 0, 0 },
    { "notationName", JSEntity::NotationNameAttrNum, DontDelete|ReadOnly, 0, &JSEntityTableEntries[5] },
    { "publicId", JSEntity::PublicIdAttrNum, DontDelete|ReadOnly, 0, &JSEntityTableEntries[4] },
    { 0, 0, 0, 0, 0 },
    { "systemId", JSEntity::SystemIdAttrNum, DontDelete|ReadOnly, 0, 0 },
    { "constructor", JSEntity::ConstructorAttrNum, DontDelete|DontEnum|ReadOnly, 0, 0 }
};

static const HashTable JSEntityTable = 
{
    2, 6, JSEntityTableEntries, 4
};

/* Hash table for constructor */

static const HashEntry JSEntityConstructorTableEntries[] =
{
    { 0, 0, 0, 0, 0 }
};

static const HashTable JSEntityConstructorTable = 
{
    2, 1, JSEntityConstructorTableEntries, 1
};

class JSEntityConstructor : public DOMObject {
public:
    JSEntityConstructor(ExecState* exec)
    {
        setPrototype(exec->lexicalInterpreter()->builtinObjectPrototype());
        putDirect(exec->propertyNames().prototype, JSEntityPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    JSValue* getValueProperty(ExecState*, int token) const;
    virtual const ClassInfo* classInfo() const { return &info; }
    static const ClassInfo info;

    virtual bool implementsHasInstance() const { return true; }
};

const ClassInfo JSEntityConstructor::info = { "EntityConstructor", 0, &JSEntityConstructorTable, 0 };

bool JSEntityConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSEntityConstructor, DOMObject>(exec, &JSEntityConstructorTable, this, propertyName, slot);
}

JSValue* JSEntityConstructor::getValueProperty(ExecState*, int token) const
{
    // The token is the numeric value of its associated constant
    return jsNumber(token);
}

/* Hash table for prototype */

static const HashEntry JSEntityPrototypeTableEntries[] =
{
    { 0, 0, 0, 0, 0 }
};

static const HashTable JSEntityPrototypeTable = 
{
    2, 1, JSEntityPrototypeTableEntries, 1
};

const ClassInfo JSEntityPrototype::info = { "EntityPrototype", 0, &JSEntityPrototypeTable, 0 };

JSObject* JSEntityPrototype::self(ExecState* exec)
{
    return KJS::cacheGlobalObject<JSEntityPrototype>(exec, "[[JSEntity.prototype]]");
}

const ClassInfo JSEntity::info = { "Entity", &JSNode::info, &JSEntityTable, 0 };

JSEntity::JSEntity(ExecState* exec, Entity* impl)
    : JSNode(exec, impl)
{
    setPrototype(JSEntityPrototype::self(exec));
}

bool JSEntity::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSEntity, JSNode>(exec, &JSEntityTable, this, propertyName, slot);
}

JSValue* JSEntity::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case PublicIdAttrNum: {
        Entity* imp = static_cast<Entity*>(impl());

        return jsStringOrNull(imp->publicId());
    }
    case SystemIdAttrNum: {
        Entity* imp = static_cast<Entity*>(impl());

        return jsStringOrNull(imp->systemId());
    }
    case NotationNameAttrNum: {
        Entity* imp = static_cast<Entity*>(impl());

        return jsStringOrNull(imp->notationName());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}

JSValue* JSEntity::getConstructor(ExecState* exec)
{
    return KJS::cacheGlobalObject<JSEntityConstructor>(exec, "[[Entity.constructor]]");
}

}