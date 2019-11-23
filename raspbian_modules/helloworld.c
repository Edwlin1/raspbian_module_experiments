/*
 * helloworld.c
 *
 *  Created on: Nov 17, 2019
 *      Author: edward
 */

#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include "helloworld.h"

#define DEVICE_NAME "HelloWorldDevice"
#define CLASS_NAME "HelloClass"

#define FIRST_MINOR_NUMBER 0
#define TOTAL_MINOR_NUMBERS 1

static dev_t device_driver_number;
static struct cdev character_device_handle;
static struct device* p_device_node_handle;
static struct class* p_device_class_handle;

static int device_open(struct inode* inode, struct file* file);
static int device_close(struct inode* inode, struct file* file);
static long device_ioctl(struct file* file, unsigned int command, unsigned long argument);
static const struct file_operations file_operations = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_close,
	.unlocked_ioctl = device_ioctl,
};

static int __init hello_init(void) {
	return init_logic();
}

int inline init_logic(void) {
	int result_code, major, minor;

	pr_info("HELLOWORLD MESSAGE: Entry\n");

	//Allocate device driver numbers (Major & Minor)
	result_code = alloc_chrdev_region(&device_driver_number, FIRST_MINOR_NUMBER,
									  TOTAL_MINOR_NUMBERS, DEVICE_NAME);
	if (result_code < 0) {
		pr_info("HELLOWORLD ERROR: Unable to dynamically allocate device major and minor numbers\n");
		return result_code;
	}

	major = MAJOR(device_driver_number);
	minor = MKDEV(major, FIRST_MINOR_NUMBER);
	pr_info("HELLOWORLD MESSAGE: Received device id numbers major %d, minor %d",
			major, minor);

	//Create and register character device(s)
	cdev_init(&character_device_handle, &file_operations);
	result_code = cdev_add(&character_device_handle, device_driver_number, TOTAL_MINOR_NUMBERS);
	if (result_code < 0) {
		unregister_chrdev_region(device_driver_number, TOTAL_MINOR_NUMBERS);
		pr_info("HELLOWORLD ERROR: Unable to register as character device, result code: %d\n",
				result_code);
		return result_code;
	}

	//Create device class
	p_device_class_handle = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(p_device_class_handle)) {
		cdev_del(&character_device_handle);
		unregister_chrdev_region(device_driver_number, TOTAL_MINOR_NUMBERS);
		pr_info("HELLOWORLD ERROR: Unable to register device class, returned address: %lu\n",
				(long)p_device_class_handle);
		return PTR_ERR(p_device_class_handle);
	}

	//Create device node
	p_device_node_handle = device_create(p_device_class_handle, NULL, device_driver_number,
										 NULL, DEVICE_NAME);
	if(IS_ERR(p_device_node_handle)) {
		class_destroy(p_device_class_handle);
		cdev_del(&character_device_handle);
		unregister_chrdev_region(device_driver_number, TOTAL_MINOR_NUMBERS);
		pr_info("HELLOWORLD ERROR: Unable to create device node, returned address: %lu\n",
				(long)p_device_node_handle);
		return PTR_ERR(p_device_node_handle);
	}

	pr_info("HELLOWORLD MESSAGE: Started\n");
	return 0;
}

static void __exit hello_exit(void) {
	exit_logic();
}

int inline exit_logic(void) {
	device_destroy(p_device_class_handle, device_driver_number);
	class_destroy(p_device_class_handle);
	cdev_del(&character_device_handle);
	unregister_chrdev_region(device_driver_number, TOTAL_MINOR_NUMBERS);
	pr_info("HELLOWORLD MESSAGE: Exit\n");
	return 0;
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

