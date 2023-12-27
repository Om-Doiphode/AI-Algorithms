#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 1024


int main() {
    // Create a socket
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if (connection_status == -1) {
        printf("Error making a connection to the server\n");
        return 1;
    }

    char user_string[MAX_MESSAGE_LENGTH];
    char server_response[MAX_MESSAGE_LENGTH];

    while(1)
    {
        // Send data to the server
        printf("You: ");
        fgets(user_string, sizeof(user_string), stdin);
        send(network_socket, user_string, sizeof(user_string), 0);

        // Break the loop if the user types 'exit'
        if(strcmp(user_string,"exit\n")==0)
            break;


        // Receive and print the echoed data
        recv(network_socket, server_response, sizeof(server_response), 0);
        printf("Server: %s\n", server_response);
    }

    // Close the socket
    close(network_socket);

    return 0;
}
