#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    int age;
    char email[100];
} Clients;

void clearInputBuffer()
{
    // pega o caractere e armazena na variavel c e compara se é um \n ou se chegou ao final do arquivo
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(int argc, char const *argv[])
{
    // Seta o idioma para o portugues
    SetConsoleOutputCP(CP_UTF8);
    Clients client[100];
    int option, i, j, numberCustomers = 0;
    do
    {
        printf("Selecione a opção :\n");
        printf("1 - Cadastrar um novo cliente.\n");
        printf("2 - Vizualizar um cliente\n");
        printf("3 - Editar um cliente.\n");
        printf("4 - Excluir um cliente.\n");
        printf("5 - Sair\n");
        printf("-----------------\n");
        scanf("%d", &option);
        clearInputBuffer(); // Limpa o buffer após a entrada de dados
        switch (option)
        {
        case 1:
            if (numberCustomers < 100)
            {
                printf("Digite o nome : ");
                fgets(client[numberCustomers].name, 50, stdin);
                // remove o caractere de nova linha que fgets armazena.
                client[numberCustomers].name[strcspn(client[numberCustomers].name, "\n")] = '\0';

                printf("Digite a idade : ");
                scanf("%d", &client[numberCustomers].age);
                clearInputBuffer();

                printf("Digite o email : ");
                fgets(client[numberCustomers].email, 100, stdin);
                client[numberCustomers].email[strcspn(client[numberCustomers].email, "\n")] = '\0';

                numberCustomers++;
                printf("------------------------------\n");
                printf("Cliente %s adicionado com sucesso\n", client[numberCustomers - 1].name);
                printf("------------------------------\n");
            }
            else
            {
                printf("Capacidade máxima de clientes atingida\n");
            }
            break;
        case 2:
            printf("----------------------\n");
            printf("Clientes cadastrados:\n");
            printf("----------------------\n");
            for (i = 0; i < numberCustomers; i++)
            {
                printf("Nome :%s\n", client[i].name);
                printf("Idade :%d\n", client[i].age);
                printf("Email :%s\n", client[i].email);
                printf("------------------------\n");
            }
            break;
        case 3:
        {
            char name[100];
            int found = 0; // Variável para controlar se o cliente foi encontrado
            while (!found) // Loop continua até o cliente ser encontrado
            {
                printf("------------------------------\n");
                printf("Digite o nome do cliente que deseja editar :");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                for (i = 0; i < numberCustomers; i++)
                {
                    if (strcmp(client[i].name, name) == 0)
                    {
                        found = 1; // Cliente encontrado, sai do loop
                        printf("Digite o novo nome do cliente :");
                        fgets(client[i].name, 50, stdin);
                        client[i].name[strcspn(client[i].name, "\n")] = '\0';
                        printf("Digite a idade :");
                        scanf("%d", &client[i].age);
                        fflush(stdin);
                        printf("Digite o novo email :");
                        fgets(client[i].email, 100, stdin);
                        client[i].email[strcspn(client[i].email, "\n")] = '\0';
                        printf("------------------------------\n");
                        printf("Cliente %s alterado com sucesso!\n", client[i].name);
                        printf("------------------------------\n");
                    }
                    if (!found) // Se o cliente não foi encontrado, avisa e repete
                    {
                        printf("------------------------------------------\n");
                        printf("Nome inválido. Por favor, digite o nome correto.\n");
                        printf("------------------------------------------\n");
                    }
                }
            }
            break;
        }
        case 4:
        {
            char name[100];
            printf("----------------------------\n");
            printf("Digite o nome do cliente que deseja excluir :");
            printf("----------------------------\n");
            scanf("%s", name);
            fflush(stdin);
            for (i = 0; i < numberCustomers; i++)
            {
                if (strcmp(client[i].name, name) == 0)
                {
                    for (j = i; j < numberCustomers - 1; j++)
                    {
                        client[j] = client[j + 1];
                    }
                    printf("----------------------------\n");
                    printf("Cliente %s excluido com sucesso!\n", client[i].name);
                    printf("----------------------------\n");
                    numberCustomers--;
                }
            }
            break;
        }
        case 5:
            printf("Finalizando o programa...\n");
            break;
        default:
            printf("Opcao invalida. Digite a opcao correta.\n");
            printf("---------------------------\n");
            break;
        }
    } while (option != 5);
    return 0;
}