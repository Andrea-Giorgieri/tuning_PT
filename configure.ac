AC_PREREQ([2.59])
AC_INIT([tuning_PT], [0.1.0], [andrea.giorgieri.pi@gmail.com])
AM_INIT_AUTOMAKE(subdir-objects)
AC_CONFIG_SRCDIR([./include/macro.h])
AC_CONFIG_HEADERS([config.h])

# overwrite default values
if test x${ac_cv_env_CFLAGS_set} != xset; then
  CFLAGS=''
fi 
if test x${ac_cv_env_CPPFLAGS_set} != xset; then
  CPPFLAGS=''
fi 

### GENERAL CHECKS

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC

# Checks for header files.

AC_CHECK_HEADERS([limits.h], [], [AC_MSG_ERROR([Required header limits.h not found.])])

AC_CHECK_HEADERS([math.h], [], [AC_MSG_ERROR([Required header math.h not found.])])

AC_CHECK_HEADERS([stdio.h], [], [AC_MSG_ERROR([Required header stdio.h not found.])])

AC_CHECK_HEADERS([stdlib.h], [], [AC_MSG_ERROR([Required header stdlib.h not found.])])

AC_CHECK_HEADERS([time.h], [], [AC_MSG_ERROR([Required header time.h not found.])])

AC_SEARCH_LIBS([sqrt], [m], [], 
     [AC_MSG_FAILURE([Required c mathematical library not found.])])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
