#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_FILENAME_SIZE 256
#define MAX_MESSAGE_SIZE 1024

void receiveFile(int server_socket) {
    struct sockaddr_in client_address;
    socklen_t clientAddrLen = sizeof(client_address);

    char filename[MAX_FILENAME_SIZE];
    recvfrom(server_socket, filename, sizeof(filename), 0, (struct sockaddr *)&client_address, &clientAddrLen);

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_MESSAGE_SIZE];
    size_t bytesRead;

    while ((bytesRead = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &clientAddrLen)) > 0) {
        // Receive each packet
        fwrite(buffer, 1, bytesRead, fp);
    }

    fclose(fp);
    printf("File %s received successfully\n", filename);
}

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    printf("Server waiting for connections...\n");

    // Receive the file from the client
    receiveFile(server_socket);

    // Close the socket
    close(server_socket);

    return 0;
}
