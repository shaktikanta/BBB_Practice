#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int val, arr[4];
char *name;
int cb_val = 0;

/* Set the variable values accepted from command line to the vars*/
module_param(val, int, S_IWUSR|S_IRUSR);
module_param(name, charp, 0644);
module_param_array(arr, int, NULL, 0644);

/* Call back function for notifying the user when the value is changing. */
int notify_val(const char *val, const struct kernel_param *kp){
    int res = param_set_int(val, kp);
    if(res == 0) {
        printk(KERN_INFO "Value is changed\n Value : %d\n", cb_val);
        return 0;
    }
    return -1;
}

/* Declare avariable of type Kernel structure for set and get function */
struct kernel_param_ops driver_param = 
{
    .set = &notify_val,     // call back function address
    .get = &param_get_int,  // standard getter function
};

static int __init argumentDriver_init(void) {
    /* Trying to access the variables values given form command line */
    printk(KERN_INFO "Val : %d", val);
    printk(KERN_INFO "Name : %s", name);
    printk(KERN_INFO "callback var val : %d", cb_val);
    int i = 0;
    for (i = 0; i < 4; i++){
        printk(KERN_INFO "Array[%d] : %d", i, arr[i]);
    }
    printk(KERN_INFO "Module is loaded successfully.\n");
    return 0;
} 

void __exit argumentDriver_exit(void) {
    printk(KERN_INFO "Module removed successfully\n");
}

module_init(argumentDriver_init);
module_exit(argumentDriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shaktikanta Nayak");
MODULE_DESCRIPTION("A sample driver for testing cmd line arguments for a driver");
MODULE_VERSION("1:0:2");