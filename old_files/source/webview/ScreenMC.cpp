
#include "config.h"
#include "Screen.h"

#include "IntRect.h"
#include "FloatRect.h"
#include "Frame.h"
#include "FrameView.h"
#include "Page.h"

namespace WebCore {

extern int pixelPerBytes(void);
extern int screenWidth(void);
extern int screenHeight(void);

FloatRect screenRect(Widget* widget)
{
    return FloatRect(0, 0, screenWidth(), screenHeight());
}

FloatRect screenAvailableRect(Widget* widget)
{
    return screenRect(widget);
}

int screenDepth(Widget*)
{
    return pixelPerBytes()*8;
}

int screenDepthPerComponent(Widget*)
{
    return pixelPerBytes()*8;
}

bool screenIsMonochrome(Widget*)
{ 
    return false;
}


} // namespace WebCore
