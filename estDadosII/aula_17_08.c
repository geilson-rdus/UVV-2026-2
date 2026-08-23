#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define NUM_ALUNOS 30

typedef struct aluno {
    char *nome;
    int nro_USP;
} aluno;

int main()
{
    FILE *arquivo = fopen("alunos.dat", "wb+");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    aluno alunos[NUM_ALUNOS];

    for (int i = 0; i < NUM_ALUNOS; i++) {

        char buffer[TAM_NOME];

        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%99s", buffer);

        alunos[i].nome = malloc(strlen(buffer) + 1);

        if (alunos[i].nome == NULL) {
            printf("Erro ao alocar memoria!\n");

            for (int j = 0; j < i; j++) {
                free(alunos[j].nome);
            }

            fclose(arquivo);
            return 1;
        }

        strcpy(alunos[i].nome, buffer);

        alunos[i].nro_USP = i + 1;

        char nomeArquivo[TAM_NOME] = {0};

        strcpy(nomeArquivo, alunos[i].nome);

        fwrite(nomeArquivo, sizeof(char), TAM_NOME, arquivo);
        fwrite(&alunos[i].nro_USP, sizeof(int), 1, arquivo);
    }

    int uspAluno;

    printf("\nDigite o numero USP do aluno que quer encontrar: ");
    scanf("%d", &uspAluno);

    long tamanhoRegistro = TAM_NOME * sizeof(char) + sizeof(int);
                           
    long posicao = (uspAluno - 1) * tamanhoRegistro;

    fseek(arquivo, posicao, SEEK_SET);

    char nomeAux[TAM_NOME];
    int uspAux;

    fread(nomeAux, sizeof(char), TAM_NOME, arquivo);
    fread(&uspAux, sizeof(int), 1, arquivo);

    if (uspAux == uspAluno) {
        printf("\nAluno encontrado!\n");
        printf("USP: %d\n", uspAux);
        printf("Nome: %s\n", nomeAux);
    }
    else {
        printf("\nAluno nao encontrado!\n");
    }

    for (int i = 0; i < NUM_ALUNOS; i++) {
        free(alunos[i].nome);
    }

    fclose(arquivo);

    printf("\nArquivo criado com sucesso!\n");

    return 0;
}
