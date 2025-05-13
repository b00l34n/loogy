
#include <stdio.h>
#include <unistd.h>
#include "../inc/logger.h"

int main ( int argc, char * argv[] ) {
	
	logger l = logger();

	if ( l.status() ) {
		logger::info("Info");
		logger::warn("Warning");
		logger::error("Error");
		logger::debug("Debug");
		usleep(300);
	} else {
		fprintf(stderr, "Fucked up");
	}
	
	l.clean();
	
	return 0;
}
