/*
 * helloworld.c
 *
 *  Created on: Nov 17, 2019
 *      Author: edward
 */

#include <linux/module.h>
#include "helloworld.h"

static int __init hello_init(void)
{
	init_logic();
	return 0;
}

void init_logic(void)
{
	pr_info("Hello world init\n");
}

static void __exit hello_exit(void)
{
	exit_logic();
}

void exit_logic(void)
{
	pr_info("Hello world exit\n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Linderoth-Olson <edward.linderotholson@gmail.com>");
MODULE_DESCRIPTION("Demonstration module that prints Hello world on entry and exit");

