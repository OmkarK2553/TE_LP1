import socket


def client():

    try:
        socket_client = socket.socket()
        print("Successfully formed the socket!")
    except socket.error as err:
        print("Error while forming the socket %s" % (err))

    try:
        host = socket.gethostbyname("localhost")
        port = 5000
        print("Successfully created the host and port!")
    except socket.gaierror:
        print("Error while creating the host and port!")

    try:
        socket_client.connect((host, port))
        print("Successfully formed the connection!")
    except TimeoutError as te:
        print("The connection timed out ", te.__class__)
    except InterruptedError as ie:
        print("An interrupt occured while connecting to the server ", ie.__class__)
    except Exception as e:
        print("An error occured while forming the connection ", e.__class__)

    msg = input('Enter the message for server: ')

    while msg.lower().strip() != "exit":
        socket_client.send(msg.encode())

        data = socket_client.recv(1024).decode()
        print("Message from server: ", str(data))

        msg = input('->')

    socket.close()


if __name__ == '__main__':
    client()
