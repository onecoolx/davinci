/*
 * PlatformStrategiesDavinci.cpp: PlatformStrategies implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PlatformStrategiesDavinci.h"

#include "IntSize.h"
#include "Page.h"
#include "PageGroup.h"
#include "PlatformCookieJar.h"
#include "PluginDatabase.h"

using namespace WebCore;

void PlatformStrategiesDavinci::initialize()
{
    DEFINE_STATIC_LOCAL(PlatformStrategiesDavinci, platformStrategies, ());
}

PlatformStrategiesDavinci::PlatformStrategiesDavinci()
{
    setPlatformStrategies(this);
}

CookiesStrategy* PlatformStrategiesDavinci::createCookiesStrategy()
{
    return this;
}

DatabaseStrategy* PlatformStrategiesDavinci::createDatabaseStrategy()
{
    return this;
}

LoaderStrategy* PlatformStrategiesDavinci::createLoaderStrategy()
{
    return this;
}

PasteboardStrategy* PlatformStrategiesDavinci::createPasteboardStrategy()
{
    return 0;
}

PluginStrategy* PlatformStrategiesDavinci::createPluginStrategy()
{
    return this;
}

SharedWorkerStrategy* PlatformStrategiesDavinci::createSharedWorkerStrategy()
{
    return this;
}

StorageStrategy* PlatformStrategiesDavinci::createStorageStrategy()
{
    return this;
}

VisitedLinkStrategy* PlatformStrategiesDavinci::createVisitedLinkStrategy()
{
    return this;
}

String PlatformStrategiesDavinci::cookiesForDOM(const NetworkStorageSession& session, const KURL& firstParty, const KURL& url)
{
    return WebCore::cookiesForDOM(session, firstParty, url);
}

void PlatformStrategiesDavinci::setCookiesFromDOM(const NetworkStorageSession& session, const KURL& firstParty, const KURL& url, const String& cookieString)
{
    WebCore::setCookiesFromDOM(session, firstParty, url, cookieString);
}

bool PlatformStrategiesDavinci::cookiesEnabled(const NetworkStorageSession& session, const KURL& firstParty, const KURL& url)
{
    return WebCore::cookiesEnabled(session, firstParty, url);
}

String PlatformStrategiesDavinci::cookieRequestHeaderFieldValue(const NetworkStorageSession& session, const KURL& firstParty, const KURL& url)
{
    return WebCore::cookieRequestHeaderFieldValue(session, firstParty, url);
}

bool PlatformStrategiesDavinci::getRawCookies(const NetworkStorageSession& session, const KURL& firstParty, const KURL& url, Vector<Cookie>& rawCookies)
{
    return WebCore::getRawCookies(session, firstParty, url, rawCookies);
}

void PlatformStrategiesDavinci::deleteCookie(const NetworkStorageSession& session, const KURL& url, const String& cookieName)
{
    WebCore::deleteCookie(session, url, cookieName);
}

void PlatformStrategiesDavinci::refreshPlugins()
{
    PluginDatabase::installedPlugins()->refresh();
}

void PlatformStrategiesDavinci::getPluginInfo(const Page*, Vector<PluginInfo>& outPlugins)
{
    const Vector<PluginPackage*>& plugins = PluginDatabase::installedPlugins()->plugins();

    outPlugins.resize(plugins.size());

    for (size_t i = 0; i < plugins.size(); ++i) {
        PluginPackage* package = plugins[i];

        PluginInfo info;
        info.name = package->name();
        info.file = package->fileName();
        info.desc = package->description();

        const MIMEToDescriptionsMap& mimeToDescriptions = package->mimeToDescriptions();

        info.mimes.reserveCapacity(mimeToDescriptions.size());

        MIMEToDescriptionsMap::const_iterator end = mimeToDescriptions.end();
        for (MIMEToDescriptionsMap::const_iterator it = mimeToDescriptions.begin(); it != end; ++it) {
            MimeClassInfo mime;

            mime.type = it->key;
            mime.desc = it->value;
            mime.extensions = package->mimeToExtensions().get(mime.type);

            info.mimes.append(mime);
        }

        outPlugins[i] = info;
    }
}

bool PlatformStrategiesDavinci::isLinkVisited(Page* page, LinkHash hash, const KURL&, const AtomicString&)
{
    return page->group().isLinkVisited(hash);
}

void PlatformStrategiesDavinci::addVisitedLink(Page* page, LinkHash hash)
{
    page->group().addVisitedLinkHash(hash);
}
