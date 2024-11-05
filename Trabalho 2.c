#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

typedef struct Processo {
    char nome[30];
    int prioridade;
    float taxaCompleto;
    float taxaPorCiclo;
    int tempoProcessamento;
    struct Processo *prox;
} Processo;

Processo* inicializar() {
    return NULL;
}

Processo* inserir(Processo *lista, char nome[], int prioridade, float taxaPorCiclo, int tempoProcessamento) {
    Processo *novoProcesso = (Processo*) malloc(sizeof(Processo));
    strcpy(novoProcesso->nome, nome);
    novoProcesso->prioridade = prioridade;
    novoProcesso->taxaCompleto = 0;
    novoProcesso->taxaPorCiclo = taxaPorCiclo;
    novoProcesso->tempoProcessamento = tempoProcessamento;
    novoProcesso->prox = NULL;

    if (!lista) {
        return novoProcesso;
    }

    Processo *atual = lista, *anterior = NULL;

    while (atual && atual->prioridade <= prioridade) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!anterior) {
        novoProcesso->prox = lista;
        return novoProcesso;
    } else {
        novoProcesso->prox = anterior->prox;
        anterior->prox = novoProcesso;
    }

    return lista;
}


Processo* remover(Processo* lista, char nome[]) {
    if (!lista) return NULL;

    Processo *prev = NULL, *current = lista;

    do {
        if (strcmp(current->nome, nome) == 0) break;
        prev = current;
        current = current->prox;
    } while (current != lista);

    if (prev) {
        prev->prox = current->prox;
        if (current == lista) lista = prev->prox;
    } else {
        if (current->prox == current) {
            free(current);
            return NULL;
        }
        Processo* last = lista;
        while (last->prox != lista) last = last->prox;
        last->prox = current->prox;
        lista = current->prox;
    }

    free(current);
    return lista;
}

void processar(Processo **lista) {
    int algumProcessoAtivo = 1;
    
    // Primeiro, processa todos os processos até que todos sejam completados
    while (algumProcessoAtivo) {
        algumProcessoAtivo = 0; // Assume que nenhum processo é ativo até que provado o contrário
        Processo *current = *lista;

        while (current) {
            if (current->taxaCompleto < 100.0) {
                printf("%s entrou no processador\n", current->nome);
                sleep(current->tempoProcessamento);
                current->taxaCompleto += current->taxaPorCiclo;
                if (current->taxaCompleto > 100.0) current->taxaCompleto = 100.0;
                printf("%s saiu do processador com taxa de %.2f%%\n", current->nome, current->taxaCompleto);

                // Indica que ainda temos um processo ativo
                if (current->taxaCompleto < 100.0) {
                    algumProcessoAtivo = 1;
                }
            }

            current = current->prox;
        }
    }

    // Agora, remove os processos completados
    Processo *current = *lista;
    while (current) {
        if (current->taxaCompleto == 100.0) {
            printf("%s foi finalizado\n", current->nome);
            *lista = remover(*lista, current->nome);
            current = *lista;
        } else {
            current = current->prox;
        }
    }
}




void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int prioridadeExiste(Processo *lista, int prioridade) {
    Processo *current = lista;
    while (current) {
        if (current->prioridade == prioridade) {
            return 1; // Encontrou prioridade já existente
        }
        current = current->prox;
    }
    return 0; // Prioridade não foi encontrada
}

void inserirProcessoUsuario(Processo **lista) {
    char nome[30];
    int prioridade;
    float taxaPorCiclo;
    int tempoProcessamento;
    char opcao;

    do {
        printf("Insira o nome do processo: ");
        scanf("%s", nome);
        limparBuffer();

        do {
            printf("Insira a prioridade do processo (1-5): ");
            scanf("%d", &prioridade);
            limparBuffer();

            if (prioridadeExiste(*lista, prioridade)) {
                printf("Erro: A prioridade %d já existe! Escolha outra prioridade.\n", prioridade);
            }
        } while (prioridadeExiste(*lista, prioridade));

        printf("Insira a taxa por ciclo do processo: ");
        scanf("%f", &taxaPorCiclo);
        limparBuffer();

        printf("Insira o tempo de processamento do processo: ");
        scanf("%d", &tempoProcessamento);
        limparBuffer();

        *lista = inserir(*lista, nome, prioridade, taxaPorCiclo, tempoProcessamento);

        printf("Deseja inserir outro processo? (S/N) ");
        scanf(" %c", &opcao);
        limparBuffer();
    } while(opcao == 'S' || opcao == 's');
}

int main() {
    Processo *lista = inicializar();

    inserirProcessoUsuario(&lista);

    while (lista) {
        processar(&lista);
    }

    return 0;
}




