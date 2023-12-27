#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created for server\n");

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    printf("Server waiting for messages...\n");

    // Receive and echo data
    char buffer[256];
    socklen_t clientAddrLen = sizeof(server_address);
    recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_address, &clientAddrLen);
    printf("Received from client: %s\n", buffer);

    // Send the received data back to the client
    sendto(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_address, clientAddrLen);

    // Close the socket
    close(server_socket);
    printf("Socket closed\n");

    return 0;
}
