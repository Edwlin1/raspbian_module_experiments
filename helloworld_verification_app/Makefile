

all: ioctl_test

app: ioctl_test.c
	$(CC) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -o $@ $^

clean: 
	rm ioctl_test