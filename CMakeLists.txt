cmake_minimum_required(VERSION 3.6)
project(PDL)

include_directories(
        /Users/vikin/PHP-7.0.0/main
        /Users/vikin/PHP-7.0.0/Zend
        /Users/vikin/PHP-7.0.0
)

set(SOURCE_FILES
        kernel/config/pdl_config.c
        kernel/config/pdl_config.h
        kernel/config/pdl_config.lo
        kernel/main/pdl_main.c
        kernel/main/pdl_main.h
        kernel/main/pdl_main.lo
        kernel/perform/pdl_perform.c
        kernel/perform/pdl_perform.h
        kernel/perform/pdl_perform.lo
        kernel/variable/pdl_variable.c
        kernel/variable/pdl_variable.h
        kernel/clean/pdl_clean.c
        kernel/clean/pdl_clean.h
        tests/001.phpt
        CMakeLists.txt
        config.m4
        config.w32
        CREDITS
        EXPERIMENTAL
        pdl.c
        pdl.php
        php_pdl.h
        README.md)

add_executable(PDL ${SOURCE_FILES})