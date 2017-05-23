/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Jiexin Wang   <vikindev@outlook.com>                         |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"

#include "pdl_resource.h"

/** var_dump */
#include "ext/standard/php_var.h"

/** {{{ _pdl_resource_close */
void __pdl_resource_close(zend_resource *resource TSRMLS_DC)
{
    PDL_RES *res = (PDL_RES *)resource->ptr;

    zend_string_free(res->path);
    zend_string_free(res->library_name);
    dlclose(&(res->handle));

    efree(res);
}
/** }}} */