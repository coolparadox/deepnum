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

SUBDIRS = src @TEST_SUBDIR@
dist_doc_DATA = README

ACLOCAL_AMFLAGS = -I m4

totalclean: maintainer-clean
	-rm -f *.in~
	-rm -f aclocal.m4 ar-lib compile config.guess config.h.in config.sub
	-rm -f configure depcomp install-sh ltmain.sh missing Makefile.in
	-rm -f src/Makefile.in test/unit/Makefile.in
	-rm -rf m4/ doc/
	-rm -rf test/unit/.deps/ test/unit/Makefile test/unit/strategy/.deps/

doc:
	doxygen
.PHONY: doc
