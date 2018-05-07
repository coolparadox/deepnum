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

AC_PREREQ([2.69])
LT_PREREQ([2.4.6])
AC_INIT([coolparadox-number-reducer],[0.0.0],[coolparadox@gmail.com])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/protocol.hpp])
AC_CONFIG_HEADERS([config.h])

AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AM_PROG_AR
LT_INIT
AC_PROG_CXX
AC_LANG([C++])

AC_CHECK_HEADER_STDBOOL

AC_MSG_CHECKING([whether to build unit tests])
AC_ARG_ENABLE(
    [check],
    [AS_HELP_STRING([--enable-check], [build unit tests [default=no]])],
    [ac_enable_check=$enableval],
    [ac_enable_check=no]
)
AC_MSG_RESULT([$ac_enable_check])

AS_VAR_IF([ac_enable_check], [yes], [
    AC_SUBST([TEST_SUBDIR], [test/unit])
# 
#     AC_CHECK_HEADER([gtest/gtest.h], [], [
#         AC_MSG_ERROR([unit tests require Google Test])
#     ])
# 
#     AC_MSG_CHECKING([for testing::InitGoogleTest in -lgtest])
#     LIBS_ORIG=$LIBS
#     LIBS="$LIBS -lgtest"
#     AC_LINK_IFELSE(
#         [AC_LANG_PROGRAM(
#             [[#include <gtest/gtest.h>]],
#             [[testing::InitGoogleTest(nullptr, static_cast<char**>(nullptr));]]
#         )],
#         [AC_MSG_RESULT([yes])],
#         [
#             AC_MSG_RESULT([no])
#             AC_MSG_ERROR([unit tests require Google Test])
#         ]
#     )
#     LIBS=$LIBS_ORIG
# 
#     AC_CHECK_HEADER([gmock/gmock.h], [], [
#         AC_MSG_ERROR([unit tests require Google Mock])
#     ])
# 
#     AC_MSG_CHECKING([for testing::InitGoogleMock in -lgmock])
#     LIBS_ORIG=$LIBS
#     LIBS="$LIBS -lgmock"
#     AC_LINK_IFELSE(
#         [AC_LANG_PROGRAM(
#             [[#include <gmock/gmock.h>]],
#             [[testing::InitGoogleMock(nullptr, static_cast<char**>(nullptr));]]
#         )],
#         [AC_MSG_RESULT([yes])],
#         [
#             AC_MSG_RESULT([no])
#             AC_MSG_ERROR([unit tests require Google Mock])
#         ]
#     )
#     LIBS=$LIBS_ORIG
# 
])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/unit/Makefile])
AC_OUTPUT
