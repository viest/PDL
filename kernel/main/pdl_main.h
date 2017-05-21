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

#ifndef PHP_MAIN_H
#define PHP_MAIN_H

/**
 *  config class attribute
 */
#define PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE "configInstance"

/**
 *  vtiful_application.c -> zend_class_entry * vtiful_application_ce;
 */
extern zend_class_entry *pdl_main_ce;

/**
 * #define PDL_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(pdl_##module)
 */
PDL_STARTUP_FUNCTION(main);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */