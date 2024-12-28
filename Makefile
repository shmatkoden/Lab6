ifneq ($(KERNELRELEASE),)
# Kbuild part
obj-m := hello1.o hello2.o
ccflags-y := -I$(src)/inc -g
else
# Normal Makefile
KDIR ?= /path/to/linux-4.19.324
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

strip:
	$(CROSS_COMPILE)strip -g hello1.ko hello2.ko
endif


