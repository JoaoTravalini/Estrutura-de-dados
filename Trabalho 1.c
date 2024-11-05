#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno {
    char nome[30];
    int matricula;
    int idade;
    int nroDisciplinas;
    struct Aluno* prox;
} Aluno;

typedef struct Universidade {
    char nome[30];
    int qtdAlunos;
    struct Universidade* prox;
    Aluno* inicio;
} Universidade;

Universidade* insereUniversidade(Universidade* lista, char nome[30]);
Universidade* insereAluno(Universidade* lista, char nomeU[30], char nomeA[30], int matricula, int idade, int nroDisciplinas);
Universidade* buscaUniversidade(Universidade* lista, char nome[30]);
Universidade* buscaAluno(Universidade* lista, int matricula);
Universidade* removeUniversidade(Universidade* lista, char nome[30]);
Universidade* removeAluno(Universidade* lista, int matricula);
void salvaDados(Universidade* lista);
Universidade* recuperaDados();
void liberarMemoria(Universidade* lista);




void menu(Universidade* lista) {
    int opcao;
    char nomeU[30];
    char nomeA[30];
    int matricula, idade, nroDisciplinas;

    do {
        printf("1) Insere Universidade\n");
        printf("2) Insere Aluno\n");
        printf("3) Busca Universidade\n");
        printf("4) Busca Aluno\n");
        printf("5) Remove Universidade\n");
        printf("6) Remove Aluno\n");
        printf("0) Fechar\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome da Universidade: ");
                scanf(" %[^\n]", nomeU);
                lista = insereUniversidade(lista, nomeU);
                break;
            case 2:
                
                printf("Nome da Universidade: ");
                scanf(" %[^\n]", nomeU);
                printf("Nome do Aluno: ");
                scanf(" %[^\n]", nomeA);
                printf("Matrícula do Aluno: ");
                scanf("%d", &matricula);
                printf("Idade do Aluno: ");
                scanf("%d", &idade);
                printf("Número de Disciplinas: ");
                scanf("%d", &nroDisciplinas);
                insereAluno(lista, nomeU, nomeA, matricula, idade, nroDisciplinas);
                break;
                
            case 3:
                printf("Nome da Universidade: ");
                scanf(" %[^\n]", nomeU);
                Universidade* u = buscaUniversidade(lista, nomeU);
                if (u != NULL) {
                printf("Universidade %s encontrada com %d alunos.\n", u->nome, u->qtdAlunos);
                } else {
                 printf("Universidade %s não encontrada.\n", nomeU);
                }
                break;

            case 4:
                printf("Matrícula do Aluno: ");
                scanf("%d", &matricula);
                buscaAluno(lista, matricula);
                break;
            case 5:
                printf("Nome da Universidade: ");
                scanf(" %[^\n]", nomeU);
                lista = removeUniversidade(lista, nomeU);
                break;
            case 6:
                printf("Matrícula do Aluno: ");
                scanf("%d", &matricula);
                lista = removeAluno(lista, matricula);
                break;
            case 0:
                salvaDados(lista);
                break;
        }

    } while (opcao != 0);
}

int main() {
    Universidade* lista = recuperaDados();
    menu(lista);
    liberarMemoria(lista);
    return 0;
}


Universidade* insereUniversidade(Universidade* lista, char nome[30]) {
    Universidade* novo = (Universidade*) malloc(sizeof(Universidade));
    Universidade* ant = NULL;
    Universidade* p = lista;

    strcpy(novo->nome, nome);
    novo->qtdAlunos = 0;
    novo->inicio = NULL;

    while (p != NULL && strcmp(p->nome, nome) < 0) {
        ant = p;
        p = p->prox;
    }

    if (p != NULL && strcmp(p->nome, nome) == 0) {
        printf("Universidade já cadastrada.\n");
        free(novo);
        return lista;
    }

    novo->prox = p;

    if (ant == NULL) {
        return novo;
    }

    ant->prox = novo;
    return lista;
}

Universidade* insereAluno(Universidade* lista, char nomeUniversidade[30], char nomeAluno[30], int matricula, int idade, int nroDisciplinas) {
    Universidade* p = lista;
    while (p != NULL && strcmp(p->nome, nomeUniversidade) != 0) {
        p = p->prox;
    }

    if (p == NULL) {
        printf("Universidade não encontrada. Deseja inserir em outra universidade? (1 para sim, 0 para não): ");
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            printf("Digite o nome da universidade: ");
            scanf(" %[^\n]", nomeUniversidade);
            return insereAluno(lista, nomeUniversidade, nomeAluno, matricula, idade, nroDisciplinas);
        } else {
            return lista;
        }
    }

    Aluno* novo = (Aluno*) malloc(sizeof(Aluno));
    strcpy(novo->nome, nomeAluno);
    novo->matricula = matricula;
    novo->idade = idade;
    novo->nroDisciplinas = nroDisciplinas;

    if (p->inicio == NULL || p->inicio->matricula > matricula) {
        novo->prox = p->inicio;
        p->inicio = novo;
    } else {
        Aluno* ant = NULL;
        Aluno* atual = p->inicio;
        while (atual != NULL && atual->matricula < matricula) {
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = novo;
        novo->prox = atual;
    }

    p->qtdAlunos++;
    return lista;
}

