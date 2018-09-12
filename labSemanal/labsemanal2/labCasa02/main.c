/**
    Nome: Rebecca Moreira Messias
    RA: 186416
    Turma: W

    Objetivo do programa: Dadas a configuração da maquete, o preço e a capacidade do galão de
    água em vários fornecedores, o aniversário da cidade e o último ano em que a exposição estará
    aberta, determinar quanto será gasto pela prefeitura com água, para manter a maquete sempre
    cheia.

    Entradas: A entrada contém várias informações:
        -> Na primeira linha, um inteiro não negativo K, com K < 100, o número de ilhas na maquete.
        -> Cada uma das próximas K linhas da entrada contém os vértices de uma ilha: N + 1 pares ordenados
           de números reais (X0, Y0)(X1, Y1). . .(XN , YN ),(XN+1, YN+1) as coordenadas, em metros, dos
           vértices, em sentido horário ou anti-horário. −1000 < Xi, Yi < 1000, de modo que (Xi, Yi) e
           (Xi+1, Yi+1) são vértices consecutivos e (X0, Y0) é igual a (XN+1, YN+1).
        -> Uma linha contendo a data de aniversário da cidade, no formato dia/mes.
        -> O último ano ANO em que a exposição irá funcionar. ANO ≥ 2016
        -> Um inteiro positivo F, com F < 100, o número de fornecedores de água.
        -> F linhas, cada uma contendo 1 número inteiro c, a capacidade do galão daquele fornecedor, um
           caractere $ e um número real Pi, o preço, em $, do galão.

    Saída: Uma única linha: “A manutencao da maquete custara $X aos cofres publicos.”, onde X é o custo
        calculado da água, com 2 casas decimais.

    OBSERVAÇÕES:
        1- No feedback do último lab semanal foi informado que existia cometários excessivos, contudo os comentários
        que fiz no código foram feitos de acordo como o professor Lehilton sugeriu em sala com o passo a passo algoritmo.
        Nesse lab fiz como o professor sugeriu em sala.

        2- Normalmente, não comento meus códigos, pois acho que nomeando as variáveis e funções do código adequadamente
        não é necessário fazer comentários explicando o que cada coisa faz

        3- Sobre colocar variáveis no início do código: Creio que as variáveis que devo deixar no início do código são as
        que são de mais "importância" para o programa como as que lerão as entradas do programa. As outras que serão usadas
        em determinada partes para auxiliar uma parte do código eu posso declara-lá apenas nessa parte. Dessa maneira, o código
        aparenta estar mais limpo.

        4- Boa correção.
*/
#include <stdio.h>

