/*
 *  Copyright (C) 2024 Zhang Ji Peng <onecoolx@gmail.com>
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
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA
 */

#include "config.h"
#include "PlatformScreen.h"

#include "DestinationColorSpace.h"
#include "FloatRect.h"
#include "NotImplemented.h"

namespace WebCore {

int screenDepth(Widget*)
{
    notImplemented();
    return 24;
}

int screenDepthPerComponent(Widget*)
{
    notImplemented();
    return 8;
}

bool screenIsMonochrome(Widget*)
{
    notImplemented();
    return false;
}

bool screenHasInvertedColors()
{
    return false;
}

FloatRect screenRect(Widget*)
{
    notImplemented();
    return { 0, 0, 1920, 1080 };
}

FloatRect screenAvailableRect(Widget*)
{
    notImplemented();
    return { 0, 0, 1920, 1080 };
}

bool screenSupportsExtendedColor(Widget*)
{
    return false;
}

DestinationColorSpace screenColorSpace(Widget*)
{
    return DestinationColorSpace::SRGB();
}

} // namespace WebCore
