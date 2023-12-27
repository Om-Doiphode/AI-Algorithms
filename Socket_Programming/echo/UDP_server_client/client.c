#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int network_socket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created for client\n");

    // Specify the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    char user_string[1024];
    printf("Enter a message: ");
    fgets(user_string, sizeof(user_string), stdin);

    // Send data to the server
    sendto(network_socket, user_string, sizeof(user_string), 0, (struct sockaddr*)&server_address, sizeof(server_address));

    // Receive and print the echoed data
    char server_response[256];
    socklen_t serverAddrLen = sizeof(server_address);
    recvfrom(network_socket, server_response, sizeof(server_response), 0, (struct sockaddr*)&server_address, &serverAddrLen);
    printf("Server echoed: %s\n", server_response);

    // Close the socket
    close(network_socket);
    printf("Socket closed\n");

    return 0;
}
