import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8820
LOGIN_CODE = 100
SIGNUP_CODE = 69
get_bin = lambda x, n: format(x, 'b').zfill(n)


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
    username = input("Enter username: ")
    password = input("Enter password: ")
    mail = input("Enter mail or 0 if you dont have one: ")
    code = 0
        #making the msg
    if mail == '0':
        msg = '{"username":"' + username + '", "password":"' + password + '"}'
        code = LOGIN_CODE
    else:
        msg = '{"username":"' + username + '", "password":"' + password + '", "email":"' + mail + '"}'
        code = SIGNUP_CODE
        #creating the protocol
    binMsg = ''.join((format(ord(x), 'b').zfill(8)) for x in msg) #turns string into binary
    print("msg: ", msg)
    msg = "{0:b}".format(code).zfill(8) + "{0:b}".format(len(msg)).zfill(32) + binMsg #msg len
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
