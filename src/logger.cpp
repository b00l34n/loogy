#ifndef _H_LOGGING
#define _H_LOGGING

#include <stdio.h>
#include "../inc/logger.h"

static bool 				_g_logging_kill_signal;
static std::queue<logMessage>		_msgQueue     = std::queue<logMessage>(); 	
static pthread_cond_t			_condMessage  = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t			_mutexMessage = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t 			_mutexQueue   = PTHREAD_MUTEX_INITIALIZER;
static int				_fd;

logger::logger(std::string s) {

	_status = false;
	_g_logging_kill_signal = false;

	_fd = open( s.c_str(), O_RDWR ); 
	if ( _fd == -1 ) {
		_fd = creat( s.c_str(), 0644); 
	}

	pthread_attr_t	_attribute;

	int errorCode = pthread_attr_init(&_attribute);
	if ( errorCode != 0 ) {
		fprintf( stderr, "failed to initiate logging thread\n" );
		return;
	}
	errorCode = pthread_create( &_id, &_attribute, _writter, NULL);
	if ( errorCode != 0 ) {
		fprintf( stderr, "failed to start logging thread\n" );
		return;	
	}

	_status = true;

}

void * logger::_writter( void * e ) {
	while (! _g_logging_kill_signal) {
		if (_msgQueue.empty()) {	
			pthread_mutex_lock(&_mutexMessage);
			pthread_cond_wait(&_condMessage, &_mutexMessage);
		}	
		while ( ! _msgQueue.empty() ) {
			std::string s 	= _msgQueue.front().toString();	
			size_t len 	= s.size();	
			write(_fd, s.c_str(), len);
			_msgQueue.pop();
		}

		pthread_mutex_unlock(&_mutexMessage);
	}
	return NULL;
}

void logger::clean() {
	void * _dummy;
	_g_logging_kill_signal = true;
	pthread_cond_signal(&_condMessage);
	pthread_join(_id, &_dummy);
	close(_fd);
	pthread_mutex_destroy(&_mutexQueue);
	pthread_mutex_destroy(&_mutexMessage);
	pthread_cond_destroy(&_condMessage);
}

void logger::_pushLogMsg( logMessage l ) {
	pthread_mutex_lock(&_mutexQueue);
	_msgQueue.push(l);
	pthread_mutex_unlock(&_mutexQueue);
	pthread_cond_signal(&_condMessage);
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
#ifdef DEBUG
	_pushLogMsg(logMessage( _e_debug, s));
#endif
}

#endif
