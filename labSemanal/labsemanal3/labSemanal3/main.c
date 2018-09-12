/*
    Nome: Rebecca Moreira Messias RA:186416 Turma: W

    Problema: 
        Desenvolver um programa que faz o processamento de imagem em 3 passos:
            1- Descomprimir uma imagem colorida
            2- Tranformá-la em uma imagem em escala de cinza
            3- Aplicar filtro sobre a imagem

    Entrada:
        
        -> Uma linha contendo um inteiro D, representando o divisor da terceira fase

        -> Uma linha contendo um inteiro X representando a ordem da matriz quadrada M,
        usada na terceira fase. X < 10

        -> A matriz quadrada M com X² números inteiros disposta em X linhas e X colunas

        -> Uma linha com 2 inteiros positivos maiores que 600 representando a resolução
        da imagem em pixels (Largura e Altura)

        -> Uma sequcia de pares de números inteiros (frequência, intensidade) representando
        a imagem colorida comprimida com o algoritmo RLE. É composta apenas pelos números 
        separados por espaço, sem vírgula ou parênteses. Apresenta a compressão da amtriz R, 
        seguida da G e B  

    Saída:
        -> Uma linha com os caracteres 'P2'

        -> Uma linha com dois números inteiros informando o tamanho da imagem em pixels (largura
        e altura)

        -> Uma linha com o número 255 que representa a intensidade máxima de um pixel 

        ->A matriz de intensidade com A linhas e L colunas, onde A é a altura e L a largurada imagem
        em pixels

    Observações:
        1- Explicando o porque usei matrizes unsigned char e não de outro tipo: Como são 5 matrizes
        que acabo utilizando, se todas fossem do tipo int o susy não aceitaria por conta da quantidade 
        de memória usada (apesar de no meu computador ter funcionado), por esse motivo troquei para 
        unsigned char e dessa forma reduzindo a quantidade de memória usada e funcionando :D

        2- Não sei bem se esse lab era só o de matrizes ou matrizes e funções juntos, mas como o professor
        já havia ensinado funções, tomei a liberdade de fazer algumas

        3- Tentei seguir a dica de declarar tudo no começo, mesmo achando estranho, mas ok...

        4- Sobre o comentário dos meus comentários: Percebi que tem uns comentários que você (seja lá quem for
        que corrigiu meu labSemanal2) não entendeu... Vou tentar elhorar a semÂntica deles. E em quastão de 
        inutilidade de comentários, sei lá, é difícil julgar um comentário útil ou não, mas estou tentando 
        melhorar nisso :P

        5- Acho que tinha como eu melhorar ainda mais o código na função aplicacaoFiltro, mas não consegui 
        pensar em uma maneira decente de fazer isso.

        6- Sobre esse lab: Eu gostei de fazer, foi divertido :D

        7- Acho que é isso. Boa correção!!! o/

*/

#include <stdio.h>
#include <stdlib.h>

// defines para torna o código mais legível
#define TAM_MAXIMO_IMAGEM 600
#define TAM_MAXIMO_FILTRO 10

// função para ler os valors da matriz Filtro
void leituraMatrizFiltro (int matFiltro[][TAM_MAXIMO_FILTRO], int ordem) {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            scanf (" %d", &matFiltro[i][j]);
        }
    }
}

// função para fazer a leitura e descompactação das matrizes RGB separadamente
void leituraDescompactacaoMAtrizRGB (int largura, int altura, unsigned char cor[][TAM_MAXIMO_IMAGEM]) {
    unsigned char intensidade;
    int frequencia, somatoria = 0, repeticaoFrequencia = 1, linAtu = 0, colAtu = 0;

    while (somatoria < largura*altura) {
        repeticaoFrequencia = 1;
        scanf (" %d %hhu", &frequencia, &intensidade);
        while (repeticaoFrequencia <= frequencia) {
            cor[linAtu][colAtu] = intensidade;

            colAtu++;

            if (colAtu == largura) {
                colAtu = 0;
                linAtu++;
            }

            repeticaoFrequencia++;
        }
        somatoria += frequencia;
    }
}

// função que transforma a imagem em tons de cinza
void transformacaoCinza (int largura, int altura, 
                         unsigned char cinza[][TAM_MAXIMO_IMAGEM],
                         unsigned char R[][TAM_MAXIMO_IMAGEM],
                         unsigned char G[][TAM_MAXIMO_IMAGEM],
                         unsigned char B[][TAM_MAXIMO_IMAGEM]) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int somaIJ = R[i][j] + G[i][j] + B[i][j];
            cinza[i][j] = somaIJ/3;
        }
    }
}

