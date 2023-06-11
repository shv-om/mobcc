/*
Encoding normal string to base64 string
*/

// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
// #include <linux/string.h>
// #include <linux/slab.h>

// static char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// static char *input_data = "SGVsbG8sIFdvcmxkIQ==";
// static char decoded_data[256];

// static int b64_decode(const char *input, size_t input_len, char *output, size_t output_len)
// {
//     int i, j;
//     int decoded_len = 0;
//     unsigned char buf[4];

//     for (i = 0; i < input_len; i += 4) {
//         memset(buf, 0, sizeof(buf));

//         for (j = 0; j < 4; ++j) {
//             buf[j] = strchr(base64_chars, input[i + j]) - base64_chars;
//         }

//         output[decoded_len++] = (buf[0] << 2) | (buf[1] >> 4);
//         if (output_len <= decoded_len)
//             break;

//         if (buf[2] < 64) {
//             output[decoded_len++] = (buf[1] << 4) | (buf[2] >> 2);
//             if (output_len <= decoded_len)
//                 break;
//         }

//         if (buf[3] < 64) {
//             output[decoded_len++] = (buf[2] << 6) | buf[3];
//             if (output_len <= decoded_len)
//                 break;
//         }
//     }

//     return decoded_len;
// }

// static int __init my_module_init(void)
// {
//     char *input = input_data;
//     char *output = decoded_data;
//     int input_len = strlen(input);
//     int output_len = sizeof(decoded_data);
//     int decoded_len;

//     pr_info("Base64 decoding data: %s\n", input_data);

//     // Perform base64 decoding
//     decoded_len = b64_decode(input, input_len, output, output_len);
//     if (decoded_len < 0) {
//         pr_err("Base64 decoding failed\n");
//         return -1;
//     }

//     output[decoded_len] = '\0';

//     pr_info("Base64 decoded data: %s\n", decoded_data);

//     pr_info("Module unloaded\n");
//     return 0;
// }

// static void __exit my_module_exit(void)
// {
//     pr_info("Module unloaded\n");
// }

// module_init(my_module_init);
// module_exit(my_module_exit);

// MODULE_LICENSE("GPL");


/*
Command execution from kernel module
*/

// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
// #include <linux/kmod.h>
// #include <linux/fs.h>
// #include <linux/file.h>
// #include <linux/fcntl.h>
// #include <linux/uaccess.h>

// static int __init my_module_init(void)
// {
//     char *argv[] = { "usr/bin/wget", "http://0.0.0.0:8080/Makefile", NULL };
//     static char *envp[] = {
//         "HOME=/",
//         "TERM=linux",
//         "PATH=/sbin:/usr/sbin:/bin:/usr/bin",
//         NULL
//     };
//     struct file *file;
//     int ret;
//     char *filename = "/tmp/downloaded_file.txt";

//     file = filp_open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     if (IS_ERR(file)) {
//         pr_err("Failed to open file: %s\n", filename);
//         return PTR_ERR(file);
//     }

//     ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
//     if (ret < 0) {
//         pr_err("Failed to execute wget command: %d\n", ret);
//         filp_close(file, NULL);
//         return ret;
//     }

//     filp_close(file, NULL);

//     return 0;
// }

// static void __exit my_module_exit(void)
// {
//     pr_info("Module unloaded\n");
// }

// module_init(my_module_init);
// module_exit(my_module_exit);

// MODULE_LICENSE("GPL");



/* Downloading files from the server using wget */

// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
// #include <linux/kmod.h>
// #include <linux/fs.h>
// #include <linux/file.h>
// #include <linux/fcntl.h>
// #include <linux/uaccess.h>

// static int __init my_module_init(void)
// {
//     char *argv[] = { "/usr/bin/wget", "-O", "/tmp/downloaded_file.txt", "http://0.0.0.0:8080/Makefile", NULL };
//     static char *envp[] = {
//         "HOME=/",
//         "TERM=linux",
//         "PATH=/sbin:/usr/sbin:/bin:/usr/bin",
//         NULL
//     };
//     int ret;

//     ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
//     if (ret < 0) {
//         pr_err("Failed to execute wget command: %d\n", ret);
//         return ret;
//     }

//     return 0;
// }

// static void __exit my_module_exit(void)
// {
//     // Cleanup code, if needed
// }

// module_init(my_module_init);
// module_exit(my_module_exit);

// MODULE_LICENSE("GPL");