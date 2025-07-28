# Module name
obj-m := testDriver.o

# Path to BeagleBone kernel source or headers
BB_KERNEL_DIR := ~/BBB_Kernel/linux

# Cross compiler prefix
CROSS_COMPILE := arm-linux-gnueabihf-

# ARCH for BeagleBone
ARCH := arm

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(BB_KERNEL_DIR) M=$(PWD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(BB_KERNEL_DIR) M=$(PWD) clean