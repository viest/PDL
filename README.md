### Notice

请使用GCC进行编译！

### 一、安装

##### 1、下载扩展

```bash
git clone https://github.com/VikinDev/PDL.git && cd PDL
```

##### 2、依赖

1. libffi


```bash
//  Debian or Ubuntu
sudo apt-get install libffi-dev

// Mac
brew install libffi

vim ~/.bash_profile

export C_INCLUDE_PATH=$C_INCLUDE_PATH:/usr/include/ffi
```

##### 3、执行安装脚本

```bash
./install.sh --root enable
```

##### 4、运行测试

```bash
which php

export TEST_PHP_EXECUTABLE=which command result

cd PDL && php -f run-test.php
```

### 二、返回值类型

 - int
 - double
 - string

### 三、语法糖

> call(string $method_names, array $parameter, string $return_type)

```php
$config = [
    'directory' => '/vagrant/www/library'
];

$pdl    = new \vikin\PDL($config);
$test   = $pdl->open('test.so')
$result = $test->call('test', [1, 2], 'int');

var_dump($result);
```
