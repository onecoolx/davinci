#!/usr/bin/env python

import os
import sys
import subprocess
import shutil

# make dir
def MakeDirIfNotExists(path):
  is_exit = os.path.exists(path)
  if not is_exit:
    os.makedirs(path)
    return True
  return False

# write lines file
def WriteLinesToFile(contents, path):
  f = open(path, "wb")
  for line in contents:
    f.write(line)
  f.close()

# write lines file
def AppendLinesToFile(contents, path):
  f = open(path, "ab")
  for line in contents:
    f.write(line)
  f.close()

# write lines to br file
def WriteLinesWithBrToFile(contents, path):
  f = open(path, "wb")
  for line in contents:
    f.write(line+"\n")
  f.close()

# read lines file
def ReadLinesFromFile(path):
  f = open(path, "r")
  contents = f.readlines()
  f.close()
  return contents

# read file
def ReadFromFile(path):
  ret = ''
  f = open(path, "r")
  contents = f.readlines()
  for line in contents:
    ret = ret + line.strip('\n')
  f.close()
  return ret

# get files list
def GetFileListDir(path, exts, base, r):
  file_list = []
  files = os.listdir(path)
  files = RemoveItemMatch(files, ['.lproj', '.vcxproj', '.xcodeproj'])
  for file_name in files:
    if (r and os.path.isdir(path+"/"+file_name)):
      file_list = file_list + GetFileListDir(path+"/"+file_name, exts, base+file_name+"/", True)
    elif os.path.splitext(file_name)[1] in (exts):
      file_list.append(base+file_name)
  return file_list

# list to string
def ListToString(slist):
  ret = ''
  for line in slist:
    ret = ret + line + " "
  return ret

# remove item match
def RemoveItemMatch(slist, matchs):
  file_list = []
  for file_name in slist:
    finded = 0
    for match in matchs:
      if file_name.find(match) != -1:
        finded = 1
        continue
    if finded == 0:
      file_list.append(file_name)
  return file_list

# generate defined macros header.
def GenerateMacrosHeader(path, out):
  f = open(path, "r")
  fo = open(out, "w")
  fo.write("#ifndef _DAV_FEATURES_DEFINES_H_\n")
  fo.write("#define _DAV_FEATURES_DEFINES_H_\n")
  fo.write("\n")
  contents = f.readlines()
  for line in contents:
    slist = line.split('=')
    fo.write("#if defined("+slist[0]+")\n")
    fo.write("#undef "+slist[0]+"\n")
    fo.write("#endif"+"\n")
    fo.write("#define "+slist[0]+" "+slist[1])
    fo.write("\n")
  fo.write("#endif /*_DAV_FEATURES_DEFINES_H_*/\n")
  f.close()
  fo.close()


