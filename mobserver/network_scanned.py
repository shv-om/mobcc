"""
This is a simple network scanning module specially build for project purpose.
This module scans the network for the IP address and their open ports from the list below.
It also checks the service banner for the open ports.

Ports Scanned by this module
15 Netstat
20/21 FTP
23 Telnet
25 SMTP
50/51 IPSec
53 DNS
67/68 DHCP
69 TFTP
80 HTTP
88 Kerberos
110 POP3
139 NetBIOS
143 IMAP
161 SNMP
389 LDAP
443 HTTPS
445 SMB
3306 MySQL
3389 RDP
5601 Kibana
5432 PostgreSQL
9200/9300 Elasticsearch

Network IP Addresses
Class A: 10.0.0.0 to 10.255.255.255
Class B: 172.16.0.0 to 172.31.255.255
Class C: 192.168.0.0 to 192.168.255.255

Author: Thorfinn_9
"""

import socket
import threading

# network_A = ["10." + str(i) + '.' + str(j) + '.' + str(k) for i in range(0, 255) for j in range(0, 255) for k in range(0, 255)]  # Class A Network
# network_B = ["172." + str(i) + '.' + str(j) + '.' + str(k) for i in range(16, 32) for j in range(0, 255) for k in range(0, 255)]  # Class B Network

# network_C = ["192.168." + str(i) + '.' + str(j) for i in range(1, 255) for j in range(1, 255)]  # Class C Network

network_dummy = ["10.10.27." + str(i) for i in range(70, 200)]  # Dummy Network

target_ports = [15, 20, 21, 22, 23, 25, 50, 51, 53, 67, 68, 69, 80, 88, 110, 139, 143, 161, 389, 443, 445, 3306, 3389, 5601, 5432, 8080, 9200, 9300]  # List of target ports to scan
MAX_THREADS = 16
port_dict = {}

thread_semaphore = threading.BoundedSemaphore(value=MAX_THREADS)

def scan_ports(ip):
    print(f"Scanning IP: {ip}")

    try:
        for port in target_ports:
            # Create a socket object
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            
            # Set a timeout value for the socket (optional)
            sock.settimeout(2)
            
            # Connect to the target IP and port
            result = sock.connect_ex((ip, port))
            
            if result == 0:
                # Port is open
                try:
                    port_dict[ip].append(port)
                except KeyError:
                    port_dict[ip] = [port]
                    # print(f"Port {port} is open")
                
                # Attempt to fetch the service version
                try:
                    banner = sock.recv(1024).decode('utf-16').strip()
                    print(f"Service version: {banner}")
                except socket.error:
                    print("Failed to fetch service version")
            else:
                # Port is closed
                pass
            
            # Close the socket
            sock.close()
        
    except socket.error:
        print(f"Error occurred while scanning port {port}")

    finally:
        thread_semaphore.release()


def thread_scanner():
    threads = []
    network = iter(network_dummy)

    for i in range(len(network_dummy)):
        target_ip = next(network)

        thread_semaphore.acquire()
        t = threading.Thread(target=scan_ports, args=(target_ip,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()



from ftplib import FTP

# If FTP is open then check for anonymous login and available commands.
def check_ftp_capabilities(hostname):
    try:
        ftp = FTP(hostname)
        ftp.login()  # Try anonymous login

        # Get available commands
        commands = ftp.sendcmd('help').split('\n')
        print("Available FTP commands:")
        for command in commands:
            print(command)

        ftp.quit()
        return "Anonymous FTP access is available."
    except Exception as e:
        return "Anonymous FTP access is not available or failed."


thread_scanner()
print(port_dict)


for key, val in port_dict.items():
    if '21' in val:
        hostname = key
        result = check_ftp_capabilities(hostname)

        print(result)
