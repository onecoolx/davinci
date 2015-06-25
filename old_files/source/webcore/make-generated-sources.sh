#!/bin/sh
export SOURCE_ROOT=$PWD
export SRCROOT=$PWD
export WebCore=$PWD
export CREATE_HASH_TABLE="$SRCROOT/../javascript/kjs/create_hash_table"

mkdir -p buildsrc &&
make -C buildsrc -f ../DerivedSources.make
