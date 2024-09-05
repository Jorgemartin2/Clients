#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct
{
    char name[50];
    int age;
    char email[100];
} Clients;

void clearInputBuffer();
void registerCustomer(Clients client[], int *vectorSize);
void viewCustomer(Clients client[], int *vectorSize);
void editCustomer(Clients client[], int vectorSize);
void deleteCustomer(Clients client[], int *vectorSize);
void saveToFile(Clients client[], int vectorSize);
void loadFromFile(Clients client[], int *vectorSize);

int main(int argc, char const *argv[])
{
    // Seta o idioma para o portugues
    SetConsoleOutputCP(CP_UTF8);
    Clients client[100];
    int option, numberCustomers = 0;
    loadFromFile(client, &numberCustomers);
    do
    {
        printf("1 - Cadastrar um novo cliente.\n");
        printf("2 - Vizualizar um cliente.\n");
        printf("3 - Editar um cliente.\n");
        printf("4 - Excluir um cliente.\n");
        printf("5 - Sair.\n");
        printf("---------------------------------------------\n");
        printf("Selecione a opção : ");
        scanf("%d", &option);
        clearInputBuffer();
        switch (option)
        {
        case 1:
            registerCustomer(client, &numberCustomers);
            saveToFile(client, numberCustomers);
            break;
        case 2:
            viewCustomer(client, &numberCustomers);
            break;
        case 3:
            editCustomer(client, numberCustomers);
            saveToFile(client, numberCustomers);
            break;
        case 4:
            deleteCustomer(client, &numberCustomers);
            saveToFile(client, numberCustomers);
            break;
        case 5:
            printf("Finalizando o programa...\n");
            break;
        default:
            printf("Opção invalida. Digite a opção correta.\n");
            printf("---------------------------------------------\n");
            break;
        }
    } while (option != 5);
    return 0;
}
void clearInputBuffer()
{
    // Pega o caractere e armazena na variavel c e compara se é um \n ou se chegou ao final do arquivo
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void registerCustomer(Clients client[], int *vectorSize)
{
    if (*vectorSize < 100)
    {
        printf("Digite o nome : ");
        fgets(client[*vectorSize].name, sizeof(client[*vectorSize].name), stdin);
        client[*vectorSize].name[strcspn(client[*vectorSize].name, "\n")] = '\0';
        printf("Digite a idade : ");
        scanf("%d", &client[*vectorSize].age);
        clearInputBuffer();
        printf("Digite o email : ");
        fgets(client[*vectorSize].email, sizeof(client[*vectorSize].email), stdin);
        client[*vectorSize].email[strcspn(client[*vectorSize].email, "\n")] = '\0';
        (*vectorSize)++;
        printf("---------------------------------------------\n");
        printf("Cliente %s adicionado com sucesso\n", client[*vectorSize - 1].name);
        printf("---------------------------------------------\n");
    }
    else
    {
        printf("---------------------------------------------\n");
        printf("Capacidade máxima de clientes atingida\n");
        printf("---------------------------------------------\n");
    }
}
void viewCustomer(Clients client[], int *vectorSize)
{
    char aux[50];
    int i, j;
    printf("---------------------------------------------\n");
    printf("Clientes cadastrados:\n");
    printf("---------------------------------------------\n");
    // ordenar os clientes por nome
    for (i = 0; i < *vectorSize; i++)
    {
        for (j = i + 1; j < *vectorSize; j++)
        {
            if (strcmp(client[i].name, client[j].name) > 0)
            {
                strcpy(aux, client[i].name);
                strcpy(client[i].name, client[j].name);
                strcpy(client[j].name, aux);
                // Também precisamos trocar a idade e o email
                int tempAge = client[i].age;
                client[i].age = client[j].age;
                client[j].age = tempAge;

                strcpy(aux, client[i].email);
                strcpy(client[i].email, client[j].email);
                strcpy(client[j].email, aux);
            }
        }
    }
    for (i = 0; i < *vectorSize; i++)
    {
        printf("Nome : %s\n", client[i].name);
        printf("Idade : %d\n", client[i].age);
        printf("Email : %s\n", client[i].email);
        printf("---------------------------------------------\n");
    }
}
void editCustomer(Clients client[], int vectorSize)
{
    int i;
    char name[100];
    int found = 0; // Variável para controlar se o cliente foi encontrado
    while (!found) // Loop continua até o cliente ser encontrado
    {
        printf("---------------------------------------------\n");
        printf("Digite o nome do cliente que deseja editar : ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';
        for (i = 0; i < vectorSize; i++)
        {
            if (strcmp(client[i].name, name) == 0)
            {
                found = 1; // Cliente encontrado, sai do loop
                printf("Digite o novo nome do cliente : ");
                fgets(client[i].name, 50, stdin);
                client[i].name[strcspn(client[i].name, "\n")] = '\0';
                printf("Digite a idade : ");
                scanf("%d", &client[i].age);
                clearInputBuffer();
                printf("Digite o novo email : ");
                fgets(client[i].email, 100, stdin);
                client[i].email[strcspn(client[i].email, "\n")] = '\0';
                printf("---------------------------------------------\n");
                printf("Cliente %s alterado com sucesso!\n", client[i].name);
                printf("---------------------------------------------\n");
            }
        }
        if (!found) // Continua no loop ate o cliente for encontrado
        {
            printf("---------------------------------------------\n");
            printf("Nome inválido. Por favor, digite o nome correto.\n");
        }
    }
}
void deleteCustomer(Clients client[], int *vectorSize)
{
    char name[100];
    int found = 0; // Variável para controlar se o cliente foi encontrado
    int i, j, confirm;
    while (!found)
    {
        printf("---------------------------------------------\n");
        printf("Digite o nome do cliente que deseja excluir : ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = '\0';
        for (i = 0; i < *vectorSize; i++)
        {
            // Compara se o dado de entrada é igual ao que estiver armazenado, se sim, a função strcmp retorna 0.
            if (strcmp(client[i].name, name) == 0)
            {
                printf("Deseja realmente excluir o cliente %s ?(Digite 1 para SIM e 0 para NÃO) ", client[i].name);
                scanf("%d", &confirm);
                clearInputBuffer();
                if (confirm == 1)
                {
                    for (j = i; j < *vectorSize - 1; j++)
                    {
                        client[j] = client[j + 1]; // movimentação dos elementos subsequentes para preencher o espaço vazio.
                    }
                    (*vectorSize)--;
                    printf("---------------------------------------------\n");
                    printf("Cliente %s excluido com sucesso!\n", client[i].name);
                    printf("---------------------------------------------\n");
                    found = 1;
                    break;
                }
                else // Retorna pro começo do programa se não for confirmado a exclusão
                {
                    printf("---------------------------------------------\n");
                    printf("Operação de exclusão cancelada\n");
                    printf("---------------------------------------------\n");
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
        {
            printf("---------------------------------------------\n");
            printf("Nome inválido. Por favor, digite o nome correto.\n");
        }
    }
}
void saveToFile(Clients client[], int vectorSize)
{ // variável do tipo struct stat para armazenar o estado da pasta.
    struct stat st = {0};
// verifica o sistema operacional que esta rodando
#ifdef __linux
    // Colocamos as informações da pasta escolhida na variável "st" e verificamos. Se o retorno for -1 significa que o diretório não existe e se for 0 o diretório existe.
    if (stat("/tmp/client", &st) == -1)
    {
        // Cria o diretório passando como primeiro argumento onde a pasta sera criada e o segundo as permissões.
        if (mkdir("/tmp/client", 0700) == 0)
        {
            printf("Diretorio criado\n");
        }
    }
    FILE *file = fopen("/tmp/client/clientes.txt", "w");
#elif _WIN32
    if (stat("C:/Client", &st) == -1)
    {
        if (mkdir("C:/Client") == 0)
        {
            printf("Diretorio criado\n");
        }
    }
    FILE *file = fopen("C:/Client/clientes.txt", "w");
#else
    printf("Sistema não reconhecido.");
#endif
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo para escrita.\n");
        return;
    }
    for (int i = 0; i < vectorSize; i++)
    {
        fprintf(file, "%s\n%d\n%s\n", client[i].name, client[i].age, client[i].email);
    }

    fclose(file);
}
void loadFromFile(Clients client[], int *vectorSize)
{
#ifdef _WIN32
    FILE *file = fopen("C:/Client/clientes.txt", "r");
#elif __linux
    FILE *file = fopen("/tmp/client/clientes.txt", "r");
#else
    printf("Sistema não reconhecido.");
#endif
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo para leitura.\n");
        return;
    }
    // enquanto não for o fim do arquivo, o loop continua sendo executado
    // le e armazena os dados da entrada
    // adiciona sempre +1 no tamanho do vetor
    while (fscanf(file, "%49[^\n]\n%d\n%99[^\n]\n", client[*vectorSize].name, &client[*vectorSize].age, client[*vectorSize].email) != EOF)
    {
        (*vectorSize)++;
    }

    fclose(file);
}