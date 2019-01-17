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

AC_PREREQ([2.69])
LT_PREREQ([2.4.2])
AC_INIT([dn-clarith],[0.0.0],[coolparadox@gmail.com])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/number.cpp])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([PROJECT_BRIEF], ["continued logarithm arithmetic"])

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

AC_MSG_CHECKING([whether to build documentation])
AC_ARG_ENABLE(
    [doc],
    [AS_HELP_STRING([--enable-doc], [build html documentation [default=no]])],
    [ac_enable_doc=$enableval],
    [ac_enable_doc=no]
)
AC_MSG_RESULT([$ac_enable_doc])

AS_VAR_IF([ac_enable_doc], [yes], [
    AC_SUBST([HTML_DOC], [doc/html/index.html])

    AC_CHECK_PROG([has_doxygen], [doxygen], [yes], [no])
    AS_VAR_IF([has_doxygen], [no], [
        AC_MSG_ERROR([documentation requires doxygen])
    ])

    AC_CHECK_PROG([has_graphviz], [dot], [yes], [no])
    AS_VAR_IF([has_graphviz], [no], [
        AC_MSG_ERROR([documentation requires graphviz])
    ])

    AC_CONFIG_FILES([Doxyfile])
])

test_wanted='no'

AC_MSG_CHECKING([whether to build unit tests])
AC_ARG_ENABLE(
    [check],
    [AS_HELP_STRING([--enable-check], [build unit tests [default=yes]])],
    [ac_enable_check=$enableval],
    [ac_enable_check=yes]
)
AC_MSG_RESULT([$ac_enable_check])

AS_VAR_IF([ac_enable_check], [yes], [
    test_wanted='yes'
    AC_SUBST([UNIT_TEST_SUBDIR], [test/unit])
    AC_CONFIG_FILES([test/unit/Makefile])
])

AC_MSG_CHECKING([whether to build integration tests])
AC_ARG_ENABLE(
    [tests],
    [AS_HELP_STRING([--enable-tests], [build integration tests [default=no]])],
    [ac_enable_tests=$enableval],
    [ac_enable_tests=no]
)
AC_MSG_RESULT([$ac_enable_tests])

AS_VAR_IF([ac_enable_tests], [yes], [
    test_wanted='yes'
    AC_SUBST([INTEGRATION_TEST_SUBDIR], [test/integration])
    AC_CONFIG_FILES([test/integration/Makefile])
])

AS_VAR_IF([test_wanted], [yes], [

    AC_CHECK_HEADER([CppUTest/CommandLineTestRunner.h], [], [
        AC_MSG_ERROR([tests require CppUTest])
    ])

    AC_CHECK_HEADER([CppUTest/Utest.h], [], [
        AC_MSG_ERROR([tests require CppUTest])
    ])

    AC_CHECK_HEADER([CppUTest/UtestMacros.h], [], [
        AC_MSG_ERROR([tests require CppUTest])
    ])

    AC_MSG_CHECKING([for CommandLineTestRunner::RunAllTests in -lCppUTest])
    LIBS_ORIG=$LIBS
    LIBS="$LIBS -lCppUTest"
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
            [[#include <CppUTest/CommandLineTestRunner.h>]],
            [[CommandLineTestRunner::RunAllTests(0, static_cast<char**>(nullptr));]]
        )],
        [AC_MSG_RESULT([yes])],
        [
            AC_MSG_RESULT([no])
            AC_MSG_ERROR([tests require CppUTest])
        ]
    )
    LIBS=$LIBS_ORIG

])

AC_MSG_CHECKING([whether to build for code coverage detection])
AC_ARG_ENABLE(
    [coverage],
    [AS_HELP_STRING([--enable-coverage], [build for code coverage detection [default=no]])],
    [ac_enable_coverage=$enableval],
    [ac_enable_coverage=no]
)
AC_MSG_RESULT([$ac_enable_coverage])

AS_VAR_IF([ac_enable_coverage], [yes], [
    CPPFLAGS="$CPPFLAGS --coverage"
    LDFLAGS="$LDFLAGS --coverage"
    AC_SUBST([ac_enable_coverage], [$ac_enable_coverage])
])

AC_MSG_CHECKING([whether to instrument Number class and make it sanity check its own output])
AC_ARG_ENABLE(
    [number_sanity_check],
    [AS_HELP_STRING([--enable-number-sanity-check], [instrument Number class and make it sanity check its own output [default=yes]])],
    [ac_number_sanity_check=$enableval],
    [ac_number_sanity_check=yes]
)
AC_MSG_RESULT([$ac_number_sanity_check])
number_sanity_check=0
AS_VAR_IF([ac_number_sanity_check], [yes], [number_sanity_check=1])
AC_DEFINE_UNQUOTED([NUMBER_SANITY_CHECK], [$number_sanity_check], [Define to 1 to instrument Number class and make it sanity check its own output.])

AX_CXX_COMPILE_STDCXX_17
AS_VAR_IF([HAVE_CXX17], [1], [], [
    AC_MSG_ERROR([compiler with C++17 support not found])
])

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
