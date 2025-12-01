#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5001
#define BUFLEN 1024

int main() {
    int servfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clen = sizeof(cliaddr);
    char buf[BUFLEN];

    servfd = socket(AF_INET, SOCK_STREAM, 0);
    if(servfd < 0) { perror("socket"); exit(1); }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if(bind(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind"); exit(1); }

    if(listen(servfd, 5) < 0) { perror("listen"); exit(1); }

    printf("TCP server listening on port %d\n", PORT);

    connfd = accept(servfd, (struct sockaddr*)&cliaddr, &clen);
    if(connfd < 0) { perror("accept"); exit(1); }

    ssize_t n;
    long total = 0;
    while((n = read(connfd, buf, BUFLEN)) > 0) {
        total += n;
    }
    printf("Received total %ld bytes\n", total);

    close(connfd);
    close(servfd);
    return 0;
}
