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


void test_init ( void ) 
{
	logger dut = logger(DUT_RESULT_LOG);
	dut.~logger();
		
	TEST_ASSERT_TRUE(open(DUT_RESULT_LOG, 0) != -1);

}

void test_info ( void ) 
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
	const std::regex regx_type("(INFO)");

	FILE *	fp;
	char *	line = NULL;
	size_t	len = 0;
	ssize_t	read = 0;
	size_t	line_count = 0;

	fp = fopen(DUT_RESULT_LOG, "r");
	TEST_ASSERT_MESSAGE (fp != NULL, "failed to open created log file for analyses");
	do 
	{
		read = getline(&line, &len, fp);
		fprintf(stderr, "%s", line);
		fprintf
		(
			stderr,
			"%ld | %ld\n",
			read,
			(INFO_MSG_BASE_SIZE + result_string.getString().size())
		);
		TEST_ASSERT_MESSAGE
		(
				read == (INFO_MSG_BASE_SIZE + result_string.getString().size()),
				"line length missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_match(line, regx_type),
				"msg type missmatch"
		);
		TEST_ASSERT_MESSAGE
		(
		 		std::regex_match(line, regx_msg),
				"msg value missmatch"
		);

		++line_count;
	} while ( read != -1 );
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

	RUN_TEST( test_init );
	RUN_TEST( test_info );

	return UNITY_END(); 

}
