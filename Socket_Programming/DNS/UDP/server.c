#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define MAX_BUFFER_SIZE 1021

int indexOf(char *hosts[], char *str) {
    str[strcspn(str, "\n")] = '\0';  // Remove newline character
    for (int i = 0; hosts[i] != NULL; i++) {
        if (strcmp(hosts[i], str) == 0) return i;
    }
    return -1;
}

int main() {
    char *hosts[] = {
    "zoho.com", "gmail.com", "google.com", "facebook.com",
    "yahoo.com", "amazon.com", "microsoft.com", "twitter.com",
    "linkedin.com", "instagram.com", "reddit.com", "stackoverflow.com",
    "netflix.com", "spotify.com", "github.com", "apple.com",
    "bing.com", "pinterest.com", "tumblr.com", "whatsapp.com",
    "slack.com", "dropbox.com", "uber.com", "airbnb.com",
    "wordpress.com", "wordpress.org", "wordpress.net", "wordpress.biz",
    "cnn.com", "bbc.com", "aljazeera.com", "reuters.com",
    NULL
};

char *ip[] = {
    "172.28.251.59", "172.217.11.5", "172.217.11.14", "31.13.71.36",
    "74.6.143.25", "176.32.98.166", "40.76.4.15", "104.244.42.1",
    "108.174.10.10", "34.226.122.37", "151.101.1.140", "151.101.129.69",
    "52.51.28.4", "35.186.224.37", "140.82.112.3", "17.253.144.10",
    "204.79.197.200", "151.101.0.84", "64.233.184.101", "31.13.71.53",
    "54.192.192.95", "162.125.8.1", "146.20.68.8", "23.22.29.136",
    "192.0.78.9", "198.20.242.202", "198.20.245.4", "198.20.239.65",
    "151.101.1.67", "151.101.0.81", "198.54.228.26", "23.5.112.176",
    NULL
};


    printf("Press Ctrl + C to Quit\n");

    while (1) {
        int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(9002);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

        char receivedData[MAX_BUFFER_SIZE];
        socklen_t clientAddrLen = sizeof(serverAddress);

        recvfrom(serverSocket, receivedData, sizeof(receivedData), 0, (struct sockaddr*)&serverAddress, &clientAddrLen);

        char *requestHost = receivedData;
        printf("Request for host %s\n", requestHost);

        char responseData[MAX_BUFFER_SIZE];
        int index = indexOf(hosts, requestHost);
        if (index != -1)
            strcpy(responseData, ip[index]);
        else
            strcpy(responseData, "Host Not Found");

        sendto(serverSocket, responseData, sizeof(responseData), 0, (struct sockaddr*)&serverAddress, clientAddrLen);
        close(serverSocket);
    }

    return 0;
}
