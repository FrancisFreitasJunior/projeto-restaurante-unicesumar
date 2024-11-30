#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_PESSOAS_POR_DIA 50

int pessoasPorDia[5] = {0}; // Mantém como variável global

struct reserva
{
    char cpf[15]; 
    char nome[100];
    int dia;
    int numeroPessoas;
};

void separadorDuplo()
{
    printf("==============================================\n");
}

void separadorSimples()
{
    printf("----------------------------------------------\n");
}

void separadorError()
{
    printf("##############################################\n");
}

void headSystem()
{
    system("clear");
    separadorDuplo();
    printf("==================RESTAURANT==================\n");
    separadorDuplo();
}

void menuSystem()
{
    headSystem();
    printf("|--------------Digite uma opção--------------|\n");
    separadorSimples();
    printf("1 - Fazer Reserva\n");
    printf("2 - Listar Reserva\n");
    printf("3 - Total de Pessoas por Dia\n");
    printf("4 - Sair\n");
    separadorSimples();
}

void pausa()
{
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}

void cadastroReserva(struct reserva *r)
{
    printf("Digite seu nome: \n");
    scanf(" %[^\n]s", r->nome); // Lê uma string com espaços

    separadorSimples();
    printf("Digite o CPF (somente números): \n");
    scanf("%d", &r->cpf);

    separadorSimples();
    printf("Escolha o dia da reserva:\n");
    printf("1 - Quinta\n2 - Sexta\n3 - Sábado\n4 - Domingo\n");

    // Verifica se o dia já está lotado antes de solicitar o número de pessoas
    do
    {
        separadorSimples();
        printf("Digite o número correspondente ao dia (1 a 4): \n");
        scanf("%d", &r->dia);
        
        if (r->dia < 1 || r->dia > 4)
        {
            separadorError();
            printf("####### DIA INVÁLIDO! TENTE NOVAMENTE. #######\n");
            separadorError();
        }
        else if (pessoasPorDia[r->dia] >= MAX_PESSOAS_POR_DIA)
        {
            separadorSimples();
            printf("Limite de reservas para este dia atingido! \nEscolha outro dia.\n");
            r->dia = 0; // Reseta para forçar nova entrada de dia
        }
    } while (r->dia < 1 || r->dia > 4 || pessoasPorDia[r->dia] >= MAX_PESSOAS_POR_DIA); // Verifica se o dia já está lotado

    separadorSimples();
    printf("Digite o número de pessoas: ");
    scanf("%d", &r->numeroPessoas);

    if (pessoasPorDia[r->dia] + r->numeroPessoas > MAX_PESSOAS_POR_DIA)
    {
        printf("Não é possível realizar a reserva. \nLimite de pessoas para o dia atingido.\n");
        return;
    }

    pessoasPorDia[r->dia] += r->numeroPessoas; // Incrementa o contador de reservas para o dia

    printf("\nReserva cadastrada com sucesso!\n");
}

void listarReservas(struct reserva reservas[], int numReservas)
{
    if (numReservas == 0)
    {
        printf("Nenhuma reserva cadastrada até o momento.\n");
        return;
    }

    for (int i = 0; i < numReservas; i++)
    {
        separadorDuplo();
        printf("Nome: %s\n", reservas[i].nome);
        printf("CPF: %d\n", reservas[i].cpf); // CPF formatado (apenas número por enquanto)
        printf("Dia: %d\n", reservas[i].dia);
        printf("Número de Pessoas: %d\n", reservas[i].numeroPessoas);
        separadorDuplo();
    }
}

int main()
{
    setlocale(LC_ALL, "");

    struct reserva reservas[100]; // Suporte para até 100 reservas
    int numReservas = 0;

    int opcao;

    do
    {
        menuSystem();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (numReservas < 100)
            {
                headSystem();
                printf("|-----------Preencha com seus dados----------|\n");
                separadorSimples();
                cadastroReserva(&reservas[numReservas]);
                numReservas++;
            }
            else
            {
                printf("Limite total de reservas atingido!\n");
            }
            pausa(); // Aguarda Enter antes de voltar ao menu
            break;

        case 2:
            headSystem();
            printf("|---------Listando todas as reservas---------|\n");
            separadorSimples();
            listarReservas(reservas, numReservas);
            printf("\nEnter para voltar ao menu principal...");
            getchar(); // Captura o Enter do usuário
            getchar(); // Para evitar problemas de buffer
            break;

        case 3:
            printf("Cálculo de total por dia ainda não implementado.\n");
            break;

        case 4:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }

    } while (opcao != 4);

    return 0;
}