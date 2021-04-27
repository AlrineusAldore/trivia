import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8820
get_bin = lambda x: format(x, 'b')


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
        #getting data
    username = input("enter username")
    password = input("enter password")
    mail = input("enter mail without mail type 0")
    code = 0;
        #making the msg
    if mail == '0':
        msg = '{ "username":"' + username + '", "password":' + password + '}'
        code = 420
    else:
        msg = '{ "username":"' + username + '", "password":' + password + ', "mail":"' + mail + '"}'
        code = 69
        #creating the protocol
    msg = get_bin(code, 8) + get_bin(len(msg), 32) + msg #msg len
        #seding msg
    sock.sendall(msg.encode())

    # The server's message
    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print("Server:", server_msg)

if __name__ == "__main__":
    main()

def tobits(s):
    result = []
    for c in s:
        bits = bin(ord(c))[2:]
        bits = '00000000'[len(bits):] + bits
        result.extend([int(b) for b in bits])
    return result
