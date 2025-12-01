#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 5005
#define BUFLEN 2048

// Simple TCP server that prints incoming data and header info
int main() {
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen = sizeof(cliaddr);
    char buf[BUFLEN];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    // Bind to port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind"); exit(1); }

    // Listen for connections
    if (listen(sockfd, 5) < 0) { perror("listen"); exit(1); }

    printf("TCP Network Simulator listening on port %d...\n", PORT);

    while(1) {
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clen);
        if (newsockfd < 0) { perror("accept"); continue; }

        char *client_ip = inet_ntoa(cliaddr.sin_addr);
        int client_port = ntohs(cliaddr.sin_port);
        printf("\n--- Connection from %s:%d ---\n", client_ip, client_port);

        ssize_t n;
        while ((n = read(newsockfd, buf, BUFLEN-1)) > 0) {
            buf[n] = 0; // Null terminate
            printf("Received %ld bytes:\n", n);
            printf("Data: %s\n", buf);
        }

        printf("--- Connection closed from %s:%d ---\n", client_ip, client_port);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
