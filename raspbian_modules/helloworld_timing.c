/*
 * helloworld_timing.c
 *
 *  Created on: Nov 19, 2019
 *      Author: edward
 */

#include <linux/module.h>
#include <linux/time.h>
#include "helloworld_timing.h"

static struct timeval start_time;

static int __init hello_init(void)
{
	init_logic();
	return 0;
}

void init_logic(void)
{
	do_gettimeofday(&start_time);
	pr_info("Loading first!\n");
}

static void __exit hello_exit(void)
{
	exit_logic();
}

void exit_logic(void)
{
	struct timeval end_time;
	do_gettimeofday(&end_time);
	pr_info("Unloading module after %ld seconds\n", end_time.tv_sec - start_time.tv_sec);
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Linderoth-Olson <edward.linderotholson@gmail.com>");
MODULE_DESCRIPTION("Demonstration module that prints Hello world on entry and exit");

