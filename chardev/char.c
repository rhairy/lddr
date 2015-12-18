/* char.c driver source code */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MINOR 0
#define NUM_DEVS 1
#define DEVICE_NAME "char"

/* Prototypes; These will be put in a .h file when I know what I am doing. */

static int charInit(void);
void charClean(void);
static int charOpen(struct inode *, struct file *);
static int charClose(struct inode *, struct file *);
static ssize_t charRead(struct file *, char *, size_t, loff_t *);
static ssize_t charWrite(struct file *, char *, size_t, loff_t *);

/* Some global variables ;) */
static dev_t majorNum = 0;
static int devOpen = 0; // This will track if the device is open or not. 0 = closed; 1 = open.

/* Driver Initialization Function. */
static int charInit(void)
{
  /* Allocate Major device number and check for errors. */
  int result = alloc_chrdev_region(&dev, MINOR, NUM_DEVS, DEVICE_NAME ); // The device number is stored in "dev".

  if (result < 1) {
    printk(KERN_WARNING "char: can't get major %d\n");
    return result;
  }
}

/* Driver De-Initialization Function. */
static void charClean(void)
{
  /* De-Allocate the previously allocated major number */
  unregister_chrdev_region(dev, NUM_DEVS);
}

/* Device open routine */

/* Device close routine */

/* Device read routine */

/* Device write routine */
