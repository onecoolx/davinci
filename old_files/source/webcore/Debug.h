#ifndef _DEBUG_H_
#define _DEBUG_H_

#if _DEBUG
#include <stdio.h>
#define notImplemented() {fprintf (stderr, "FIXME: %s:%d:%s\n", __FILE__, __LINE__, __FUNCTION__);}
#else
#define notImplemented()
#endif

#endif /* _DEBUG_H_ */

