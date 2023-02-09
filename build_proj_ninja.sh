#!/bin/sh

./tools/gyp/gyp --depth=./ all.gyp -f ninja --generator-output=proj
echo ""		
echo "Please change dir to \"proj\" and type \"ninja -C ./out/Debug\" or \"ninja -C ./out/Release\""
echo ""		
