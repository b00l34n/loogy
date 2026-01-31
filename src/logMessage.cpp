#include "../inc/logMessage.h"

logMessage::logMessage(std::string s) {
	_type 		= _e_no;
	_message 	= s;
	_time		= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); 
}

logMessage::logMessage(logType t, std::string s) {
	_type 		= t;
	_message 	= s;
	_time		= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); 
}

std::string logMessage::toString() { 
	std::string result;
	
	char time[std::size("yyyy-mm-dd hh:mm:ss")];

	std::strftime(std::data(time), std::size(time),
                  "%F %T", std::localtime(&_time));

	std::string log_time = "[ " ;
	log_time += time;
	log_time += " ] ";

	switch ( _type ) {
		case (_e_info):
			result += INFO_TAG;
			break;
		case (_e_warn): 
			result += WARN_TAG;
			break;
		case (_e_error): 
			result += ERROR_TAG;
			break;
		case (_e_debug):
			result += DEBUG_TAG;
			break;
		case (_e_no):
			result += "NOTYP >> ";
			break;
	}
	result += log_time + _message + "\n";
	return result;
}

