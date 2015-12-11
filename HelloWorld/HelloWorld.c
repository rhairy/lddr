#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

/* Initialization function;
   This is run upon insertion to the kernel. */
static int HelloWorld(void)
{
  printk(KERN_ALERT "Hello, World!\n");
  return 0;
}

/* Exit function;
   This is run after the module is removed from the kernel. */
static void HelloExit(void)
{
  printk(KERN_ALERT "Goodbye, World!\n");
}

/* Define HelloWorld as our initialization function */
module_init(HelloWorld);
/* Define HelloExit as our exit function */
module_exit(HelloExit);
