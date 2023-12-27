#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 1024
#define MAX_FILENAME_SIZE 256


void sendFile(int network_socket,const char* filename)
{
    send(network_socket, filename, strlen(filename) + 1, 0);

    FILE *file=fopen(filename,"rb");
    if (file==NULL)
    {
        perror("Error opening file");
        return;
    }

    char buffer[MAX_MESSAGE_LENGTH];
    size_t bytesRead;

    while((bytesRead=fread(buffer,1,sizeof(buffer),file))>0)
    {
        send(network_socket,buffer,bytesRead,0);
    }

    fclose(file);
    printf("File %s sent successfully\n",filename);
}
int main()
{
    // create a socket
    int network_socket=socket(AF_INET, SOCK_STREAM, 0);

    // Specify the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    // connect to the server
    int connection_status=connect(network_socket,(struct sockaddr *)&server_address,sizeof(server_address));

    if(connection_status==-1)
    {
        printf("Error making a connection to the server\n");
        exit(1);
    }

    char filename[MAX_FILENAME_SIZE];
    printf("Enter the name of the file: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    sendFile(network_socket,filename);

    // Close the socket
    close(network_socket);

    return 0;
}