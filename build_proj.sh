#!/bin/sh

./tools/gyp/gyp --depth=./ all.gyp --generator-output=proj
echo ""		
echo "Please change dir to \"proj\" and type \"make\" or \"make BUILDTYPE=Release\""
echo ""		