# generate files
def Main(src_dir, dst_dir):
  curr_dir = os.getcwd()
  # make output dir.
  os.chdir(src_dir)
  if not MakeDirIfNotExists(dst_dir):
    print "Generated code is existed!"
    return 0

  feature_list = ReadFromFile("WebKitFeatures.txt")
  GenerateMacrosHeader("WebKitFeatures.txt", dst_dir+"/DavinciFeatureDefines.h")

  # step 1, XPathGrammar.h XPathGrammar.cpp
  subprocess.call(["perl", "css/makegrammar.pl", "--outputDir", dst_dir, "--bison", "bison", "--symbolsPrefix", "xpathyy", "xml/XPathGrammar.y"])

  # step 2, MathMLNames.h MathMLNames.cpp MathMLElementFactory.h MathMLElementFactory.cpp
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "mathml/mathtags.in", "mathml/mathattrs.in", "--tags",\
  "mathml/mathtags.in", "--attrs", "mathml/mathattrs.in", "--factory", "--wrapperFactory", "--outputDir", dst_dir])

  # step 3, SVGNames.h SVGNames.cpp SVGElementFactory.h SVGElementFactory.cpp
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "svg/svgtags.in", "svg/svgattrs.in", "--tags",\
  "svg/svgtags.in", "--attrs", "svg/svgattrs.in", "--extraDefines", feature_list, "--factory", "--wrapperFactory", "--outputDir", dst_dir])

  # step 4, XLinkNames.h XLinkNames.cpp
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "svg/xlinkattrs.in", "--attrs", "svg/xlinkattrs.in", "--outputDir", dst_dir])

  # step 5, CSSPropertyNames.h CSSPropertyNames.cpp
  css_props = ReadLinesFromFile("css/CSSPropertyNames.in")
  WriteLinesToFile(css_props, dst_dir+"/CSSPropertyNames.in")
  css_props = ReadLinesFromFile("css/SVGCSSPropertyNames.in")
  AppendLinesToFile(css_props, dst_dir+"/CSSPropertyNames.in")
  os.chdir(dst_dir)
  subprocess.call(["perl", "-I"+curr_dir+"/"+src_dir+"/bindings/scripts", curr_dir+"/"+src_dir+"/css/makeprop.pl", "--defines", feature_list])
  os.chdir(curr_dir)
  os.chdir(src_dir)

  # step 6, CSSValueKeywords.h CSSValueKeywords.cpp
  css_values = ReadLinesFromFile("css/CSSValueKeywords.in")
  WriteLinesToFile(css_values, dst_dir+"/CSSValueKeywords.in")
  css_values = ReadLinesFromFile("css/SVGCSSValueKeywords.in")
  AppendLinesToFile(css_values, dst_dir+"/CSSValueKeywords.in")
  os.chdir(dst_dir)
  subprocess.call(["perl", "-I"+curr_dir+"/"+src_dir+"/bindings/scripts", curr_dir+"/"+src_dir+"/css/makevalues.pl", "--defines", feature_list])
  os.chdir(curr_dir)
  os.chdir(src_dir)

  # step 7, XMLViewerCSS.h XMLViewerJS.h
  subprocess.call(["perl", "inspector/xxd.pl", "XMLViewer_css", "xml/XMLViewer.css", dst_dir+"/XMLViewerCSS.h"])
  subprocess.call(["perl", "inspector/xxd.pl", "XMLViewer_js", "xml/XMLViewer.js", dst_dir+"/XMLViewerJS.h"])

  # step 8, HTMLEntityTable.cpp
  subprocess.call(["python", "html/parser/create-html-entity-table", "-o", dst_dir+"/HTMLEntityTable.cpp", "html/parser/HTMLEntityNames.in"])

  # step 9, CSSGrammar.h CSSGrammar.cpp
  subprocess.call(["perl", "-Ibindings/scripts", "css/makegrammar.pl", "--extraDefines", \
  feature_list, "--outputDir", dst_dir, "--bison", "bison", "--symbolsPrefix", "cssyy", "css/CSSGrammar.y.in"])

  # step10, UserAgentStyleSheets.h PlugInsResources.h
  files = GetFileListDir("css", ['.css'], "css/", False)
  files = RemoveItemMatch(files, ['BlackBerry', 'Qt', 'Efl', 'Win', 'Gtk', 'QuickTime'])
  subprocess.call(["perl", "-Ibindings/scripts", "css/make-css-file-arrays.pl", "--defines", feature_list, \
  dst_dir+"/UserAgentStyleSheets.h", dst_dir+"/UserAgentStyleSheetsData.cpp"] + files)
  subprocess.call(["perl", "-Ibindings/scripts", "css/make-css-file-arrays.pl", "--defines", feature_list, \
  dst_dir+"/PlugInsResources.h", dst_dir+"/PlugInsResourcesData.cpp", "Resources/plugIns.js"])

  # step11, HTMLNames.h HTMLNames.cpp HTMLElementFactory.h HTMLElementFactory.cpp
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "html/HTMLTagNames.in", "html/HTMLAttributeNames.in", "--tags",\
  "html/HTMLTagNames.in", "--attrs", "html/HTMLAttributeNames.in", "--extraDefines", feature_list, "--factory",\
  "--wrapperFactory", "--outputDir", dst_dir])

  # step12, XMLNSNames.h XMLNames.h
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "xml/xmlnsattrs.in", "--attrs", "xml/xmlnsattrs.in", "--outputDir", dst_dir])
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "xml/xmlattrs.in", "--attrs", "xml/xmlattrs.in", "--outputDir", dst_dir])

  # step13, EventHeaders.h EventInterfaces.h EventTargetHeaders.h EventTargetInterfaces.h
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_event_factory.pl", "dom/EventNames.in",\
  "--input", "dom/EventNames.in", "--outputDir", dst_dir])
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_event_factory.pl", "dom/EventTargetFactory.in",\
  "--input", "dom/EventTargetFactory.in", "--outputDir", dst_dir])

  # step14, WebKitFontFamilyNames.cpp WebKitFontFamilyNames.h
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_names.pl", "bindings/scripts/Hasher.pm",\
  "bindings/scripts/StaticString.pm", "css/WebKitFontFamilyNames.in", "--fonts", "css/WebKitFontFamilyNames.in",\
  "--outputDir", dst_dir])

  # step15, ExceptionCodeDescription.h ExceptionCodeDescription.cpp ExceptionInterfaces.h ExceptionInterfaces.h
  subprocess.call(["perl", "-Ibindings/scripts", "dom/make_dom_exceptions.pl", "dom/DOMExceptions.in",\
  "--input", "dom/DOMExceptions.in", "--outputDir", dst_dir])

  # step16, SettingsMacros.h InternalSettingsGenerated.cpp InternalSettingsGenerated.h
  subprocess.call(["perl", "-Ibindings/scripts", "page/make_settings.pl", "page/Settings.in",\
  "--input", "page/Settings.in", "--outputDir", dst_dir])

  # step17, InspectorProtocolVersion.h
  subprocess.call(["python", "inspector/generate-inspector-protocol-version", "-o", dst_dir+"/InspectorProtocolVersion.h",\
  "inspector/Inspector.json"])

  # step18, InspectorBackendDispatcher.cpp
  subprocess.call(["python", "inspector/CodeGeneratorInspector.py", "inspector/Inspector.json",\
  "--output_h_dir", dst_dir, "--output_cpp_dir", dst_dir, "--output_js_dir", dst_dir])

  # step19, InspectorOverlayPage.h InjectedScriptCanvasModuleSource.h InjectedScriptSource.h
  subprocess.call(["perl", "inspector/xxd.pl", "InspectorOverlayPage_html", "inspector/InspectorOverlayPage.html",\
  dst_dir+"/InspectorOverlayPage.h"])
  subprocess.call(["perl", "inspector/xxd.pl", "InjectedScriptCanvasModuleSource_js", "inspector/InjectedScriptCanvasModuleSource.js",\
  dst_dir+"/InjectedScriptCanvasModuleSource.h"])
  subprocess.call(["perl", "inspector/xxd.pl", "InjectedScriptSource_js", "inspector/InjectedScriptSource.js",\
  dst_dir+"/InjectedScriptSource.h"])

  # step20, glslang_tab.cpp
  subprocess.call(["bison", "--no-lines", "--defines="+dst_dir+"/glslang_tab.h",\
  "--skeleton=yacc.c", "--output="+dst_dir+"/glslang_tab.cpp", "../ThirdParty/ANGLE/src/compiler/glslang.y"])

  # step21, ANGLE tokenizer & parser
  subprocess.call(["flex", "--noline", "--nounistd", "--outfile="+dst_dir+"/glslang.cpp",\
  "../ThirdParty/ANGLE/src/compiler/glslang.l", dst_dir+"/glslang_tab.cpp"])

  # step22, ColorData.cpp
  os.chdir(dst_dir)
  subprocess.call(["perl", curr_dir+"/"+src_dir+"/make-hash-tools.pl", ".", curr_dir+"/"+src_dir+"/platform/ColorData.gperf"])
  os.chdir(curr_dir)
  os.chdir(src_dir)

  # step23, idl files generator
  idl_files = GetFileListDir(".", ['.idl'], "", True)
  idl_files.insert(0, dst_dir + "/InternalSettingsGenerated.idl")
  idl_files_list = dst_dir+"/idl_files_list"
  WriteLinesWithBrToFile(idl_files, idl_files_list)
  subprocess.call(["perl", "-Ibindings/scripts", "bindings/scripts/preprocess-idls.pl", "--defines",\
  "\"LANGUAGE_JAVASCRIPT=1 "+feature_list+"\"","--idlFilesList", idl_files_list, "--windowConstructorsFile", dst_dir+"/DOMWindowConstructors.idl",\
  "--workerGlobalScopeConstructorsFile", dst_dir+"/WorkerGlobalScopeConstructors.idl", "--sharedWorkerGlobalScopeConstructorsFile",\
  dst_dir+"/SharedWorkerGlobalScopeConstructors.idl", "--dedicatedWorkerGlobalScopeConstructorsFile", dst_dir+"/DedicatedWorkerGlobalScopeConstructors.idl",\
  "--supplementalDependencyFile", dst_dir+"/idl_supplemental_dependencies"])

  # step24, idl to JS files
  idl_files.append(dst_dir + "/DOMWindowConstructors.idl")
  idl_files.append(dst_dir + "/WorkerGlobalScopeConstructors.idl")
  idl_files.append(dst_dir + "/SharedWorkerGlobalScopeConstructors.idl")
  idl_files.append(dst_dir + "/DedicatedWorkerGlobalScopeConstructors.idl")
  for file_name in idl_files:
    print "Generate idl file : " + file_name
    base_name = os.path.splitext(file_name)[0]
    subprocess.call(["perl", "-Ibindings/scripts", "bindings/scripts/generate-bindings.pl", file_name,\
    "--outputDir", dst_dir, "--include", dst_dir, "--defines", "\"LANGUAGE_JAVASCRIPT=1 "+feature_list+"\"", "--generator", "JS", "--idlAttributesFile",\
    "bindings/scripts/IDLAttributes.txt", "--supplementalDependencyFile", dst_dir+"/idl_supplemental_dependencies", dst_dir+"/"+"JS"+base_name+".h"])

  os.chdir(curr_dir)
  return 0


# main
if __name__ == '__main__':
  sys.exit(Main(sys.argv[1], sys.argv[2]))
