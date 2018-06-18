import socket
import threading

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    #IPv4 and TCP connection
serversocket.bind(('0.0.0.0', 1111))                                #IP address and port
serversocket.listen(5)                                              #Server socket, maximum 5 connections
connections=[]

def handler(c,a):
    global connections
    while True:
        data = c.recv(64)
        if len(data) > 0:
            print(data.decode("utf-8"))
        if not data:
            connections.remove(c)
            c.close()
            break

while True:
    connection, address = serversocket.accept()
    cThread = threading.Thread(target=handler, args=(connection,address))
    cThread.daemon = True
    cThread.start()
    connections.append(connection)
    print(connections)
    break
    #print('Got connection from', address)
    #buf = connection.recv(64)
    #if len(buf) > 0:
    #    print(buf.decode("utf-8"))
    #connection.close()
