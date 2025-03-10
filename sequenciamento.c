#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct estruturaResultado{
    char *codigo_da_doenca;
    int  chance_de_ocorrencia;

}Resultado;

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


int KMP(int32_t* k, int32_t* R, char* T, char* P) {
// Pré-processamento
int32_t n = strlen(T), m = strlen(P);
int32_t indice=0;
calcular_tabela(k, P);
int32_t limite = (int32_t)round(0.9 * m); // 90% do tamanho do padrão, arredondado

// Iterando na cadeia T
for(int32_t i = 0, j = -1; i < n; i++) {

// Retorno de estado
while(j >= 0 && P[j + 1] != T[i]) j = k[j];

// Avanço de estado
if(P[j + 1] == T[i]) j++;

// Combinação do padrão
if(j >=limite - 1) {

inserir(R, i - m + 1, indice);
j = k[j];
indice++;
}
}

if(indice>0){return 1;}else{return 0;}

}

char* ler_linha(FILE* arquivo) {
    size_t tamanho = 0;
    size_t capacidade = 100; // Tamanho inicial
    char* linha = (char*)malloc(capacidade * sizeof(char));
    if (linha == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    int caractere;
    while ((caractere = fgetc(arquivo)) != EOF && caractere != '\n' && caractere!= ' ') {
        linha[tamanho++] = (char)caractere;

        // Redimensiona a memória se necessário
        if (tamanho >= capacidade) {
            capacidade *= 2;
            char* nova_linha = (char*)realloc(linha, capacidade * sizeof(char));
            if (nova_linha == NULL) {
                printf("Erro ao realocar memória.\n");
                free(linha);
                return NULL;
            }
            linha = nova_linha;
        }
    }

    linha[tamanho] = '\0'; // Adiciona o terminador nulo
    return linha;
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

    // Variáveis para armazenar os primeiros dados
    int tamanho_minimo_das_subcadeias;
    char *codigo_dna = NULL;
    int numero_de_doencas;

    // Lê a primeira linha (tamanho mínimo da subcadeia)
    fscanf(entrada, "%d", &tamanho_minimo_das_subcadeias);
    printf("Tamanho minimo: %d\n", tamanho_minimo_das_subcadeias);

    //consoem o \n da linha anterior
    fgetc(entrada);
    
    // Lê a segunda linha (código DNA)
    codigo_dna=ler_linha(entrada);
    printf("Codigo de DNA: %s\n", codigo_dna);


    // Lê a terceira linha (número de doenças)
    fscanf(entrada, "%d", &numero_de_doencas);
    printf("NUmero de doencas: %d\n", numero_de_doencas);
    Resultado *resultadoDoencas= (Resultado*) malloc(numero_de_doencas*sizeof(Resultado));

     if (resultadoDoencas == NULL) {
        printf("Erro ao alocar memória.\n");
        free(codigo_dna);
        fclose(entrada);
        fclose(saida);
        return 1;
    }

    fgetc(entrada); // Consome o '\n' restante da linha anterior

    // Loop para ler o codigo das doenças, a quantidade e seus genes
    for (int i = 0; i < numero_de_doencas; i++) {
        char *codigo_doenca_da_vez = NULL;
        int numero_genes_doenca_da_vez;
        
        // Lê o código da doença
        codigo_doenca_da_vez=ler_linha(entrada);
        // Lê o número de genes da doença
        fscanf(entrada, "%d", &numero_genes_doenca_da_vez);
        fgetc(entrada); // Consome o '\n' restante da linha anterior
        int32_t numero_genes_correspondidos=0;

        // Loop para ler os genes da doença
        for (int j = 0; j < numero_genes_doenca_da_vez; j++) {
            int32_t *R= (int32_t*) malloc(strlen(codigo_dna)*(sizeof(int32_t)));
            
            char *subcadeia_da_vez = NULL;

            subcadeia_da_vez=ler_linha(entrada);

            if (subcadeia_da_vez == NULL) {
                free(codigo_doenca_da_vez);
                free(codigo_dna);
                free(resultadoDoencas);
                fclose(entrada);
                fclose(saida);
                return 1;
            }

            int32_t *k= (int32_t*) malloc(strlen(subcadeia_da_vez)*(sizeof(int32_t)));

            if(strlen(subcadeia_da_vez)<tamanho_minimo_das_subcadeias){
                 free(subcadeia_da_vez);
                free(R);
                free(k);
                continue;
                }
          
            // Aqui você pode processar a subcadeia_da_vez (gene) como necessário
            numero_genes_correspondidos+=KMP(k, R, codigo_dna, subcadeia_da_vez);
            printf("Numero de Genes Correspondidos com a doenca %s: %d/n", codigo_doenca_da_vez, numero_genes_correspondidos);
            // Libera a memória alocada para a subcadeia
            free(subcadeia_da_vez);
            free(R);
            free(k);
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