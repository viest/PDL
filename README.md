### 安装

##### 1、下载扩展

```bash
git lone && cd PDL
```

##### 2、执行安装脚本

```bash
./install.sh --root enable
```

### 语法糖

```php
$config = [
    'directory' => '/vagrant/www/library'
];

$pdl = new \vikin\PDL($config);

$test = $pdl->open('test.so')
$result = $test->call('test', [1, 2], 'int');

var_dump($result);
```