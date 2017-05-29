--TEST--
Check for pdl class presence
--FILE--
<?php
if (class_exists("\\vikin\\PDL")) {
    echo "pdl class is available";
}
?>
--EXPECT--
pdl class is available
