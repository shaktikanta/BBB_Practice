#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>


/* Major and Minor no allocation for the device */
dev_t dev = 0;
static struct class *drvrClass;

/* Module Init Function */
static int __init charDriverDevfs_init(void) {
    
    /* Allocate the major and minor no dynamically */
    if(alloc_chrdev_region(&dev, 0, 1, "CharDriver_Devfs") < 0) {
        printk(KERN_INFO "Failed to allocate device\n");
        return -1;
    }
    pr_info("MAJOR: %d MINOR: %d \n", MAJOR(dev), MINOR(dev));

    /* Allocate structure class for the device type */
    drvrClass = class_create(THIS_MODULE, "CharDriver_Class");
    if(IS_ERR(drvrClass)) {
        pr_err("Unable to create device structure class\n");
        // return -1;
        goto class_destroy;
    }
    pr_info("Class created for the device type\n");

    /* Create Device type */
    if(IS_ERR(device_create(drvrClass, NULL, dev, NULL, "CharDriver_Device"))) {
        pr_err("Uanble to create the device type\n");
        // return -1;
        goto device_destroy;
    }
    pr_info("Device created \n");

    printk(KERN_INFO "Module Inserted Successfully\n");
    return 0;


class_destroy:
    class_destroy(drvrClass);
device_destroy:
    device_destroy(drvrClass, dev);

    return -1;
}

/* Module Exit Function */
void __exit charDriverDevfs_exit(void) {
    /* device destroy */
    device_destroy(drvrClass, dev);
    /* class destroy */
    class_destroy(drvrClass);
    /* uregister chardev region / remove major and minor no */
    unregister_chrdev_region(dev, 1);
    pr_info("Module Removed Successfully\n");
}

module_init(charDriverDevfs_init);
module_exit(charDriverDevfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakti");
MODULE_DESCRIPTION("Creating teh /dev structure class for a driver");
MODULE_VERSION("1:0.5");