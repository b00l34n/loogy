#include <queue>
#include <string>
#include "./logMessage.h"

extern "C" {
	#include <stdio.h> 
	#include <pthread.h>
	#include <unistd.h>
	#include <fcntl.h>
}

class logger {

	private:
		bool				_status;
		pthread_t		 	_id;

		static void *			_writter( void * );
		static void 			_pushLogMsg( logMessage );

	public:
		logger();

		static void 			info( std::string );	
		static void 			warn( std::string );	
		static void 			error( std::string );	
		static void 			debug( std::string );	

		bool				status() { return _status; };	
		void				clean();
};
