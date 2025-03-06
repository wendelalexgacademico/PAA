#include <stdio.h>
// Padrão de tipos por tamanho
#include <stdint.h>

// Procedimento de cálculo da tabela de transição
void calcular_tabela(int32_t* k, char* P) {
// i = sufixo, j = prefixo
for(int32_t i = 1, j = -1; i < strlen(P); i++) {
// Prefixo e sufixo diferentes
while(j >= 0 && P[j + 1] != P[i])
// Retorno de estado
j = k[j];
// Combinação de prefixo e sufixo
if(P[j + 1] == P[i])
// Avanço de estado
j++;
// Atualização da transição do estado
k[i] = j;
}
}

void inserir(int32_t* R, int posicao, int indice ){

}


void KMP(int32_t* k, int32_t* R, char* T, char* P) {
// Pré-processamento
int32_t n = strlen(T), m = strlen(P);

calcular_tabela(k, P);

// Iterando na cadeia T
for(int32_t i = 0, j = -1; i < n; i++) {

// Retorno de estado
while(j >= 0 && P[j + 1] != T[i]) j = k[j];

// Avanço de estado
if(P[j + 1] == T[i]) j++;

// Combinação do padrão
if(j == m - 1) {

inserir(R, i - m + 1);
j = k[j];

}
}
}


int main(int argc, char *argv[]){

     FILE *entrada = fopen(argv[1], "r");//habilita a leitura do arquivo
     FILE *saida = fopen(argv[1], "w");  //habilita a escrita no arquivo

}