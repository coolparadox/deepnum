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

lib_LTLIBRARIES = libdn_clarith.la

libdn_clarith_la_SOURCES = \
	math.cpp \
	protocol/violation_error.cpp \
	protocol/watcher.cpp \
	reducer.cpp \
	strategy/exhaustion_error.cpp \
	strategy/infinity.cpp \
	strategy/ratio.cpp \
	strategy/unavailable_error.cpp \
	strategy/undefined_ratio_error.cpp

include_HEADERS = \
	math.hpp \
	protocol/protocol.hpp \
	protocol/violation_error.hpp \
	protocol/watcher.hpp \
	reducer.hpp \
	strategy/exhaustion_error.hpp \
	strategy/infinity.hpp \
	strategy/ratio.hpp \
	strategy/unavailable_error.hpp \
	strategy/undefined_ratio_error.hpp \
	strategy/strategy.hpp

