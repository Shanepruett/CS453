/*
* author: Shane Pruett
*
*/

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
#include <linux/random.h>
#include "booga.h"


static int booga_major = BOOGA_MAJOR;
module_param(booga_major, int, 0);
static int booga_nr_devs = BOOGA_NR_DEVS;
module_param(booga_nr_devs, int, 0);

MODULE_AUTHOR("Shane Pruett");
MODULE_LICENSE("GPL v2");

static int booga_open (struct inode *inode, struct file *filp);
static int booga_release (struct inode *inode, struct file *filp);
static ssize_t booga_read (struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t booga_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static int __init booga_init (void);
static void __exit booga_exit (void);

static char* stream_1 = "booga! booga! ";
static char* stream_2 = "googoo! gaagaa! ";
static char* stream_3 = "neka! maka! ";
static char* stream_4 = "wooga! wooga! ";

static booga_dev *booga_device;

static struct file_operations booga_fops = {
	read:		booga_read,
	write:		booga_write,
	open:		booga_open,
	release:	booga_release,
};


//static struct proc_dir_entry* booga_proc_file;

static void __exit booga_exit (void)
{	 
//	remove_proc_entry("device/booga", NULL);
	
	unregister_chrdev(booga_major, "booga");
	kfree (booga_device);
	printk("<1> booga device driver: unloaded");
	
}


static int booga_open (struct inode *inode, struct file *filp)
{

	return 0;
}


static int booga_release (struct inode *inode, struct file *filp)
{

	return 0;
}


static ssize_t booga_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	// update stats proc info
	char choice;
	// random phrase
	char randvalue;
	get_random_bytes(&randvalue, 1);
	choice = (randvalue & 0x7F) % 4;

	printk("count= %d\n",(int) count);

	return 0;
}

static ssize_t booga_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{

	return 0;
}



static int __init booga_init (void)
{
	int result;

	result = register_chrdev(booga_major, "booga", &booga_fops);
	if (result < 0) {
		printk(KERN_WARNING "booga: can't get major %d\n", booga_major);
		return result;
	}	
	if (booga_major == 0) booga_major = result;
	printk("<1> booga device driver: loaded at major number %d\n", booga_major);

	booga_device = (struct booga_dev *) kmalloc(sizeof(struct booga_dev), GFP_KERNEL);
	if (!booga_device){
		result = -ENOMEM;
		goto fail_malloc;
	}
	// init device stuff

	booga_device->minor = result;

//	booga_proc_file = proc_create("driver/booga", 0, NULL, &booga_fops);
//	if (!booga_proc_file) {
//		result = -ENOMEM;
//		goto fail_malloc;
//	}	
		
	return 0;

fail_malloc:
	unregister_chrdev(booga_major, "booga");
//	remove_proc_entry("driver/booga", NULL );
	return result;

}


module_init(booga_init);
module_exit(booga_exit);

