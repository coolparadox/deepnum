#
# Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
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

bin_PROGRAMS = unit_tests
unit_tests_CPPFLAGS = -I@srcdir@/../../src
unit_tests_LDADD = @builddir@/../../src/.libs/libdn_clarith.la -lCppUTest -lCppUTestExt
unit_tests_SOURCES = \
	number_test.cpp \
	protocol/watcher_test.cpp \
	strategy/infinity_test.cpp \
	strategy/playback_test.cpp \
	strategy/ratio_test.cpp \
	strategy/strategy_mock.cpp \
	strategy/strategy_mock.hpp \
	unit_tests.cpp \
	util/compare_test.cpp

check: unit_tests
	echo
	echo "Running unit tests:"
	./unit_tests
	if test x$(ac_enable_coverage) = xyes ; then \
	echo "Code coverage summary:" && \
	cd $(top_builddir)/src && \
	find . -name '*.gcda' | xargs -r gcov -n -r && \
	echo ; fi
.SILENT: check
.PHONY: check
