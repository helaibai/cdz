/* $Id: log4c.h,v 1.4 2006/11/07 23:13:28 rbyrne Exp $
 *
 * log4c.h
 *
 * Copyright 2001-2002, Meiosys (www.meiosys.com). All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef log4c_log4c_h
#define log4c_log4c_h

#include <log4c/version.h>
#include <log4c/init.h>
#include <log4c/rc.h>
#include <log4c/appender.h>
#include <log4c/rollingpolicy.h>
#include <log4c/category.h>
#include <log4c/layout.h>
#include <log4c/logging_event.h>
#include <log4c/priority.h>

#define logerr 	printf
#define logwar 	printf
#define loginfo printf
#define logdbg	printf
#define cdz_log_init() do{\
	log4c_init();\
}while(0)
#define cdz_log_fini() do{\
	log4c_fini();\
}while(0)
#endif

