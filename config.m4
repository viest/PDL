dnl $Id$
dnl config.m4 for extension pdl

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

 PHP_ARG_WITH(pdl, for pdl support,
dnl Make sure that the comment is aligned:
 [  --with-pdl             Include pdl support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(pdl, whether to enable pdl support,
dnl Make sure that the comment is aligned:
dnl [  --enable-pdl           Enable pdl support])

if test "$PHP_PDL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-pdl -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pdl.h"  # you most likely want to change this
  dnl if test -r $PHP_PDL/$SEARCH_FOR; then # path given as parameter
  dnl   PDL_DIR=$PHP_PDL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pdl files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PDL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PDL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pdl distribution])
  dnl fi

  dnl # --with-pdl -> add include path
  dnl PHP_ADD_INCLUDE($PDL_DIR/include)

  dnl # --with-pdl -> check for lib and symbol presence
  dnl LIBNAME=pdl # you may want to change this
  dnl LIBSYMBOL=pdl # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PDL_DIR/$PHP_LIBDIR, PDL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PDLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pdl lib version or lib not found])
  dnl ],[
  dnl   -L$PDL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PDL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pdl, kernel/perform/pdl_perform.c \
    kernel/config/pdl_config.c \
    kernel/main/pdl_main.c \
    pdl.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
