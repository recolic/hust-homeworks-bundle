#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include "rlib/macro.hpp"
MODULE_LICENSE("Dual BSD/GPL");

#define DATA_FNAME "/.recolic-hust.buffer"
#define DEV_COUNT 1
dev_t dev_id;
struct cdev actual_cdev;

#define CONTEXT_PTR ((struct session_context *)filep->private_data)
struct session_context {
    struct file *filep;
};

int hustmod_fops_open(struct inode *inode, struct file *filep) {
    struct file *actual_filep = filp_open(DATA_FNAME, filep->f_flags | O_CREAT, 0000);
    if(IS_ERR(actual_filep)) {
        printk(KERN_ALERT "HUSTMOD: filp_open failed.\n");
        return -1;
    }

    filep->private_data = vmalloc(sizeof(struct session_context));
    if(filep->private_data == NULL) {
        printk(KERN_ALERT "HUSTMOD: vmalloc failed.\n");
        return -1;
    }

    CONTEXT_PTR->filep = actual_filep;
    return 0;
}

int hustmod_fops_release(struct inode *inode, struct file *filep) {
    filp_close(CONTEXT_PTR->filep, NULL);
    vfree(filep->private_data);
    return 0;
}

#define RLIB_IMPL_FALLBACK_VFS(vfs_func, ...) \
    __auto_type ret = vfs_func(CONTEXT_PTR->filep, __VA_ARGS__); \
    if(ret < 0) printk(KERN_ALERT "HUSTMOD: " RLIB_MACRO_TO_CSTR(vfs_func) " failed.\n"); \
    return ret;

ssize_t hustmod_fops_read(struct file *filep, char __user *buf, size_t count, loff_t *offset) {
    RLIB_IMPL_FALLBACK_VFS(vfs_read, buf, count, offset)
}

ssize_t hustmod_fops_write(struct file *filep, const char __user *buf, size_t count, loff_t *offset) {
    RLIB_IMPL_FALLBACK_VFS(vfs_write, buf, count, offset)
}

loff_t hustmod_fops_llseek(struct file *filep, loff_t offset, int whence) {
    RLIB_IMPL_FALLBACK_VFS(vfs_llseek, offset, whence)
}

struct file_operations actual_fops = {
    .owner = THIS_MODULE,
    .open = hustmod_fops_open,
    .release = hustmod_fops_release,
    .read = hustmod_fops_read,
    .write = hustmod_fops_write,
    .llseek = hustmod_fops_llseek
};

static int hustmod_init(void) {
    printk(KERN_INFO "HUSTMOD: init\n");
    int err = 0;

    err = alloc_chrdev_region(&dev_id, 0, DEV_COUNT, "hustmod_dev");
    if(err) {
        printk(KERN_ALERT "HUSTMOD: alloc_chrdev_region returns %d", err);
        return err;
    }
    printk(KERN_INFO "HUSTMOD: device id MAJOR:MINOR = %d:%d", MAJOR(dev_id), MINOR(dev_id));

    cdev_init(&actual_cdev, &actual_fops);
    actual_cdev.owner = THIS_MODULE;
    actual_cdev.ops = &actual_fops;
    err = cdev_add(&actual_cdev, dev_id, 1);
    if(err) {
        printk(KERN_ALERT "HUSTMOD: cdev_add returns %d", err);
        return err;
    }

    return err;
}

static void hustmod_exit(void) {
    printk(KERN_INFO "HUSTMOD: exit\n");
    cdev_del(&actual_cdev);
    unregister_chrdev_region(dev_id, DEV_COUNT);
}

module_init(hustmod_init);
module_exit(hustmod_exit);

