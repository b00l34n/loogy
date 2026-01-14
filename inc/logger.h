#include <queue>
#include <string>
#include "./logMessage.h"

extern "C" {
	#include <stdio.h> 
	#include <pthread.h>
	#include <unistd.h>
	#include <fcntl.h>
}

#ifndef LOOGY_H_
#define LOOGY_H_

class logger {

	private:
		bool				_status;
		pthread_t		 	_id;

		static void *			_writter( void * );
		static void 			_pushLogMsg( logMessage );

	public:
		logger(std::string);
		logger() : logger("./logfile"){};

		static void 			info( std::string );	
		static void 			warn( std::string );	
		static void 			error( std::string );	
		static void 			debug( std::string );	

		bool				status() { return _status; };	
		void				clean();

		~logger();
};

#endif
