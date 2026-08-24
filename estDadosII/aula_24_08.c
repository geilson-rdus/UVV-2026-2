#include <stdio.h>

typedef struct Aluno{ 
	int id; 
	int matricula; 
	char nome[40]; 
	float media; 
} aluno;

//Questão b)
void imprimeAluno(FILE* f, int mat){
    int contador = 0;
    aluno alunoLido;
    
    rewind(f);
    
    for(int i = 0; i < 100; i++){
        fread(&alunoLido, sizeof(aluno), 1, f);
        contador++;
        if(alunoLido.matricula == mat){
            printf("ID: %d\nMatrícula: %d\nNome:%s\nMédia:%.2f\nQuantidade de registros lidos durante a busca: %d\n",
            alunoLido.id, alunoLido.matricula, alunoLido.nome, alunoLido.media, contador);
            break;
        }
    }
    
    if(contador > 99){
        printf("Matrícula não encontrada.\n");
    }
}

//Questão c)
void imprimeAlunoRNN(FILE* f, int rnn){
    aluno alunoLido;
    
    rewind(f);
    
    if (fseek(f, rnn*sizeof(aluno), 0)){
        printf("Erro na busca");
    }else{
        fread(&alunoLido, sizeof(aluno), 1, f);
        printf("ID: %d\nMatrícula: %d\nNome:%s\nMédia:%.2f\n",
            alunoLido.id, alunoLido.matricula, alunoLido.nome, alunoLido.media);
    }
}

//Questão d)
void alterarMedia(FILE* f, int rnn, float media){
    aluno alunoLido;

    if (fseek(f, rnn * sizeof(aluno), SEEK_SET) != 0){
        printf("Erro na busca\n");
        return;
    }

    if (fread(&alunoLido, sizeof(aluno), 1, f) != 1){
        printf("Erro ao ler o registro\n");
        return;
    }

    alunoLido.media = media;

    if (fseek(f, rnn * sizeof(aluno), SEEK_SET) != 0){
        printf("Erro ao reposicionar o arquivo\n");
        return;
    }

    if (fwrite(&alunoLido, sizeof(aluno), 1, f) != 1){
        printf("Erro ao alterar o registro\n");
        return;
    }

    printf("Media alterada com sucesso!\n");
}

int main()
{
    FILE *f = fopen("alunos.txt","r");
    
    FILE *fbin = fopen("aluno.dat","wb+");
    
    aluno alunos[100];
    
    char txt[100];
    
    fscanf(f,"%s\n",txt);
    
    for(int i = 0; i < 100; i++){
        fscanf(f, "%d;%d;%[^;];%f", &alunos[i].id,&alunos[i].matricula,&alunos[i].nome,&alunos[i].media);
    }
    
    fwrite(alunos, sizeof(aluno), 100, fbin);
    
    int matAux = 0;
    float medAux = 0;
    
    printf("Informe a matrícula do aluno: ");
    scanf("%d",&matAux);
    imprimeAluno(fbin,matAux);
    
    printf("Informe um número [0,100]: ");
    scanf("%d",&matAux);
    imprimeAlunoRNN(fbin,matAux);
    
    printf("Informe a nova média do aluno: ");
    scanf("%f",&medAux);
    alterarMedia(fbin,matAux,medAux);
 
    fclose(f);
    fclose(fbin);
    
    return 0;
}
