#include "../inc/logger.h"

logger::logger() {
	_condMessage  = PTHREAD_COND_INITIALIZER; 
	_mutexMessage = PTHREAD_MUTEX_INITIALIZER; 
	_mutexQueue   = PTHREAD_MUTEX_INITIALIZER;

	_fd = open( "test.log", O_RDWR); 
	if ( _fd == -1 ) {
		_fd = creat( "test.log", 0644); 
	}
	
}

void * logger::_writter( void * e ) {

	while (true) {
		pthread_mutex_lock(&_mutexMessage);
		pthread_cond_wait(&_condMessage, &_mutexMessage);
		
		while ( ! _msgQueue.empty() ) {
			std::string s 	= _msgQueue.front().toString();	
			size_t len 	= s.size();	
			write(_fd, s.c_str(), len);
			_msgQueue.pop();
		}

		pthread_mutex_unlock(&_mutexMessage);
	}

	close(_fd);
}

void logger::_pushLogMsg( logMessage l ) {
	pthread_mutex_lock(&_mutexQueue);
	_msgQueue.push(l);
	pthread_mutex_unlock(&_mutexQueue);
}

void logger::info( std::string s ) {
	_pushLogMsg(logMessage( _e_info, s));
}
void logger::warn( std::string s ) { 
	_pushLogMsg(logMessage( _e_warn, s));
}	
void logger::error( std::string s ) {
	_pushLogMsg(logMessage( _e_error, s));
}	
void logger::debug( std::string s ) {
	_pushLogMsg(logMessage( _e_debug, s));
}
