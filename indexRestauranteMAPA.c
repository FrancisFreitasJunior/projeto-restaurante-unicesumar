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
    int status; // 1 para reserva confirmada, 0 para não confirmada
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
    while (getchar() != '\n') // Limpa o buffer de entrada
        ;
    getchar(); // Espera o Enter
}

void cadastroReserva(struct reserva *r)
{
    printf("Digite seu nome: \n");
    fgets(r->nome, sizeof(r->nome), stdin);
    r->nome[strcspn(r->nome, "\n")] = '\0'; // Remove a nova linha no final, caso seja capturada

    separadorSimples();
    printf("Digite o CPF (somente números): \n");
    fgets(r->cpf, sizeof(r->cpf), stdin);
    r->cpf[strcspn(r->cpf, "\n")] = '\0'; // Remove a nova linha no final, caso seja capturada

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
        else if (pessoasPorDia[r->dia - 1] >= MAX_PESSOAS_POR_DIA) // Ajuste aqui para usar r->dia - 1
        {
            separadorSimples();
            printf("Limite de reservas para este dia atingido! \nEscolha outro dia.\n");
            r->dia = 0; // Reseta para forçar nova entrada de dia
        }
    } while (r->dia < 1 || r->dia > 4 || pessoasPorDia[r->dia - 1] >= MAX_PESSOAS_POR_DIA); // Corrigido aqui também

    separadorSimples();
    printf("Digite o número de pessoas: ");
    scanf("%d", &r->numeroPessoas);

    // Valida a quantidade de pessoas para garantir que o número de pessoas não ultrapasse a capacidade
    if (pessoasPorDia[r->dia - 1] + r->numeroPessoas > MAX_PESSOAS_POR_DIA) // Correção do índice
    {
        printf("Não é possível realizar a reserva. \nLimite de pessoas para o dia atingido.\n");
        return; // Retorna sem cadastrar a reserva
    }

    // Caso a validação passe, incrementa o contador de reservas para o dia
    pessoasPorDia[r->dia - 1] += r->numeroPessoas;

    // Define o status da reserva como 1 (reserva confirmada)
    r->status = 1;

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
        if (reservas[i].status == 1) // Verifica se a reserva foi válida (status 1)
        {
            separadorDuplo();
            printf("Nome: %s\n", reservas[i].nome);
            printf("CPF: %s\n", reservas[i].cpf); // CPF formatado
            printf("Dia: %d\n", reservas[i].dia);
            printf("Número de Pessoas: %d\n", reservas[i].numeroPessoas);
            separadorDuplo();
        }
    }
}

void mostrarTotalPorDia()
{
    const char *dias[] = {"Quinta-feira", "Sexta-feira", "Sábado", "Domingo"};

    for (int i = 0; i < 4; i++) // Corrigido: o índice deve começar em 0
    {
        int totalReservado = pessoasPorDia[i]; // Corrigido: agora acessa o índice correto
        int vagasDisponiveis = MAX_PESSOAS_POR_DIA - totalReservado;

        separadorDuplo();
        printf("%s:\n", dias[i]);
        if (totalReservado >= MAX_PESSOAS_POR_DIA)
        {
            printf("Total pessoas: %d\n", totalReservado);
            printf("Disponível: LOTADO\n");
        }
        else
        {
            printf("Total reservas: %d\n", totalReservado);
            printf("Disponíveis: %d\n", vagasDisponiveis);
        }
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
        // Limpa o buffer após ler a opção
        while (getchar() != '\n')
            ;

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
            printf("\nPressione Enter para voltar ao menu principal...");
            getchar(); // Espera o Enter do usuário
            break;

        case 3:
            headSystem();
            printf("|---------Total de pessoas por dia-----------|\n");
            mostrarTotalPorDia();
            printf("\nEnter para voltar ao menu principal...");
            getchar(); // Espera o Enter do usuário
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