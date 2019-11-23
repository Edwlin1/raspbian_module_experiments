/*
 * ioctl_test.c
 *
 *  Created on: Nov 20, 2019
 *      Author: edward
 */

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int main (void)
{
	int hw_device = open("/dev/HelloWorldDevice", 0);

	if(hw_device < 0) {
		perror("Hellworld App Error: Fail to open device file: /dev/HelloWorldDevice\n");
	} else {
		ioctl(hw_device, 100, 110);
		close(hw_device);
	}

	return 0;
}
