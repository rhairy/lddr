/* char.c driver source code */
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define NUM_DEVS 1
#define DEVICE_NAME "chardev"

/* Module Licensing. */
MODULE_LICENSE("GPL");

/* Prototypes; These will be put in a .h file when I know what I am doing. */
int charInit(void);
void charClean(void);
static struct cdev cdev;
static int charOpen(struct inode *, struct file *);
static int charClose(struct inode *, struct file *);
static ssize_t charRead(struct file *, char *, size_t, loff_t *);

/* Init and exit macros. */
module_init(charInit);
module_exit(charClean);

/* File Operations struct. */
static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = charOpen,
  .release = charClose,
  .read = charRead
};

/* Some global variables ;) */
static dev_t dev = 0;
static int devOpen = 0; // This will track if the device is open or not. 0 = closed; 1 = open.
static char *krnBuf = "Hello, World!";

/* Driver Initialization Function. */
int charInit(void)
{
  /* Allocate Major device number and check for errors. */
  int result = alloc_chrdev_region(&dev, 0, NUM_DEVS, DEVICE_NAME ); // The device number is stored in "dev".

  if (result < 0) {
    printk(KERN_WARNING "char: can't get major %d\n", result);
    return -1;
  }

  /* Initialize cdev structure and set fields. */
  cdev_init(&cdev, &fops);
  cdev.owner = THIS_MODULE;
  cdev_add(&cdev, dev, 1);
  
  return 0;
}

/* Driver De-Initialization Function. */
void charClean(void)
{
  /* Remove char device. */
  cdev_del(&cdev);
  
  /* De-Allocate the previously allocated major number */
  unregister_chrdev_region(dev, NUM_DEVS);
}

/* Device open routine */
static int charOpen(struct inode *inode, struct file *file)
{
  devOpen = 1;
  return 0;
}

/* Device close routine */
static int charClose(struct inode *inode, struct file *file)
{
  devOpen = 0;
  return 0;
}

/* Device read routine */
static ssize_t charRead(struct file *filp, char *usrBuf, size_t count, loff_t *offset)
{
  int readByte = 0;
  int i = 0;
  
  while(count != 0 && krnBuf[i] != '\0') {
    put_user(krnBuf[i], usrBuf);
    usrBuf++;
    readByte++;
    i++;
    count--;
  }
  return readByte;
}
