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