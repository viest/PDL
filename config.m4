PHP_ARG_WITH(pdl, for pdl support,
[  --with-pdl             Include pdl support])

if test "$PHP_PDL" != "no"; then

  for i in /usr /usr/local /opt; do
    if test -f $i/include/ffi/ffi.h; then
      FFI_DIR=$i
    fi
  done

  if test -z "$FFI_DIR"; then
    AC_MSG_ERROR([libffi not installed])
  fi

  PHP_ADD_LIBRARY_WITH_PATH(ffi, $FFI_DIR/lib, FFI_SHARED_LIBADD)
  PHP_ADD_INCLUDE($FFI_DIR/include)

  AC_MSG_RESULT([found in $FFI_DIR])
  AC_DEFINE(HAVE_FFI, 1, [libffi found and included])

  PHP_NEW_EXTENSION(pdl, kernel/perform/pdl_perform.c \
    kernel/config/pdl_config.c \
    kernel/main/pdl_main.c \
    kernel/resource/pdl_resource.c \
    pdl.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_SUBST(FFI_SHARED_LIBADD)
fi
