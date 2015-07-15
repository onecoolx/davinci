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

# generate files
def Main(src_dir, dst_dir):
  # make output dir.
  MakeDirIfNotExists(dst_dir)

  # step 1, KeywordLookup.h 
  subprocess.call(["python", src_dir+"/KeywordLookupGenerator.py", src_dir+"/parser/Keywords.table", ">", dst_dir+"/KeywordLookup.h"])
  # step 2, RegExpJitTables.h 
  subprocess.call(["python", src_dir+"/create_regex_tables", ">", dst_dir+"/RegExpJitTables.h"])
  # step 3, Lexer.lut.h
  p = subprocess.Popen("perl "+src_dir+"/create_hash_table "+src_dir+"/parser/Keywords.table", shell=True, stdout=subprocess.PIPE)
  WriteLinesToFile(p, dst_dir+"/Lexer.lut.h")
  # step 4, %.lut.h
  file_list = []
  for file_name in os.listdir(src_dir+"/runtime/"):
    if os.path.splitext(file_name)[1] in (".cpp"):
      p = subprocess.Popen("perl "+src_dir+"/create_hash_table "+src_dir+"/runtime/"+file_name+" -i", shell=True, stdout=subprocess.PIPE)
      WriteLinesToFile(p, dst_dir+"/"+os.path.splitext(file_name)[0]+".lut.h")

  return 0


# main
if __name__ == '__main__':
  sys.exit(Main(sys.argv[1], sys.argv[2]))
