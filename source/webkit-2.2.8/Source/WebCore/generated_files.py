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

# write lines file
def WriteLinesToFile(contents, path):
  f = open(path, "wb")
  for line in contents:
    f.write(line)
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
def GetFileListDir(path, exts, base):
  file_list = []
  for file_name in os.listdir(path):
    if os.path.splitext(file_name)[1] in (exts):
      file_list.append(base+file_name)
  return file_list

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

# generate files
def Main(src_dir, dst_dir):
  curr_dir = os.getcwd()
  # make output dir.
  MakeDirIfNotExists(dst_dir)

  feature_list = ReadFromFile(src_dir+"/WebKitFeatures.txt")

  # step 1, XPathGrammar.h XPathGrammar.cpp
  subprocess.call(["perl", src_dir+"/css/makegrammar.pl", "--outputDir", dst_dir, "--bison", "bison", "--symbolsPrefix", "xpathyy", src_dir+"/xml/XPathGrammar.y"])

  # step 2, MathMLNames.h MathMLNames.cpp MathMLElementFactory.h MathMLElementFactory.cpp
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/mathml/mathtags.in", src_dir+"/mathml/mathattrs.in", "--tags",\
  src_dir+"/mathml/mathtags.in", "--attrs", src_dir+"/mathml/mathattrs.in", "--factory", "--wrapperFactory", "--outputDir", dst_dir])

  # step 3, SVGNames.h SVGNames.cpp SVGElementFactory.h SVGElementFactory.cpp
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/svg/svgtags.in", src_dir+"/svg/svgattrs.in", "--tags",\
  src_dir+"/svg/svgtags.in", "--attrs", src_dir+"/svg/svgattrs.in", "--extraDefines", feature_list, "--factory", "--wrapperFactory", "--outputDir", dst_dir])

  # step 4, XLinkNames.h XLinkNames.cpp
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/svg/xlinkattrs.in", "--attrs", src_dir+"/svg/xlinkattrs.in", "--outputDir", dst_dir])

  # step 5, CSSPropertyNames.h CSSPropertyNames.cpp
  css_props = ReadLinesFromFile(src_dir+"/css/CSSPropertyNames.in")
  WriteLinesToFile(css_props, dst_dir+"/CSSPropertyNames.in")
  os.chdir(dst_dir)
  subprocess.call(["perl", "-I"+curr_dir+"/"+src_dir+"/bindings/scripts", curr_dir+"/"+src_dir+"/css/makeprop.pl", "--defines", feature_list])
  os.chdir(curr_dir)

  # step 6, CSSValueKeywords.h CSSValueKeywords.cpp
  css_props = ReadLinesFromFile(src_dir+"/css/CSSValueKeywords.in")
  WriteLinesToFile(css_props, dst_dir+"/CSSValueKeywords.in")
  os.chdir(dst_dir)
  subprocess.call(["perl", "-I"+curr_dir+"/"+src_dir+"/bindings/scripts", curr_dir+"/"+src_dir+"/css/makevalues.pl", "--defines", feature_list])
  os.chdir(curr_dir)

  # step 7, XMLViewerCSS.h XMLViewerJS.h
  subprocess.call(["perl", src_dir+"/inspector/xxd.pl", "XMLViewer_css", src_dir+"/xml/XMLViewer.css", dst_dir+"/XMLViewerCSS.h"])
  subprocess.call(["perl", src_dir+"/inspector/xxd.pl", "XMLViewer_js", src_dir+"/xml/XMLViewer.js", dst_dir+"/XMLViewerJS.h"])

  # step 8, HTMLEntityTable.cpp
  subprocess.call(["python", src_dir+"/html/parser/create-html-entity-table", "-o", dst_dir+"/HTMLEntityTable.cpp", src_dir+"/html/parser/HTMLEntityNames.in"])

  # step 9, CSSGrammar.h CSSGrammar.cpp
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/css/makegrammar.pl", "--extraDefines", \
  feature_list, "--outputDir", dst_dir, "--bison", "bison", "--symbolsPrefix", "cssyy", src_dir+"/css/CSSGrammar.y.in"])

  # step10, UserAgentStyleSheets.h PlugInsResources.h
  files = GetFileListDir(src_dir+"/css", ['.css'], "css/")
  files = RemoveItemMatch(files, ['BlackBerry', 'Qt', 'Efl', 'Win', 'Gtk', 'QuickTime'])
  os.chdir(src_dir)
  subprocess.call(["perl", "-Ibindings/scripts", "css/make-css-file-arrays.pl", "--defines", feature_list, \
  dst_dir+"/UserAgentStyleSheets.h", dst_dir+"/UserAgentStyleSheetsData.cpp"] + files)
  subprocess.call(["perl", "-Ibindings/scripts", "css/make-css-file-arrays.pl", "--defines", feature_list, \
  dst_dir+"/PlugInsResources.h", dst_dir+"/PlugInsResourcesData.cpp", "Resources/plugIns.js"])
  os.chdir(curr_dir)

  # step11, HTMLNames.h HTMLNames.cpp HTMLElementFactory.h HTMLElementFactory.cpp
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/html/HTMLTagNames.in", src_dir+"/html/HTMLAttributeNames.in", "--tags",\
  src_dir+"/html/HTMLTagNames.in", "--attrs", src_dir+"/html/HTMLAttributeNames.in", "--extraDefines", feature_list, "--factory",\
  "--wrapperFactory", "--outputDir", dst_dir])

  # step12, XMLNSNames.h XMLNames.h
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/xml/xmlnsattrs.in", "--attrs", src_dir+"/xml/xmlnsattrs.in", "--outputDir", dst_dir])
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_names.pl", src_dir+"/bindings/scripts/Hasher.pm",\
  src_dir+"/bindings/scripts/StaticString.pm", src_dir+"/xml/xmlattrs.in", "--attrs", src_dir+"/xml/xmlattrs.in", "--outputDir", dst_dir])

  # step13, EventHeaders.h EventInterfaces.h EventTargetHeaders.h EventTargetInterfaces.h
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_event_factory.pl", src_dir+"/dom/EventNames.in",\
  "--input", src_dir+"/dom/EventNames.in", "--outputDir", dst_dir])
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_event_factory.pl", src_dir+"/dom/EventTargetFactory.in",\
  "--input", src_dir+"/dom/EventTargetFactory.in", "--outputDir", dst_dir])

  # step14, ExceptionCodeDescription.h ExceptionCodeDescription.cpp ExceptionInterfaces.h ExceptionInterfaces.h   
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/dom/make_dom_exceptions.pl", src_dir+"/dom/DOMExceptions.in",\
  "--input", src_dir+"/dom/DOMExceptions.in", "--outputDir", dst_dir])

  # step15, SettingsMacros.h InternalSettingsGenerated.cpp InternalSettingsGenerated.h
  subprocess.call(["perl", "-I"+src_dir+"/bindings/scripts", src_dir+"/page/make_settings.pl", src_dir+"/page/Settings.in",\
  "--input", src_dir+"/page/Settings.in", "--outputDir", dst_dir])




  #for file_name in os.listdir(src_dir+"/runtime/"):
  #  if os.path.splitext(file_name)[1] in (".cpp"):
  #    p = subprocess.Popen("perl "+src_dir+"/create_hash_table "+src_dir+"/runtime/"+file_name+" -i", shell=True, stdout=subprocess.PIPE)
  #    WriteLinesToFile(p, dst_dir+"/"+os.path.splitext(file_name)[0]+".lut.h")

  return 0


# main
if __name__ == '__main__':
  sys.exit(Main(sys.argv[1], sys.argv[2]))
