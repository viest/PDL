PHP_ARG_WITH(pdl, for pdl support,
[  --with-pdl             Include pdl support])

if test "$PHP_PDL" != "no"; then
  PHP_NEW_EXTENSION(pdl, kernel/perform/pdl_perform.c \
    kernel/config/pdl_config.c \
    kernel/main/pdl_main.c \
    kernel/resource/pdl_resource.c \
    pdl.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
