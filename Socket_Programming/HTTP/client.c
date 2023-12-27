#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <host>\n", argv[0]);
        return 1;
    }

    char *address = argv[1];

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);

    if (inet_aton(address, &remote_address.sin_addr) == 0) {
        fprintf(stderr, "Invalid IP address: %s\n", address);
        return 1;
    }

    if (connect(client_socket, (struct sockaddr*)&remote_address, sizeof(remote_address)) == -1) {
        perror("Error connecting to the server");
        return 1;
    }

    char request[] = "GET / HTTP/1.1\r\n"
                     "Host: %s\r\n"
                     "\r\n";
    
    // Allocate enough space for the request, considering the length of the host
    char *full_request = (char *)malloc(strlen(request) + strlen(address) + 1);
    sprintf(full_request, request, address);

    ssize_t bytes_sent = send(client_socket, full_request, strlen(full_request), 0);
    if (bytes_sent < 0) {
        perror("Error sending data");
        return 1;
    }

    char response[4096];
    ssize_t bytes_received = recv(client_socket, response, sizeof(response) - 1, 0);
    if (bytes_received < 0) {
        perror("Error receiving data");
        return 1;
    }

    // Null-terminate the received data
    response[bytes_received] = '\0';

    printf("response from the server:\n%s\n", response);

    // Free the allocated memory
    free(full_request);

    close(client_socket);

    return 0;
}
