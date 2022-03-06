#include <linux/module.h>

#include <linux/cdev.h>
#include <linux/fs.h>

#define MAJOR_NUM 100

static struct cdev dummy_dev;

static int dummy_dev_open(struct inode *inode, struct file *file)
{
    pr_info("dummy_device is now open.\n");
    return 0;
}

static int dummy_dev_close(struct inode *inode, struct file *file)
{
    pr_info("dummy_device is now closed.\n");
    return 0;
}

static const struct file_operations dummy_dev_fops = {
    .owner = THIS_MODULE,
    .open = dummy_dev_open,
    .release = dummy_dev_close,
};

static char *name = "Stranger";

module_param(name, charp, 0);

static int __init hello_init(void)
{
    int ret;

    dev_t dev = MKDEV(MAJOR_NUM, 0);
    pr_info("Hello, %s\n", name);

    ret = register_chrdev_region(dev, 1, "dummy_char_device");
    if (ret < 0) {
        pr_info("Problem allocating major number %d\n", MAJOR_NUM);
        return ret;
    }

    cdev_init(&dummy_dev, &dummy_dev_fops);
    ret = cdev_add(&dummy_dev, dev, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev, 1);
        pr_info("Problem adding cdev\n");
        return ret;
    }

    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, %s\n", name);
    cdev_del(&dummy_dev);
    unregister_chrdev_region(MKDEV(MAJOR_NUM, 0), 1);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neeraj Kumar");
MODULE_DESCRIPTION("This module creates a dummy char device");