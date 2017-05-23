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

#include "../../php_pdl.h"
#include "../config/pdl_config.h"
#include "../perform/pdl_perform.h"
#include "pdl_main.h"

/** var_dump */
#include "ext/standard/php_var.h"

zend_class_entry *pdl_main_ce;

ZEND_BEGIN_ARG_INFO_EX(pdl_main_construct_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(pdl_main_open_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, library)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(pdl_main_call_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, function_name)
                ZEND_ARG_ARRAY_INFO(0, parameter, 0)
                ZEND_ARG_INFO(0, return_type)
ZEND_END_ARG_INFO()

//ZEND_BEGIN_ARG_INFO_EX(pdl_main_call_arginfo, 0, 0, 4)
//                ZEND_ARG_INFO(0, library)
//                ZEND_ARG_INFO(0, function_name)
//                ZEND_ARG_ARRAY_INFO(0, parameter, 0)
//                ZEND_ARG_INFO(0, return_type)
//ZEND_END_ARG_INFO()

/**
 * {{{ proto Vikin\PDL::__construct()
*/
PHP_METHOD(PDL, __construct) {

    zval *config_arg, *config_instance, rv;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(config_arg)
 	ZEND_PARSE_PARAMETERS_END();

    config_instance = zend_read_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE), 0, &rv TSRMLS_DC);

    if(UNEXPECTED(Z_TYPE_P(config_arg) == IS_ARRAY)) {

        if(UNEXPECTED(Z_TYPE_P(config_instance) == IS_NULL)) {
            object_init_ex(config_instance, pdl_config_ce);

            zend_update_property(pdl_config_ce, config_instance, ZEND_STRL(PDL_CONFIG_CLASS_ATTRIBUTE_CONFIG), config_arg TSRMLS_CC);
            zend_update_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE), config_instance TSRMLS_CC);
        }

    }
}
/** }}} */

/**
 * {{{ proto Vikin\PDL::open()
*/
PHP_METHOD(PDL, open) {

    zend_string *library, *directory, *library_path;
    zval *config_instance, *config_array, *path_config_tmp;
    zval rv1, rv2, res_tmp;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(library)
    ZEND_PARSE_PARAMETERS_END();

    config_instance = zend_read_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE), 0, &rv1 TSRMLS_DC);
    config_array    = zend_read_property(pdl_config_ce, config_instance, ZEND_STRL(PDL_CONFIG_CLASS_ATTRIBUTE_CONFIG), 0, &rv2 TSRMLS_DC);

    directory       = zend_string_init("directory", sizeof("directory")-1, 0);
    path_config_tmp = zend_hash_find(Z_ARRVAL_P(config_array), directory);

    if (EXPECTED(path_config_tmp == NULL)) {
        php_error_docref(NULL, E_ERROR, "PDL warning: Configuration directory does not exist\n");
        RETURN_NULL();
    }

    if(EXPECTED(Z_TYPE_P(path_config_tmp) != IS_STRING)) {
        php_error_docref(NULL, E_ERROR, "PDL warning: Directory configuration must be a string\n");
        RETURN_NULL();
    }

    // 拼接路径及动态库名
    library_path = strpprintf(0, "%s/%s", Z_STRVAL_P(path_config_tmp), ZSTR_VAL(library));
    ZVAL_RES(&res_tmp, LIBRARY_OPEN(library_path, library));

    zend_update_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_HANDLE_INSTANCE), &res_tmp TSRMLS_CC);

    ZVAL_COPY(return_value, getThis());
}
/** }}} */

/**
 * {{{ proto Vikin\PDL::call()
*/
PHP_METHOD(PDL, call) {

    zend_string *function_name, *return_type;
    zval *parameter, *res;
    zval rv;

    ZEND_PARSE_PARAMETERS_START(3, 3)
            Z_PARAM_STR(function_name)
            Z_PARAM_ARRAY(parameter)
            Z_PARAM_STR(return_type)
    ZEND_PARSE_PARAMETERS_END();

    res = zend_read_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_HANDLE_INSTANCE), 0, &rv TSRMLS_DC);

    if(EXPECTED(Z_TYPE_P(res) != IS_RESOURCE)) {
        php_error_docref(NULL, E_ERROR, "PDL warning: handle is missing\n");
        RETURN_NULL();
    }

    LIBRARY_CALL(res, ZSTR_VAL(function_name), PDL_RETURN_INT, parameter);
}
/** }}} */

/**
 * {{{ proto Vikin\PDL::call()
*/
//PHP_METHOD(PDL, call) {
//
//    zend_string *library, *return_type, *function_name, *library_path, *directory;
//    zval *parameter, *config_instance, *config_array, *path_config_tmp;
//    zval rv1, rv2;
//
//    ZEND_PARSE_PARAMETERS_START(4, 4)
//            Z_PARAM_STR(library)
//            Z_PARAM_STR(function_name)
//            Z_PARAM_ARRAY(parameter)
//            Z_PARAM_STR(return_type)
//    ZEND_PARSE_PARAMETERS_END();
//
//    config_instance = zend_read_property(pdl_main_ce, getThis(), ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE), 0, &rv1 TSRMLS_DC);
//    config_array    = zend_read_property(pdl_config_ce, config_instance, ZEND_STRL(PDL_CONFIG_CLASS_ATTRIBUTE_CONFIG), 0, &rv2 TSRMLS_DC);
//
//    directory       = zend_string_init("directory", sizeof("directory")-1, 0);
//    path_config_tmp = zend_hash_find(Z_ARRVAL_P(config_array), directory);
//
//    if (EXPECTED(path_config_tmp == NULL)) {
//        php_error_docref(NULL, E_ERROR, "PDL warning: Configuration directory does not exist\n");
//        RETURN_NULL();
//    }
//
//    if(Z_TYPE_P(path_config_tmp) != IS_STRING) {
//        php_error_docref(NULL, E_ERROR, "PDL warning: Directory configuration must be a string\n");
//        RETURN_NULL();
//    }
//
//    // 拼接路径及动态库名
//    library_path = strpprintf(0, "%s/%s", Z_STRVAL_P(path_config_tmp), ZSTR_VAL(library));
//
//    LIBRARY_CALL(ZSTR_VAL(library_path), ZSTR_VAL(library), ZSTR_VAL(function_name), PDL_RETURN_INT, parameter);
//
//
//    zend_string_free(library_path);
//    zend_string_free(directory);
//}
/** }}} */

/**
 * {{{ pdl_methods
*/
zend_function_entry pdl_main_methods[] = {
        PHP_ME(PDL, __construct, pdl_main_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(PDL, open,        pdl_main_open_arginfo,      ZEND_ACC_PUBLIC)
        PHP_ME(PDL, call,        pdl_main_call_arginfo,      ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/** }}} */


/**
 * {{{ PDL_STARTUP_FUNCTION
 * 这里的参数必须和PDL_STARTUP_MODULE函数中的参数一致
*/
PDL_STARTUP_FUNCTION(main) {
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vikin", "PDL", pdl_main_methods);

    pdl_main_ce = zend_register_internal_class_ex(&ce, NULL);
    pdl_main_ce->ce_flags |= ZEND_ACC_FINAL;

    zend_declare_property_null(pdl_main_ce, ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_CONFIG_INSTANCE), ZEND_ACC_PROTECTED);
    zend_declare_property_null(pdl_main_ce, ZEND_STRL(PDL_MAIN_CLASS_ATTRIBUTE_HANDLE_INSTANCE), ZEND_ACC_PROTECTED);

    return SUCCESS;
}
/** }}} */