/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
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
#ifndef PHP_EV_EMBED_H
#define PHP_EV_EMBED_H

#include "common.h"
#include "types.h"

#define EV_MULTIPLICITY 1
#define EV_COMPAT3      0
#define EV_MINPRI       -2
#define EV_MAXPRI       2

/* We compile multiple source files.So we don't need static API */
#undef EV_API_STATIC

#ifdef PHP_EV_DEBUG
# define EV_VERIFY 2
#else
# define EV_VERIFY 0
#endif

#ifdef _WIN32
# define EV_USE_SELECT          1
# define EV_SELECT_IS_WINSOCKET 1 /* configure libev for windows select            */
/* AFAIK, there is no m4 processor for the default PHP build environment for Windows.
 * So we can't make use of libev.m4, and we'll define libev configuration manually. */
# define EV_STANDALONE      1
# define EV_PERIODIC_ENABLE 1
# define EV_IDLE_ENABLE     1
# define EV_EMBED_ENABLE    1
# define EV_STAT_ENABLE     1
# define EV_PREPARE_ENABLE  1
# define EV_CHECK_ENABLE    1
# define EV_FORK_ENABLE     1
# define EV_SIGNAL_ENABLE   1
# define EV_ASYNC_ENABLE    1
#endif /* _WIN32 */

/* Override `data` member of the watcher structs.
 * See types.h and libev/ev.h */
#define EV_COMMON                                                                            \
	void                 *e_next;    /* Next item of doubly linked list(ev_watcher *) */     \
	void                 *e_prev;    /* Previous item of doubly linked list(ev_watcher *) */ \
	php_ev_loop          *loop;                                                              \
	int                   type;      /* EV_ *constant from libev/ev.h */                     \
	int                   e_flags;   /* PHP_EV_WATCHER_FLAG_* */                             \
	php_ev_func_info      func;                                                              \
	zval                  self;                                                              \
	zval                  data;      /* custom var attached by user */

#include "../libev/ev.h"

/*
 * TODO: consider refactoring of embed.h and types.h.
 * We can't declare this above #include "libev/ev.h", since we'll get
 * `field 'periodic' has incomplete type' compilation error.
 *
 * php_ev_periodic is special type for periodic watcher.
 * I.e. we don't want to embed extra members into EV_COMMON
 * Extends ev_watcher
 */

typedef struct _php_ev_periodic {
	struct ev_periodic periodic;   /* Contains common watcher vars embedded */
	php_ev_func_info   func;       /* Rescheduler function */
} php_ev_periodic;

typedef struct _php_ev_stat {
	struct ev_stat  stat;   /* Extending ev_stat */
	char           *path;
} php_ev_stat;

typedef struct _php_ev_embed {
	struct ev_embed embed;   /* Extending ev_embed */
	zval            other;   /* Loop to embed      */
} php_ev_embed;

#endif /* PHP_EV_EMBED_H */
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 sts=4 fdm=marker
 * vim<600: noet sw=4 ts=4 sts=4
 */
