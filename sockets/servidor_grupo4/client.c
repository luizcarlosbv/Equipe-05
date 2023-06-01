#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 4446

int main() {
    int sckt;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    char requestBuffer[2048];

    // Cria o socket
    sckt = socket(AF_INET, SOCK_STREAM, 0);

    // Configura o endereço do servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Conecta ao servidor
    if (connect(sckt, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Falha ao conectar ao servidor");
        return 1;
    }

    printf("-------------------- Ajuste salarial --------------------\n");
    printf("formato de entrada: NOME CARGO SALARIO\n");
    printf("Digite 'exit' para fechar\n");

    while (1) {
        printf("> ");

        // Lê a entrada do usuário
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Falha ao ler a entrada do usuário");
            return 1;
        }

        // Remove a quebra de linha da entrada
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Verifica se o usuário deseja sair
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Adiciona "RAJ " antes da string lida no buffer
        sprintf(requestBuffer, "RAJ %s", buffer);

        // Envia a solicitação para o servidor
        if (send(sckt, requestBuffer, strlen(requestBuffer), 0) < 0) {
            printf("Falha ao enviar dados para o servidor");
            return 1;
        }

        // Recebe a resposta do servidor
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(sckt, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead < 0) {
            printf("Falha ao receber dados do servidor");
            return 1;
        } else if (bytesRead == 0) {
            printf("Conexão fechada pelo servidor\n");
            break;
        } else {
            printf("Resposta do servidor: %s\n", buffer);
        }
    }

    close(sckt);

    return 0;
}
