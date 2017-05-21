cmake_minimum_required(VERSION 3.6)
project(pdl)

include_directories(
        /Users/vikin/Desktop/php-src-PHP-7.0.0/main
        /Users/vikin/Desktop/php-src-PHP-7.0.0/Zend
        /Users/vikin/Desktop/php-src-PHP-7.0.0/
)

set(CMAKE_C_COMPILER C99)

set(SOURCE_FILES
    tests/001.phpt
    config.m4
    config.w32
    CREDITS
    EXPERIMENTAL
    pdl.c
    pdl.php
    php_pdl.h)

add_executable(pdl ${SOURCE_FILES})