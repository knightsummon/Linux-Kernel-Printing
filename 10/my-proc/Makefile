.PHONY:all clean
ifneq ($(KERNELRELEASE),)

obj-m := my_proc.o

else
		
EXTRA_CFLAGS += -DDEBUG 
#KDIR := /lib/modules/4.4.0-62-generic/build
KDIR := /home/linux-4.4
all:
		make  CROSS_COMPILE=arm-linux-gnueabi- ARCH=arm -C $(KDIR) M=$(PWD) modules
		cp my_proc.ko /home/nfs
clean:
		rm -fr .*.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order .tmp_versions

endif
