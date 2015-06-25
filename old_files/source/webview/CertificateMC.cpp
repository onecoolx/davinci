#include "config.h"
#include "CString.h"
#include "CertificateMC.h"

namespace WebCore
{
#if ENABLE(SSLFILE)
static CString _caPath;

const CString & caPath(void)
{
    return _caPath;
}

void setCaPath(const CString &caPath)
{
    _caPath = caPath;
}
#endif
}
