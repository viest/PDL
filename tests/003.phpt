--TEST--
Check for pdl class presence
--FILE--
<?php
$config = [
	'directory' => __DIR__ . '/../resources'
];

$pdl    = new \vikin\PDL($config);
$test   = $pdl->open('test.so');
$result = $test->call('test', [1, 4], 'int');

echo $result;
?>
--EXPECT--
5
