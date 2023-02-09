#!/bin/sh

cd ../
python ./tools/generated_javascriptcore_files.py ./source/webkit-2.2.8/Source/JavaScriptCore ./source/webkit-2.2.8/Source/JavaScriptCore/Generated
python ./tools/generated_webcore_files.py ./source/webkit-2.2.8/Source/WebCore Generated
cd -

ninja -j32 -C ./out/$1