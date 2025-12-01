#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("10.0.0.1");   // Mininet server IP

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect"); exit(1);
    }

    char fruit[20];
    int qty;

    printf("Enter fruit name: ");
    scanf("%s", fruit);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    send(sock, fruit, sizeof(fruit), 0);
    send(sock, &qty, sizeof(qty), 0);

    char buffer[500];
    int n = recv(sock, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';

    printf("\n--- Server Response ---\n%s\n", buffer);

    close(sock);
    return 0;
}

