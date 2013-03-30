
#include "config.h"
#include "ResourceHandle.h"
#include "ResourceHandleClient.h"
#include "ResourceHandleInternalCurl.h"
#include "MIMETypeRegistry.h"
#include "DataProtocolHandler.h"
#include "HTTPParsers.h"
#include "Base64.h"

namespace WebCore {

void handleAboutUrl(ResourceHandle* handle)
{
    DeprecatedString data = handle->request().url().url();
    DeprecatedString header = "text/plain;charset=US-ASCII";

    ResourceResponse response;
    ResourceHandleClient* client = handle->getInternal()->client();

    response.setMimeType(extractMIMETypeFromMediaType(header));
    response.setTextEncodingName(extractCharsetFromMediaType(header));
    response.setExpectedContentLength(data.length());
    response.setHTTPStatusCode(200);

    client->didReceiveResponse(handle, response);
    client->didReceiveData(handle, 0, 0, 0);
    client->didFinishLoading(handle);
}

} /* namespace WebCore */
