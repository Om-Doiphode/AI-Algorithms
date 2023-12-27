#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int csd, cport, len, i;
    char sendmsg[20], rcvmsg[100], rmsg[100], oid[100];
    struct sockaddr_in servaddr;

    printf("Enter the port: ");
    scanf("%d", &cport);

    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd < 0)
        printf("Can't create socket\n");
    else
        printf("Socket is created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);

    if (connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        printf("Can't connect\n");
    else
        printf("Connected\n");

    printf("\n 1. TCP Connection\n");
    printf("\n 2. System\n");

    printf("Enter the number for the type of information needed....\n");
    scanf("%d", &i);

    if (i == 1) {
        printf("Enter the Object ID for Client: \n");
        scanf("%s", oid);
        send(csd, oid, sizeof(oid), 0);
        recv(csd, rmsg, sizeof(rmsg), 0);
        printf("\nThe window size of %s is %s\n", oid, rmsg);
    } else {
        printf("\nEnter the Object ID for the System\n");
        scanf("%s", oid);
        send(csd, oid, sizeof(oid), 0);
        recv(csd, rmsg, sizeof(rmsg), 0);
        printf("\nThe Manufacturing date for %s is %s\n", oid, rmsg);
        recv(csd, rmsg, sizeof(rmsg), 0);
        printf("\nThe time of last utilization for %s is %s\n", oid, rmsg);
    }

    // Close the socket
    close(csd);

    return 0;
}
