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
#include "pdl_perform.h"
#include <dlfcn.h>


int __library_call(char *path, char *handle_name, char *function_name, long return_type, zval *param) {
    void *lib_handle, *func_handle, *return_val;
    int int_val[10];
    zval *tmp_val;
    zend_ulong index;

    char *hash_key = emalloc(strlen(handle_name)-2);
    memset(hash_key, '\0', strlen(handle_name)-2);
    memcpy(hash_key, handle_name, strlen(handle_name)-3);

    lib_handle = dlopen(path, RTLD_LAZY);

    if(!lib_handle) {
        php_error_docref(NULL, E_ERROR, "PDL warning: Unable to load dynamic library '%s' - %s\n", path, dlerror());
        dlerror();
        return FAILURE;
    }

    func_handle = dlsym(lib_handle, function_name);

    if(!func_handle) {
        php_error_docref(NULL, E_ERROR, "PDL warning: Unable to get the dynamic link library %s method\n", function_name);
        dlclose(lib_handle);
        return FAILURE;
    }

    switch (return_type) {
        case 0:
            return_val  = (char *)return_val;
            func_handle = (char *)func_handle;
            break;
        case 1:
            return_val  = (long *)return_val;
            func_handle = (long *)func_handle;
            break;
        case 2:
            return_val  = (double *)return_val;
            func_handle = (double *)func_handle;
            break;
    }

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(param), index, tmp_val){
                switch (Z_TYPE_P(tmp_val)) {
                    case IS_STRING :
                        break;
                    case IS_LONG :
                        int_val[index] = Z_LVAL_P(tmp_val);
                        break;
                    case IS_DOUBLE :
                        break;
                }
            }ZEND_HASH_FOREACH_END();

    __asm__ __volatile__ (
            "mov %2, %%rdi;\n"
            "mov %3, %%rsi;\n"
            "call *%1;\n"
            "mov %%rax, %0;\n"
            :"=m"(return_val)
            :"m"(func_handle), "m"(int_val[0]), "m"(int_val[1])
    );

    php_printf("结果：%d\n", return_val);

    dlclose(lib_handle);
    efree(hash_key);

    return SUCCESS;
}

