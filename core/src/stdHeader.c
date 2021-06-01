#include "stdHeader.h"

void die(const char *fmt, ...){
	va_list args;
	va_start (args, fmt);
	vprintf (fmt, args);
	va_end (args);
	exit(1);
}

/* DEBUG */


int getData( void *debugData ){
	if( debugData != NULL ){
		dData* dD = ( typeof( dD ) ) debugData;
		return dD->value;
	}
	return 0;
}

/* END DEBUG */