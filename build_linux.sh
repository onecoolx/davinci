#!/bin/sh

./tools/gyp/gyp --depth=./ all.gyp -f ninja --generator-output=proj
cp ./tools/ninja-build.sh ./proj/
echo ""		
echo "Please change dir to \"proj\" and type \"./ninja-build.sh Debug\" or \"./ninja-build.sh Release\""
echo ""		
