#ifndef _H_LOG_MESSAGE
#define _H_LOG_MESSAGE

#include <string>
#include <chrono>
#include <ctime>


typedef enum {
	_e_debug = 4,
	_e_error = 3,
	_e_warn = 2,
	_e_info = 1,
	_e_no = 0,
} logType;

class logMessage {

	private:
		logType		_type;
		std::string	_message;		
		std::time_t 	_time;

	public:
		logMessage(){ /* Nothing */ };
		logMessage(std::string s);
		logMessage(logType t, std::string s);

		logType getType() { return _type; };
		std::string getString() { return _message; };

		std::string toString(); 
};

#endif
