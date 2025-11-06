#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(array) (sizeof(array) / sizeof(array[0]))

FILE* fptr;

typedef struct aluno_s {
  char nome[50];
  char curso[30];
  int data_nasc[4];
  int matricula;
  float altura;
  float peso;
  float notas[4];
  float media_final;
} aluno_t;

void menu();
void cadastrar_aluno(aluno_t* aluno);
int imprimir_alunos();
void buscar_aluno(char nome[], int matricula);
void remover_aluno(char nome[], int matricula);
void gerarRelatorio_geral();
void exibir_estatisticas();

int main(int argc, char* argv[]) {
  aluno_t aluno;

  strcpy(aluno.nome, "teste");
  strcpy(aluno.curso, "teste1");

  for (int i = 0; i < LEN(aluno.data_nasc); i++)
    aluno.data_nasc[i] = i;

  aluno.matricula = 1;
  aluno.altura = 175;
  aluno.peso = 70;

  for (int i = 0; i < LEN(aluno.notas); i++)
    aluno.notas[i] = i;

  aluno.media_final = 7.5;

  cadastrar_aluno(&aluno);
  // menu();
  return 0;
}

void menu() {}

void cadastrar_aluno(aluno_t *aluno) {
  fptr = fopen("alunos.dat", "ab");

  if (!fptr)
    printf("O arquivo não existe. Ele será criado.");

  aluno_t a;

  strcpy(a.nome, aluno->nome);
  strcpy(a.curso, aluno->curso);

  for (int i = 0; i < LEN(aluno->data_nasc); i++)
    a.data_nasc[i] = aluno->data_nasc[i];

  a.matricula = aluno->matricula;
  a.altura = aluno->altura;
  a.peso = aluno->peso;

  for (int i = 0; i < LEN(aluno->notas); i++)
    a.notas[i] = aluno->notas[i];

  a.media_final = aluno->media_final;

  fwrite(&a, sizeof(aluno_t), 1, fptr);

  fclose(fptr);
}

int imprimir_alunos() {
  fptr = fopen("alunos.dat", "rb");

  if (!fptr) {
    fprintf(stderr, "Erro ao abrir arquivo!\n");
    return EXIT_FAILURE;
  }

  char buffer_aluno[100];
  while (fscanf(fptr, "%s\n", buffer_aluno) > 0)
    printf("%s", buffer_aluno);

  fclose(fptr);

  return 0;
}

void buscar_aluno(char nome[], int matricula) {
  
}

void remover_aluno(char nome[], int matricula) {}

void gerarRelatorio_geral() {}

void exibir_estatisticas() {}