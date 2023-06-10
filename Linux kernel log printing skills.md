

# 1. Linux kernel log printing skills



Try to print a "Hello World!" in kernel using NFS

Three files beneath folder "x86-driver"

Makefile:

```
.PHONY:all clean
ifneq ($(KERNELRELEASE),)

obj-m := hello.o

else
		
KDIR := /lib/modules/4.4.0-62-generic/build
all:
		make  -C $(KDIR) M=$(PWD) modules
clean:
		rm -fr .*.cmd *.ko *.o *.mod.o *.mod.c *.symvers *.order .*.ko .tmp_versions

endif
```

hello.c:

```
#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk(KERN_ALERT"-----------------!\n");
	printk(KERN_ALERT"hello world!\n");
	printk(KERN_ALERT"hello world!\n");
	printk(KERN_ALERT"-----------------!\n");

	BUG();
	return 0;
}

static void  __exit hello_exit(void)
{
	printk(KERN_ALERT"goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

```

console.sh

```
#!/bin/sh
while true
do
	sudo dmesg -c
	sleep 1
done
```

**sudo make** sometimes ca not make, try add specified destination to resolve this question

![1](https://github.com/knightsummon/Linux-Kernel-Printing/blob/main/Linux%20kernel%20log%20printing%20skills.assets/1.jpg)

The command "sudo make -C /usr/src/linux-headers-5.4.0-52-generic M=$(pwd) modules" is a Linux command used to build kernel modules. Let's break down each component:

- "sudo" is a command used in Unix-like systems to run a command with administrative or superuser privileges. It allows the user to execute the subsequent command with elevated permissions.
- "make" is a build automation tool commonly used in Linux environments. It is used to compile and build software projects, including kernel modules.
- "-C /usr/src/linux-headers-5.4.0-52-generic" specifies the directory where the make command should operate. In this case, it points to the Linux kernel headers directory for the version "5.4.0-52-generic." The kernel headers provide the necessary files and definitions to compile kernel modules.
- "M=$(pwd)" sets the value of the "M" variable to the current working directory. This variable is often used in kernel module build systems to indicate the source directory of the module to be built.
- "modules" is a target specified to the make command, indicating that it should build kernel modules.
<<<<<<< HEAD
=======

## Failure: Vexpress Compile hello.ko failed

What I meet the question is Vexpress can not compile the hello.ko which I make in the Linux Server

```
uname -r
```

Found the kernel of Vexpress is mot match the kernel od Linux Ubuntu Server

![2](https://github.com/knightsummon/Linux-Kernel-Printing/blob/main/Linux%20kernel%20log%20printing%20skills.assets/2.jpg)

Try to download a Linux kernel 5.4.70 and try to compile it on Ubuntu.
>>>>>>> 3b45713 (Version 2)
