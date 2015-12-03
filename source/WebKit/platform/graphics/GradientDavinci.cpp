/*
 * GradientDavinci.cpp: gradient implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Gradient.h"

#include "GraphicsContext.h"

namespace WebCore {

void Gradient::platformDestroy()
{
#if 0
    if (m_gradient) {
        ps_gradient_unref(m_gradient);
        m_gradient = 0;
    }
#endif
}

void Gradient::setPlatformGradientSpaceTransform(const AffineTransform& gradientSpaceTransformation)
{
#if 0
    if (m_gradient) {
        ps_matrix* matrix = gradientSpaceTransformation;
    }
#endif
}

void Gradient::fill(GraphicsContext* context, const FloatRect& rect)
{
}

}
