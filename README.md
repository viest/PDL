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

$pdl = new PDL($config);

$args   = [1, 2];
$result = $pdl->call('test.so.6', $args);

var_dump($result);

// array(2, 3)
```