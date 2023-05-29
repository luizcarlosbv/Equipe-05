#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int position;
    float salary;
} ClientData;

void splitMensagem(ClientData* data, char* message);

int main() {
    ClientData clientData;
    char buffer[1024];

    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(5000)
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);
    int client, x;
    int csize = sizeof caddr;

    bind(server, (struct sockaddr *)&saddr, sizeof saddr);

    listen(server, 5);

    while (1) {
        client = accept(server, (struct sockaddr *)&caddr, &csize);
        x = recv(client, buffer, sizeof buffer, 0);

        buffer[x] = '\0';

        splitMensagem(&clientData, buffer);

        printf("Name: %s\n", clientData.name);
        printf("Position: %d\n", clientData.position);
        printf("Salary: %.2f\n", clientData.position == 0 ? clientData.salary : clientData.salary * 1.2);

        send(client, &clientData, sizeof clientData, 0);

        close(client);
    }

    return 0;
}

void splitMensagem(ClientData* data, char* message) {
    char* token;

    token = strtok(message, "|");
    strncpy(data->name, token, sizeof(data->name));

    token = strtok(NULL, "|");
    data->position = atoi(token);

    token = strtok(NULL, "|");
    data->salary = atof(token);
}