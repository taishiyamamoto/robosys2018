#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
MODULE_AUTHOR("Taishi Yamamoto");
MODULE_DESCRIPTION("driver for 7 segment LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static const u32 lednum[]={0x3f,0x0c,0x5b,0x5e,0x6c,0x76,0x77,0x3c,0x7f,0x7c}; /*0,1,2,3,4,5,6,7,8,9*/

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos){
    char c;
    int n;
    if(copy_from_user(&c,buf,sizeof(char))) return -EFAULT;
    
    if('0'<=c&&c<='9'){
        gpio_base[10]=lednum[8]<<20;
	n=c-'0';    
    	gpio_base[7]=lednum[n]<<20;
    }
    else if(c=='c'||c=='C'){
        gpio_base[10]=lednum[8]<<20; 
    }
 
    return 1;
}

static struct file_operations led_fops = {
        .owner = THIS_MODULE,
        .write = led_write,
};

static int __init init_mod(void){
    int retval;

    gpio_base = ioremap_nocache(0x3f200000, 0xA0);
    gpio_base[2]=0xffe49249; /*11111111111001001001001001001001*/
    printk(KERN_INFO "%d\n",gpio_base[2]);

    retval = alloc_chrdev_region(&dev, 0, 1, "myled");
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__, MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
        return retval;
        }
    cls = class_create(THIS_MODULE, "myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
    return 0;
}

static void __exit cleanup_mod(void){
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
