#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/of.h>

static int misc_dev_open(struct inode *inode, struct file *file)
{
    pr_info("misc_device is now open.\n");
    return 0;
}

static int misc_dev_close(struct inode *inode, struct file *file)
{
    pr_info("misc_device is now closed.\n");
    return 0;
}

static const struct file_operations misc_dev_fops = {
    .owner = THIS_MODULE,
    .open = misc_dev_open,
    .release = misc_dev_close,
};

static struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "misc_dev",
	.fops = &misc_dev_fops,
};

/* probe() function to initialize the device */
static int __init dev_probe(struct platform_device *pdev)
{
	int ret;
	pr_info("dev_probe() called");
	ret = misc_register(&misc_dev);
	if (ret != 0)
	{
		pr_err("Problem registering misc device");
		return ret;
	}
	pr_info("Registration successful, minor#: %i\n", misc_dev.minor);
	return 0;
}

/* remove() function to remove the device */
static int __exit dev_remove(struct platform_device *pdev)
{
	pr_info("dev_remove() called");
	misc_deregister(&misc_dev);
	return 0;
}

/* List of devices this driver manages */
static const struct of_device_id of_ids[] = {
	{ .compatible = "neerajkc,dummy_misc_dev" },
	{},
};
MODULE_DEVICE_TABLE(of, of_ids);

/* Define a platform_driver structure */
static struct platform_driver dummy_platform_driver = {
	.probe = dev_probe,
	.remove = dev_remove,
	.driver = {
				.name = "dummy_platform_driver",
				.of_match_table = of_ids,
				.owner = THIS_MODULE,
	}
};

static int demo_init(void)
{
	pr_info("demo_init entered\n");
	platform_driver_register(&dummy_platform_driver);
	pr_info("demo_init exited\n");
	return 0;
}

static void demo_exit(void)
{
	pr_info("demo_exit entered\n");
	platform_driver_unregister(&dummy_platform_driver);
	pr_info("demo_exit exited\n");
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neeraj Kumar");
MODULE_DESCRIPTION("This is a dummy platform driver");
