#!/bin/env bash
set -e -u -o pipefail
WHEREAMI=$( dirname $( realpath "$0" ) )
set -x
cd ${WHEREAMI}/..
make clean || :
CXXFLAGS='-pg' ./configure --enable-test --disable-check --disable-shared
make -j4
cd test/integration
./integration_tests 'TEST(RatioTest, ComparisonMatch)'
gprof integration_tests gmon.out >../../scratch/RatioTestComparisonMatch.gprof
