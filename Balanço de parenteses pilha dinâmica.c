#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node *next;
};

struct Pilha {
    struct Node *top;
};

void inicializaPilha(struct Pilha *pilha) {
    pilha->top = NULL;
}

void empilha(struct Pilha *pilha, char item) {
    struct Node *novoNo = (struct Node *)malloc(sizeof(struct Node));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocacao de memoria.\n");
        exit(1);
    }
    novoNo->data = item;
    novoNo->next = pilha->top;
    pilha->top = novoNo;
}

char desempilha(struct Pilha *pilha) {
    if (pilha->top != NULL) {
        char item = pilha->top->data;
        struct Node *temp = pilha->top;
        pilha->top = pilha->top->next;
        free(temp);
        return item;
    }
    return '\0';
}

int estaVazia(struct Pilha *pilha) {
    return pilha->top == NULL;
}

int main() {
    char entrada[10001];

    while (scanf("%s", entrada) != EOF) {
        struct Pilha pilha;
        inicializaPilha(&pilha);
        int i = 0;
        while (entrada[i] != '\0') {
            if (entrada[i] == '(') {
                empilha(&pilha, '(');
            } else if (entrada[i] == ')') {
                if (estaVazia(&pilha) || desempilha(&pilha) != '(') {
                    printf("incorreto\n");
                    break;
                }
            }
            i++;
        }
        if (entrada[i] == '\0' && estaVazia(&pilha)) {
            printf("correto\n");
        } else if (entrada[i] == '\0') {
            printf("incorreto\n");
        }
    }

    return 0;
}
