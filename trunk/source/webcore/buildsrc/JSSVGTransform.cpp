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


#if ENABLE(SVG)

#include "Document.h"
#include "Frame.h"
#include "SVGDocumentExtensions.h"
#include "SVGElement.h"
#include "SVGAnimatedTemplate.h"
#include "JSSVGTransform.h"

#include <wtf/GetPtr.h>

#include "JSSVGMatrix.h"
#include "SVGTransform.h"

using namespace KJS;

namespace WebCore {

/* Hash table */

static const HashEntry JSSVGTransformTableEntries[] =
{
    { "angle", JSSVGTransform::AngleAttrNum, DontDelete|ReadOnly, 0, 0 },
    { "matrix", JSSVGTransform::MatrixAttrNum, DontDelete|ReadOnly, 0, &JSSVGTransformTableEntries[4] },
    { 0, 0, 0, 0, 0 },
    { "type", JSSVGTransform::TypeAttrNum, DontDelete|ReadOnly, 0, 0 },
    { "constructor", JSSVGTransform::ConstructorAttrNum, DontDelete|DontEnum|ReadOnly, 0, 0 }
};

static const HashTable JSSVGTransformTable = 
{
    2, 5, JSSVGTransformTableEntries, 4
};

/* Hash table for constructor */

static const HashEntry JSSVGTransformConstructorTableEntries[] =
{
    { "SVG_TRANSFORM_SCALE", SVGTransform::SVG_TRANSFORM_SCALE, DontDelete|ReadOnly, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "SVG_TRANSFORM_UNKNOWN", SVGTransform::SVG_TRANSFORM_UNKNOWN, DontDelete|ReadOnly, 0, &JSSVGTransformConstructorTableEntries[7] },
    { "SVG_TRANSFORM_ROTATE", SVGTransform::SVG_TRANSFORM_ROTATE, DontDelete|ReadOnly, 0, &JSSVGTransformConstructorTableEntries[9] },
    { "SVG_TRANSFORM_SKEWY", SVGTransform::SVG_TRANSFORM_SKEWY, DontDelete|ReadOnly, 0, 0 },
    { "SVG_TRANSFORM_MATRIX", SVGTransform::SVG_TRANSFORM_MATRIX, DontDelete|ReadOnly, 0, &JSSVGTransformConstructorTableEntries[8] },
    { "SVG_TRANSFORM_TRANSLATE", SVGTransform::SVG_TRANSFORM_TRANSLATE, DontDelete|ReadOnly, 0, 0 },
    { "SVG_TRANSFORM_SKEWX", SVGTransform::SVG_TRANSFORM_SKEWX, DontDelete|ReadOnly, 0, 0 }
};

static const HashTable JSSVGTransformConstructorTable = 
{
    2, 10, JSSVGTransformConstructorTableEntries, 7
};

class JSSVGTransformConstructor : public DOMObject {
public:
    JSSVGTransformConstructor(ExecState* exec)
    {
        setPrototype(exec->lexicalInterpreter()->builtinObjectPrototype());
        putDirect(exec->propertyNames().prototype, JSSVGTransformPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    JSValue* getValueProperty(ExecState*, int token) const;
    virtual const ClassInfo* classInfo() const { return &info; }
    static const ClassInfo info;

    virtual bool implementsHasInstance() const { return true; }
};

const ClassInfo JSSVGTransformConstructor::info = { "SVGTransformConstructor", 0, &JSSVGTransformConstructorTable, 0 };

bool JSSVGTransformConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTransformConstructor, DOMObject>(exec, &JSSVGTransformConstructorTable, this, propertyName, slot);
}

JSValue* JSSVGTransformConstructor::getValueProperty(ExecState*, int token) const
{
    // The token is the numeric value of its associated constant
    return jsNumber(token);
}

/* Hash table for prototype */

static const HashEntry JSSVGTransformPrototypeTableEntries[] =
{
    { "SVG_TRANSFORM_MATRIX", SVGTransform::SVG_TRANSFORM_MATRIX, DontDelete|ReadOnly, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "setTranslate", JSSVGTransform::SetTranslateFuncNum, DontDelete|Function, 2, 0 },
    { "SVG_TRANSFORM_UNKNOWN", SVGTransform::SVG_TRANSFORM_UNKNOWN, DontDelete|ReadOnly, 0, &JSSVGTransformPrototypeTableEntries[15] },
    { 0, 0, 0, 0, 0 },
    { "setMatrix", JSSVGTransform::SetMatrixFuncNum, DontDelete|Function, 1, 0 },
    { "setSkewY", JSSVGTransform::SetSkewYFuncNum, DontDelete|Function, 1, 0 },
    { "SVG_TRANSFORM_SCALE", SVGTransform::SVG_TRANSFORM_SCALE, DontDelete|ReadOnly, 0, &JSSVGTransformPrototypeTableEntries[14] },
    { "SVG_TRANSFORM_ROTATE", SVGTransform::SVG_TRANSFORM_ROTATE, DontDelete|ReadOnly, 0, &JSSVGTransformPrototypeTableEntries[13] },
    { 0, 0, 0, 0, 0 },
    { "SVG_TRANSFORM_TRANSLATE", SVGTransform::SVG_TRANSFORM_TRANSLATE, DontDelete|ReadOnly, 0, 0 },
    { "setRotate", JSSVGTransform::SetRotateFuncNum, DontDelete|Function, 3, 0 },
    { "setSkewX", JSSVGTransform::SetSkewXFuncNum, DontDelete|Function, 1, 0 },
    { "SVG_TRANSFORM_SKEWX", SVGTransform::SVG_TRANSFORM_SKEWX, DontDelete|ReadOnly, 0, 0 },
    { "SVG_TRANSFORM_SKEWY", SVGTransform::SVG_TRANSFORM_SKEWY, DontDelete|ReadOnly, 0, 0 },
    { "setScale", JSSVGTransform::SetScaleFuncNum, DontDelete|Function, 2, 0 }
};

static const HashTable JSSVGTransformPrototypeTable = 
{
    2, 16, JSSVGTransformPrototypeTableEntries, 13
};

const ClassInfo JSSVGTransformPrototype::info = { "SVGTransformPrototype", 0, &JSSVGTransformPrototypeTable, 0 };

JSObject* JSSVGTransformPrototype::self(ExecState* exec)
{
    return KJS::cacheGlobalObject<JSSVGTransformPrototype>(exec, "[[JSSVGTransform.prototype]]");
}

bool JSSVGTransformPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSSVGTransformPrototypeFunction, JSSVGTransformPrototype, JSObject>(exec, &JSSVGTransformPrototypeTable, this, propertyName, slot);
}

JSValue* JSSVGTransformPrototype::getValueProperty(ExecState*, int token) const
{
    // The token is the numeric value of its associated constant
    return jsNumber(token);
}

const ClassInfo JSSVGTransform::info = { "SVGTransform", 0, &JSSVGTransformTable, 0 };

JSSVGTransform::JSSVGTransform(ExecState* exec, JSSVGPODTypeWrapper<SVGTransform>* impl, SVGElement* context)
    : m_context(context)
    , m_impl(impl)
{
    setPrototype(JSSVGTransformPrototype::self(exec));
}

JSSVGTransform::~JSSVGTransform()
{
    ScriptInterpreter::forgetDOMObject(m_impl.get());

}

bool JSSVGTransform::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTransform, KJS::DOMObject>(exec, &JSSVGTransformTable, this, propertyName, slot);
}

