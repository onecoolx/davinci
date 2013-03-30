/* Automatically generated from /home/jpzhang/mbrowser/source/webcore/bindings/js/kjs_navigator.cpp using /home/jpzhang/mbrowser/source/webcore/../javascript/kjs/create_hash_table. DO NOT EDIT ! */

namespace KJS {

static const struct HashEntry NavigatorTableEntries[] = {
   { "appVersion", Navigator::AppVersion, DontDelete|ReadOnly, 0, &NavigatorTableEntries[17] }/* 737224111 */ ,
   { "appCodeName", Navigator::AppCodeName, DontDelete|ReadOnly, 0, &NavigatorTableEntries[16] }/* 2036402863 */ ,
   { 0, 0, 0, 0, 0 },
   { "javaEnabled", Navigator::JavaEnabled, DontDelete|Function, 0, 0 }/* 3101780464 */ ,
   { "productSub", Navigator::ProductSub, DontDelete|ReadOnly, 0, 0 }/* 2097335881 */ ,
   { "language", Navigator::Language, DontDelete|ReadOnly, 0, &NavigatorTableEntries[13] }/* 389985029 */ ,
   { "appName", Navigator::AppName, DontDelete|ReadOnly, 0, &NavigatorTableEntries[14] }/* 1928575421 */ ,
   { "vendorSub", Navigator::VendorSub, DontDelete|ReadOnly, 0, 0 }/* 2200565686 */ ,
   { 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0 },
   { "vendor", Navigator::Vendor, DontDelete|ReadOnly, 0, 0 }/* 4183282360 */ ,
   { 0, 0, 0, 0, 0 },
   { "mimeTypes", Navigator::_MimeTypes, DontDelete|ReadOnly, 0, 0 }/* 541397713 */ ,
   { "userAgent", Navigator::UserAgent, DontDelete|ReadOnly, 0, &NavigatorTableEntries[15] }/* 1491767165 */ ,
   { "platform", Navigator::Platform, DontDelete|ReadOnly, 0, 0 }/* 1656147642 */ ,
   { "plugins", Navigator::_Plugins, DontDelete|ReadOnly, 0, 0 }/* 3805841733 */ ,
   { "product", Navigator::Product, DontDelete|ReadOnly, 0, 0 }/* 3666888811 */ ,
   { "cookieEnabled", Navigator::CookieEnabled, DontDelete|ReadOnly, 0, 0 }/* 2175375748 */ 
};

const struct HashTable NavigatorTable = { 2, 18, NavigatorTableEntries, 13 };

} // namespace

namespace KJS {

static const struct HashEntry PluginsTableEntries[] = {
   { "refresh", Plugins::Refresh, DontDelete|Function, 0, 0 }/* 561650708 */ ,
   { "length", Plugins::Length, DontDelete|ReadOnly, 0, 0 }/* 2484182065 */ 
};

const struct HashTable PluginsTable = { 2, 2, PluginsTableEntries, 2 };

} // namespace

namespace KJS {

static const struct HashEntry MimeTypesTableEntries[] = {
   { "length", MimeTypes::Length, DontDelete|ReadOnly, 0, 0 }/* 2484182065 */ 
};

const struct HashTable MimeTypesTable = { 2, 1, MimeTypesTableEntries, 1 };

} // namespace

namespace KJS {

static const struct HashEntry PluginTableEntries[] = {
   { 0, 0, 0, 0, 0 },
   { "name", Plugin::Name, DontDelete|ReadOnly, 0, &PluginTableEntries[4] }/* 4135969945 */ ,
   { "filename", Plugin::Filename, DontDelete|ReadOnly, 0, 0 }/* 2442346670 */ ,
   { "description", Plugin::Description, DontDelete|ReadOnly, 0, 0 }/* 432724751 */ ,
   { "length", Plugin::Length, DontDelete|ReadOnly, 0, 0 }/* 2484182065 */ 
};

const struct HashTable PluginTable = { 2, 5, PluginTableEntries, 4 };

} // namespace

namespace KJS {

static const struct HashEntry MimeTypeTableEntries[] = {
   { "suffixes", MimeType::Suffixes, DontDelete|ReadOnly, 0, 0 }/* 272507524 */ ,
   { 0, 0, 0, 0, 0 },
   { "enabledPlugin", MimeType::EnabledPlugin, DontDelete|ReadOnly, 0, 0 }/* 4109007998 */ ,
   { "type", MimeType::Type, DontDelete|ReadOnly, 0, &MimeTypeTableEntries[4] }/* 924663163 */ ,
   { "description", MimeType::Description, DontDelete|ReadOnly, 0, 0 }/* 432724751 */ 
};

const struct HashTable MimeTypeTable = { 2, 5, MimeTypeTableEntries, 4 };

} // namespace
