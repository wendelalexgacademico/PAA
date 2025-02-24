#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

     FILE *entrada = fopen(argv[1], "r");//habilita a leitura do arquivo
     FILE *saida = fopen(argv[1], "w");  //habilita a escrita no arquivo

    int quantidade_de_Sequências;       //variàvelque armazena a quantidade de variáveis para compressão
    sscanf("%d", &quantidade_de_Sequências, entrada); //lê a primeira linha do arquivo que co0ntém a quantidade de sequeências;

    int i=0;
    for(i=0; i<quantidade_de_Sequências; i++){
            
            int quantidade_de_simbolos;//ler a quantidade de simbolos
            //chamar a função que vai ter a quantidade como parâmetro, para ler e armazenar os simbolos
            //função para comprimir os símbolos lidos como HUF
            //função para comprimir os símbolos lidos como RLE
            //função que compara e imprime os dados no formato


    }

}
