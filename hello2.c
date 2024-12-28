#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/slab.h> 
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Hello2 Kernel Module");
MODULE_VERSION("1.0");

static unsigned int call_count = 1;
module_param(call_count, uint, 0660);
MODULE_PARM_DESC(call_count, "Number of times to call print_hello");

static int __init hello2_init(void)
{
    int i;
    void *event = NULL; 

    
    if (call_count > 10) {
        pr_err("Error: call_count is %u. Module will not load.\n", call_count);
        return -EINVAL; 
    }

    if (call_count == 0 || (call_count >= 5 && call_count <= 10)) {
        pr_warn("Warning: call_count is %u. Proceeding with caution.\n", call_count);
    }

    pr_info("Calling print_hello() %u times\n", call_count);

    for (i = 0; i < call_count; i++) {
        if (i == 4) { 
            event = NULL; 
        } else {
            event = kmalloc(128, GFP_KERNEL); 
        }

        if (!event) {
            pr_err("Failed to allocate memory for event on iteration %d\n", i);
            return -ENOMEM; 
        }

        print_hello();

        kfree(event); 
    }

    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2: Module exiting\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
