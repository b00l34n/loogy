extern "C" {
#include "../Unity/src/unity.h"
#include <unistd.h>
}
#include "../inc/logger.h" 
#include <regex>

#define DUT_RESULT_LOG "/tmp/result.log"

void setUp(void)
{
	if (remove(DUT_RESULT_LOG))
	{
		perror("remove");
	}

}


void tearDown(void) {}


void init ( void ) 
{
	logger dut = logger(DUT_RESULT_LOG);
	dut.~logger();
		
	TEST_ASSERT_TRUE(open(DUT_RESULT_LOG, 0) != -1);

}


void info ( void ) 
{	
	const char * test_str = "test";
	logger dut = logger(DUT_RESULT_LOG);
	dut.info(test_str);	
	dut.~logger();

	logMessage result_string = logMessage(_e_info, test_str); 
	std::string str_msg = "(";
	str_msg += test_str;
	str_msg += ")";
	const std::regex regx_msg(str_msg);
	const std::regex regx_type(R"(^INFO.*)");

	FILE *	fp;
	char *	line = NULL;
	size_t	len = 0;
	ssize_t	read = 0;
	size_t	line_count = 0;

	fp = fopen(DUT_RESULT_LOG, "r");
	TEST_ASSERT_MESSAGE (fp != NULL, "failed to open created log file for analyses");
		
	read = getline(&line, &len, fp);
	TEST_ASSERT_MESSAGE ( read != -1, "log file is empty");	
	while ( read != -1 ) 
	{
		TEST_ASSERT_MESSAGE
		(
				read == result_string.toString().size(),
				"line length missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_type),
				"msg type missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_msg),
				"msg value missmatch"
		);

		
		++line_count;
		read = getline(&line, &len, fp);
	}
	fclose(fp);
	
	TEST_ASSERT_MESSAGE
	(
		line_count == 1,
		"line count missmatch"
	);

}


void warn ( void ) 
{	
	const char * test_str = "warn";
	logger dut = logger(DUT_RESULT_LOG);
	dut.warn(test_str);	
	dut.~logger();

	logMessage result_string = logMessage(_e_warn, test_str); 
	std::string str_msg = "(";
	str_msg += test_str;
	str_msg += ")";
	const std::regex regx_msg(str_msg);
	const std::regex regx_type(R"(^WARN.*)");

	FILE *	fp;
	char *	line = NULL;
	size_t	len = 0;
	ssize_t	read = 0;
	size_t	line_count = 0;

	fp = fopen(DUT_RESULT_LOG, "r");
	TEST_ASSERT_MESSAGE (fp != NULL, "failed to open created log file for analyses");
		
	read = getline(&line, &len, fp);
	TEST_ASSERT_MESSAGE ( read != -1, "log file is empty");	
	while ( read != -1 ) 
	{
		TEST_ASSERT_MESSAGE
		(
				read == result_string.toString().size(),
				"line length missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_type),
				"msg type missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_msg),
				"msg value missmatch"
		);

		
		++line_count;
		read = getline(&line, &len, fp);
	}
	fclose(fp);
	
	TEST_ASSERT_MESSAGE
	(
		line_count == 1,
		"line count missmatch"
	);

}


void error ( void ) 
{	
	const char * test_str = "error";
	logger dut = logger(DUT_RESULT_LOG);
	dut.error(test_str);	
	dut.~logger();

	logMessage result_string = logMessage(_e_error, test_str); 
	std::string str_msg = "(";
	str_msg += test_str;
	str_msg += ")";
	const std::regex regx_msg(str_msg);
	const std::regex regx_type(R"(^ERROR.*)");

	FILE *	fp;
	char *	line = NULL;
	size_t	len = 0;
	ssize_t	read = 0;
	size_t	line_count = 0;

	fp = fopen(DUT_RESULT_LOG, "r");
	TEST_ASSERT_MESSAGE (fp != NULL, "failed to open created log file for analyses");
		
	read = getline(&line, &len, fp);
	TEST_ASSERT_MESSAGE ( read != -1, "log file is empty");	
	while ( read != -1 ) 
	{
		TEST_ASSERT_MESSAGE
		(
				read == result_string.toString().size(),
				"line length missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_type),
				"msg type missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_search(line, regx_msg),
				"msg value missmatch"
		);

		
		++line_count;
		read = getline(&line, &len, fp);
	}
	fclose(fp);
	
	TEST_ASSERT_MESSAGE
	(
		line_count == 1,
		"line count missmatch"
	);

}



int main ( void )
{

	UNITY_BEGIN();

	RUN_TEST( init );
	RUN_TEST( info );
	RUN_TEST( warn );
	RUN_TEST( error );

	return UNITY_END(); 

}
