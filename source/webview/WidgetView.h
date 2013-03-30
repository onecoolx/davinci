/*
** WidgetView.h: WidgetView interface.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#ifndef _WIDGETVIEW_H_
#define _WIDGETVIEW_H_
#include "config.h"

namespace WebCore {

class WidgetView 
{
public:
	virtual ~WidgetView(){}
	virtual void updateRect(int x, int y, int width, int height) = 0;
	virtual void scrollRect(int sx, int sy, int x, int y, int width, int height) = 0;
};

} // namespace WebCore
#endif/* _WIDGETVIEW_H_ */
