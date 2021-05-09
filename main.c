/***************************************************************
*
* Luiz Fernando Vilarga Vilalva e Herick Vinicius Ferreira Gustavo
* Trabalho 01
* Professor(a): Marco Aurelio Stefanes
*
*/

//-Wall -std=c99 -pedantic (opções de compilação)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

typedef struct{
	int nclass;					 // Classificação do time.
	char nometime[1000]; // Define qual vai ser o nome do time.
	int ntotpontos;			 // Total de pontos ganhos.
	int njogos;					 // Números de jogos realizados.
	int nvitorias;			 // Números de vitórias.
	int nempates;				 // Número de empates.
	int nderrotas;			 // Número de derrotas.
	int nsaldgols;			 // Número de saldo de gols.
	int ngols;					 // Quantidade de gols que um time faz.
	int ngolsofrido;		 //Número de gols sofridos.
} time;

void swap(time vetor[], int posA, int posB){
	time temp;
	temp = vetor[posA];
	vetor[posA] = vetor[posB];
	vetor[posB] = temp;
}

void ordenaPorNome(time vetor[], int i, int j){
	if (strcasecmp(vetor[i].nometime, vetor[j].nometime) > 0){
		swap(vetor, i, j);
	}
}

void ordenaPorMenosJogos(time vetor[], int i, int j){
	if (vetor[i].njogos == vetor[j].njogos){
		ordenaPorNome(vetor, i, j);
	}else{
		if (vetor[i].njogos > vetor[j].njogos){
			swap(vetor, i, j);
		}
	}
}

void ordenaPorQtdDeGols(time vetor[], int i, int j){
	if (vetor[i].ngols == vetor[j].ngols){
		ordenaPorMenosJogos(vetor, i, j);
	}else{
		if (vetor[i].ngols < vetor[j].ngols){
			swap(vetor, i, j);
		}
	}
}

void ordenaPorSaldoDeGols(time vetor[], int i, int j){
	if (vetor[i].nsaldgols == vetor[j].nsaldgols){
		ordenaPorQtdDeGols(vetor, i, j);
	}else{
		if (vetor[i].nsaldgols < vetor[j].nsaldgols){
			swap(vetor, i, j);
		}
	}
}

void ordenaPorVitorias(time vetor[], int i, int j){
	if (vetor[i].nvitorias == vetor[j].nvitorias){
		ordenaPorSaldoDeGols(vetor, i, j);
	}else{
		if (vetor[i].nvitorias < vetor[j].nvitorias){
			swap(vetor, i, j);
		}
	}
}

void ordenaPorPontos(time vetor[], int i, int j){
	if (vetor[i].ntotpontos == vetor[j].ntotpontos){
		ordenaPorVitorias(vetor, i, j);
	}else{
		if (vetor[i].ntotpontos < vetor[j].ntotpontos){
			swap(vetor, i, j);
		}
	}
}

void ordenaTabela(time vetor[], int qtdtimes){
	for (int i = 0; i < qtdtimes - 1; i++){
		for (int j = i + 1; j < qtdtimes; j++){
			ordenaPorPontos(vetor, i, j);
		}
		vetor[i].nclass = i + 1;
		vetor[i + 1].nclass = i + 2;
	}
}

void processaJogo(time vetor[], int qtdTimes, char time[], int placarA, int placarB, int matchResult){
  for (int i = 0; i < qtdTimes; i++){
    if (strcmp(vetor[i].nometime, time) == 0){
      vetor[i].ngols += placarA;
      vetor[i].ngolsofrido += placarB;
      vetor[i].njogos++;
      vetor[i].nsaldgols += placarA - placarB;
      if (matchResult == 0){
        vetor[i].nempates++;
        vetor[i].ntotpontos += 1;
      }else{
        if (matchResult < 0){
          vetor[i].nvitorias++;
          vetor[i].ntotpontos += 3;
        }else{
          vetor[i].nderrotas++;
        }
      }
    }
  }
}

int main(){
	int n; //N campeonatos
	int t; //T linhas cada uma contendo um nome de um time.
	int j; //J representa o número de jogos já realizados no campeonato Ex: "nome_do_time1 gols1 X gols2 nome_do_time".
	char nomecopa[100]; //Define qual vai ser o nome da copa.
	scanf("%d", &n);		//Recebe o valor e guarda em n, representa a quantidade de copas
	printf("\n");
	for (int contador = 0; contador < n; contador++){
		scanf(" %[^\n]", nomecopa); // Recebe o nome da copa.
		scanf("%d", &t);						// Recebe o valor de quantos times vão jogar nessa copa.
		time lista[t];							// Cria uma lista de times
		for (int i = 0; i < t; i++){
			lista[i].nclass = 1; // Todo time recebe a classificação como 1, pois ainda nao teve nenhum jogo;
			lista[i].ntotpontos = 0;
			lista[i].njogos = 0;
			lista[i].nvitorias = 0;
			lista[i].nempates = 0;
			lista[i].nderrotas = 0;
			lista[i].nsaldgols = 0;
			lista[i].ngols = 0;
			lista[i].ngolsofrido = 0;
			scanf(" %[^\n]", lista[i].nometime); // Leitura do nome do time.
		}
		scanf("%d", &j); //Recebe um valor quantidades de jogos.
		for (int i = 0; i < j; i++){
			char timeA[100];
			char timeB[100];
			int placarA = 0;
			int placarB = 0;
			scanf("%s %d X %d %s", timeA, &placarA, &placarB, timeB);
			int matchResult = placarB - placarA;
      // Time A ganhou: match = -1.
      // Empate: match = 0.
      // Time B ganhou: match = 1.
			processaJogo(lista, t, timeA, placarA, placarB, matchResult);	 // Calculo do time A.
			processaJogo(lista, t, timeB, placarB, placarA, (matchResult*-1)); // Calculo do time B.
		}
		// Ordenação dos times por pontuação
		ordenaTabela(lista, t);
		//Saida final
		printf("%s\n", nomecopa);
		for (int i = 0; i < t; i++){
			printf("%d) %s %dp, %dj (%d-%d-%d), %dsg (%d-%d)\n", lista[i].nclass, lista[i].nometime, lista[i].ntotpontos, lista[i].njogos, lista[i].nvitorias, lista[i].nempates, lista[i].nderrotas, lista[i].nsaldgols, lista[i].ngols, lista[i].ngolsofrido);
		}
		printf("\n");
	}
	return 0;
}