/*
 * AffineTransformDavinci.cpp: AffineTransform implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "AffineTransform.h"

#include "FloatRect.h"
#include "IntRect.h"

namespace WebCore {

AffineTransform::AffineTransform()
    : m_matrix(ps_matrix_create())
{
    setMatrix(1, 0, 0, 1, 0, 0);
}

AffineTransform::AffineTransform(double a, double b, double c, double d, double e, double f)
    : m_matrix(ps_matrix_create_init(a, b, c, d, e, f))
{
    setMatrix(a, b, c, d, e, f);
}

AffineTransform::AffineTransform(ps_matrix* mtx)
    : m_matrix(ps_matrix_create_copy(mtx))
{
    float sx, sy, shx, shy, tx, ty;
    ps_matrix_get_scale_factor(m_matrix, &sx, &sy);
    ps_matrix_get_shear_factor(m_matrix, &shx, &shy);
    ps_matrix_get_translate_factor(m_matrix, &tx, &ty);

    setMatrix(sx, shy, shx, sy, tx, ty);
}

AffineTransform::~AffineTransform()
{
    ps_matrix_unref(m_matrix);
}

AffineTransform::AffineTransform(const AffineTransform& other)
    : m_matrix(ps_matrix_create_copy(other.m_matrix))
{
    setMatrix(a(), b(), c(), d(), e(), f());
}

AffineTransform& AffineTransform::operator=(const AffineTransform& other)
{
    if (this == &other)
        return *this;

    setMatrix(other.m_transform);

    ps_matrix_unref(m_matrix);
    m_matrix = ps_matrix_create_copy(other.m_matrix);
    return *this;
}

PlatformMatrix AffineTransform::platformTransform(void) const
{
    ps_matrix_init(m_matrix, a(), b(), c(), d(), e(), f());
    return m_matrix;
}

AffineTransform::operator PlatformMatrix() const
{
    ps_matrix_init(m_matrix, a(), b(), c(), d(), e(), f());
    return m_matrix;
}

}

