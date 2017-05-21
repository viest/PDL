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
#include "pdl_config.h"

/** var_dump */
#include "ext/standard/php_var.h"

zend_class_entry *pdl_config_ce;

ZEND_BEGIN_ARG_INFO_EX(pdl_config_construct_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

/**
 * {{{ proto Vikin\PDL\Kernel\Config::__construct()
 * application 类的 构造函数
*/
PHP_METHOD(pdl_config, __construct) { }
/** }}} */

/**
 * {{{ proto Vikin\PDL\Kernel\Config::getInstance()
*/
PHP_METHOD(pdl_config, getInstance) {
    zval *instance, *config_arg;

    instance = zend_read_static_property(pdl_config_ce, ZEND_STRL("instance"), 0);

    if(Z_TYPE_P(instance) == IS_NULL) {
        ZEND_PARSE_PARAMETERS_START(1, 1)
                Z_PARAM_ARRAY(config_arg)
        ZEND_PARSE_PARAMETERS_END();

        object_init_ex(instance, pdl_config_ce);
        zend_update_static_property(pdl_config_ce, ZEND_STRL("instance"), instance TSRMLS_CC);
        zend_update_property(pdl_config_ce, instance, ZEND_STRL(PDL_CONFIG_CLASS_ATTRIBUTE_CONFIG), config_arg TSRMLS_CC);
    } else {
        RETURN_ZVAL(instance, 1, 0);
    }
    RETURN_ZVAL(instance, 1, 0);

    zval_ptr_dtor(instance);
}
/** }}} */


/**
 * {{{ config_methods
*/
zend_function_entry config_methods[] = {
        PHP_ME(pdl_config, getInstance, pdl_config_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_MALIAS(pdl_config, __construct, getInstance, pdl_config_construct_arginfo, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/** }}} */


/**
 * {{{ PDL_STARTUP_FUNCTION
 * 这里的参数必须和PDL_STARTUP_MODULE函数中的参数一致
*/
PDL_STARTUP_FUNCTION(config) {
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vikin\\PDL\\Kernel", "Config", config_methods);

    pdl_config_ce = zend_register_internal_class_ex(&ce, NULL);
    pdl_config_ce->ce_flags |= ZEND_ACC_FINAL;

    zend_declare_property_null(pdl_config_ce, ZEND_STRL(PDL_CONFIG_CLASS_ATTRIBUTE_CONFIG), ZEND_ACC_PROTECTED);
    zend_declare_property_null(pdl_config_ce, ZEND_STRL("instance"),   ZEND_ACC_PROTECTED | ZEND_ACC_STATIC);

    return SUCCESS;
}
/** }}} */