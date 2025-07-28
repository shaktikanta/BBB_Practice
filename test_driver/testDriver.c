#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/*
    Module init function
*/
static int __init testDriver_init(void) {
    printk(KERN_INFO "Test Driver Loaded Sucessfully\n");
    printk(KERN_INFO "JAI JAGNNATH !!!\n");
    return 0;
}

void __exit testDriver_exit(void){
    printk(KERN_INFO "EXITING...\n");
    printk(KERN_INFO "BYE BYE !!!\n");
}

module_init(testDriver_init);
module_exit(testDriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shaktikanta Nayak");
MODULE_DESCRIPTION("TEST DRIVER FOR LEARNING");
MODULE_VERSION("1:0:1");