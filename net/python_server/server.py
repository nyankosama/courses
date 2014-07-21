import socket

def handle(client_socket, client_addr):
    while True:
        data = client_socket.recv(4096)
        if data:
            sent = client_socket.send(data)
        else:
            client_socket.close()
            break

if __name__ == "__main__":
    listen_addr = ("0.0.0.0", 9123)
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind(listen_addr)
    server_sock.listen(5)

    while True:
        (client_socket, client_addr) = server_sock.accept()
        print "got connection from", client_socket
        handle(client_socket, client_addr)
