dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(event-emitter-cpp, 0.1)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11
AC_PROG_LIBTOOL

ACLOCAL_AMFLAGS = '-I m4'

AC_MSG_CHECKING([if release version needed])
AC_ARG_ENABLE([release], [ --enable-release 	enable release version],
[ 
	CPPFLAGS="-std=c++11 -O3 -Wall -fmessage-length=0 ${CPPFLAGS}";
	CXXFLAGS="";
	AC_MSG_RESULT([yes])
],
[ 
	CPPFLAGS="-std=c++11 -O0 -g3 -Wall -fmessage-length=0${CPPFLAGS}";
	CXXFLAGS="";
	AC_MSG_RESULT([no])
	AC_DEFINE( DEBUG) 
])

AC_ARG_WITH(
	[tests],
	[AS_HELP_STRING([--without-tests], [disable tests])],
	[with_tests=no],
	[with_tests=yes]
)

AM_CONDITIONAL([TESTS_ENABLED], [test x"$with_tests" != xno])

AS_IF(
	[test "x$with_tests" != xno],
	[
		AC_CHECK_LIB([gtest], [main], [],
		[ 
			echo "gtest failure." 
			exit -1
		])
		
		AC_CHECK_LIB([gmock], [main], [],
		[ 
			echo "gmock failure." 
			exit -1
		])
	]
)  


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_PREFIX_DEFAULT( "/usr/")

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES(Makefile 
				src/Makefile
				test/Makefile)
AC_OUTPUT

