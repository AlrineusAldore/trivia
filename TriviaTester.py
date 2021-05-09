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

    username = input("Enter username: ")
    password = input("Enter password: ")
    mail = input("Enter mail to sign up with or 0 if you want to log in: ")
    code = 0

    # Constructing the json message
    if mail == '0':
        msg = '{"username":"' + username + '", "password":"' + password + '"}'
        code = LOGIN_CODE
    else:
        msg = '{"username":"' + username + '", "password":"' + password + '", "email":"' + mail + '"}'
        code = SIGNUP_CODE

    # Converting json message to binary by the protocol
    binMsg = ''.join((format(ord(x), 'b').zfill(8)) for x in msg)  # Turns string into binary
    msg = "{0:b}".format(code).zfill(8) + "{0:b}".format(len(msg)).zfill(32) + binMsg  # Turn status and len to binary

    # sending msg
    sock.sendall(msg.encode())

    # The server's response
    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()
    print("\nServer: ", (binStrToStr(server_msg))[2:])  # First char is status and second char is len, so we skip them


def binStrToStr(binStr):
    string = ""

    # Get the status
    string += chr(int(binStr[:8], 2))

    # Get the len
    string += chr(int(binStr[8:40], 2))

    # Get the message
    for i in range(40, len(binStr), 8):
        string += chr(int(binStr[i:i+8], 2))

    return string


def tobits(s):
    result = []
    for c in s:
        bits = bin(ord(c))[2:]
        bits = '00000000'[len(bits):] + bits
        result.extend([int(b) for b in bits])
    return result



if __name__ == "__main__":
    main()
