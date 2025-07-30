/* Static declaration Method for major and Minor no */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>


/* Allocate statically the Major and Minor No */
dev_t dev = MKDEV(235, 0);


/* Init Method */
static int __init firstCharDriver_init(void) {
    if(register_chrdev_region(dev, 1, "First Char Driver") == 0){
        printk(KERN_INFO "MAJOR: %d - MINOR: %d\n", MAJOR(dev), MINOR(dev));
        printk("Module Loaded Sucessfully.\n");
    } else {
        printk(KERN_INFO "Allocating driver no is failed.\n");
    }
    return 0;
}

/* Exit Method */
void __exit firstCharDriver_exit(void) {
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Module removed successfully.\n");
}


/* Invoking init and exit function */
module_init(firstCharDriver_init);
module_exit(firstCharDriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakti");
MODULE_DESCRIPTION("Allocating Major and Minor no example for a char driver");
MODULE_VERSION("1.0.3");