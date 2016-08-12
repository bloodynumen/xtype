dnl $Id$
dnl config.m4 for extension xtype

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(xtype, for xtype support,
dnl Make sure that the comment is aligned:
dnl [  --with-xtype             Include xtype support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(xtype, whether to enable xtype support,
Make sure that the comment is aligned:
[  --enable-xtype           Enable xtype support])

if test "$PHP_XTYPE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-xtype -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/xtype.h"  # you most likely want to change this
  dnl if test -r $PHP_XTYPE/$SEARCH_FOR; then # path given as parameter
  dnl   XTYPE_DIR=$PHP_XTYPE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for xtype files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       XTYPE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$XTYPE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the xtype distribution])
  dnl fi

  dnl # --with-xtype -> add include path
  dnl PHP_ADD_INCLUDE($XTYPE_DIR/include)

  dnl # --with-xtype -> check for lib and symbol presence
  dnl LIBNAME=xtype # you may want to change this
  dnl LIBSYMBOL=xtype # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XTYPE_DIR/$PHP_LIBDIR, XTYPE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_XTYPELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong xtype lib version or lib not found])
  dnl ],[
  dnl   -L$XTYPE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(XTYPE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(xtype, xtype.c, $ext_shared)
fi


if test -z "$PHP_DEBUG"; then
        AC_ARG_ENABLE(debug,
                [--enable-debg  compile with debugging system],
                [PHP_DEBUG=$enableval], [PHP_DEBUG=no]
        )
fi
