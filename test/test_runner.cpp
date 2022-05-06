/*
 * test_runner.cpp
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#include "gtest/gtest.h"


int main(int argc, char **argv) {
	std::string result = "results.xml";

	::testing::InitGoogleTest(&argc, argv);

	/*
	JUnitResultListener *listener = new JUnitResultListener(result);
	::testing::UnitTest::GetInstance()->listeners().Append(listener);
	 */

	int ret = RUN_ALL_TESTS();


	return ret;
}
