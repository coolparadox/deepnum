#
# Copyright 2019 Rafael Lorandi <coolparadox@gmail.com>
#
# This file is part of dn-clarith, a library for performing arithmetic
# in continued logarithm representation.
# 
# dn-clarith is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# dn-clarith is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with dn-clarith.  If not, see <http://www.gnu.org/licenses/>
#

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = integration_tests
integration_tests_CPPFLAGS = -I@srcdir@/../../src
integration_tests_LDADD = @builddir@/../../src/.libs/libdn_clarith.la -lCppUTest -lCppUTestExt
integration_tests_SOURCES = \
	integration_tests.cpp \
	ratio_test.cpp

tests: integration_tests
	echo
	echo "Running integration tests:"
	./integration_tests
.SILENT: tests
.PHONY: tests
