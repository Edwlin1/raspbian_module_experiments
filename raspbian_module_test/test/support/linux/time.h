/*
 * timing.h
 *
 *  Created on: Nov 19, 2019
 *      Author: edward
 */

#ifndef TEST_SUPPORT_LINUX_TIME_H_
#define TEST_SUPPORT_LINUX_TIME_H_

#include <bits/types/struct_timeval.h>

typedef struct {
	long sec;
} test_struct_t;

typedef struct timeval timeval_t;

void do_gettimeofday(timeval_t* timeval);

void do_testStruct(test_struct_t* testStruct);

#endif /* TEST_SUPPORT_LINUX_TIME_H_ */
