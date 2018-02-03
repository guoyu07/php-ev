/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2011 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Ruslan Osmanov <osmanov@php.net>                             |
   +----------------------------------------------------------------------+
*/
#ifndef PHP_EV_FE_H
#define PHP_EV_FE_H

#include "embed.h"

/* {{{ Ev */
PHP_METHOD(Ev, supportedBackends);
PHP_METHOD(Ev, recommendedBackends);
PHP_METHOD(Ev, embeddableBackends);
PHP_METHOD(Ev, feedSignal);
PHP_METHOD(Ev, feedSignalEvent);
PHP_METHOD(Ev, sleep);
PHP_METHOD(Ev, time);
PHP_METHOD(Ev, run);
PHP_METHOD(Ev, now);
PHP_METHOD(Ev, stop);
PHP_METHOD(Ev, iteration);
PHP_METHOD(Ev, depth);
PHP_METHOD(Ev, verify);
PHP_METHOD(Ev, backend);
PHP_METHOD(Ev, nowUpdate);
PHP_METHOD(Ev, suspend);
PHP_METHOD(Ev, resume);
/* }}} */

/* {{{ EvLoop */
PHP_METHOD(EvLoop, __construct);
PHP_METHOD(EvLoop, defaultLoop);
PHP_METHOD(EvLoop, loopFork);
PHP_METHOD(EvLoop, verify);
PHP_METHOD(EvLoop, invokePending);
PHP_METHOD(EvLoop, nowUpdate);
PHP_METHOD(EvLoop, suspend);
PHP_METHOD(EvLoop, resume);
PHP_METHOD(EvLoop, backend);
PHP_METHOD(EvLoop, now);
PHP_METHOD(EvLoop, run);
PHP_METHOD(EvLoop, stop);
PHP_METHOD(EvLoop, io);
PHP_METHOD(EvLoop, timer);
#if EV_PERIODIC_ENABLE
PHP_METHOD(EvLoop, periodic);
#endif
#if EV_SIGNAL_ENABLE
PHP_METHOD(EvLoop, signal);
#endif
#if EV_CHILD_ENABLE
PHP_METHOD(EvLoop, child);
#endif
#if EV_STAT_ENABLE
PHP_METHOD(EvLoop, stat);
#endif
#if EV_IDLE_ENABLE
PHP_METHOD(EvLoop, idle);
#endif
#if EV_CHECK_ENABLE
PHP_METHOD(EvLoop, check);
#endif
#if EV_PREPARE_ENABLE
PHP_METHOD(EvLoop, prepare);
#endif
#if EV_EMBED_ENABLE
PHP_METHOD(EvLoop, embed);
#endif
#if EV_FORK_ENABLE
PHP_METHOD(EvLoop, fork);
#endif
/* }}} */

/* {{{ EvWatcher */
/* PHP_METHOD(EvWatcher, __construct); */
PHP_METHOD(EvWatcher, start);
PHP_METHOD(EvWatcher, stop);
PHP_METHOD(EvWatcher, clear);
PHP_METHOD(EvWatcher, invoke);
PHP_METHOD(EvWatcher, feed);
PHP_METHOD(EvWatcher, getLoop);
PHP_METHOD(EvWatcher, keepalive);
PHP_METHOD(EvWatcher, setCallback);
/* }}} */

/* {{{ EvIo */
PHP_METHOD(EvIo, __construct);
PHP_METHOD(EvIo, set);
PHP_METHOD(EvIo, createStopped);
/* }}} */

/* {{{ EvTimer */
PHP_METHOD(EvTimer, __construct);
PHP_METHOD(EvTimer, set);
PHP_METHOD(EvTimer, again);
PHP_METHOD(EvTimer, createStopped);
/* }}} */

#if EV_PERIODIC_ENABLE
/* {{{ EvPeriodic */
PHP_METHOD(EvPeriodic, __construct);
PHP_METHOD(EvPeriodic, set);
PHP_METHOD(EvPeriodic, again);
PHP_METHOD(EvPeriodic, at);
PHP_METHOD(EvPeriodic, createStopped);
/* }}} */
#endif

#if EV_SIGNAL_ENABLE
/* {{{ EvSignal */
PHP_METHOD(EvSignal, __construct);
PHP_METHOD(EvSignal, set);
PHP_METHOD(EvSignal, createStopped);
/* }}} */
#endif

#if EV_CHILD_ENABLE
/* {{{ EvChild */
PHP_METHOD(EvChild, __construct);
PHP_METHOD(EvChild, set);
PHP_METHOD(EvChild, createStopped);
/* }}} */
#endif

#if EV_STAT_ENABLE
/* {{{ EvStat */
PHP_METHOD(EvStat, __construct);
PHP_METHOD(EvStat, set);
PHP_METHOD(EvStat, attr);
PHP_METHOD(EvStat, prev);
PHP_METHOD(EvStat, stat);
PHP_METHOD(EvStat, createStopped);
/* }}} */
#endif

#if EV_IDLE_ENABLE
/* {{{ EvIdle */
PHP_METHOD(EvIdle, __construct);
PHP_METHOD(EvIdle, createStopped);
/* }}} */
#endif

#if EV_CHECK_ENABLE
/* {{{ EvCheck */
PHP_METHOD(EvCheck, __construct);
PHP_METHOD(EvCheck, createStopped);
/* }}} */
#endif

#if EV_PREPARE_ENABLE
/* {{{ EvPrepare */
PHP_METHOD(EvPrepare, __construct);
PHP_METHOD(EvPrepare, createStopped);
/* }}} */
#endif

#if EV_EMBED_ENABLE
/* {{{ EvEmbed */
PHP_METHOD(EvEmbed, __construct);
PHP_METHOD(EvEmbed, set);
PHP_METHOD(EvEmbed, sweep);
PHP_METHOD(EvEmbed, createStopped);
/* }}} */
#endif

#if EV_FORK_ENABLE
/* {{{ EvFork*/
PHP_METHOD(EvFork, __construct);
PHP_METHOD(EvFork, createStopped);
/* }}} */
#endif

#endif /* PHP_EV_FE_H */

/* 
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * vim600: fdm=marker
 * vim: noet sts=4 sw=4 ts=4
 */
