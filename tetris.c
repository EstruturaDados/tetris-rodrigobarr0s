#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdlib.h>
#include <string.h>

#define MAX_FILA 5
#define MAX_PILHA 3
#define MAX_HISTORICO 10

// Estrutura que representa uma peça
typedef struct
{
    int id;
    char nome[2]; // Ex: "I", "O", "T", "L"
} Peca;

// Histórico para desfazer última jogada
typedef struct
{
    char acao[20];
    Peca peca;
} Historico;

// Fila circular
Peca fila[MAX_FILA];
int frente = 0;
int tras = 0;
int quantidadeFila = 0;
int contadorId = 1;

// Pilha linear
Peca pilha[MAX_PILHA];
int topo = -1;

// Histórico de ações
Historico historico[MAX_HISTORICO];
int topoHistorico = -1;

// Função para gerar automaticamente uma peça
Peca gerarPeca()
{
    Peca nova;
    nova.id = contadorId++;
    char tipos[4][2] = {"I", "O", "T", "L"};
    strcpy(nova.nome, tipos[rand() % 4]);
    return nova;
}

// Inserir peça na fila (enqueue)
void inserirPeca()
{
    if (quantidadeFila == MAX_FILA)
        return;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % MAX_FILA;
    quantidadeFila++;
}

// Remover peça da fila (dequeue)
Peca jogarPeca()
{
    if (quantidadeFila == 0)
    {
        Peca vazio = {-1, " "};
        return vazio;
    }
    Peca jogada = fila[frente];
    frente = (frente + 1) % MAX_FILA;
    quantidadeFila--;

    inserirPeca();

    // Registrar no histórico
    if (topoHistorico < MAX_HISTORICO - 1)
    {
        topoHistorico++;
        strcpy(historico[topoHistorico].acao, "jogar");
        historico[topoHistorico].peca = jogada;
    }

    return jogada;
}

// Visualizar fila
void visualizarFila()
{
    printf("\n===== Fila de Peças Futuras =====\n");
    int i, idx;
    for (i = 0, idx = frente; i < quantidadeFila; i++, idx = (idx + 1) % MAX_FILA)
    {
        printf("Posição %d -> ID=%d, Tipo=%s\n", i, fila[idx].id, fila[idx].nome);
    }
    printf("=================================\n\n");
}

// Visualizar pilha
void visualizarPilha()
{
    printf("\n===== Pilha de Peças Reservadas =====\n");
    for (int i = topo; i >= 0; i--)
    {
        printf("Topo-%d -> ID=%d, Tipo=%s\n", i, pilha[i].id, pilha[i].nome);
    }
    printf("=====================================\n\n");
}

// Reservar peça (push)
void reservarPeca()
{
    if (topo == MAX_PILHA - 1 || quantidadeFila == 0)
        return;
    Peca reservada = jogarPeca();
    topo++;
    pilha[topo] = reservada;

    // Registrar no histórico
    if (topoHistorico < MAX_HISTORICO - 1)
    {
        topoHistorico++;
        strcpy(historico[topoHistorico].acao, "reservar");
        historico[topoHistorico].peca = reservada;
    }
}

// Usar peça reservada (pop)
void usarReservada()
{
    if (topo == -1)
        return;
    Peca usada = pilha[topo];
    topo--;

    // Registrar no histórico
    if (topoHistorico < MAX_HISTORICO - 1)
    {
        topoHistorico++;
        strcpy(historico[topoHistorico].acao, "usar");
        historico[topoHistorico].peca = usada;
    }

    printf("Peça usada da reserva: ID=%d, Tipo=%s\n", usada.id, usada.nome);
}

// Trocar peça do topo da pilha com a da frente da fila
void trocarPeca()
{
    if (topo == -1 || quantidadeFila == 0)
        return;
    Peca temp = pilha[topo];
    pilha[topo] = fila[frente];
    fila[frente] = temp;

    printf("Troca realizada entre topo da pilha e frente da fila.\n");
}

// Desfazer última jogada
void desfazer()
{
    if (topoHistorico == -1)
    {
        printf("Nenhuma ação para desfazer.\n");
        return;
    }

    Historico ultima = historico[topoHistorico];
    topoHistorico--;

    if (strcmp(ultima.acao, "jogar") == 0)
    {
        // Recoloca peça na frente da fila
        frente = (frente - 1 + MAX_FILA) % MAX_FILA;
        fila[frente] = ultima.peca;
        quantidadeFila++;
        printf("Desfeito: peça %s (ID=%d) voltou para a fila.\n", ultima.peca.nome, ultima.peca.id);
    }
    else if (strcmp(ultima.acao, "reservar") == 0)
    {
        // Remove da pilha
        if (topo >= 0)
            topo--;
        printf("Desfeito: peça %s (ID=%d) removida da pilha.\n", ultima.peca.nome, ultima.peca.id);
    }
    else if (strcmp(ultima.acao, "usar") == 0)
    {
        // Recoloca na pilha
        topo++;
        pilha[topo] = ultima.peca;
        printf("Desfeito: peça %s (ID=%d) voltou para a pilha.\n", ultima.peca.nome, ultima.peca.id);
    }
}

// Inverter fila com pilha
void inverterFilaPilha()
{
    int i = 0;
    while (quantidadeFila > 0 && topo < MAX_PILHA - 1)
    {
        Peca p = jogarPeca();
        topo++;
        pilha[topo] = p;
        i++;
    }
    printf("Inversão realizada: %d peças movidas da fila para a pilha.\n", i);
}

// Função principal com menu interativo
int main()
{

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    int opcao;

    // Inicializar fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++)
    {
        inserirPeca();
    }

    do
    {
        printf("===== MENU =====\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Usar peça reservada\n");
        printf("4. Trocar peça do topo da pilha com a da frente da fila\n");
        printf("5. Desfazer última jogada\n");
        printf("6. Inverter fila com pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            Peca jogada = jogarPeca();
            if (jogada.id != -1)
                printf("Peça jogada: ID=%d, Tipo=%s\n", jogada.id, jogada.nome);
            break;
        }
        case 2:
            reservarPeca();
            break;
        case 3:
            usarReservada();
            break;
        case 4:
            trocarPeca();
            break;
        case 5:
            desfazer();
            break;
        case 6:
            inverterFilaPilha();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }

        // Mostrar estado atual
        visualizarFila();
        visualizarPilha();

    } while (opcao != 0);

    return 0;
}
