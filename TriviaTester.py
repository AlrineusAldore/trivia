import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8820


def main():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connecting to host
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    # The server's message
    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print("Server:", server_msg)

    # Send data to server
    msg = "Hello! I'm the client here, and they say to treat the clients like gods. SO WORSHIP ME MORTAL!"
    sock.sendall(msg.encode())


if __name__ == "__main__":
    main()
