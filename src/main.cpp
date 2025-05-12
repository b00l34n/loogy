#include "../inc/logger.h"

int main ( int argc, char * argv[] ) {
	
	logger l = logger();

	if ( logger::status() ) {
		logger::info("Test");
		logger::warn("Test");
		logger::error("Test");
		logger::clean();
	}

	return 0;

}
