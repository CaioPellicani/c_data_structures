#include "stdHeader.h"

static void die(const char *fmt, ...){
	va_list args;
	va_start (args, fmt);
	vprintf (fmt, args);
	va_end (args);
	exit(1);
}