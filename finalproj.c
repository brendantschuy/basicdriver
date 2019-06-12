#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>


#define DEVICE_NAME "cdd_device"

#define MSG_LEN 128


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brendan Tschuy");
MODULE_DESCRIPTION("CS 533 Final Project");
MODULE_VERSION("1.0");

//prevents concurrency errors
//(makeshift lock)
static int isDeviceOpen = 0;

//length of message allowed
static char msg[MSG_LEN];
static char *msgPtr;
static char *ogPtr;

static int cdd_open(struct inode * mem, struct file * fp)
{
	/*if(isDeviceOpen)
	{
		printk(KERN_ALERT "busy right now.");
		return -EBUSY;
	}*/
	isDeviceOpen++;

	msgPtr = msg;
	ogPtr = msg;

	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

	return 0;
}

static int cdd_close(struct inode * mem, struct file * fp)
{
	isDeviceOpen--;
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

static ssize_t cdd_read(struct file * fp, char * buffer, size_t length, loff_t * offset)
{
	int bytesRead = 0;

	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	if(*msgPtr == 0)
	{
		return 0;
	}
	while(length && *msgPtr)
	{
		put_user(*(msgPtr++), buffer++);
		length--;
		bytesRead++;
	}
	return bytesRead;
}

static ssize_t cdd_write(struct file * fp, const char * buffer, size_t length, loff_t * offset)
{
	int i;
	int j;

	j = 0;

/*	while(msg[j])
	{
		j++;
	}*/

	printk(KERN_INFO "In cdd_write.\n");
	printk(KERN_INFO "Length of string provided: %ld", length);
	for(i = j; i < length; i++)
	{
		get_user(msg[i], buffer + i);
	}
	msgPtr = msg;
	return i;
}


//static int major_num;
//static char *msg_ptr;

static struct file_operations file_ops = {
	.owner = THIS_MODULE,
	.read = cdd_read,
	.write = cdd_write,
	.open = cdd_open,
	.release = cdd_close
};

static int __init cdd_init(void)
{
	register_chrdev(240, "cdd", &file_ops);
	printk(KERN_INFO "Initialized module cdd.\n");

	msg[0] = '\0';
	return 0;
}

static void __exit cdd_exit(void)
{
	printk(KERN_INFO "Exited module cdd.\n");
	unregister_chrdev(240, DEVICE_NAME);
}

module_init(cdd_init);
module_exit(cdd_exit);
