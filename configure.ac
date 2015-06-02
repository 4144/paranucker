AC_INIT(astdumper, 1.0, akaras@inbox.ru)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])

AC_PROG_CXX
#AC_PROG_CC
#AM_PROG_CC_C_O
LT_INIT
AC_PROG_LIBTOOL
AC_ENABLE_SHARED
AC_DISABLE_STATIC

AC_ARG_ENABLE(
    [sanitize],
    AC_HELP_STRING(
        [--enable-sanitize],
        [
            Enables or Disables Sanitize Address Checking (SANITIZE is disabled by default)
        ]
    ),
    [
        enable_sanitize="$enableval"
        case $enableval in
            "no");;
            "yes");;
            *) AC_MSG_ERROR([[invalid argument --enable-sanitize=$disableval... stopping]]);;
        esac
    ],
    [enable_sanitize="no"]
)
AM_CONDITIONAL(ENABLE_SANITIZE, test x$enable_sanitize = xyes)

AC_ARG_ENABLE(
    [gprof],
    AC_HELP_STRING(
        [--enable-gprof],
        [
            Enables or Disables Gprof (disabled by default)
        ]
    ),
    [
        enable_gprof="$enableval"
        case $enableval in
            "no");;
            "yes");;
            *) AC_MSG_ERROR([[invalid argument --enable-gprof=$disableval... stopping]]);;
        esac
    ],
    [enable_gprof="no"]
)
AM_CONDITIONAL(ENABLE_GPROF, test x$enable_gprof = xyes)

AC_OUTPUT(Makefile src/Makefile)
