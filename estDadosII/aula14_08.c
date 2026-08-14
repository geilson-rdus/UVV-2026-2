#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno{
    int id;
    char nome[50];
    float nota;
}aluno;

int main()
{
    FILE *arquivo = fopen("alunos.txt", "w+");
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
        alunos[i].id = i+1;
        fprintf(arquivo, "ID: %d || Aluno: %s || Nota: %.2f \n",alunos[i].id, alunos[i].nome, alunos[i].nota);
    }
    
    int idAluno = 0;
    int idAux;
    char nomeAux[50];
    float notaAux;
    
    printf("Digite o id do aluno que quer encontrar: ");
    scanf("%d",&idAluno);
    
    rewind(arquivo);
    
    for(int i = 0; i < 3; i++){
        fscanf(arquivo, " ID: %d || Aluno: %s || Nota: %f",
           &idAux,
           &nomeAux,
           &notaAux);

        if(idAluno == idAux){
            printf("ID: %d || Aluno: %s || Nota: %.2f\n",
                   idAux,
                   nomeAux,
                   notaAux);
        }
    }
    
    fclose(arquivo);
    
    printf("Arquivo criado com sucesso!");
    
    return 0;
}
