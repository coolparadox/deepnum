#
# Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
#
# This file is part of coolparadox-number-reducer, a library for handling
# rational numbers in continued log format.
# 
# coolparadox-number-reducer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# coolparadox-number-reducer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with coolparadox-number-reducer.  If not, see <http://www.gnu.org/licenses/>
#

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = unit_tests
unit_tests_CPPFLAGS = -I@srcdir@/../../src
unit_tests_LDADD = @builddir@/../../src/.libs/libreducer.la -lCppUTest
unit_tests_SOURCES = \
	unit_tests.cpp \
	strategy/infinite_test.cpp

check: @builddir@/unit_tests
	@builddir@/unit_tests
