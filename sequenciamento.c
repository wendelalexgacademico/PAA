#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

void inserir(int32_t* R, int posicao, int32_t indice){

     R[indice]=posicao;
 
}


void KMP(int32_t* k, int32_t* R, char* T, char* P) {
// Pré-processamento
int32_t n = strlen(T), m = strlen(P);
int32_t indice=0;
calcular_tabela(k, P);

// Iterando na cadeia T
for(int32_t i = 0, j = -1; i < n; i++) {

// Retorno de estado
while(j >= 0 && P[j + 1] != T[i]) j = k[j];

// Avanço de estado
if(P[j + 1] == T[i]) j++;

// Combinação do padrão
if(j == m - 1) {

inserir(R, i - m + 1, indice);
j = k[j];
indice++;
}
}
}


int main(int argc, char *argv[]){

     FILE *entrada = fopen(argv[1], "r");
     if (entrada == NULL) {
          printf("Erro ao abrir o arquivo de entrada.\n");
          return 1;
     }

     FILE *saida = fopen(argv[2], "w"); // Arquivo de saída diferente
     if (saida == NULL) {
          printf("Erro ao abrir o arquivo de saída.\n");
          fclose(entrada);
          return 1;
     }

      // Variáveis para armazenar os dados
    int tamanho_minimo_subcadeia;
    char *codigo_dna = NULL;
    int numero_doencas;

    // Lê a primeira linha (tamanho mínimo da subcadeia)
    fscanf(entrada, "%d", &tamanho_minimo_subcadeia);

    //consoem o \n da linha anterior
    fgetc(entrada);
    
    // Lê a segunda linha (código DNA)
    int32_t contcar=0;
     while(1){
     int caractere = fgetc(entrada); // CORRETO
     if (caractere == '\n' || caractere == EOF) {
          
          codigo_dna[contcar] = '\0';
          break;
     
     }
     
     codigo_dna[contcar] = (char)caractere; // Conversão para char
     contcar++;
    
    }
     contcar=0;
    // Lê a terceira linha (número de doenças)
    fscanf(entrada, "%d", &numero_doencas);

    // Loop para ler as doenças e seus genes
    for (int i = 0; i < numero_doencas; i++) {
        char *codigo_doenca_da_vez = NULL;
        int numero_genes_doenca_da_vez;

        fgetc(entrada); // Consome o '\n' restante da linha anterior
        
        // Lê o código da doença
        while(1){
          char *caractere=fgetc(entrada);
          if(caractere==' '){
          codigo_dna[contcar]='\0';
          break;
          }
          codigo_doenca_da_vez[contcar]=caractere;
          contcar++;
          }
          contcar=0;

        // Lê o número de genes da doença
        fscanf(entrada, "%d", &numero_genes_doenca_da_vez);

        // Loop para ler os genes da doença
        for (int j = 0; j < numero_genes_doenca_da_vez; j++) {
            char *subcadeia_da_vez = NULL;

          while(1){
          char *caractere=fgetc(entrada);
          if(caractere==' '){
          codigo_dna[contcar]='\0';
          break;
          }
          subcadeia_da_vez[i]=caractere;
          contcar++;
          }
          contcar=0;
            // Aqui você pode processar a subcadeia_da_vez (gene) como necessário
            printf("Doença: %s, Gene %d: %s\n", codigo_doenca_da_vez, j + 1, subcadeia_da_vez);

            // Libera a memória alocada para a subcadeia
            free(subcadeia_da_vez);
        }

        // Libera a memória alocada para o código da doença
        free(codigo_doenca_da_vez);
    }

    // Libera a memória alocada para o código DNA
    free(codigo_dna);

    // Fecha o arquivo
    fclose(entrada);

    return 0;
}
