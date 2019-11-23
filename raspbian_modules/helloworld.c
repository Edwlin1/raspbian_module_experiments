/*
 * helloworld.c
 *
 *  Created on: Nov 17, 2019
 *      Author: edward
 */

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include "helloworld.h"

#define DEVICE_NAME "HelloWorldDevice"
#define CLASS_NAME "HelloClass"

#define FIRST_MINOR_NUMBER 0
#define TOTAL_MINOR_NUMBERS 1

static int device_open(struct inode* inode, struct file* file);
static int device_close(struct inode* inode, struct file* file);
static long device_ioctl(struct file* file, unsigned int command, unsigned long argument);
static const struct file_operations file_operations = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_close,
	.unlocked_ioctl = device_ioctl,
};

static struct miscdevice miscdevice_handle = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &file_operations,
};

int __init hello_init(void) {
	int result_code;

	pr_info("HELLOWORLD MESSAGE: Entry\n");

	//Register device with the kernel
	result_code = misc_register(&miscdevice_handle);
	if (result_code != 0) {
		pr_info("HELLOWORLD ERROR: Unable register miscellaneous device, result code: %d\n",
				result_code);
		return result_code;
	}

	pr_info("HELLOWORLD MESSAGE: Started, registered with minor: %d\n", miscdevice_handle.minor);
	return 0;
}

void __exit hello_exit(void) {
	misc_deregister(&miscdevice_handle);

	pr_info("HELLOWORLD MESSAGE: Exit\n");
}

static int device_open(struct inode* inode, struct file* file)
{
	pr_info("HELLOWORLD: device_open() was called\n");
	return 0;
}

static int device_close(struct inode* inode, struct file* file)
{
	pr_info("HELLOWORLD: device_close() was called\n");
	return 0;
}

static long device_ioctl(struct file* file, unsigned int command, unsigned long argument)
{
	pr_info("HELLOWORLD: device_ioctl() was called, command %d, argument %ld\n", command, argument);
	return 0;
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Edward Linderoth-Olson <edward.linderotholson@gmail.com>");
MODULE_DESCRIPTION("Demonstration module");

