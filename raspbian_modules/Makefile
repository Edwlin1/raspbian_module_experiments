obj-m += helloworld.o helloworld_with_parameters.o

KERNEL_DIR ?= $(HOME)/linux
BUILD_DIR ?= $(PWD)/build
BUILD_DIR_MAKEFILE ?= $(PWD)/build/Makefile

all: $(BUILD_DIR_MAKEFILE)
	make -C $(KERNEL_DIR) \
	ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
	M=$(BUILD_DIR) src=$(PWD) modules

$(BUILD_DIR):
	mkdir -p "$@"

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	touch "$@"
	
clean:
	make -C $(KERNEL_DIR) \
	ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
	M=$(BUILD_DIR) src=$(PWD) clean
