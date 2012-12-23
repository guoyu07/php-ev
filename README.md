ev PECL extension

DESCRIPTION
===========

ev is a PECL extension providing inteface to libev library - high performance
full-featured event loop written in C.


ABOUT LIBEV
-----------

Libev is an event loop: you register interest in certain events (such as a file
descriptor being readable or a timeout occurring), and it will manage these
event sources and provide your program with events.

To do this, it must take more or less complete control over your process (or
thread) by executing the event loop handler, and will then communicate events
via a callback mechanism.

You register interest in certain events by registering so-called event watchers,
and then hand it over to libev by starting the watcher.

For details refer to the libev's homepage:
<http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod#EMBEDDING>

For installation instructions see file named INSTALL.


LIBEV IS EMBEDDED
-----------------

You don't need to install libev separately, since it is embedded into this
extension.


PORTABILITY
-----------

Currently GNU/Linux platforms supported only. But likely will work on others
too.


EXAMPLES
========

SIMPLE TIMERS
-------------

	<?php
	// Create and start timer firing after 2 seconds
	$w1 = new EvTimer(2, 0, function () {
		echo "2 seconds elapsed\n";
	});

	// Create and launch timer firing after 2 seconds repeating each second
	// until we manually stop it
	$w2 = new EvTimer(2, 1, function ($w) {
		echo "is called every second, is launched after 2 seconds\n";
		echo "iteration = ", ev_iteration(), PHP_EOL;

		// Stop the watcher after 5 iterations
		ev_iteration() == 5 and $w->stop();
		// Stop the watcher if further calls cause more than 10 iterations
		ev_iteration() >= 10 and $w->stop();
	});

	// Create stopped timer. It will be inactive until we start it ourselves
	$w_stopped = EvTimer::createStopped(10, 5, function($w) {
		echo "Callback of a timer created as stopped\n";

		// Stop the watcher after 2 iterations
		ev_iteration() >= 2 and $w->stop();
	});

	// Loop until ev_break() is called or all of watchers stop
	ev_run();

	// Start and look if it works
	$w_stopped->start();
	echo "Run single iteration\n";
	ev_run(EVRUN_ONCE);

	echo "Restart the second watcher and try to handle the same events, but don't block\n";
	$w2->again();
	ev_run(EVRUN_NOWAIT);

	$w = new EvTimer(10, 0, function() {});
	echo "Running a blocking loop\n";
	ev_run();
	echo "END\n";
	?>

*Output*

	2 seconds elapsed
	is called every second, is launched after 2 seconds
	iteration = 1
	is called every second, is launched after 2 seconds
	iteration = 2
	is called every second, is launched after 2 seconds
	iteration = 3
	is called every second, is launched after 2 seconds
	iteration = 4
	is called every second, is launched after 2 seconds
	iteration = 5
	Run single iteration
	Callback of a timer created as stopped
	Restart the second watcher and try to handle the same events, but don't block
	Running a blocking loop
	is called every second, is launched after 2 seconds
	iteration = 8
	is called every second, is launched after 2 seconds
	iteration = 9
	is called every second, is launched after 2 seconds
	iteration = 10
	END

PERIODIC TIMERS
---------------

*Example 1*

	<?php
	// Tick each 10.5 seconds
	$w = new EvPeriodic(0., 10.5, NULL, function ($w, $revents) {
		echo time(), PHP_EOL;
	});
	ev_run();
	?>

*Example 2*

	<?php
	// Tick each 10.5 seconds. Use reschedule callback

	function reschedule_cb ($watcher, $now) {
		return $now + (10.5. - fmod($now, 10.5));

	}

	$w = new EvPeriodic(0., 0., "reschedule_cb", function ($w, $revents) {
		echo time(), PHP_EOL;
	});
	ev_run();
	?>

*Example 3*

	<?php
	// Tick every 10.5 seconds starting at now
	$w = new EvPeriodic(fmod(ev_now(), 10.5), 10.5, NULL, function ($w, $revents) {
		echo time(), PHP_EOL;
	});
	ev_run();
	?>

I/O EVENTS
----------

*Example 1*

	<?php
	// Wait until STDIN is readable
	$w = new EvIo(STDIN, EV_READ, function ($watcher, $revents) {
		echo "STDIN is readable\n";
	});
	ev_run(EVRUN_ONCE);
	?>

