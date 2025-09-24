// Incluímos as bibliotecas essenciais para o nosso programa funcionar.
#include <stdio.h>   // Para funções de entrada e saída, como printf e scanf.
#include <stdlib.h>  // Para funções utilitárias, como rand() e exit().
#include <string.h>  // Para manipulação de strings, como strcpy.
#include <time.h>    // Para usar a função time() e gerar números aleatórios de verdade.

// Definimos o tamanho máximo da nossa fila. O desafio sugere 5 peças.
#define MAX 5

// --- Estruturas de Dados ---

// A estrutura "Pessoa" vai representar cada peça do jogo.
// Ela tem um nome (o tipo da peça) e um ID.
typedef struct {
  char nome[30]; // Campo para guardar o nome/tipo da peça.
  int idade;    // Campo para guardar o ID da peça.
} Pessoa;

// A estrutura "Fila" vai controlar a ordem das peças.
// Ela contém um array para armazenar as peças e variáveis de controle.
typedef struct {
  Pessoa itens[MAX]; // Array para armazenar as peças da fila.
  int inicio;        // Índice que aponta para o começo da fila.
  int fim;           // Índice que aponta para o final da fila.
  int total;         // Contador para saber quantos elementos a fila tem.
} Fila;

// --- Funções Auxiliares ---

// Função que inicializa a fila, zerando os índices e o contador de elementos.
// Isso garante que a fila comece vazia e sem lixo de memória.
void inicializarFila(Fila *f) {
  f->inicio = 0;
  f->fim = 0;
  f->total = 0;
}

// Função que verifica se a fila está cheia.
// Ela retorna 1 (verdadeiro) se o número total de elementos for igual ao tamanho máximo.
int filaCheia(Fila *f) {
  return f->total == MAX;
}

// Função que verifica se a fila está vazia.
// Ela retorna 1 (verdadeiro) se o número total de elementos for igual a zero.
int filaVazia(Fila *f) {
  return f->total == 0;
}

// Esta é uma função auxiliar para criar novas pecas automaticamente.
// Ela gera um nome de peca aleatorio e um ID unico.
Pessoa gerarPeca() {
  static int id_contador = 0; // Usamos um contador estático para IDs únicos.
  Pessoa novaPeca;
  int tipo = rand() % 4; // A gente pode usar um número para escolher o tipo de peca.
  
  if (tipo == 0) strcpy(novaPeca.nome, "I");
  else if (tipo == 1) strcpy(novaPeca.nome, "O");
  else if (tipo == 2) strcpy(novaPeca.nome, "T");
  else strcpy(novaPeca.nome, "L");
  
  novaPeca.idade = id_contador++; // Atribuímos o ID e incrementamos o contador.
  
  return novaPeca;
}

// --- Funções Principais da Fila ---

// Função que insere uma nova peça no final da fila (enqueue).
void inserir(Fila *f, Pessoa p) {
  if (filaCheia(f)) {
    printf("Fila cheia. Nao e possivel inserir mais pecas.\n");
    return;
  }
  
  f->itens[f->fim] = p; // Colocamos a nova peça na posição atual do "fim" da fila.
  f->fim = (f->fim + 1) % MAX; // Usamos a lógica circular para atualizar o índice "fim".
  f->total++; // Aumentamos o contador de elementos.
}

// Função que remove a peça do início da fila (dequeue).
void remover(Fila *f) {
  if (filaVazia(f)) {
    printf("Fila vazia. Nao ha pecas para jogar.\n");
    return;
  }
  
  printf("Peça jogada: [%s, %d]\n", f->itens[f->inicio].nome, f->itens[f->inicio].idade);
  f->inicio = (f->inicio + 1) % MAX; // Usamos a lógica circular para atualizar o índice "inicio".
  f->total--; // Diminuímos o contador de elementos.
}

// Função que exibe todos os elementos da fila na ordem correta (do início para o fim).
void mostrarFila(Fila *f) {
  printf("\n--- Estado atual da Fila ---\n");
  if (filaVazia(f)) {
    printf("A fila esta vazia.\n");
    return;
  }
  
  int i;
  int idx = f->inicio;
  for (i = 0; i < f->total; i++) {
    printf("[%s %d] ", f->itens[idx].nome, f->itens[idx].idade);
    idx = (idx + 1) % MAX; // Usamos a mesma lógica circular para avançar para o próximo elemento.
  }
  printf("\n--------------------------\n");
}


// --- Função Principal: O Jogo ---

int main() {
  Fila f;
  int opcao;
  
  // A semente para a função rand() é inicializada para que os números sejam diferentes a cada rodada.
  srand(time(NULL));

  // Inicializamos a nossa fila antes de usá-la.
  inicializarFila(&f);

  // O desafio pede para a fila já começar com alguns elementos.
  printf("Inicializando a fila com 5 pecas...\n");
  for (int i = 0; i < MAX; i++) {
    inserir(&f, gerarPeca());
  }

  do {
    // Exibimos o estado atual da fila no começo de cada rodada.
    mostrarFila(&f);
    
    // Mostramos as opções para o jogador.
    printf("\nOpcoes de acao:\n");
    printf("1 - Jogar peca (remover)\n");
    printf("2 - Inserir nova peca\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
    
    // Lemos a opção do jogador.
    scanf("%d", &opcao);
    
    switch(opcao) {
      case 1:
        remover(&f);
        break;
      case 2:
        inserir(&f, gerarPeca());
        break;
      case 0:
        printf("Saindo do jogo. Ate mais!\n");
        break;
      default:
        printf("Opcao invalida. Tente novamente.\n");
    }
    
  } while (opcao != 0); // O loop continua até que o jogador escolha sair (opção 0).
  
  return 0; // Retorna 0 para indicar que o programa rodou com sucesso.
}