Universidade* buscaUniversidade(Universidade* lista, char nome[30]) {
    Universidade* p = lista;
    while (p != NULL) {
        if (strcmp(p->nome, nome) == 0) {
            return p;
        }
        p = p->prox;
    }
    return NULL;  // Retorna NULL se não encontrar.
}

Universidade* buscaAluno(Universidade* lista, int matricula) {
    Universidade* p = lista;
    while (p != NULL) {
        Aluno* aluno = p->inicio;
        while (aluno != NULL) {
            if (aluno->matricula == matricula) {
                printf("Aluno encontrado na universidade %s\n", p->nome);
                return p;
            }
            aluno = aluno->prox;
        }
        p = p->prox;
    }
    printf("Aluno não encontrado.\n");
    return NULL;
}

Universidade* removeUniversidade(Universidade* lista, char nome[30]) {
    Universidade* ant = NULL;
    Universidade* p = lista;
    
    while (p != NULL && strcmp(p->nome, nome) != 0) {
        ant = p;
        p = p->prox;
    }
    
    if (p == NULL) {
        printf("Universidade não encontrada.\n");
        return lista;
    }
    
    if (ant == NULL) {
        lista = p->prox;
    } else {
        ant->prox = p->prox;
    }

    while (p->inicio != NULL) {  // Liberar os alunos.
        Aluno* temp = p->inicio;
        p->inicio = p->inicio->prox;
        free(temp);
    }

    free(p);
    return lista;
}

Universidade* removeAluno(Universidade* lista, int matricula) {
    Universidade* p = lista;
    while (p != NULL) {
        if (p->inicio && p->inicio->matricula == matricula) {  // Se o aluno for o primeiro.
            Aluno* temp = p->inicio;
            p->inicio = p->inicio->prox;
            free(temp);
            p->qtdAlunos--;
            return lista;
        }
        Aluno* ant = NULL;
        Aluno* aluno = p->inicio;
        while (aluno != NULL && aluno->matricula != matricula) {
            ant = aluno;
            aluno = aluno->prox;
        }
        if (aluno) {
            ant->prox = aluno->prox;
            free(aluno);
            p->qtdAlunos--;
            return lista;
        }
        p = p->prox;
    }
    printf("Aluno não encontrado.\n");
    return lista;
}

void salvaDados(Universidade* inicio) {
    FILE* file = fopen("lista_uni.txt", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    Universidade* auxUniv = inicio;
    while (auxUniv != NULL) {
        fprintf(file, "%s\n", auxUniv->nome);
        fprintf(file, "%d\n", auxUniv->qtdAlunos);

        Aluno* auxAluno = auxUniv->inicio;
        while (auxAluno != NULL) {
            fprintf(file, "%s\n", auxAluno->nome);
            fprintf(file, "%d\n", auxAluno->matricula);
            fprintf(file, "%d\n", auxAluno->idade);
            fprintf(file, "%d\n", auxAluno->nroDisciplinas);
            auxAluno = auxAluno->prox;
        }

        fprintf(file, "\n");
        auxUniv = auxUniv->prox;
    }

    fclose(file);
}

Universidade* recuperaDados() {
    FILE* file = fopen("lista_uni.txt", "r");
    if (file == NULL) {
        printf("Arquivo inexistente, será criado.\n");
        return NULL;
    }

    Universidade* inicio = NULL;
    Universidade* auxUniv = NULL;
    Aluno* auxAluno = NULL;
    char line[30];

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) {
            auxUniv = NULL;
            auxAluno = NULL;
        } else if (auxUniv == NULL) {
            Universidade* nova_uni = malloc(sizeof(Universidade));
            strcpy(nova_uni->nome, line);

            fgets(line, sizeof(line), file);
            nova_uni->qtdAlunos = atoi(line);

            nova_uni->prox = NULL;
            nova_uni->inicio = NULL;

            if (inicio == NULL) {
                inicio = nova_uni;
            } else {
                auxUniv->prox = nova_uni;
            }
            auxUniv = nova_uni;
        } else {
            Aluno* novo_aluno = malloc(sizeof(Aluno));
            strcpy(novo_aluno->nome, line);

            fgets(line, sizeof(line), file);
            novo_aluno->matricula = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->idade = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->nroDisciplinas = atoi(line);

            novo_aluno->prox = NULL;

            if (auxUniv->inicio == NULL) {
                auxUniv->inicio = novo_aluno;
            } else {
                auxAluno->prox = novo_aluno;
            }
            auxAluno = novo_aluno;
        }
    }

    fclose(file);
    return inicio;
}

void imprime(Universidade* head){
    if(head == NULL){
        printf("Lista vazia");
        return;
    }

    Universidade *aux = head;
    while(aux != NULL){
        printf("%s ", aux->nome);
        aux = aux->prox;
    }
}

        
void liberarMemoria(Universidade* lista) {
    Universidade* tempU;
    Aluno* tempA;

    while (lista) {
        while (lista->inicio) {
            tempA = lista->inicio;
            lista->inicio = lista->inicio->prox;
            free(tempA);
        }
        tempU = lista;
        lista = lista->prox;
        free(tempU);
    }
}