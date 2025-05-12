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
		
		static int				_fd;
		static std::queue<logMessage>		_msgQueue; 	
		static pthread_cond_t			_condMessage;
		static pthread_mutex_t			_mutexMessage; 
		static pthread_mutex_t 			_mutexQueue;
		static pthread_t		 	_id;

		static bool				_status;

		static void * 				_writter( void * );
		static void 				_pushLogMsg( logMessage );

	public:
		logger();

		static void 				info( std::string );	
		static void 				warn( std::string );	
		static void 				error( std::string );	
		static void 				debug( std::string );	
		
		static bool 				status() { return _status; };	
		static void				clean();
};