*Example 2*

	<?php
	/* Use some async I/O to access a socket */

	// `sockets' extension still logs warnings
	// for EINPROGRESS, EAGAIN/EWOULDBLOCK etc.
	error_reporting(E_ERROR);

	$e_nonblocking = array (/*EAGAIN or EWOULDBLOCK*/11, /*EINPROGRESS*/115);

	// Get the port for the WWW service
	$service_port = getservbyname('www', 'tcp');

	// Get the IP address for the target host
	$address = gethostbyname('google.co.uk');

	// Create a TCP/IP socket
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket === FALSE) {
    	echo "socket_create() failed: reason: "
			.socket_strerror(socket_last_error()) . "\n";
	}

	// Set O_NONBLOCK flag
	socket_set_nonblock($socket);

	// Abort on timeout
	$timeout_watcher = new EvTimer(10.0, 0., function () use ($socket) {
		socket_close($socket);
		ev_break(EVBREAK_ALL);
	});

	// Make HEAD request when the socket is writable
	$write_watcher = new EvIo($socket, EV_WRITE, function ($w)
		use ($socket, $timeout_watcher, $e_nonblocking) {
		// Stop timeout watcher
		$timeout_watcher->stop();
		// Stop write watcher
		$w->stop();

		$in = "HEAD / HTTP/1.1\r\n";
		$in .= "Host: google.co.uk\r\n";
		$in .= "Connection: Close\r\n\r\n";

		if (!socket_write($socket, $in, strlen($in))) {
			trigger_error("Failed writing $in to socket", E_USER_ERROR);
		}

		$read_watcher = new EvIo($socket, EV_READ, function ($w, $re)
			use ($socket, $e_nonblocking) {
			// Socket is readable. recv() 20 bytes using non-blocking mode
			$ret = socket_recv($socket, $out, 20, MSG_DONTWAIT);

			if ($ret) {
    			echo $out;
			} elseif ($ret === 0) {
				// All read
				$w->stop();
				socket_close($socket);
				return;
			}

			// Caught EINPROGRESS, EAGAIN, or EWOULDBLOCK
			if (in_array(socket_last_error(), $e_nonblocking)) {
				return;
			}

			$w->stop();
			socket_close($socket);
		});

		ev_run();
	});

	$result = socket_connect($socket, $address, $service_port);

	ev_run();
	?>

Sample output:

	HTTP/1.1 301 Moved Permanently
	Location: http://www.google.co.uk/
	Content-Type: text/html; charset=UTF-8
	Date: Sun, 23 Dec 2012 16:08:27 GMT
	Expires: Tue, 22 Jan 2013 16:08:27 GMT
	Cache-Control: public, max-age=2592000
	Server: gws
	Content-Length: 221
	X-XSS-Protection: 1; mode=block
	X-Frame-Options: SAMEORIGIN
	Connection: close


SIGNALS
-------

	<?php
	// Handle SIGTERM signal
	$w = new EvSignal(SIGTERM, function ($watcher) {
		echo "SIGTERM received\n";
		$watcher->stop();
	});
	ev_run();
	?>

STAT - FILE STATUS CHANGES
--------------------------

*Example 1*

	<?php
	// Monitor changes of /var/log/messages.
	// Use 10 second update interval.
	$w = new EvStat("/var/log/messages", 8, function ($w) {
		echo "/var/log/messages changed\n";

		$attr = $w->attr();

		if ($attr['nlink']) {
			printf("Current size: %ld\n", $attr['size']);
			printf("Current atime: %ld\n", $attr['atime']);
			printf("Current mtime: %ld\n", $attr['mtime']);
		} else {
			fprintf(STDERR, "`messages` file is not there!");
			$w->stop();
		}
	});

	ev_run();
	?>

*Example 2*

	<?php
	// Avoid missing updates by means of one second delay
	$timer = EvTimer::createStopped(0., 1.02, function ($w) {
		$w->stop();

		$stat = $w->data;

		// 1 second after the most recent change of the file
		printf("Current size: %ld\n", $stat->attr()['size']);
	});

	$stat = new EvStat("/var/log/messages", 0., function () use ($timer) {
		// Reset timer watcher
		$timer->again();
	});

	$timer->data = $stat;

	ev_run();
	?>

PROCESS STATUS CHANGES
----------------------

	<?php
	$pid = pcntl_fork();

	if ($pid == -1) {
		fprintf(STDERR, "pcntl_fork failed\n");
	} elseif ($pid) {
		$w = new EvChild($pid, FALSE, function ($w, $revents) {
			$w->stop();

			printf("Process %d exited with status %d\n", $w->rpid, $w->rstatus);
		});

		ev_run();

		// Protect against Zombies
		pcntl_wait($status);
	} else {
		//Forked child
		exit(2);
	}
	?>

AUTHORS
=======

Ruslan Osmanov <osmanov@php.net>


COPYRIGHT
=========

Copyright (c) 2012 Ruslan Osmanov <osmanov@php.net>

This project is subject to version 3.01 of the PHP license, that is bundled
with this package in the file LICENSE, and is available through the
world-wide-web at the following url: http://www.php.net/license/3_01.txt If you
did not receive a copy of the PHP license and are unable to obtain it through
the world-wide-web, please send a note to license@php.net so we can mail you a
copy immediately.


vim: tw=80 ft=markdown