JSValue* JSSVGTransform::getValueProperty(ExecState* exec, int token) const
{
    switch (token) {
    case TypeAttrNum: {
        SVGTransform imp(*impl());

        return jsNumber(imp.type());
    }
    case MatrixAttrNum: {
        SVGTransform imp(*impl());

        return toJS(exec, new JSSVGPODTypeWrapperCreatorReadOnly<AffineTransform>(imp.matrix()), context());
    }
    case AngleAttrNum: {
        SVGTransform imp(*impl());

        return jsNumber(imp.angle());
    }
    case ConstructorAttrNum:
        return getConstructor(exec);
    }
    return 0;
}

JSValue* JSSVGTransform::getConstructor(ExecState* exec)
{
    return KJS::cacheGlobalObject<JSSVGTransformConstructor>(exec, "[[SVGTransform.constructor]]");
}
JSValue* JSSVGTransformPrototypeFunction::callAsFunction(ExecState* exec, JSObject* thisObj, const List& args)
{
    if (!thisObj->inherits(&JSSVGTransform::info))
      return throwError(exec, TypeError);

    JSSVGTransform* castedThisObj = static_cast<JSSVGTransform*>(thisObj);
    JSSVGPODTypeWrapper<SVGTransform>* wrapper = castedThisObj->impl();
    SVGTransform imp(*wrapper);

    switch (id) {
    case JSSVGTransform::SetMatrixFuncNum: {
        AffineTransform matrix = toSVGMatrix(args[0]);

        imp.setMatrix(matrix);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    case JSSVGTransform::SetTranslateFuncNum: {
        float tx = args[0]->toFloat(exec);
        float ty = args[1]->toFloat(exec);

        imp.setTranslate(tx, ty);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    case JSSVGTransform::SetScaleFuncNum: {
        float sx = args[0]->toFloat(exec);
        float sy = args[1]->toFloat(exec);

        imp.setScale(sx, sy);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    case JSSVGTransform::SetRotateFuncNum: {
        float angle = args[0]->toFloat(exec);
        float cx = args[1]->toFloat(exec);
        float cy = args[2]->toFloat(exec);

        imp.setRotate(angle, cx, cy);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    case JSSVGTransform::SetSkewXFuncNum: {
        float angle = args[0]->toFloat(exec);

        imp.setSkewX(angle);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    case JSSVGTransform::SetSkewYFuncNum: {
        float angle = args[0]->toFloat(exec);

        imp.setSkewY(angle);
        wrapper->commitChange(exec, imp);

        if (castedThisObj->context())
            castedThisObj->context()->notifyAttributeChange();
        return jsUndefined();
    }
    }
    return 0;
}
KJS::JSValue* toJS(KJS::ExecState* exec, JSSVGPODTypeWrapper<SVGTransform>* obj, SVGElement* context)
{
    return KJS::cacheSVGDOMObject<JSSVGPODTypeWrapper<SVGTransform>, JSSVGTransform>(exec, obj, context);
}
SVGTransform toSVGTransform(KJS::JSValue* val)
{
    return val->isObject(&JSSVGTransform::info) ? (SVGTransform) *static_cast<JSSVGTransform*>(val)->impl() : SVGTransform();
}

}

#endif // ENABLE(SVG)