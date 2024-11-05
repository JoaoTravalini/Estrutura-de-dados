#include <stdio.h>

#define TAM_MAX 10000

struct Pilha {
    char dados[TAM_MAX];
    int topo;
};

void inicializaPilha(struct Pilha *pilha) {
    pilha->topo = -1;
}

void empilha(struct Pilha *pilha, char item) {
    if (pilha->topo < TAM_MAX - 1) {
        pilha->dados[++pilha->topo] = item;
    }
}

char desempilha(struct Pilha *pilha) {
    if (pilha->topo >= 0) {
        return pilha->dados[pilha->topo--];
    }
    return '\0';
}

int estaVazia(struct Pilha *pilha) {
    return pilha->topo == -1;
}

int main() {
    char entrada[TAM_MAX];

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
