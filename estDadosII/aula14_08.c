#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    char nome[50];
    float nota;
}aluno;

int main()
{
    FILE *arquivo = fopen("alunos.txt", "w");
    aluno alunos[50];
    
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    
    for(int i = 0; i < 3; i++){
        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%s",&alunos[i].nome);
        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%f",&alunos[i].nota);
        fprintf(arquivo, "Aluno: %s || Nota: %.2f \n",alunos[i].nome, alunos[i].nota);
    }
    
    fclose(arquivo);
    
    printf("Arquivo criado com sucesso!");
    
    return 0;
}
