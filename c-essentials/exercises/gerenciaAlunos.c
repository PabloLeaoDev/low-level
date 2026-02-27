#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(array) (sizeof(array) / sizeof(array[0]))

FILE* fptr;

typedef struct aluno_s {
  char nome[50];
  char curso[30];
  int data_nasc[3];
  int matricula;
  float altura;
  float peso;
  float notas[4];
  float media_final;
} aluno_t;

void menu();
void cadastrar_aluno(aluno_t* aluno);
void buscar_aluno(char nome[], int matricula);
void remover_aluno(char nome[], int matricula);
void gerarRelatorio_geral();
void exibir_estatisticas();
int imprimir_alunos();
char[4] completar_zeros(int valor, int qtd_zeros);

int main(int argc, char* argv[]) {
  aluno_t aluno;

  strcpy(aluno.nome, "teste");
  strcpy(aluno.curso, "teste1");

  aluno.data_nasc[0] = 1;
  aluno.data_nasc[1] = 3;
  aluno.data_nasc[2] = 2000;

  aluno.matricula = 1;
  aluno.altura = 175;
  aluno.peso = 70;

  for (int i = 0; i < LEN(aluno.notas); i++)
    aluno.notas[i] = 10;

  cadastrar_aluno(&aluno);

  imprimir_alunos();

  // menu();
  return 0;
}

void menu() {}

char[] completar_zeros(int valor, int qtd_zeros) {
  char[qtd_zeros] valor_formatado;

  for (int i = 0; i < qtd_zeros; i++) {
    if (i == 0)
      sprintf(valor_formatado, "%d", valor);
    else
      sprintf(valor_formatado, "%d", 0);
  }

  return valor_formatado;
}

void cadastrar_aluno(aluno_t *aluno) {
  fptr = fopen("alunos.dat", "ab");

  if (!fptr)
    printf("O arquivo não existe. Ele será criado.");

  aluno_t a = {0};

  strcpy(a.nome, aluno->nome);
  strcpy(a.curso, aluno->curso);

  for (int i = 0; i < LEN(aluno->data_nasc); i++)
    a.data_nasc[i] = aluno->data_nasc[i];

  a.matricula = aluno->matricula;
  a.altura = aluno->altura;
  a.peso = aluno->peso;

  for (int i = 0; i < LEN(aluno->notas); i++) {
    a.notas[i] = aluno->notas[i];
    a.media_final += aluno->notas[i];
  }

  a.media_final = a.media_final / LEN(aluno->notas);

  fwrite(&a, sizeof(aluno_t), 1, fptr);

  fclose(fptr);
}

int imprimir_alunos() {
  fptr = fopen("alunos.dat", "rb");

  if (!fptr) {
    fprintf(stderr, "Erro ao abrir arquivo para impressão!\n");
    return EXIT_FAILURE;
  }

  aluno_t aluno_lido;

  while (fread(&aluno_lido, sizeof(aluno_t), 1, fptr) == 1) {
    printf("Nome: %s\n", aluno_lido.nome);
    printf("Curso: %s\n", aluno_lido.curso);

    char nascimento[20];

    sprintf(nascimento, "%s/%s/%s", completar_zeros(aluno_lido.data_nasc[0], 2), completar_zeros(aluno_lido.data_nasc[1], 2), completar_zeros(aluno_lido.data_nasc[2], 4));

    printf("Nascimento: %s\n", nascimento);
    printf("Matricula: %d\n", aluno_lido.matricula);
    printf("Altura: %d\n", aluno_lido.altura);
    printf("Peso: %d\n", aluno_lido.peso);
    printf("Media Final: %.2f\n", aluno_lido.media_final);
    printf("---------------------------\n");
  }

  fclose(fptr);

  return 0;
}

void buscar_aluno(char nome[], int matricula) {
  fptr = fopen("alunos.dat", "rb");

  if (!fptr) {
      printf("Erro: O arquivo de dados nao foi encontrado.\n");
      return;
  }

  aluno_t aluno_lido;
  int encontrado = 0;

  while (fread(&aluno_lido, sizeof(aluno_t), 1, fptr) == 1) {
      if (
        (matricula > 0 && aluno_lido.matricula == matricula) 
        || (strlen(nome) > 0 && strcmp(aluno_lido.nome, nome) == 0)
      ) {
        printf("\n--- Aluno Encontrado ---\n");
        printf("Nome: %s\n", aluno_lido.nome);
        printf("Matricula: %d\n", aluno_lido.matricula);
        printf("Curso: %s\n", aluno_lido.curso);
        printf("Media Final: %.2f\n", aluno_lido.media_final);
        printf("------------------------\n");
        
        encontrado = 1;
        break; 
      }
  }

  if (!encontrado)
      printf("\nAluno nao encontrado no sistema.\n");

  fclose(fptr);
}

void remover_aluno(char nome[], int matricula) {}

void gerarRelatorio_geral() {}

void exibir_estatisticas() {}
