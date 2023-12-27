#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_FILENAME_SIZE 256
#define MAX_MESSAGE_SIZE 1024

void receiveFile(int client_socket)
{
    char filename[MAX_FILENAME_SIZE];
    recv(client_socket,filename,sizeof(filename),0);

    FILE *fp=fopen(filename,"wb");
    if(fp==NULL)
    {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_MESSAGE_SIZE];
    size_t bytesRead;

    while((bytesRead=recv(client_socket,buffer,sizeof(buffer),0))>0)
    {
        fwrite(buffer,1,bytesRead,fp);
    }

    fclose(fp);
    printf("File %s received successfully\n",filename);
}

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

    // Receive the file from the client
    receiveFile(client_socket);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
