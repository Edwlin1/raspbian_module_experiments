/*
 * helloworld.c
 *
 *  Created on: Nov 17, 2019
 *      Author: edward
 */

#include <linux/module.h>

static int num = 5;

module_param(num, int, S_IRUGO);

static int __init hello_init(void)
{
	pr_info("Init: Parameter is %d.\n", num);
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Exit: Parameter is %d.\n", num);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Linderoth-Olson <edward.linderotholson@gmail.com>");
MODULE_DESCRIPTION("Demonstration module that prints its parameter5 on entry and exit");

