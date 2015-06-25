
#ifndef HttpProtocolHandler_h
#define HttpProtocolHandler_h

#include "config.h"

namespace WebCore {

class ResourceHandle;

void initHttpJob(ResourceHandle *job);
inline bool isAuthentication(int code) {return (code==401 || code==407);}
inline bool isServerRedirection(int code) {return (code==301 || code==302 || code==303 || code==307);}
inline bool isUseCacheData(int code) {return code==304;}

void responseMIMETypeCheck(ResourceHandle* job, void* ptr, size_t totalSize);

} /* namespace WebCore */

#endif /* HttpProtocolHandler_h */
