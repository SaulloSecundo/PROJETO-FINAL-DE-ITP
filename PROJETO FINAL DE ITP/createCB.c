#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_final.h"
#include "validade_codigo.h"
#include "codigo_bin.h"
#define ESPACAMENTO_LATERAL_PADRAO 4
#define LARGURA_AREA_PADRAO 3
#define ALTURA_CODIGO_PADRAO 50
#define NOME_IMAGEM_PADRAO "codigo_de_barras_ean8.pbm"

int main(void){
    //definição das variáveis utilizadas na implemtação do código de barras
    int** img;
    char codigo_string[100];
    int codigo_int[8];
    int* codigo_ean = calloc(67, sizeof(int));
    int espaco_lateral, altura_cod, largura_area;
    char nome[100];
    char nome_img_completo[100];
    char verifica_entradas;
    int linhas_img, colunas_img;

    //recebimento das entradas definidas pelo o usuário
    printf("Informe o codigo no padrao EAN-8:\n");
    scanf("%s", &codigo_string);

    //verificações de validação do código informado pelo o usuário e, se válido, construção do código de barras
    if(quant_tipo_elementos(codigo_string)){

        for(int i = 0; i < 8; ++i){

            codigo_int[i] = convertInter(codigo_string[i]);
        }

        if(validacao_identificador(codigo_int)){
            //recebimentos das entradas informadas pelo o usuário
            printf("Deseja especificar o espacamento lateral do codigo na imagem (s/n)?\n");
            scanf(" %c", &verifica_entradas);

            if(verifica_entradas == 's'){
                printf("Espacamento lateral: ");
                scanf("%d", &espaco_lateral);
            }else{
                espaco_lateral = ESPACAMENTO_LATERAL_PADRAO;
            }

            printf("Deseja especificar a quantidade de pixels por area do codigo (s/n)?\n");
            scanf(" %c", &verifica_entradas);

            if(verifica_entradas == 's'){
                printf("Pixels por area: ");
                scanf("%d", &largura_area);
            }else{
                largura_area = LARGURA_AREA_PADRAO;
            }

            printf("Deseja especificar a altura do codigo de barras (s/n)?\n");
            scanf(" %c", &verifica_entradas);

            if(verifica_entradas == 's'){
                printf("Altura do codigo (pixels): ");
                scanf("%d", &altura_cod);
            }else{
                altura_cod = ALTURA_CODIGO_PADRAO;
            }

            printf("Deseja especificar o nome da imagem (s/n)?\n");
            scanf(" %c", &verifica_entradas);

            if(verifica_entradas == 's'){
                printf("Nome da imagem: ");
                scanf("%s", &nome);
                strcpy(nome_img_completo, strcat(nome, ".pbm"));
            }else{
                strcpy(nome_img_completo, NOME_IMAGEM_PADRAO);
            }

            //dimensionando a matriz final que conterá a informação que definirá a imagem com o código de barras
            linhas_img = (altura_cod + 2*espaco_lateral);
            colunas_img = (67*largura_area + 2*espaco_lateral);

            bits_padrao(codigo_ean);

            for(int i = 0; i < 8; ++i){
                if(i < 4){
                    conversor_L_code(codigo_ean, codigo_int[i]);

                }else{
                    conversor_R_code(codigo_ean, codigo_int[i]);
                }
            }

            img = dimensionar(linhas_img, colunas_img);

            montarMatriz(img, codigo_ean, espaco_lateral, largura_area, linhas_img, colunas_img);

            print(img, linhas_img, colunas_img, nome_img_completo);

        }

    }

    return 0;

}
