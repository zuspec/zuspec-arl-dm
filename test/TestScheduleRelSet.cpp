/*
 * TestScheduleRelSet.cpp
 *
 *  Created on: May 7, 2022
 *      Author: mballance
 */

#include "TestScheduleRelSet.h"
#include "ScheduleRelSet.h"

namespace arl {

TestScheduleRelSet::TestScheduleRelSet() {
	// TODO Auto-generated constructor stub

}

TestScheduleRelSet::~TestScheduleRelSet() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestScheduleRelSet, smoke) {

	ScheduleRelSet set(4);
	ASSERT_TRUE(set.setRel(0, 1, ScheduleRelE::SeqAB));
	ASSERT_TRUE(set.setRel(1, 2, ScheduleRelE::SeqAB));
	ASSERT_EQ(set.getRel(0, 2), ScheduleRelE::SeqAB);
	fprintf(stdout, "RelSet:\n%s\n", set.toString().c_str());
}

TEST_F(TestScheduleRelSet, all_seq_ab) {

	ScheduleRelSet set(4);
	ASSERT_TRUE(set.setRel(0, 1, ScheduleRelE::SeqAB));
	ASSERT_TRUE(set.setRel(1, 2, ScheduleRelE::SeqAB));
	ASSERT_TRUE(set.setRel(2, 3, ScheduleRelE::SeqAB));
	ASSERT_EQ(set.getRel(0, 2), ScheduleRelE::SeqAB);
	fprintf(stdout, "RelSet:\n%s\n", set.toString().c_str());
}

TEST_F(TestScheduleRelSet, all_par_ab) {

	ScheduleRelSet set(4);
	ASSERT_TRUE(set.setRel(0, 1, ScheduleRelE::Par));
	ASSERT_TRUE(set.setRel(1, 2, ScheduleRelE::Par));
	ASSERT_TRUE(set.setRel(2, 3, ScheduleRelE::Par));
	fprintf(stdout, "RelSet:\n%s\n", set.toString().c_str());
}

TEST_F(TestScheduleRelSet, contradiction_1) {

	ScheduleRelSet set(4);
	ASSERT_TRUE(set.setRel(0, 1, ScheduleRelE::SeqAB));
	ASSERT_TRUE(set.setRel(1, 2, ScheduleRelE::SeqAB));
	ASSERT_FALSE(set.setRel(0, 1, ScheduleRelE::Par));
	fprintf(stdout, "RelSet:\n%s\n", set.toString().c_str());
}

} /* namespace arl */
