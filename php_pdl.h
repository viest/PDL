/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
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

/* $Id$ */

#ifndef PHP_PDL_H
#define PHP_PDL_H

extern zend_module_entry pdl_module_entry;
#define phpext_pdl_ptr &pdl_module_entry

#define PHP_PDL_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_PDL_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PDL_API __attribute__ ((visibility("default")))
#else
#	define PHP_PDL_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/**
 *  Starter definition
 */
#define PDL_STARTUP_MODULE(module) ZEND_MODULE_STARTUP_N(pdl_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define PDL_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(pdl_##module)

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(pdl)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(pdl)
*/

/* Always refer to the globals in your function as PDL_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define PDL_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(pdl, v)

#if defined(ZTS) && defined(COMPILE_DL_PDL)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_PDL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
