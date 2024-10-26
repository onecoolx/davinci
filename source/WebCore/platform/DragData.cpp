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
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"
#include "DragData.h"
#include "NotImplemented.h"

namespace WebCore {

bool DragData::canSmartReplace() const
{
    return false;
}

bool DragData::containsColor() const
{
    return false;
}

bool DragData::containsFiles() const
{
    notImplemented();
    return false;
}

unsigned DragData::numberOfFiles() const
{
    notImplemented();
    return 0;
}

Vector<String> DragData::asFilenames() const
{
    if (m_disallowFileAccess)
        return { };

    notImplemented();
    return { };
}

bool DragData::containsPlainText() const
{
    notImplemented();
    return false;
}

String DragData::asPlainText() const
{
    notImplemented();
    return String(); 
}

Color DragData::asColor() const
{
    return Color();
}

bool DragData::containsCompatibleContent(DraggingPurpose) const
{
    notImplemented();
    return false;//containsPlainText() || containsURL() || m_platformDragData->hasMarkup() || containsColor() || containsFiles();
}

bool DragData::containsURL(FilenameConversionPolicy filenamePolicy) const
{
    notImplemented();
    return false;//!asURL(filenamePolicy).isEmpty();
}

String DragData::asURL(FilenameConversionPolicy filenamePolicy, String* title) const
{
    notImplemented();
    //if (!m_platformDragData->hasURL())
    //    return String();
    //if (filenamePolicy != ConvertFilenames) {
    //    if (m_platformDragData->url().protocolIsFile())
    //        return { };
    //}

    //if (title)
    //    *title = m_platformDragData->urlLabel();
    //return m_platformDragData->url().string();
    return String();
}

bool DragData::shouldMatchStyleOnDrop() const
{
    return false;
}

}
