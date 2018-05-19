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
LT_PREREQ([2.4.2])
AC_INIT([coolparadox-number-reducer],[0.0.0],[coolparadox@gmail.com])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/protocol.hpp])
AC_CONFIG_HEADERS([config.h])
AC_SUBST([PROJECT_BRIEF], ["continued log arithmetic"])

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
        AC_MSG_ERROR([documentation building requires doxygen])
    ])
    AC_CONFIG_FILES([Doxyfile])
])

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
    AC_SUBST([UNIT_TESTER], [unit_tests])

    AC_CHECK_HEADER([CppUTest/CommandLineTestRunner.h], [], [
        AC_MSG_ERROR([unit tests require CppUTest])
    ])

    AC_CHECK_HEADER([CppUTest/Utest.h], [], [
        AC_MSG_ERROR([unit tests require CppUTest])
    ])

    AC_CHECK_HEADER([CppUTest/UtestMacros.h], [], [
        AC_MSG_ERROR([unit tests require CppUTest])
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
            AC_MSG_ERROR([unit tests require CppUTest])
        ]
    )
    LIBS=$LIBS_ORIG

    AC_CONFIG_FILES([test/unit/Makefile])
])

AX_CXX_COMPILE_STDCXX_17

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
