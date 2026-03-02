#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
void gerar_relatorio_geral();
void exibir_estatisticas();
int imprimir_alunos();

int main(int argc, char* argv[]) {
  aluno_t aluno;

  strcpy(aluno.nome, "Pablo");
  strcpy(aluno.curso, "ADS");

  aluno.data_nasc[0] = 31;
  aluno.data_nasc[1] = 8;
  aluno.data_nasc[2] = 2005;

  aluno.matricula = 1;
  aluno.altura = 177;
  aluno.peso = 73;

  for (int i = 0; i < LEN(aluno.notas); i++)
    aluno.notas[i] = 10;

  // cadastrar_aluno(&aluno);

  // imprimir_alunos();
  // remover_aluno("teste", 0);
  // imprimir_alunos();
  // gerar_relatorio_geral();
  exibir_estatisticas();

  // menu();
  return 0;
}

void menu() {}

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

    sprintf(nascimento, "%02d/%02d/%d", aluno_lido.data_nasc[0], aluno_lido.data_nasc[1], aluno_lido.data_nasc[2]);

    printf("Nascimento: %s\n", nascimento);
    printf("Matricula: %d\n", aluno_lido.matricula);
    printf("Altura: %.2f\n", aluno_lido.altura);
    printf("Peso: %.2f\n", aluno_lido.peso);
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

void remover_aluno(char nome[], int matricula) {
  FILE* fptr_orig = fopen("alunos.dat", "rb");
  FILE* fptr_cp = fopen("alunos_cp.dat", "wb");

  if (!fptr_orig) {
    fprintf(stderr, "Erro ao abrir arquivo para remoção!\n");
    if (fptr_cp) fclose(fptr_cp);
    return;
  }
  
  if (!fptr_cp) {
    fprintf(stderr, "Erro ao criar arquivo temporário!\n");
    fclose(fptr_orig);
    return;
  }

  aluno_t a;

  while (fread(&a, sizeof(aluno_t), 1, fptr_orig) == 1) {
    if (
      !(
        (matricula > 0 && a.matricula == matricula) || 
        (strlen(nome) > 0 && strcmp(a.nome, nome) == 0)
      )
    )
      fwrite(&a, sizeof(aluno_t), 1, fptr_cp);
  }

  fclose(fptr_orig);
  fclose(fptr_cp);

  remove("alunos.dat");
  rename("alunos_cp.dat", "alunos.dat");
}

void gerar_relatorio_geral() {
  FILE *fBin = fopen("alunos.dat", "rb");
  FILE *fTxt = fopen("relatorio.txt", "w");

  if (!fBin || !fTxt) {
      printf("Erro ao abrir os arquivos para o relatorio.\n");
      if (fBin) fclose(fBin);
      return;
  }

  aluno_t atual;
  aluno_t melhor, pior;
  int totalAlunos = 0;
  int aprovados = 0, reprovados = 0;
  float somaMedias = 0.0;

  while (fread(&atual, sizeof(aluno_t), 1, fBin) == 1) {
    if (totalAlunos == 0) {
        melhor = pior = atual;
    } else {
        if (atual.media_final > melhor.media_final) melhor = atual;
        if (atual.media_final < pior.media_final) pior = atual;
    }

    somaMedias += atual.media_final;
    totalAlunos++;

    if (atual.media_final >= 6.0) aprovados++;
    else reprovados++;
  }

  if (totalAlunos > 0) {
    float mediaGeral = somaMedias / totalAlunos;

    fprintf(fTxt, "=== RELATORIO ACADEMICO ===\n\n");
    fprintf(fTxt, "Total de alunos: %d\n", totalAlunos);
    fprintf(fTxt, "Media geral da turma: %.2f\n", mediaGeral);
    fprintf(fTxt, "Maior nota: %s (Media: %.2f)\n", melhor.nome, melhor.media_final);
    fprintf(fTxt, "Menor nota: %s (Media: %.2f)\n", pior.nome, pior.media_final);
    fprintf(fTxt, "Aprovados: %d\n", aprovados);
    fprintf(fTxt, "Reprovados: %d\n", reprovados);
    
    printf("Relatorio 'relatorio.txt' gerado com sucesso!\n");
  } else {
    fprintf(fTxt, "Nenhum aluno cadastrado no sistema.\n");
    printf("Nao ha dados para gerar o relatorio.\n");
  }

  fclose(fBin);
  fclose(fTxt);
}

void exibir_estatisticas() {
  fptr = fopen("alunos.dat", "rb");
  if (!fptr) {
    printf("Erro ao abrir arquivo para estatisticas!\n");
    return;
  }

  int anoAtual;
  printf("Informe o ano atual: ");
  scanf("%d", &anoAtual);

  aluno_t a;
  int faixas[4] = {0};
  int vogais = 0, consoantes = 0;
  int frequenciaLetras[26] = {0};

  while (fread(&a, sizeof(aluno_t), 1, fptr) == 1) {
    int idade = anoAtual - a.data_nasc[2];
    if (idade <= 18) faixas[0]++;
    else if (idade <= 30) faixas[1]++;
    else if (idade <= 50) faixas[2]++;
    else faixas[3]++;

    for (int i = 0; a.nome[i] != '\0'; i++) {
      char c = tolower(a.nome[i]);

      if (c >= 'a' && c <= 'z') {
        frequenciaLetras[c - 'a']++;

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
          vogais++;
        else
          consoantes++;
      }
    }
  }

  fclose(fptr);

  printf("\n=== ESTATISTICAS GERAIS ===\n");
  printf("Faixas Etarias:\n");
  printf("  Ate 18 anos: %d\n  19-30 anos: %d\n  31-50 anos: %d\n  Acima de 50: %d\n", 
    faixas[0], faixas[1], faixas[2], faixas[3]);

  printf("\nAnalise de Nomes:\n");
  printf("  Total de vogais: %d\n", vogais);
  printf("  Total de consoantes: %d\n", consoantes);

  printf("\nFrequencia de Letras (A-Z):\n");
  for (int i = 0; i < 26; i++) {
    if (frequenciaLetras[i] > 0) {
      printf("  %c: %d | ", i + 'a', frequenciaLetras[i]);
      if ((i + 1) % 5 == 0) printf("\n");
    }
  }
  printf("\n---------------------------\n");
}
