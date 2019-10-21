#include "pch.h"
#include "..//nya-nn//nyann.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace {


} // namespace

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int returnValue;

	// Setup
	std::ofstream log("logs\\tests_main_log.log");
	auto temp_buf = log.rdbuf();
	std::clog.rdbuf(log.rdbuf());

	returnValue = RUN_ALL_TESTS();

	// Teardown
	std::clog.rdbuf(temp_buf);


	return returnValue;
}