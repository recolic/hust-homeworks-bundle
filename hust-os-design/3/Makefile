ifneq ($(KERNELRELEASE),)
obj-m := hustmod.o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

hustmod.ko:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

ins: hustmod.ko
	insmod hustmod.ko
	mknod /dev/hustmod0 c $$(dmesg | grep 'HUSTMOD: device id' | tail -n 1 | sed 's/^.*MAJOR:MINOR = //g' | sed 's/:/ /')

rm:
	rmmod hustmod
	rm -f /dev/hustmod0

endif

