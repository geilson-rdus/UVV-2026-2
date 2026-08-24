#include <stdio.h>

typedef struct Aluno{ 
	int id; 
	int matricula; 
	char nome[40]; 
	float media; 
} aluno;


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
    
    fwrite(alunos, sizeof(aluno), 1, fbin);
 
    fclose(f);
    fclose(fbin);
    
    return 0;
}
