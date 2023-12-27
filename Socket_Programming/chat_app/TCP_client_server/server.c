#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 1024

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

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

    // Receive and echo data
    char client_message[MAX_MESSAGE_LENGTH];
    char server_message[MAX_MESSAGE_LENGTH];

    while(1)
    {
        recv(client_socket, client_message, sizeof(client_message), 0);
        printf("Client: %s\n", client_message);

        if(strcmp(client_message,"exit\n")==0)
            break;

        // Send server message to the client
        printf("You: ");
        fgets(server_message, sizeof(server_message), stdin);

        // Send the received data back to the client
        send(client_socket, server_message, sizeof(server_message), 0);
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
