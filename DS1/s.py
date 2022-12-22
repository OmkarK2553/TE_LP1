import socket
import sys


def server():

    try:
        socket_server = socket.socket()
        print("Successfully formed the socket!")
    except socket.error as err:
        print("Error while creating the socket %s" % (err))

    try:
        host = socket.gethostbyname("localhost")
        port = 5000
        print("Successfully created the host and the port!")
    except socket.gaierror:
        print("Error while resolving the host!")
        sys.exit()

    try:
        socket_server.bind((host, port))
        print("Successfully bound the host and port to the socket!")
    except Exception as e:
        print("Error while binding the host and port ", e.__class__)

    try:
        socket_server.listen(10)
        print("Successfully listening to the socket!")
    except Exception as e:
        print("Error while listening to the socket ", e.__class__)

    try:
        conn, addr = socket_server.accept()
        print("Successfully accepted the connection request!")
        print("connection established with ", str(addr))
    except InterruptedError as ie:
        print("Error while accepting the connection ", ie.__class__)
    except Exception as e:
        print("Error while accepting the connection ", e.__class__)

    while True:
        data = conn.recv(1024).decode()

        if not data:
            break

        print("From connected user: ", str(data))

        data = input('->')
        conn.send(data.encode())

    conn.close()
    socket_server.close()


if __name__ == '__main__':
    server()
