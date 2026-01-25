extern "C" {
	#include "../Unity/src/unity.h"
}

#include <regex>
#include "../inc/logMessage.h"

void setUp(void) {};

void tearDown(void) {};


void test_CreateMessage ( void ) {
	logMessage dut = logMessage(_e_no, "Test");
	const std::regex reg("NOTYP >> \\[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \\] Test\n");
	TEST_ASSERT_TRUE(std::regex_match(dut.toString(), reg));
}

void test_LogTypesInfo ( void ) {
	logMessage dut = logMessage(_e_info, "info");
	const std::regex regI("INFO  >> \\[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \\] info\n");
	TEST_ASSERT_TRUE(std::regex_match(dut.toString(), regI));
}

void test_LogTypesWarn ( void ) {
	logMessage dut = logMessage(_e_warn, "warn");
	const std::regex regW("WARN  >> \\[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \\] warn\n");
	TEST_ASSERT_TRUE(std::regex_match(dut.toString(), regW));
}

void test_LogTypesError ( void ) {
	logMessage dut = logMessage(_e_error, "error");
	const std::regex regE("ERROR >> \\[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \\] error\n");
	TEST_ASSERT_TRUE(std::regex_match(dut.toString(), regE));
}

int main ( void ) {

	UNITY_BEGIN();

	RUN_TEST(test_CreateMessage);
	
	RUN_TEST(test_LogTypesInfo);
	RUN_TEST(test_LogTypesWarn);
	RUN_TEST(test_LogTypesError);

	return UNITY_END(); 
}
