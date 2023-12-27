#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created for server\n");

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 3);

    printf("Server waiting for connections...\n");

    // Accept a client connection
    int client_socket = accept(server_socket, NULL, NULL);
    printf("Client connection accepted\n");

    // Receive and echo data
    char buffer[256];
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // Send the received data back to the client
    send(client_socket, buffer, sizeof(buffer), 0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
