#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 1024
int main() {

    // open a file to serve
    FILE *html_data;
    html_data=fopen("index.html", "r");

    char response_data[MAX_MESSAGE_LENGTH];
    fgets(response_data, MAX_MESSAGE_LENGTH, html_data);

    char http_header[2*MAX_MESSAGE_LENGTH]="HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created for server\n");

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified IP and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 5);

    // Accept a client connection
    int client_socket;

    while(1)
    {
        client_socket=accept(server_socket, NULL, NULL);
        send(client_socket, http_header,sizeof(http_header),0);
        close(client_socket);
    }
    // Close the sockets
    close(server_socket);

    return 0;
}
