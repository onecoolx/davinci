
#ifndef _CERTIFICATEPS_H_
#define _CERTIFICATEPS_H_

#include "config.h"
namespace WebCore {
#if ENABLE(SSLFILE)
    class CString;
    const CString & caPath(void);	
    void setCaPath(const CString &caPath);
#endif
}

#endif/* _CERTIFICATEMG_H_ */
