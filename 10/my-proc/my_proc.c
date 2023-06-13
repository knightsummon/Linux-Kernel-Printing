#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>

#include<linux/delay.h>
#include<linux/slab.h>

#include <asm/uaccess.h>
#include <asm/io.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("litao.wang");

static struct proc_dir_entry *root;
static struct proc_dir_entry *entry;
static struct proc_dir_entry *node;

char proc_buf[200] ={0}; 
unsigned long value;
int myshow(struct seq_file *file,void *v)
{
	seq_printf(file,"%lu\n",value);
	return 0;
}

static int my_proc_open(struct inode *inode,struct file  *file)
{
	single_open(file,myshow,inode->i_private);
	return 0;
}

static ssize_t my_proc_write(struct file *file,const char *buf,size_t count,loff_t*pos)
{
	if(count > 200)
		count = 200;
	if(copy_from_user(proc_buf,buf,count))
	{
		printk("proc write error!\n");
		return -EFAULT;
	}
	value = simple_strtoul(proc_buf,NULL,10);
	return count;
}

static const struct file_operations my_proc_fops ={
	.owner  = THIS_MODULE,
	.open   = my_proc_open,
	.read   = seq_read,
	.release   = single_release,
	.llseek   = seq_lseek,
	.write  = my_proc_write,
};

static int my_proc_init(void)
{
	root = proc_mkdir("my_proc",NULL);
	if(NULL == root)
	{
		printk("Creat root /proc/my_proc error!\n");
		return -1;
	}
	printk("Creat entry /proc/my_proc...\n");

	entry = proc_mkdir_mode("my_entry",666,root);
	if(NULL == entry)
	{
		printk("Creat entry /proc/my_entry error!\n");
		goto error_exit;
	}
	printk("Creat entry /proc/my_proc/my_entry...\n");
	
	node = proc_create_data("my_node",666,root,&my_proc_fops,NULL);
	if(NULL == node)
	{
		printk("Creat node /proc/my_node error!\n");
		goto error_exit;
	}
	printk("Creat node /proc/my_proc/my_node...\n");

	return 0;

error_exit:
	remove_proc_entry("my_proc",root);
	return -1;
}

static void  __exit my_proc_exit(void)
{
	printk("remove my_proc...\n");
	remove_proc_entry("my_node",root);
	remove_proc_entry("my_entry",root);
	remove_proc_entry("my_proc",NULL);
	printk("Done!\n");
}

module_init(my_proc_init);
module_exit(my_proc_exit);
