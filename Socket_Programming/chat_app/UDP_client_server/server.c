#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 1024

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    printf("Server waiting for messages...\n");

    // Receive and echo data
    char client_message[MAX_MESSAGE_LENGTH];
    socklen_t clientAddrLen = sizeof(server_address);

    while(1) {
        // Receive data from the client
        recvfrom(server_socket, client_message, sizeof(client_message), 0, (struct sockaddr*)&server_address, &clientAddrLen);
        printf("Client: %s\n", client_message);

        if (strcmp(client_message, "exit\n") == 0)
            break;

        // Send a response to the client
        printf("You: ");
        fgets(client_message, sizeof(client_message), stdin);
        sendto(server_socket, client_message, sizeof(client_message), 0, (struct sockaddr*)&server_address, clientAddrLen);
    }

    // Close the socket
    close(server_socket);

    return 0;
}
