#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5555
#define MAX 100

// Fruit record structure
struct Fruit {
    char name[20];
    int quantity;
    char last_sold[40];
};

struct Fruit fruits[3] = {
    {"apple", 10, "N/A"},
    {"banana", 15, "N/A"},
    {"orange", 20, "N/A"}
};

char customers[100][50];
int unique_count = 0;

// Add customer if not present
void add_customer(char *id) {
    for (int i = 0; i < unique_count; i++) {
        if (strcmp(customers[i], id) == 0)
            return;
    }
    strcpy(customers[unique_count++], id);
}

// Find fruit index
int find_fruit(char *name) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(fruits[i].name, name) == 0)
            return i;
    }
    return -1;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(1); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind"); exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen"); exit(1);
    }

    printf("Server running...\n");

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) { perror("accept"); continue; }

        char client_id[50];
        sprintf(client_id, "%s:%d", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        add_customer(client_id);

        char fruit_name[20];
        int qty;

        recv(new_socket, fruit_name, sizeof(fruit_name), 0);
        recv(new_socket, &qty, sizeof(qty), 0);

        int idx = find_fruit(fruit_name);
        char response[200];

        if (idx == -1) {
            sprintf(response, "Fruit not found.\n");
        } else {
            if (fruits[idx].quantity >= qty) {
                fruits[idx].quantity -= qty;

                time_t now = time(NULL);
                strcpy(fruits[idx].last_sold, ctime(&now));
                fruits[idx].last_sold[strlen(fruits[idx].last_sold) - 1] = '\0';

                sprintf(response,
                    "PURCHASE SUCCESSFUL\n"
                    "Remaining %s: %d\n"
                    "Last sold: %s\n"
                    "Total Unique Customers: %d\n",
                    fruits[idx].name,
                    fruits[idx].quantity,
                    fruits[idx].last_sold,
                    unique_count
                );
            } else {
                sprintf(response,
                    "SORRY! Only %d %s left.\n"
                    "Total Unique Customers: %d\n",
                    fruits[idx].quantity,
                    fruits[idx].name,
                    unique_count
                );
            }
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}