// função que aplica o filtro na matriz com tons de cinza
void aplicacaoFiltro(int ordem, int largura, int altura, int divisor, 
                     unsigned char covolucionada[][TAM_MAXIMO_IMAGEM],
                     unsigned char cinza[][TAM_MAXIMO_IMAGEM],
                     int filtro[][TAM_MAXIMO_FILTRO])
{

    int somatoriaPixels, pixelFiltrado, i, j, k, l;

    switch (ordem) {
        case 3: //Para um filtro de ordem  3
            // percorro cada pixel da imagem 
            for (i = 0; i < altura; i++)
            { 
                for (j = 0; j < largura; j++)
                {
                    // verifico se é um pixel da borda para colocar o mesmo valor
                    if ((i == 0) || (j == 0) || (i == altura - 1) || (j == largura - 1))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else // se não for da borda
                    {
                        // covoluciono o pixel aplicando operações matemáticas na vizinhança dele
                        for (k = -1; k <=1; k++) {
                            for(l = -1; l <= 1; l++) {                          
                                somatoriaPixels += cinza[i+k][j+l]*filtro[k+1][l+1];
                            }
                        }

                        // divido o resultado da covolução pelo divisor lido inicialmente
                        pixelFiltrado = somatoriaPixels/divisor;

                        // se o pixel for menor que 0, arredondo para 0
                        if (pixelFiltrado < 0)
                            covolucionada[i][j] = 0;
                        // se for maior que 255, arredondo para 255
                        else if (pixelFiltrado > 255)
                            covolucionada[i][j] = 255;
                        else //se não deixo o valor que esta
                            covolucionada[i][j] = pixelFiltrado;
                    }
                    // seta variável para ir para o próximo pixel
                    somatoriaPixels = 0;
                }
            }
            break;
        case 5: //Para um filtro de ordem  5
            // percorro cada pixel da imagem 
            for (i = 0; i < altura; i++)
            {
                for (j = 0; j < largura; j++)
                {
                    // verifico se é um pixel da borda para colocar o mesmo valor
                    if ((i == 0) || (j == 0) || (i == altura - 1) || (j == largura - 1))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 1) || (j == 1) || (i == altura - 2) || (j == largura - 2))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else // se não for da borda
                    {
                        // covoluciono o pixel aplicando operações matemáticas na vizinhança dele
                        for (k = -2; k <=2; k++) {
                            for(l = -2; l <= 2; l++) {                          
                                somatoriaPixels += cinza[i+k][j+l]*filtro[k+2][l+2];
                            }
                        }

                        // divido o resultado da covolução pelo divisor lido inicialmente
                        pixelFiltrado = somatoriaPixels/divisor;

                        // se o pixel for menor que 0, arredondo para 0
                        if (pixelFiltrado < 0)
                            covolucionada[i][j] = 0;
                        // se for maior que 255, arredondo para 255
                        else if (pixelFiltrado > 255) 
                            covolucionada[i][j] = 255;
                        else //se não deixo o valor que esta
                            covolucionada[i][j] = pixelFiltrado;
                    }
                    // seta variável para ir para o próximo pixel
                    somatoriaPixels = 0;
                }
            }
            break;
        case 7: //Para um filtro de ordem  7
            // percorro cada pixel da imagem 
            for (i = 0; i < altura; i++)
            {
                for (j = 0; j < largura; j++)
                {
                    // verifico se é um pixel da borda para colocar o mesmo valor
                    if ((i == 0) || (j == 0) || (i == altura - 1) || (j == largura - 1))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 1) || (j == 1) || (i == altura - 2) || (j == largura - 2))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 2) || (j == 2) || (i == altura - 3) || (j == largura - 3))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else // se não for da borda
                    {
                        // covoluciono o pixel aplicando operações matemáticas na vizinhança dele
                        for (k = -3; k <= 3; k++) {
                            for(l = -3; l <= 3; l++) {                          
                                somatoriaPixels += cinza[i+k][j+l]*filtro[k+3][l+3];
                            }
                        }                        
                        
                        // divido o resultado da covolução pelo divisor lido inicialmente
                        pixelFiltrado = somatoriaPixels/divisor;

                        // se o pixel for menor que 0, arredondo para 0
                        if (pixelFiltrado < 0)
                            covolucionada[i][j] = 0;
                        // se for maior que 255, arredondo para 255
                        else if (pixelFiltrado > 255) 
                            covolucionada[i][j] = 255;
                        else //se não deixo o valor que esta
                            covolucionada[i][j] = pixelFiltrado;
                    }
                    // seta variável para ir para o próximo pixel
                    somatoriaPixels = 0;
                }
            }
            break;
        case 9: //Para um filtro de ordem  9
            // percorro cada pixel da imagem 
            for (i = 0; i < altura; i++)
            {
                for (j = 0; j < largura; j++)
                {
                    // verifico se é um pixel da borda para colocar o mesmo valor
                    if ((i == 0) || (j == 0) || (i == altura - 1) || (j == largura - 1))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 1) || (j == 1) || (i == altura - 2) || (j == largura - 2))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 2) || (j == 2) || (i == altura - 3) || (j == largura - 3))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else if ((i == 3) || (j == 3) || (i == altura - 4) || (j == largura - 4))
                    {
                        covolucionada[i][j] = cinza[i][j];
                    }
                    else // se não for da borda
                    {
                        // covoluciono o pixel aplicando operações matemáticas na vizinhança dele
                        for (k = -4; k <= 4; k++) {
                            for(l = -4; l <= 4; l++) {                          
                                somatoriaPixels += cinza[i+k][j+l]*filtro[k+4][l+4];
                            }
                        }                        
                        
                        // divido o resultado da covolução pelo divisor lido inicialmente
                        pixelFiltrado = somatoriaPixels/divisor;

                        // se o pixel for menor que 0, arredondo para 0
                        if (pixelFiltrado < 0)
                            covolucionada[i][j] = 0;
                        // se for maior que 255, arredondo para 255
                        else if (pixelFiltrado > 255) 
                            covolucionada[i][j] = 255;
                        else //se não deixo o valor que esta
                            covolucionada[i][j] = pixelFiltrado;
                    }
                    // seta variável para ir para o próximo pixel
                    somatoriaPixels = 0;
                }
            }
            break;
    }
}

