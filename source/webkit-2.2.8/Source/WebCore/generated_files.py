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

# write file
def WriteLinesToFile(p, path):
  f = open(path, "wb")
  contents = p.stdout.readlines()
  for line in contents:
    f.write(line)
  f.close()

# read file
def ReadLinesFromFile(path):
  ret = ''
  f = open(path, "r")
  contents = f.readlines()
  for line in contents:
    ret = ret + line.strip('\n')
  f.close()
  return ret

# generate files
def Main(src_dir, dst_dir):
  # make output dir.
  MakeDirIfNotExists(dst_dir)

  feature_list = ReadLinesFromFile(src_dir+"/WebKitFeatures.txt")

  # step 1, XPathGrammar.h XPathGrammar.cpp
  subprocess.call(["perl", src_dir+"/css/makegrammar.pl", "--outputDir" ,dst_dir, "--bison", "bison", "--symbolsPrefix", "xpathyy", src_dir+"/xml/XPathGrammar.y"])

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

  # step 4, %.lut.h
  #file_list = []
  #for file_name in os.listdir(src_dir+"/runtime/"):
  #  if os.path.splitext(file_name)[1] in (".cpp"):
  #    p = subprocess.Popen("perl "+src_dir+"/create_hash_table "+src_dir+"/runtime/"+file_name+" -i", shell=True, stdout=subprocess.PIPE)
  #    WriteLinesToFile(p, dst_dir+"/"+os.path.splitext(file_name)[0]+".lut.h")

  return 0


# main
if __name__ == '__main__':
  sys.exit(Main(sys.argv[1], sys.argv[2]))
