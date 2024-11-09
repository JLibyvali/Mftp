import socket


buf = "Hello world, New clinet"

sock  = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
serv_addr = ("127.0.0.1",9001)

print("Open new connect\n")
sock.connect(serv_addr)

try:
    sock.sendall(buf)

    str_len = len(buf)
    ret =0

    # Receive all message
    ret = sock.recv(str_len)
finally:
    print("Received message: ",ret)
