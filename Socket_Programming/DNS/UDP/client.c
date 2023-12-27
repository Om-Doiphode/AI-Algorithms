#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 1024

int main() {
    // Create a socket
    int network_socket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket created for client\n");

    // Specify the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    char user_string[MAX_MESSAGE_SIZE];
    printf("Enter the hostname: ");
    fgets(user_string, sizeof(user_string), stdin);

    // Send data to the server
    sendto(network_socket, user_string, sizeof(user_string), 0, (struct sockaddr*)&server_address, sizeof(server_address));

    // Receive and print the IP address
    char server_response[MAX_MESSAGE_SIZE];
    socklen_t serverAddrLen = sizeof(server_address);
    recvfrom(network_socket, server_response, sizeof(server_response), 0,(struct sockaddr*)&server_address,&serverAddrLen);
    printf("IP address: %s\n", server_response);

    // Close the socket
    close(network_socket);

    return 0;
}
