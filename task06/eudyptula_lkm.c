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

// interal driver data
struct device_ctx {
	char *id;
	struct device *dev;
};

static struct device_ctx ctx = {
	.id = "n2h9"
};

static int misc_open(struct inode *inode, struct file *f)
{

	dev_dbg(ctx.dev, "open method called \n");
	return nonseekable_open(inode, f);
}

static ssize_t misc_read(struct file *f, char __user *ubuf, size_t count, loff_t *offset)
{
	size_t strsize = strlen(ctx.id);
	dev_dbg(ctx.dev, "read method called \n");
	if(copy_to_user(ubuf, ctx.id, strsize)) {
		dev_warn(ctx.dev, "copy_to_user failed");
		return -EFAULT;
	}

	return strsize;
}

static ssize_t misc_write(struct file *f, const char __user *ubuf, size_t count, loff_t *offset)
{
	char *kbuf; 
	unsigned long uncopied_num;
	
	dev_dbg(ctx.dev, "write method called\n");

	kbuf = (char *)kvmalloc(count, 0);
	dev_dbg(ctx.dev, "kbuf allocated\n");
	
	uncopied_num = copy_from_user(kbuf, ubuf, count);
	dev_dbg(ctx.dev, "copy_from_user called\n");
	if (uncopied_num > 0) {
		dev_dbg(ctx.dev, "copy_from_user returned not 0\n");
		goto err0;
	}
	
	if (strcmp(ctx.id, kbuf) != 0) {
		dev_dbg(ctx.dev, "write string not equal to id\n");
		goto err0;
	}

	kvfree(kbuf);
	return strlen(ctx.id);

	err0:
		kvfree(kbuf);
		return -EINVAL;
}

static int misc_release(struct inode *inode, struct file *f)
{
	dev_dbg(ctx.dev, "release method called \n");
	return 0;
}

static const struct file_operations misc_fops = {
	.open = misc_open,
	.read = misc_read,
	.write = misc_write,
	.release = misc_release,
	.llseek = no_llseek,
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

	ret = misc_register(&n2h9_miscdev);
	if (ret != 0) {
		pr_err("misc device registration error, aborting\n");
		return ret;
	}

	ctx.dev = n2h9_miscdev.this_device;
	
	dev_dbg(
		ctx.dev, 
		"misc device driver registered, minor number = %d", 
		n2h9_miscdev.minor
	);

	return 0; /* success */
}

static void __exit module_exit_func(void)
{
	ctx.dev = NULL;
	misc_deregister(&n2h9_miscdev);
	pr_debug("misc device deregistered\n");
}


module_init(module_init_func);
module_exit(module_exit_func);
