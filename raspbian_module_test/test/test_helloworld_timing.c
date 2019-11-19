/*
 * test_helloworld_timing.c
 *
 *  Created on: Nov 19, 2019
 *      Author: edward
 */

#include "unity.h"
#include "helloworld_timing.h"
#include "mock_module.h"
#include "mock_time.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_init(void)
{
	pr_info_Expect("Loading first!\n");

	init_logic();
}

void test_exit(void)
{
	typedef struct timeval timeval_t;
	timeval_t timeofDayStart;
	timeval_t timeofDayEnd;
	timeofDayStart.tv_sec = 219;
	timeofDayEnd.tv_sec = 319;
	pr_info_Expect("Unloading module after 100 seconds\n");

	do_gettimeofday_ReturnThruPtr_timeval(&timeofDayStart);
	do_gettimeofday_ReturnThruPtr_timeval(&timeofDayEnd);

	exit_logic();
}



