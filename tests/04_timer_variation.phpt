--TEST--
Check for EvTimer various calls
--FILE--
<?php
# The code is a translated version of Perl EV module's 09_brandon.t file

error_reporting(0);


$a = new EvTimer(1.6, 0, function() { echo "not ok 2\n"; Ev::stop(); });
$b = new EvTimer(0.3, 0, function() { echo "ok 2\n"; Ev::stop(); });

echo "ok 1\n";
Ev::run();
echo "ok 3\n";

$b = new EvTimer(0.3, 0, function() { echo "ok 5\n"; Ev::stop(); });
$a = new EvTimer(1.6, 0, function() { echo "not ok 5\n"; Ev::stop(); });

echo "ok 4\n";
Ev::run();
echo "ok 6\n";

$a = new EvTimer(1.9, 0, function() { echo "not ok 8\n"; Ev::stop(); });
$b = new EvTimer(1.6, 0, function() { echo "not ok 8\n"; Ev::stop(); });
$c = new EvTimer(0.3, 0, function() { echo "ok 8\n"; Ev::stop(); });

echo "ok 7\n";
Ev::run();
echo "ok 9\n";

$a = new EvTimer(1.6, 0, function() { echo "not ok 11\n"; Ev::stop(); });
$b = new EvTimer(0.3, 0, function() { echo "ok 11\n"; Ev::stop(); });
$c = new EvTimer(1.9, 0, function() { echo "not ok 11\n"; Ev::stop(); });

echo "ok 10\n";
Ev::run();
echo "ok 12\n";
?>
--EXPECT--
ok 1
ok 2
ok 3
ok 4
ok 5
ok 6
ok 7
ok 8
ok 9
ok 10
ok 11
ok 12
