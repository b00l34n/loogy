
#include <stdio.h>
#include "../inc/logger.h"

int main ( int argc, char * argv[] ) {
	
	logger l = logger();

	if ( l.status() ) {
		logger::info("Test");
		logger::warn("Test");
		logger::error("Test");
	} else {
		fprintf(stderr, "Fucked up");
	}	
	l.clean();
	
	return 0;
}
