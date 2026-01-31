#ifndef _H_LOG_MESSAGE
#define _H_LOG_MESSAGE

#include <string>
#include <chrono>
#include <ctime>

#define INFO_TAG		"INFO  >> "
#define WARN_TAG		"WARN  >> "
#define ERROR_TAG		"ERROR >> "
#define DEBUG_TAG		"DEBUG >> "

#define TIME_DATE_TAG_SIZE	std::size("[ yyyy-mm-dd hh:mm:ss ] ")

/* + 1 because of line feed */
#define INFO_MSG_BASE_SIZE	std::size(INFO_TAG) + TIME_DATE_TAG_SIZE 
#define WARN_MSG_BASE_SIZE 	std::size(WARN_TAG) + TIME_DATE_TAG_SIZE 
#define ERROR_MSG_BASE_SIZE 	std::size(ERROR_TAG) + TIME_DATE_TAG_SIZE 
#define DEBUG_MSG_BASE_SIZE 	std::size(DEBUG_TAG) + TIME_DATE_TAG_SIZE

typedef enum {
	_e_debug	= 4,
	_e_error	= 3,
	_e_warn		= 2,
	_e_info		= 1,
	_e_no		= 0,
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
