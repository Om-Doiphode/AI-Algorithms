#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    int i, sd, sd2, nsd, clilen, sport;
    char sendmsg[20], recvmsg[100];
    char oid[5][10] = {"client1", "client2", "client3", "client4", "client5"};
    char wsize[5][5] = {"5", "10", "15", "3", "6"};
    struct sockaddr_in servaddr, cliaddr;

    printf("I'm the Agent-TCP Connection\n");
    printf("\nEnter the Server port: ");
    scanf("%d", &sport);

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd < 0)
        printf("Can't create socket\n");
    else
        printf("Socket is created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);

    sd2 = bind(sd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    if (sd2 < 0)
        printf("Can't Bind\n");
    else
        printf("\nBinded\n");

    listen(sd, 5);
    clilen = sizeof(cliaddr);
    nsd = accept(sd, (struct sockaddr*)&cliaddr, &clilen);

    if (nsd < 0)
        printf("Can't Accept\n");
    else
        printf("Accepted\n");

    recv(nsd, recvmsg, sizeof(recvmsg), 0);

    for (i = 0; i < 5; i++)
    {
        if (strcmp(recvmsg, oid[i]) == 0)
        {
            send(nsd, wsize[i], sizeof(wsize[i]), 0);
        }
    }

    // Close the sockets
    close(sd);
    close(nsd);

    return 0;
}
