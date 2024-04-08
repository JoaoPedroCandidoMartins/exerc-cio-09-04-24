#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_QUEUE_SIZE 100

// Definição das estruturas para cada tipo de frequentador
typedef struct {
    int matricula;
    char nome[MAX_NAME_LENGTH];
    char curso[MAX_NAME_LENGTH];
} Aluno;

typedef struct {
    int siape;
    char nome[MAX_NAME_LENGTH];
    char titulacao[MAX_NAME_LENGTH];
} Professor;

typedef struct {
    int siape;
    char nome[MAX_NAME_LENGTH];
} TecnicoAdministrativo;

// Definição do tipo de dados para a fila
typedef struct {
    void* items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Funções de manipulação da fila
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

void enqueue(Queue* queue, void* item) {
    if (queue->size == MAX_QUEUE_SIZE) {
        printf("Fila cheia!\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    queue->items[queue->rear] = item;
    queue->size++;
}

void* dequeue(Queue* queue) {
    if (queue->size == 0) {
        printf("Fila vazia!\n");
        return NULL;
    }
    void* item = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    queue->size--;
    return item;
}

// Função principal
int main() {
    // Criar fila
    Queue* fila = createQueue();

    // Exemplo de utilização: adicionar frequentadores
    Aluno* aluno1 = (Aluno*)malloc(sizeof(Aluno));
    aluno1->matricula = 12345;
    strcpy(aluno1->nome, "Joao");
    strcpy(aluno1->curso, "Engenharia");

    Professor* professor1 = (Professor*)malloc(sizeof(Professor));
    professor1->siape = 54321;
    strcpy(professor1->nome, "Maria");
    strcpy(professor1->titulacao, "Doutorado");

    TecnicoAdministrativo* tecnico1 = (TecnicoAdministrativo*)malloc(sizeof(TecnicoAdministrativo));
    tecnico1->siape = 98765;
    strcpy(tecnico1->nome, "Pedro");

    // Adicionar frequentadores à fila
    enqueue(fila, aluno1);
    enqueue(fila, professor1);
    enqueue(fila, tecnico1);

    // Exemplo de utilização: remover frequentadores da fila
    void* frequentador1 = dequeue(fila);
    if (frequentador1 != NULL) {
        printf("Frequentador removido: ");
        if (frequentador1 == aluno1) {
            printf("Aluno\n");
            free(aluno1);
        } else if (frequentador1 == professor1) {
            printf("Professor\n");
            free(professor1);
        } else if (frequentador1 == tecnico1) {
            printf("Técnico Administrativo\n");
            free(tecnico1);
        }
    }

    // Liberação de memória da fila
    free(fila);

    return 0;
}
