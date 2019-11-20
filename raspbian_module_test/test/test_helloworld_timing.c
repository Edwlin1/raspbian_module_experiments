/*
 * test_helloworld_timing.c
 *
 *  Created on: Nov 19, 2019
 *      Author: edward
 */

#define HELLOWORLD_TIMING

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
	timeval_t timeofDayStart;
	timeofDayStart.tv_sec = 219;

	do_gettimeofday_Expect(&timeofDayStart);
	do_gettimeofday_IgnoreArg_timeval();
	do_gettimeofday_ReturnThruPtr_timeval(&timeofDayStart);

	pr_info_Expect("Loading first!\n");

	init_logic();
	resetTest();
}

void test_exit(void)
{
	timeval_t timeofDayStart;
	timeval_t timeofDayEnd;
	timeofDayStart.tv_sec = 219;
	timeofDayEnd.tv_sec = 319;

	do_gettimeofday_Expect(&timeofDayStart);
	do_gettimeofday_IgnoreArg_timeval();
	do_gettimeofday_ReturnThruPtr_timeval(&timeofDayStart);

	pr_info_Expect("Loading first!\n");

	init_logic();


	do_gettimeofday_Expect(&timeofDayEnd);
	do_gettimeofday_IgnoreArg_timeval();
	do_gettimeofday_ReturnThruPtr_timeval(&timeofDayEnd);

	pr_info_Expect("Unloading module after %ld seconds\n");

	exit_logic();
	resetTest();
}



