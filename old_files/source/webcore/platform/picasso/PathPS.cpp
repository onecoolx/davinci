/*
** PathPS.cpp: path implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "MathExtras.h"
#include "Path.h"
#include "FloatRect.h"
#include "AffineTransform.h"

namespace WebCore {

Path::Path()
    :m_path(ps_path_create()),m_rule(RULE_NONZERO)
{
}

Path::Path(ps_path * p)
	:m_path(p),m_rule(RULE_NONZERO)
{
}

Path::~Path()
{
	ps_path_unref(m_path);
}

Path::Path(const Path& other) 
    :m_path(ps_path_create_copy(other.m_path)),m_rule(other.m_rule)
{
}

Path& Path::operator=(const Path& other)
{
    if (&other != this) {
		ps_path_unref(m_path);
		m_path = ps_path_create_copy(other.m_path);
        m_rule = other.m_rule;
    }
    return*this;
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

FloatRect Path::boundingRect() const 
{ 
	if (ps_path_is_empty(m_path))
		return FloatRect();

	ps_rect r = ps_path_bounding_rect(m_path);
    return FloatRect(r.x, r.y, r.w, r.h);
}

void Path::clear()
{
	ps_path_clear(m_path);
}

bool Path::isEmpty() const 
{
    return ps_path_is_empty(m_path) ? true : false;
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

void Path::addArcTo(const FloatPoint& p1, const FloatPoint& p2, float radius) 
{
	ps_point pp1 = {p1.x(), p1.y()};
	ps_point pp2 = {p2.x(), p2.y()};
	ps_path_tangent_arc_to(m_path, radius, &pp1, &pp2);
}

void Path::closeSubpath() 
{
	if (ps_path_is_empty(m_path))
		return;

	ps_path_sub_close(m_path);	
}


void Path::addRect(const FloatRect& r) 
{
	ps_rect rc = {r.x(), r.y(), r.width(), r.height()};
	ps_path_add_rect(m_path, &rc);
}

void Path::addEllipse(const FloatRect& r) 
{
    if (r.isEmpty())
        return;

	ps_rect rc = {r.x(), r.y(), r.width(), r.height()};
	ps_path_add_ellipse(m_path, &rc);
}

void Path::addArc(const FloatPoint& p, float r, float sar, float ear, bool anticlockwise)
{
	ps_point pt = {p.x(), p.y()};
	ps_path_add_arc(m_path, &pt, r, sar, ear, (anticlockwise ? True : False));
}

void Path::transform(const AffineTransform& matrix) 
{
	ps_matrix_transform_path(matrix.platformTransform(), m_path);
}

float Path::length()
{
	return (float)ps_path_get_length(m_path);
}

static inline double calc_distance(double x1, double y1, double x2, double y2)
{
	double dx = x2-x1;
	double dy = y2-y1;
	return sqrt(dx * dx + dy * dy);
}

FloatPoint Path::pointAtLength(float length, bool& ok)
{
	if (length < 0) {
		ok = false;
		return FloatPoint();
	}

	ps_point pt = {0 , 0};
	if ((length < 0.01) && (length > -0.01)) { //mean length is 0
		ps_path_get_vertex(m_path, 0, &pt);
		ok = true;
		return FloatPoint(pt.x, pt.y);
	}

	double len = 0.0;
	double start_x = 0.0;
	double start_y = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	bool first = true;
	unsigned int idx = 0;
	unsigned int total = ps_path_get_vertex_count(m_path);

	ps_path_cmd cmd;
	while(((cmd = ps_path_get_vertex(m_path, idx, &pt)) == PATH_CMD_STOP) || (idx == total)) {
		
		if (cmd >= PATH_CMD_MOVE_TO && cmd < PATH_CMD_END_POLY) {
			if (first || cmd == PATH_CMD_MOVE_TO) {
				start_x = pt.x;
				start_y = pt.y;
			} else {
				len += calc_distance(x1, y1, pt.x, pt.y);
			}

			x1 = pt.x;
			y1 = pt.y;
			first = false;
		} else {
			if(cmd == PATH_CMD_STOP && !first)
			{
				len += calc_distance(x1, y1, start_x, start_y);
			}
		}

		if (len >= length) {
			double w = pt.x -x1;
			double h = pt.y -y1;
			double slope = atan2(h, w);
			double offset = length - len;
			ok =  true;
			return FloatPoint(x1 + offset * cos(slope), y1 + offset * sin(slope));
		}

		idx++;
	}

	ok = false;
	return FloatPoint();
}

float Path::normalAngleAtLength(float length, bool& ok)
{
	if (length <= 0) {
		ok = false;
		return 0.0;
	}

	double len = 0.0;
	double start_x = 0.0;
	double start_y = 0.0;
	double x1 = 0.0;
	double y1 = 0.0;
	bool first = true;
	unsigned int idx = 0;
	unsigned int total = ps_path_get_vertex_count(m_path);

	ps_path_cmd cmd;
	ps_point pt = {0 , 0};
	while(((cmd = ps_path_get_vertex(m_path, idx, &pt)) == PATH_CMD_STOP) || (idx == total)) {
		
		if (cmd >= PATH_CMD_MOVE_TO && cmd < PATH_CMD_END_POLY) {
			if (first || cmd == PATH_CMD_MOVE_TO) {
				start_x = pt.x;
				start_y = pt.y;
			} else {
				len += calc_distance(x1, y1, pt.x, pt.y);
			}

			x1 = pt.x;
			y1 = pt.y;
			first = false;
		} else {
			if(cmd == PATH_CMD_STOP && !first)
			{
				len += calc_distance(x1, y1, start_x, start_y);
			}
		}

		if (len >= length) {
			double w = pt.x -x1;
			double h = pt.y -y1;
			double slope = atan2(h, w);
			double angle = rad2deg(slope);
			ok =  true;
			return angle;
		}

		idx++;
	}

	ok = false;
	return 0.0;
}

Path Path::createRoundedRectangle(const FloatRect& rect, const FloatSize& rs)
{
	ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
	ps_path* p = ps_path_create();
	ps_path_add_rounded_rect(p, &r, rs.width(), rs.height(), 
									rs.width(), rs.height(),
									rs.width(), rs.height(),
									rs.width(), rs.height());
	return Path(p);
}

Path Path::createRoundedRectangle(const FloatRect& rect, const FloatSize& topLeft, const FloatSize& topRight, const FloatSize& bottomLeft, const FloatSize& bottomRight)
{
	ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
	ps_path* p = ps_path_create();
	ps_path_add_rounded_rect(p, &r, topLeft.width(), topLeft.height(), 
									topRight.width(), topRight.height(),
									bottomLeft.width(), bottomLeft.height(),
									bottomRight.width(), bottomRight.height());
	return Path(p);
}

Path Path::createRectangle(const FloatRect& rect)
{
	ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
	ps_path* p = ps_path_create();
	ps_path_add_rect(p, &r);
	return Path(p);
}

Path Path::createEllipse(const FloatPoint& center, float rx, float ry)
{
	ps_rect r = {center.x()-rx, center.y()-ry, 2*rx, 2*ry};
	ps_path* p = ps_path_create();
	ps_path_add_ellipse(p, &r);
	return Path(p);
}

Path Path::createCircle(const FloatPoint& center, float r)
{
    return createEllipse(center, r, r);
}

Path Path::createLine(const FloatPoint& start, const FloatPoint& end)
{
	ps_point s = {start.x(), start.y()};
	ps_point e = {end.x(), end.y()};
	ps_path* p = ps_path_create();
	ps_path_add_line(p, &s, &e);
	return Path(p);
}

}
