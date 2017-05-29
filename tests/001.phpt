--TEST--
Check for pdl presence
--SKIPIF--
<?php if (!extension_loaded("pdl")) print "skip"; ?>
--FILE--
<?php 
echo "pdl extension is available";
?>
--EXPECT--
pdl extension is available
