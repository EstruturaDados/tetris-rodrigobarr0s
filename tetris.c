#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdlib.h>
#include <string.h>

#define MAX_FILA 5

// Estrutura que representa uma peça
typedef struct
{
    int id;
    char nome[2]; // Ex: "I", "O", "T", "L"
} Peca;

// Fila circular
Peca fila[MAX_FILA];
int frente = 0;
int tras = 0;
int quantidade = 0;
int contadorId = 1;

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
    if (quantidade == MAX_FILA)
    {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    fila[tras] = gerarPeca();
    tras = (tras + 1) % MAX_FILA;
    quantidade++;
}

// Remover peça da fila (dequeue)
void jogarPeca()
{
    if (quantidade == 0)
    {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca jogada = fila[frente];
    printf("Peça jogada: ID=%d, Tipo=%s\n", jogada.id, jogada.nome);
    frente = (frente + 1) % MAX_FILA;
    quantidade--;

    // Inserir automaticamente uma nova peça
    inserirPeca();
}

// Visualizar fila
void visualizarFila()
{
    if (quantidade == 0)
    {
        printf("Fila vazia.\n");
        return;
    }
    printf("\n===== Fila de Peças Futuras =====\n");
    int i, idx;
    for (i = 0, idx = frente; i < quantidade; i++, idx = (idx + 1) % MAX_FILA)
    {
        printf("Posição %d -> ID=%d, Tipo=%s\n", i, fila[idx].id, fila[idx].nome);
    }
    printf("=================================\n\n");
}

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
        printf("1. Jogar peça (dequeue)\n");
        printf("2. Inserir nova peça (enqueue)\n");
        printf("3. Visualizar fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            jogarPeca();
            break;
        case 2:
            inserirPeca();
            break;
        case 3:
            visualizarFila();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;

}
