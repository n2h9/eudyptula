#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define MODNAME   "eudyptula_task01"
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("n2h9");
MODULE_DESCRIPTION("task01");



static int __init module_init_func(void)
{
	pr_debug("Hello World!\n");

	return 0;	/* success */
}

static void __exit module_exit_func(void)
{
}

module_init(module_init_func);
module_exit(module_exit_func);