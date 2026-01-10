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
	
	std::string time = std::ctime(&_time);
	time.pop_back();
	std::string log_time = "[" + time + "] ";

	switch ( _type ) {
		case (_e_info):
			result += "INFO  >> ";
			break;
		case (_e_warn): 
			result += "WARN  >> ";
			break;
		case (_e_error): 
			result += "ERROR >> ";
			break;
		case (_e_debug):
			result += "DEBUG >> ";
			break;
		case (_e_no):
			result += "NOTYP >> ";
			break;
	}
	result += log_time + _message + "\n";
	return result;
}

