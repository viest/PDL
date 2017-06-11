#!/bin/bash

#-----------------------------------------------------------------------#
#  PDL php extension                                                    #
#                                                                       #
#  Copyright (c) 2017-2018 Vikin  (http://www.vikin.cc)                 #
#                                                                       #
#                                                                       #
#  Available params:                                                    #
#  --root                                                               #
#  --phpize                                                             #
#  --php-config                                                         #
#                                                                       #
#                                                                       #
#  Example:                                                             #
#  ./install --root enable  \                                           #
#            --phpize /usr/bin/phpize \                                 #
#            --php-config /usr/bin/php-config                           #
#                                                                       #
#-----------------------------------------------------------------------#

MESSAGE_START="\033["
MESSAGE_END="\033[0m"

echo -e "$MESSAGE_START""42;37m   Message: PDL extension to start the installation   ""$MESSAGE_END"

BUILD_PATH=$(cd `dirname $0`; pwd)
PHP_BIN=`which php`
PHP_IZE_PATH=`which phpize`
PHP_CONFIG_PATH=`which php-config`
PHP_VERSION=`${PHP_BIN} -v`
EXT_PERMISSIONS="0"

# -----------------------------------------------
# 如果php版本不是7，终止编译
# -----------------------------------------------
if [ "${PHP_VERSION:4:1}" != "7" ]; then
    echo -e "$MESSAGE_START""41;37m   Error: PDL extension does not support PHP 7.0 version below   ""$MESSAGE_END"
    exit 1
fi

# -----------------------------------------------
# 处理用户出入的参数
# -----------------------------------------------
for arg in "$@"; do
  shift
  case "$arg" in
    "--phpize")     set -- "$@" "-i" ;;
    "--php-config") set -- "$@" "-c" ;;
    "--root")       set -- "$@" "-r" ;;
    *) set -- "$@" "$arg"
  esac
done

# -----------------------------------------------
# 将用户传入的参数进行赋值
# -----------------------------------------------
while getopts i:c:r: opts; do
   case ${opts} in
      i) PHP_IZE_PATH=${OPTARG} ;;
      c) PHP_CONFIG_PATH=${OPTARG} ;;
      r) EXT_PERMISSIONS=${OPTARG} ;;
   esac
done

# -----------------------------------------------
# 如果php_config没找到则要求必须携带参数
# -----------------------------------------------
if [ -z "$PHP_CONFIG_PATH" ]; then
    echo -e "$MESSAGE_START""41;37m   Error: Not found php-config, you should use --php-config /PATH   ""$MESSAGE_END"
    exit 1
fi

# -----------------------------------------------
# 未找到php-config
# -----------------------------------------------
#if [ $? != 0 ]; then
#	echo "php-config is not installed"
#	exit 1
#fi

# -----------------------------------------------
# 安装依赖 ffi
# -----------------------------------------------
#if [ ! -f /usr/local/include/ffi.h ]; then
#    cd $BUILD_PATH/source/ffi
#    bash ./autogen.sh
#
#    if [ $? != 0 ]; then
#    echo -e "$MESSAGE_START""41;37m   Error: extended dependency \"autoconf\" failed, please according to the error message to deal with   ""$MESSAGE_END"
#    exit 1
#    fi
#
#    bash ./configure && make && sudo make install
#fi

# -----------------------------------------------
# 清除之前的编译文件
# -----------------------------------------------
if [ -f Makefile ]; then
    make clean
	${PHP_IZE_PATH} --clean
    for file2 in `ls -a $BUILD_PATH/kernel/*`
    do
        if [ x"$file2" != x"." -a x"$file2" != x".." ];then
            TMP_PATH=${file2##*/}
            TMP_DIR=${TMP_PATH%%:}

            # 进入kernel下的组件目录
            if [ x"${TMP_PATH:0-1:1}" = x":" ];then
               cd  $BUILD_PATH/kernel/$TMP_DIR
            fi

            # 删除组件下的.libs目录
            if [ x"$file2" = x".libs" ];then
                rm -rf $file2
            fi

            # 删除组件下的lo文件
            if [ x"${TMP_PATH:0-2:2}" = x"lo" ];then
                rm $file2
            fi
        fi
    done
fi

# -----------------------------------------------
# 进入框架目录，准备编译
# -----------------------------------------------
cd $BUILD_PATH

# -----------------------------------------------
# 编译安装扩展
# -----------------------------------------------
${PHP_IZE_PATH} && \
./configure --with-php-config=${PHP_CONFIG_PATH} && make

# -----------------------------------------------
# 是否开启root权限安装
# -----------------------------------------------
if [ $EXT_PERMISSIONS == "enable" ]; then
    sudo make install
else
    make install
fi

# -----------------------------------------------
# 判断是否安装成功
# -----------------------------------------------
if [ $? != 0 ]; then
    echo -e "\n"
    echo -e "$MESSAGE_START""41;37m   Error: PDL extension installation failed,need sudo permissions?   ""$MESSAGE_END"
    exit 1
else
    echo -e "\n" && \
    echo -e "$MESSAGE_START""42;37m   Message: PDL extension successful installation   ""$MESSAGE_END"
fi

# -----------------------------------------------
# 获取php的conf.d目录
# -----------------------------------------------
PHP_CONF_D_PATH=`${PHP_BIN} -i|grep '^Scan this dir for additional .ini files'`

# -----------------------------------------------
# 判断是否开启加载附加ini文件
# -----------------------------------------------
if [ ${PHP_CONF_D_PATH#*=>} == "(none)" ]; then
    echo -e "\n"
    echo -e "$MESSAGE_START""41;37m   Warning: Did not open \"config file scan dir\"  ""$MESSAGE_END"
    echo -e "$MESSAGE_START""41;37m   Add \"pdl.so\" to \"php.ini\" file             ""$MESSAGE_END"
    exit 1
fi

# -----------------------------------------------
# 进入conf_d文件夹
# -----------------------------------------------
cd ${PHP_CONF_D_PATH#*=>}

# -----------------------------------------------
# 如果vtiful.ini文件存在，删除
# -----------------------------------------------
if [ -f "pdl.ini" ]; then
  rm pdl.ini
fi

# -----------------------------------------------
# 创建ini文件并写入
# -----------------------------------------------
echo "[pdl]">>pdl.ini
echo "extension = pdl.so">>pdl.ini

if [ $? != 0 ]; then
	echo -e "\n"
    echo -e "$MESSAGE_START""41;37m   Error: \"pdl.ini\" file to create failure,please manually create and restart PHP-FPM   ""$MESSAGE_END"
else
    echo -e "\n"
    echo -e "$MESSAGE_START""42;37m   Message: \"pdl.ini\" file to create success,please restart the PHP-FPM   ""$MESSAGE_END"
fi