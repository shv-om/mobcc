#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xdd8f8694, "module_layout" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xa7eedcc4, "call_usermodehelper" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0x3b825fc1, "commit_creds" },
	{ 0x611bf0f1, "prepare_creds" },
	{ 0x9e423bbc, "unregister_ftrace_function" },
	{ 0xc5850110, "printk" },
	{ 0x58f03b99, "register_ftrace_function" },
	{ 0xc8f162c9, "ftrace_set_filter_ip" },
	{ 0xe007de41, "kallsyms_lookup_name" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7D19D2AB9CA64BED4D760B2");
