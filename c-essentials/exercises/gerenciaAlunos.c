#include <stdio.h>
#include <stdlib.h>

FILE* fptr;

typedef struct Aluno {
  char nome[50];
  char curso[30];
  int dataNascimento[4];
  int matricula;
  float altura;
  float peso;
  float notas[4];
  float mediaFinal;
} Aluno;

void menu();
void cadastrarAluno(Aluno* aluno);
void imprimirAlunos();
void buscarAluno(char nome[], int matricula);
void removerAluno(char nome[], int matricula);
void gerarRelatorioGeral();
void exibirEstatisticas();

int main(int argc, char* argv[]) {
  Aluno aluno;

  scanf("");
  // menu();
  return 0;
}

void menu() {}

void cadastrarAluno(Aluno* aluno) {
  fptr = fopen("alunos.txt", "a");

  if (fptr == NULL) {
    printf("The file is not exists. It will be create.");
  }

  fprintf(fptr, "======= Aluno: %s =======\n", aluno->nome);
  fprintf(fptr, "Curso: %s\n", aluno->curso);
  fprintf(fptr, "Data do Nascimento: %d/%d/%d\n", aluno->dataNascimento[0], aluno->dataNascimento[1], aluno->dataNascimento[2]);
  fprintf(fptr, "Matricula: %d\n", aluno->matricula);
  fprintf(fptr, "Altura: %.2f\n", aluno->altura);
  fprintf(fptr, "Peso: %.2f\n", aluno->peso);
  fprintf(fptr, "Notas: \n  %.2f\n  %.2f\n  %.2f\n", aluno->notas[0], aluno->notas[1], aluno->notas[2]);
  fprintf(fptr, "Media Final: %.2f\n", aluno->mediaFinal);

  fclose(fptr);

  return 0;
}

void imprimirAlunos() {}

void buscarAluno(char nome[], int matricula) {}

void removerAluno(char nome[], int matricula) {}

void gerarRelatorioGeral() {}

void exibirEstatisticas() {}