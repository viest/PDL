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


void __library_open(char *path, char *handle_name) {
    void *handle;

    char *hash_key = emalloc(strlen(handle_name)-2);
    memset(hash_key, '\0', strlen(handle_name)-2);
    memcpy(hash_key, handle_name, strlen(handle_name)-3);

    zend_string *eg_hash_key = strpprintf(0, "pdl_handle_%s", hash_key);
    handle = zend_hash_find_ptr(&EG(persistent_list), eg_hash_key);
    zend_string_free(eg_hash_key);

    if(!handle) {

        handle = dlopen(path, RTLD_LAZY);

        if(!handle) {
            php_error_docref(NULL, E_ERROR, "PDL warning: Unable to open the dynamic link library, %s\n", dlerror());
        } else {
            php_printf("%s\n", ZSTR_VAL(eg_hash_key));
//            zend_hash_add_new_ptr(&EG(persistent_list), eg_hash_key, handle);
        }
    }

    efree(hash_key);
}

int __library_func_name(char *handle_name, char *function_name) {
    void *handle = NULL, *function_handle = NULL;

    zend_string *hash_key = strpprintf(0, "PDL_handle_%s", handle_name);
    handle = zend_hash_find_ptr(&EG(persistent_list), hash_key);

    function_handle = dlsym(handle, function_name);

    if (function_handle == NULL) {
        php_error_docref(NULL, E_ERROR, "PDL warning: Unable to get the dynamic link library %s method, %s\n", function_name, dlerror());
        return FAILURE;
    }

    zend_string_free(hash_key);

    return SUCCESS;
}

void __library_call(char *return_type, void *return_val, void *handle, zval *param) {
    zval *tmp_val;
    zend_ulong index;
    int int_val[10];
    double double_val[10];

    printf("\n%s\n", return_type);

    // 检查返回值类型
    switch (1) {
        case 0:
            return_val = (char *)return_val;
            handle     = (char *)handle;
            break;
        case 1:
            return_val = (long *)return_val;
            handle     = (long *)handle;
            break;
        case 2:
            return_val = (double *)return_val;
            handle     = (double *)handle;
            break;
    }

    // 转换参数
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(param), index, tmp_val){
                switch (Z_TYPE_P(tmp_val)) {
                    case IS_STRING :
                        break;
                    case IS_LONG :
                        int_val[index] = Z_LVAL_P(tmp_val);
                        break;
                    case IS_DOUBLE :
                        double_val[index] = Z_DVAL_P(tmp_val);
                        break;
                }
            }ZEND_HASH_FOREACH_END();

    // 调用动态库
    __asm__ __volatile__ (
            "mov %2, %%rdi;\n"
            "mov %3, %%rsi;\n"
            "call *%1;\n"
            "mov %%rax, %0;\n"
            :"=m"(return_val)
            :"m"(handle), "m"(int_val[0]), "m"(int_val[1])
    );
}

void __library_close(void *handle) {
    dlclose(handle);
}

