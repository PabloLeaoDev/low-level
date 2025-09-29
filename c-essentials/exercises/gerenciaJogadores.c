#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Jogador {
  char nome[50];
  int idade;
  float altura;
  float peso;
  char posicao[30];
  int numCamisa;
} Jogador;

void imprimirJogadores(Jogador *j);
void alterarIdade(Jogador jogadores[], int qtdJogadores, char nomeJogador[], int novaIdade);
void ordenarJogadoresPorIdade(Jogador jogadores[], int n);
void calcularDobroIdade(Jogador *j);
int compararIdade(const Jogador *j1, const Jogador *j2);
int contarJogadoresNegativos(const Jogador *array, int n);
void lerJogadores(Jogador *jogadores, int qtdJogadores);

int main(int argc, char* argv[]) {
  int qtdJogadores;
  
  printf("Quantos jogadores deseja cadastrar? ");
  scanf("%d", &qtdJogadores);
  printf("\n");

  Jogador jogadores[qtdJogadores];

  lerJogadores(jogadores, qtdJogadores);
  ordenarJogadoresPorIdade(jogadores, qtdJogadores);

  for (int i = 0; i < qtdJogadores; i++) {
    imprimirJogadores(&jogadores[i]);
  }

  int contador = 0;

  while (true) {
    char texto[6];

    contador == 0 ? strcpy(texto, "algum") : strcpy(texto, "outro");
    contador++;

    char desejaAlterarIdade;
  
    printf("\n\nDeseja alterar a idade de %s jogador [S/N]? ", texto);
    scanf(" %c", &desejaAlterarIdade);
  
    if (tolower(desejaAlterarIdade) == tolower('S')) {
      char nomeJogador[50];
      int novaIdade;
  
      printf("\nQual o nome do jogador que deseja alterar idade? ");
      scanf("%s", &nomeJogador);
  
      printf("\nQual a idade que deseja atribuir ao %s? ", nomeJogador);
      scanf("%d", &novaIdade);
      
      alterarIdade(jogadores, qtdJogadores, nomeJogador, novaIdade);
    } else if (tolower(desejaAlterarIdade) == tolower('N')) {
      break;
    } else {
      printf("\nInsira um valor válido.");
    }
  }

  return 0;
}

void lerJogadores(Jogador *jogadores, int qtdJogadores) {
  for (int i = 0; i < qtdJogadores; i++) {
    printf("Digite o nome do jogador %d: ", i + 1);
    scanf(" %49[^0\n]", &jogadores[i].nome); // scan set
    printf("Digite a idade do jogador %d: ", i + 1);
    scanf("%d", &jogadores[i].idade);
    printf("Digite a altura do jogador %d: ", i + 1);
    scanf("%f", &jogadores[i].altura);
    printf("Digite o peso do jogador %d: ", i + 1);
    scanf("%f", &jogadores[i].peso);
    printf("Digite a posicao do jogador %d: ", i + 1);
    scanf("%s", &jogadores[i].posicao);
    printf("Digite o numero da camisa do jogador %d: ", i + 1);
    scanf("%d", &jogadores[i].numCamisa);
    printf("\n");
  }
}

void imprimirJogadores(Jogador *j) {
  printf("\nO jogador %s possui %d anos, %.2fm de altura, %.2fkg de peso corporal, é %s e camisa %d.", j->nome, j->idade, j->altura, j->peso, j->posicao, j->numCamisa);
}

void ordenarJogadoresPorIdade(Jogador jogadores[], int n) {
  int i, j;
  Jogador tmp;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (jogadores[j].idade > jogadores[j + 1].idade) {
        tmp = jogadores[j];
        jogadores[j] = jogadores[j + 1];
        jogadores[j + 1] = tmp;
      }
    }
  }
}

void alterarIdade(Jogador jogadores[], int qtdJogadores, char nomeJogador[], int novaIdade) {
  bool jogadorExiste = false;

  for (int i = 0; i < qtdJogadores; i++) {
    if (strcmp(jogadores[i].nome, nomeJogador) == 0) {
      jogadorExiste = true;
      jogadores[i].idade = novaIdade;

      printf("\nAlteração no jogador %s realizada", jogadores[i].nome);
      imprimirJogadores(&jogadores[i]);
    }
  }

  if (!jogadorExiste) {
    printf("\nO jogador requisitado não foi cadastrado.");
  }
}