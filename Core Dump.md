# Core Dump

1. Due to various exceptions or bugs, the application will cause abnormal exit or abort during execution

   2.The system will save the memory and register status when the program is running state, stack pointer, memory management information, various functions. The stack call information dump is in a core file

​	3.In embedded systems, core dumps sometimes pass through the serial port to prints out

## Core dump Setting

### Open Core Dump 

• /etc/profile：ulimit –c unlimited 

• Generate the fiel name core.pid：echo 1 > /proc/sys/kernel/core_uses_pid

### Core dump pattern setting

• To see the file pattern：cat /proc/sys/kernel/core_pattern

• Setting the file pattern ：**echo ./core.%e.%p**> /proc/sys/kernel/core_pattern 

### Core dump pattern



| %p     | The PID of the dumped process             |
| ------ | ----------------------------------------- |
| **%u** | **The UID of the dumped process**         |
| **%g** | **The group ID of the dumped process**    |
| **%s** | **The signal that caused this core dump** |
| **%t** | **The time of Core Dump**                 |
| **%h** | **The  name of the host machine**         |
| **%e** | **The name of the source file**           |



## Using gdb to view the dump core file

### Step

1. When compiling the program, add debugging information: -g

2. Usage: gdb program coredump 

3. Use bt to locate where the program goes wrong in the source file

 ## Rename the Generated dump Core file 

![1](https://github.com/knightsummon/Linux-Kernel-Printing/blob/main/Core%20Dump.assets/1.jpg)
