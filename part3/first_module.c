#include <linux/module.h>

static char *name = "Stranger";

module_param(name, charp, 0);

static int __init hello_init(void)
{
    pr_info("Hello, %s", name);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, %s", name);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neeraj Kumar");
MODULE_DESCRIPTION("A basic demo module");