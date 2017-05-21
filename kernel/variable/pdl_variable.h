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

#ifndef PDL_VARIABLE_H
#define PDL_VARIABLE_H

#define PDL_PARAMS_NUM(var) sizeof(var)/sizeof(zval *)

void _zval_to_long(zval *parameter, long *return_val);
void _zval_to_int(zval *parameter, int *return_val);

void _zval_to_double(zval *parameter, double *return_val);

void _zval_to_bool(zval *parameter, int *return_val);

void _zval_to_char(zval *parameter, char *return_val);
void _zend_string_to_char(zend_string *parameter, char *return_val);

#define ZVAL_TO_LONG(parameter, return_val)                _zval_to_long(parameter, return_val)
#define ZVAL_TO_INT(parameter, return_val)                 _zval_to_int(parameter, return_val)
#define ZVAL_TO_DOUBLE(parameter, return_val)              _zval_to_double(parameter, return_val)
#define ZVAL_TO_BOLL(parameter, return_val)                _zval_to_long(parameter, return_val)
#define ZVAL_TO_CHAR(parameter, length, return_val)        _zval_to_char(parameter, return_val)
#define ZEND_STRING_TO_CHAR(parameter, length, return_val) _zend_string_to_char(parameter, return_val)

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */