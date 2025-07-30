#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

dev_t dev = 0;

/* Init Method */
static int __init dynamicMajorDriver_init(void) {
    printk(KERN_INFO "Module loaded successfully.\n");
    if(alloc_chrdev_region(&dev, 0, 1, "Dynamic_major") < 0){
        printk(KERN_INFO "module major and minor no allocation failed fro device 1\n");
        return -1;
    }
    printk(KERN_INFO "MAJOR: %d & Minor: %d\n", MAJOR(dev), MINOR(dev));
    return 0;
}

/* Exit Method */
void __exit dynamicMajorDriver_exit(void) {
    /* Unregister the allocated nos for the device */
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Module removed successfully.\n");
}

module_init(dynamicMajorDriver_init);
module_exit(dynamicMajorDriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakti");
MODULE_DESCRIPTION("Dynammic allocation of amjor an dminor no for a device");
MODULE_VERSION("1:0.4");