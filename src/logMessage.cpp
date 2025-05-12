#include "../inc/logMessage.h"

logMessage::logMessage(std::string s) {
	_type 		= _e_no;
	_message 	= s;
}

logMessage::logMessage(logType t, std::string s) {
	_type 		= t;
	_message 	= s;
}

std::string logMessage::toString() { 
	std::string result;	
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
	result += _message + "\n";
	return result;
}

