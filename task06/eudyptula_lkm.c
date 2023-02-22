// SPDX-License-Identifier: GPL-2.0
#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#define MODNAME   "eudyptula"
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("n2h9");
MODULE_DESCRIPTION("task01");

static int misc_open(struct inode *inode, struct file *f)
{
	// @TODO
	return 0;
}

static ssize_t misc_read(struct file *f, char __user *ubuff, size_t count, loff_t *offset)
{
	// @TODO
	return 0;
}

static ssize_t misc_write(struct file *f, const char __user *ubuff, size_t count, loff_t *offset)
{
	// @TODO
	return 0;
}

static int misc_release(struct inode *inode, struct file *f)
{
	// @TODO
	return 0;
}

static const struct file_operations misc_fops = {
	.open = misc_open,
	.read = misc_read,
	.write = misc_write,
	.release = misc_release,
};

static struct miscdevice n2h9_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "eudyptula",
	.mode = 0666,
	.fops = &misc_fops,
};

static int __init module_init_func(void)
{
	int ret;

	pr_debug("Hello World!\n");
	ret = misc_register(&n2h9_miscdev);
	if (ret != 0) {
		pr_err("misc device registration error, aborting\n");
		return ret;
	}

	return 0;	/* success */
}

static void __exit module_exit_func(void)
{
}


module_init(module_init_func);
module_exit(module_exit_func);