// funcao para printar a saída e gerar a imagem
void printaSaida (int largura, int altura, unsigned char matrizCovolucionada[][TAM_MAXIMO_IMAGEM]) {
    printf ("P2\n");
    printf ("%d %d\n", largura, altura);
    printf ("255\n");

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == largura -1)
                printf ("%hhu", matrizCovolucionada[i][j]);
            else
                printf ("%hhu ", matrizCovolucionada[i][j]);
        }
        printf ("\n");
    }

}

int main() {
    // declaração de variáveis
    int divisor, ordem, altura, largura, qualRGB = 1;;
    int M[TAM_MAXIMO_FILTRO][TAM_MAXIMO_FILTRO];
    unsigned char R[TAM_MAXIMO_IMAGEM][TAM_MAXIMO_IMAGEM],
                  G[TAM_MAXIMO_IMAGEM][TAM_MAXIMO_IMAGEM],
                  B[TAM_MAXIMO_IMAGEM][TAM_MAXIMO_IMAGEM],
                  cinza[TAM_MAXIMO_IMAGEM][TAM_MAXIMO_IMAGEM],
                  matrizCovolucionada[TAM_MAXIMO_IMAGEM][TAM_MAXIMO_IMAGEM];

    scanf("%d", &divisor);
    scanf("%d", &ordem);

    // ler a matriz filtro
    leituraMatrizFiltro (M, ordem);

    scanf ("%d %d", &largura, &altura);

    // leitura das matrizes RGB
    while (qualRGB <= 3) {
        switch (qualRGB) {
            case 1: 
                leituraDescompactacaoMAtrizRGB (largura, altura, R);
                break;
            case 2: 
                leituraDescompactacaoMAtrizRGB (largura, altura, G);
                break;
            case 3: 
                leituraDescompactacaoMAtrizRGB (largura, altura, B);
                break;
        }
        qualRGB++;
    }

    // transforma as camadas de cores em uma matriz com tons de cinza
    transformacaoCinza (largura, altura, cinza, R, G, B);

    // aplica o filtro na matriz em tons de cinza (convolução)
    aplicacaoFiltro(ordem, largura, altura, divisor, matrizCovolucionada, cinza, M);

    // gera a imagem final para o usuário
    printaSaida (largura, altura, matrizCovolucionada);

    return 0;
}
