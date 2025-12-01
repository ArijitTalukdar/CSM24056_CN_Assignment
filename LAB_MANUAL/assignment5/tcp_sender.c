#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5001
#define BUFLEN 1024
#define MB 1024*1024

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s <server_ip> <MB_to_send>\n", argv[0]);
        exit(1);
    }

    char *server_ip = argv[1];
    long total_mb = atol(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { perror("socket"); exit(1); }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, server_ip, &servaddr.sin_addr);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect"); exit(1); }

    char buf[BUFLEN];
    memset(buf, 'A', BUFLEN);

    long sent = 0;
    long total_bytes = total_mb * MB;

    while(sent < total_bytes) {
        int to_send = BUFLEN;
        if(sent + BUFLEN > total_bytes) to_send = total_bytes - sent;
        int n = write(sockfd, buf, to_send);
        if(n <= 0) break;
        sent += n;
    }
    printf("Sent %ld bytes\n", sent);

    close(sockfd);
    return 0;
}
