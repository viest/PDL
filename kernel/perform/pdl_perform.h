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

void __library_open(char *path, char *handle_name);
int __library_func_name(char *handle_name, char *function_name);
void __library_call(char *return_type, void *return_val, void *handle, zval *param);
void __library_close(void *handle);

#define LIBRARY_OPEN(path, handle_name)       __library_open(path, handle_name)
#define LIBRARY_FUNC_NAME(handle_name, function_name) __library_func_name(handle_name, function_name)

#define LIBRARY_CALL(handle, return_type, return_val, params) __library_call(return_type, return_val, handle, params TSRMLS_CC)
#define LIBRARY_CLOSE(handle) __library_close(handle)

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */