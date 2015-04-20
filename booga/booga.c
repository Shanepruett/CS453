


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include "booga.h"


static int booga_major = BOOGA_MAJOR;
module_param(booga_major, int, 0);
static int booga_nr_devs = BOOGA_NR_DEVS;
module_param(booga_nr_devs, int, o);

MODULE_AUTHOR("Shane Pruett");
MODULE_LICENSE("GPL v2");

static int booga_open (struct inode *inode, struct file *filp);
static int booga_release (struct inode *inode, struct file *filp);
static ssize_t booga_read (struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t booga_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static int __init booga_init (void);
static void __exit booga_exit (void);

static booga_dev *booga_device;

static struct file_operations booga_fops = {
	read:		booga_read,
	write:		booga_write,
	open:		booga_open,
	release:	booga_release,
//	init:		booga_init,
//	exit:		booga_exit,
};

//struct booga_dev {
//	char *data;
//	unsigned minor;
//};
//typedef struct booga_dev booga_dev;

//extern booga_dev Booga_Dev;

static void __exit booga_exit (void)
{	 
	unregister_chrdev(booga_major, "booga");
	//free (booga_device->data);
	kfree (booga_device);
	//free (booga_device->minor);	
	printk("<1> booga device driver: unloaded");
	
}


static int booga_open (struct inode *inode, struct file *filp)
{

	return 0;
}


static int booga_release (struct inode *inode, struct file *filp);
{

	return 0;
}


static ssize_t booga_read (struct file *filp, char *buf, size_t count, loff_t *f_pos);
{

	return 0;
}

static ssize_t booga_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos);
{

	return 0;
}



static int __init booga_init (void);
{
	int result;

	reult = register_chrdev(booga_major, "booga", &booga_fops);
	if (result < 0) {
		printk(KERN_WARNING "booga: can't get major %d\n", booga_major);
		return result;
	}	
	if (booga_major == 0) booga_major = result;
	printk("<1> booga device driver: loaded at major number %d\n", booga_major);

	booga_device = (struct Booga_Dev *) kmalloc(sizeof(struct Booga_Dev), GFP_KERNEL);
	if (!booga_device){
		result = -ENOMEM;
		goto fail_malloc;
	}
		
	return 0;

fail_malloc:
	unregistered_chrdev(booga_major, "booga");
	return result;

}




