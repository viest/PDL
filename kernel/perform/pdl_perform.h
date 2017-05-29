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

#ifndef PDL_PERFORM_H
#define PDL_PERFORM_H

#define PDL_RETURN_INT    11
#define PDL_RETURN_DOUBLE 22
#define PDL_RETURN_CHAR   33

#define LIBRARY_OPEN(path, handle_name) __library_open(path, handle_name)
#define LIBRARY_CALL(res, function_name, return_type, param, return_value) __library_call(res, function_name, return_type, param, return_value)
//#define LIBRARY_CALL(path, handle_name, function_name, return_type, param) __library_call(path, handle_name, function_name, return_type, param)

zend_resource * __library_open(zend_string *path, zend_string *handle_name);
int __library_call(zval *res, char *function_name, char *return_type, zval *param, zval *return_value);

//int __library_call(char *path, char *handle_name, char *function_name, long return_type, zval *param);

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */