/*
 * helloworld.c
 *
 *  Created on: Nov 17, 2019
 *      Author: edward
 */

#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include "helloworld.h"

#define HW_MAJOR_NUM	202

static dev_t dev;
static struct cdev hw_device;

static int hw_device_open(struct inode* inode, struct file* file);
static int hw_device_close(struct inode* inode, struct file* file);
static long hw_device_ioctl(struct file* file, unsigned int command, unsigned long argument);
static const struct file_operations hw_file_operations = {
	.owner = THIS_MODULE,
	.open = hw_device_open,
	.release = hw_device_close,
	.unlocked_ioctl = hw_device_ioctl,
};

static int __init hello_init(void) {
	return init_logic();
}

int inline init_logic(void) {
	int ret;
	dev = MKDEV(HW_MAJOR_NUM, 0);
	ret = register_chrdev_region(dev, 1, "helloworld_device");
	if (ret < 0) {
		pr_info("HELLOWORLD ERROR: Unable to allocate major number: %d\n",
				HW_MAJOR_NUM);
		return ret;
	}

	cdev_init(&hw_device, &hw_file_operations);
	ret = cdev_add(&hw_device, dev, 1);
	if (ret < 0) {
		unregister_chrdev_region(dev, 1);
		pr_info("HELLOWORLD ERROR: Unable to add cdev\n");
		return ret;
	}

	pr_info("HELLOWORLD MESSAGE: Started\n");
	return 0;
}

static void __exit hello_exit(void) {
	exit_logic();
}

int inline exit_logic(void) {
	cdev_del(&hw_device);
	unregister_chrdev_region(dev, 1);
	pr_info("HELLOWORLD MESSAGE: Exiting\n");
	return 0;
}

static int hw_device_open(struct inode* inode, struct file* file)
{
	pr_info("hw_device_open() was called\n");
	return 0;
}

static int hw_device_close(struct inode* inode, struct file* file)
{
	pr_info("hw_device_close() was called\n");
	return 0;
}

static long hw_device_ioctl(struct file* file, unsigned int command, unsigned long argument)
{
	pr_info("hw_device_ioctl() was called, command %d, argument %ld\n", command, argument);
	return 0;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Linderoth-Olson <edward.linderotholson@gmail.com>");
MODULE_DESCRIPTION(
		"Demonstration module that prints Hello world on entry and exit");