int main(void)
{
    // DECLARAÇÃO DE VARIÁVEIS
    unsigned int qtdIlhas, qtdFornecedores, capacidade, diaAniversario, mesAniversario, ano;
    double preco, precoFinal, auxiliarPreco;
    double inicialX, inicialY, atualX, atualY, anteriorX, anteriorY, acumuladorArea, area, volume;
    double soma1 = 0, soma2 = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, lado1, lado2, areaMaquete;

    // LEITURA DA QUANTIDTIDADE DE ILHAS E DOS PONTOS QUE DELIMITAM AS ILHAS PARA CALCULAR O VOLUME DE ÁGUA NECESSRIO

    // leitura da quantidade de ilhas
    scanf("%u", &qtdIlhas);

    // para cada ilha faço
    int i;
    for (i = 1; i <= qtdIlhas; i++)
    {
        // seto as variáveis soma1, soma2 e area para 0;
        area = 0;
        soma1 = 0;
        soma2 = 0;

        // leio o primeiro ponto do polígono e armazeno em inicial
        scanf(" (%lf , %lf)", &inicialX, &inicialY);

        // seto as variáveis anteriores para receber a coodenada inicial
        anteriorX = inicialX;
        anteriorY = inicialY;

        // para achar o valor dos pontos da maquete eu seto x1, x2, y1, y2 com os valores iniciais
        if (i == 1)
        {
            x1 = inicialX;
            x2 = inicialX;
            y1 = inicialY;
            y2 = inicialY;
        }

        // enquanto o usuário quiser digitar novos vértice para a formação do polígono
        do
        {
            // leio a próxima coordenada e armazeno em atual
            scanf(" (%lf , %lf)", &atualX, &atualY);

            // para achar o maior x
            if (atualX >= x1)
                x1 = atualX;
            // para achar o menor x
            if (atualX <= x2)
                x2 = atualX;
            // para achar o maior y
            if (atualY >= y1)
                y1 = atualY;
            // para achar o menor y
            if (atualY <= y2)
                y2 = atualY;

            // se os pontos atuais são iguais aos iniciais significa que o poligono termina
            if ((atualX == inicialX) && (atualY == inicialY))
            {
                // pelo método do cardaço cálculo a área
                soma1 += anteriorX * atualY;
                soma2 += anteriorY * atualX;
                area = (soma1 - soma2) / 2;

                // faço o módulo da área caso seja negativa
                if (area < 0)
                    area = -area;

                // acumulo a área desse polígono em acumuladorArea
                acumuladorArea += area;

                // saio do do-while
                break;
            }
            // se não forem
            else
            {
                // pelo mtodo do cardaço cálculo a área
                soma1 += anteriorX * atualY;
                soma2 += anteriorY * atualX;

                // seto as variáveis anteriores com o valor da atual
                anteriorX = atualX;
                anteriorY = atualY;
            }
        }
        while (1);
    }

    // adiciono 0,5 para descobrir as margens da maquete
    x1 += 0.5;
    x2 -= 0.5;
    y1 += 0.5;
    y2 -= 0.5;

    // calculo o valor dos lados subitraindo o maior do menor
    lado1 = x1 - x2;
    lado2 = y1 - y2;

    // calculo a area da maquete menos a area das ilhas
    areaMaquete = (lado1*lado2) - acumuladorArea;

    // tiro o módulo da área da maquete caso ela seja negativa
    if (areaMaquete < 0)
        areaMaquete = -areaMaquete;

    // multiplico pela a altura da maquete (0.5) para descobrir o volume e por 1000 para ransforma em litros
    volume = areaMaquete * 0.5 * 1000;

    // LEITURA DO ANIVERSÁRIO DA CIDADE E DO ÚLTIMO ANO DE EVENTO PARA CALCULAR O TOTAL DE DIAS

    // leio a data de aniversário da cidade e o último ano de exposição
    scanf("%u/%u", &diaAniversario, &mesAniversario);
    scanf("%u", &ano);

    int qtdAniversario = 0, qtdSexta13 = 1;

    // verifico se a data de aniversário é em 29/02
    if ((diaAniversario == 29) && (mesAniversario == 2))
    {
        int anoAtual;
        // para cada ano até o final da exposição
        for (anoAtual = 2016; anoAtual <= ano; anoAtual++)
        {
            // verifico se o ano é bissexto, se for incremento a qtd. de aniversários
            if (((anoAtual % 4 == 0) && (anoAtual % 100 != 0)) || (anoAtual % 400 == 0))
                qtdAniversario++;
        }
    }
    // se o aniversário for em qualquer outro dia eu subtraio 2015 do ano final de exposição
    else
        qtdAniversario = ano-2015;

    unsigned int acumuladorDeDias = 18;

    // para cada ano de exposição
    for (i = 2016; i <= ano; i++)
    {
        // verifico se o ano é 2016
        if (i == 2016)
        {
            // se o aniversário um dia antes ou depois de uma sexta 13 diminuo a qtd de Sexta 13
            if (((diaAniversario == 12) && (mesAniversario == 5)) || ((diaAniversario == 14) && (mesAniversario == 5)))
                qtdSexta13--;
            // se não verifico se o aniversário é dia 13
            else if ((diaAniversario == 13) && (mesAniversario == 5))
                qtdAniversario--;
        }
        // para qualquer outro ano
        else
        {
            int contaMes;
            // para cada mês faço
            for (contaMes = 1; contaMes <= 12; contaMes++)
            {
                switch (contaMes)
                {
                case 1:
                    // incremento a qtd de dias
                    acumuladorDeDias += 31;
                    break;
                case 2:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 3:
                    // verifico se o ano é bissexto se for incremento 29 senão incremento 28
                    if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
                        acumuladorDeDias += 29;
                    else
                        acumuladorDeDias += 28;
                    break;
                case 4:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 5:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 30;
                    break;
                case 6:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 7:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 30;
                    break;
                case 8:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 9:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 10:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 30;
                    break;
                case 11:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 31;
                    break;
                case 12:
                    // segue os mesmos passos para o mês 1
                    acumuladorDeDias += 30;
                    break;
                }

                // se o resto da divisão po 7 for 0 significa que é uma sexta 13, então incremento a variável
                if (acumuladorDeDias % 7 == 0)
                    qtdSexta13++;
                // se o aniversário for um dia antes ou depois da sexta 13, diminuo a quantidade de dias
                if ((acumuladorDeDias % 7 == 0) && (((diaAniversario == 12) && (mesAniversario == contaMes)) ||
                        ((diaAniversario == 14) && (mesAniversario == contaMes))))
                    qtdSexta13--;
                // se o aniversário for numa sexta 13, diminuo a qtd. de dias
                if (((diaAniversario == 13) && (mesAniversario == contaMes)) && (acumuladorDeDias % 7 == 0))
                    qtdAniversario--;
            }
        }
    }

    // calculo a quantidade de dias total somando a qtd de Aniversario com a qtd de sexta 13
    unsigned int qtdDiasEvento = qtdSexta13 + qtdAniversario;

    // LENDO AS INFORMAÇÕES DOS FORNECEDORES E DESCOBRINDO QUAL FORNECEDOR É MAIS VIÁVEL

    // pego a parte inteira do volume
    int volumeInt = volume;

    // leio a quantidade de de fornecedores
    scanf("%u", &qtdFornecedores);

    // leio as informções do galão do primeiro fornecedor
    scanf("%u $%lf", &capacidade, &preco);

    int qtdGalao;

    // arredondo pra cima se a quantidade de galões for quabrada
    if (volumeInt - volume == 0)
    {
        if (volumeInt % capacidade == 0)
            qtdGalao = volumeInt / capacidade;
        else
            qtdGalao = volume / capacidade + 1;
    }
    else
    {
        qtdGalao = volume / capacidade + 1;
    }

    // calculo o preço final dos galões desse fornecedor
    precoFinal = qtdGalao * preco * qtdDiasEvento;

    // para os demais fornecedores
    for (i = 1; i <= qtdFornecedores; i++)
    {
        // zero a quantidade de galões para calcular a de um novo fornecedor
        qtdGalao = 0;

        // se a quantidade de fornecedores for 1, saio do for
        if (qtdFornecedores == 1)
            break;

        // leio as informações do galão de um novo fornecedor
        scanf("%u $%lf", &capacidade, &preco);

        // arredondo pra cima se a quantidade de galões for quabrada
        if (volumeInt - volume == 0)
        {
            if (volumeInt % capacidade == 0)
                qtdGalao = volumeInt / capacidade;
            else
                qtdGalao = volume / capacidade + 1;
        }
        else
        {
            qtdGalao = volume / capacidade + 1;
        }

        // calculo o preco do galao em uma varivel auxiliar
        auxiliarPreco = qtdGalao * preco * qtdDiasEvento;

        // comparo para ver que fornecedor possui o menor preço e armazeno esse preço em precoFinal
        if (auxiliarPreco < precoFinal)
            precoFinal = auxiliarPreco;
    }

    // mostro ao usuário o menor preço do custo de agua para os cofres públicos
    printf("A manutencao da maquete custara $%.2f aos cofres publicos.\n", precoFinal);

    return 0;
}
