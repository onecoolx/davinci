/*
 * PathDavinci.cpp: path implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Path.h"

#include "AffineTransform.h"
#include "FloatRect.h"
#include "GraphicsContext.h"
#include "StrokeStyleApplier.h"
#include <math.h>
#include <wtf/MathExtras.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

Path::Path()
    : m_path(ps_path_create())
{
}

Path::~Path()
{
    ps_path_unref(m_path);
}

Path::Path(const Path& other)
    : m_path(ps_path_create_copy(other.m_path))
{
}

PlatformPathPtr Path::ensurePlatformPath()
{
    return m_path;
}

Path& Path::operator=(const Path& other)
{
    if (&other != this) {
        ps_path_unref(m_path);
        m_path = ps_path_create_copy(other.m_path);
    }
    return*this;
}

void Path::clear()
{
    ps_path_clear(m_path);
}

bool Path::isEmpty() const
{
    return ps_path_is_empty(m_path) ? true : false;
}

bool Path::hasCurrentPoint() const
{
    return !isEmpty();
}

FloatPoint Path::currentPoint() const 
{
    if (!hasCurrentPoint())
        return FloatPoint();

    ps_point p = {0, 0};
    ps_path_get_vertex(m_path, ps_path_get_vertex_count(m_path) - 1, &p);
    return FloatPoint(p.x, p.y);
}

void Path::translate(const FloatSize& size) 
{
    AffineTransform matrix;
    matrix.translate (size.width(), size.height());
    transform (matrix);
}

void Path::moveTo(const FloatPoint& p) 
{
    ps_point pt = {p.x(), p.y()};
    ps_path_move_to(m_path, &pt);
}

void Path::addLineTo(const FloatPoint& p) 
{
    ps_point pt = {p.x(), p.y()};
    ps_path_line_to(m_path, &pt);
}

void Path::addRect(const FloatRect& r) 
{
    ps_rect rc = {r.x(), r.y(), r.width(), r.height()};
    ps_path_add_rect(m_path, &rc);
}

/*
 * inspired by libsvg-cairo
 */
void Path::addQuadCurveTo(const FloatPoint& c, const FloatPoint& e) 
{
    ps_point pc = {c.x(), c.y()};
    ps_point pe = {e.x(), e.y()};
    ps_path_quad_to(m_path, &pc, &pe);
}

void Path::addBezierCurveTo(const FloatPoint& c1, const FloatPoint& c2, const FloatPoint& et) 
{
    ps_point pc1 = {c1.x(), c1.y()};
    ps_point pc2 = {c2.x(), c2.y()};
    ps_point pet = {et.x(), et.y()};
    ps_path_bezier_to(m_path, &pc1, &pc2, &pet);
}

void Path::addArc(const FloatPoint& p, float r, float sar, float ear, bool anticlockwise)
{
    ps_point pt = {p.x(), p.y()};
    ps_path_add_arc(m_path, &pt, r, sar, ear, (anticlockwise ? True : False));
}

void Path::addArcTo(const FloatPoint& p1, const FloatPoint& p2, float radius) 
{
    ps_point pp1 = {p1.x(), p1.y()};
    ps_point pp2 = {p2.x(), p2.y()};
    ps_path_tangent_arc_to(m_path, radius, &pp1, &pp2);
}

void Path::addEllipse(const FloatRect& r) 
{
    if (r.isEmpty())
        return;

    ps_rect rc = {r.x(), r.y(), r.width(), r.height()};
    ps_path_add_ellipse(m_path, &rc);
}

void Path::closeSubpath() 
{
    if (ps_path_is_empty(m_path))
        return;

    ps_path_sub_close(m_path);
}

FloatRect Path::boundingRect() const 
{ 
    if (ps_path_is_empty(m_path))
        return FloatRect();

    ps_rect r = {0, 0, 0, 0};
    if (!ps_path_bounding_rect(m_path, &r))
        return FloatRect();
    return FloatRect(r.x, r.y, r.w, r.h);
}

FloatRect Path::strokeBoundingRect(StrokeStyleApplier* applier) const
{
    return boundingRect();
}

bool Path::contains(const FloatPoint& pt, WindRule rule) const 
{
    if (ps_path_is_empty(m_path))
        return false;

    ps_fill_rule fl = FILL_RULE_ERROR;
    switch(rule) {
        case RULE_NONZERO:
            fl = FILL_RULE_WINDING;
            break;
        case RULE_EVENODD:
            fl = FILL_RULE_EVEN_ODD;
            break;
    }

    ps_point p = {pt.x(), pt.y()};
    return ps_path_contains(m_path, &p, fl) ? true : false;
}

bool Path::strokeContains(StrokeStyleApplier* applier, const FloatPoint& pt) const
{
    if (ps_path_is_empty(m_path))
        return false;

    ASSERT(applier);
    GraphicsContext gc(0);
    applier->strokeStyle(&gc);

    ps_point p = {pt.x(), pt.y()};
    return ps_path_stroke_contains(m_path, &p, gc.strokeThickness()) ? true : false;
}

void Path::apply(void* info, PathApplierFunction function) const
{
    if (ps_path_is_empty(m_path))
        return;

    ps_path_cmd cmd = PATH_CMD_STOP;
    unsigned int len = ps_path_get_vertex_count(m_path);
    ps_point pt = {0, 0};

    PathElement pelement;
    FloatPoint points[3];
    pelement.points = points;

    for (int i = 0; i < (int)len; i++) {
        cmd = ps_path_get_vertex(m_path, i, &pt);
        switch (cmd) {
        case PATH_CMD_MOVE_TO:
            pelement.type = PathElementMoveToPoint;
            pelement.points[0] = FloatPoint(pt.x, pt.y);
            function(info, &pelement);
            break;
        case PATH_CMD_LINE_TO:
            pelement.type = PathElementAddLineToPoint;
            pelement.points[0] = FloatPoint(pt.x, pt.y);
            function(info, &pelement);
            break;
        case PATH_CMD_CURVE3:
            pelement.type = PathElementAddCurveToPoint;
            pelement.points[0] = FloatPoint(pt.x, pt.y);
            i++;
            cmd = ps_path_get_vertex(m_path, i, &pt);
            pelement.points[1] = FloatPoint(pt.x, pt.y);
            function(info, &pelement);
            break;
        case PATH_CMD_CURVE4:
            pelement.type = PathElementAddCurveToPoint;
            pelement.points[0] = FloatPoint(pt.x, pt.y);
            i++;
            cmd = ps_path_get_vertex(m_path, i, &pt);
            pelement.points[1] = FloatPoint(pt.x, pt.y);
            i++;
            cmd = ps_path_get_vertex(m_path, i, &pt);
            pelement.points[2] = FloatPoint(pt.x, pt.y);
            function(info, &pelement);
            break;
        case PATH_CMD_STOP:
            pelement.type = PathElementCloseSubpath;
            function(info, &pelement);
            break;
        default:
            break;
        }
    }
}

void Path::transform(const AffineTransform& matrix) 
{
    ps_matrix_transform_path(matrix.platformTransform(), m_path);
}

} // namespace WebCore
