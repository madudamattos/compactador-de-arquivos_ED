#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "compactador.h"
#include "bitmap.h"

#define TAM_NOME_CAMINHO 100
#define TAM_VETOR 128

int contaCaracteres(FILE *arquivo, int *V);
void imprimeVetorFrequencia(int *V);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return 0;
    }

    char caminhoArquivo[TAM_NOME_CAMINHO];

    strncpy(caminhoArquivo, argv[1], TAM_NOME_CAMINHO - 1);

    FILE *arquivo = fopen(caminhoArquivo, "r");

    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoArquivo);
        return 0;
    }

    int V[TAM_VETOR];

    // inicializa o vetor com 0
    for (int i = 0; i < TAM_VETOR; i++)
    {
        V[i] = 0;
    }

    int qtd = contaCaracteres(arquivo, V);

    imprimeVetorFrequencia(V);

    Lista *l = iniciaFolhas(V, TAM_VETOR, qtd);

    imprimeLista(l, imprimeNo);

    Arv *a = organizaArvore(l);

    imprimeArvore(a);

    compactaArquivo(a, arquivo);

    FILE *compactado = fopen("compactado.bin", "rb");

    Arv *a2 = leCabecalho(a2, compactado);

    imprimeArvore(a2);

    bitmap *tabela[256];
    bitmap *bm = bitmapInit(8);

    criaTabela(tabela, bm, a2);

    int i;

    printf("\nB ");
    for (i = 0; i < bitmapGetLength(tabela['b']); i++)
    {
        printf("%d", bitmapGetBit(tabela['b'], i));
    }
    printf("\n");

    printf("M ");
    for (i = 0; i < bitmapGetLength(tabela['m']); i++)
    {
        printf("%d", bitmapGetBit(tabela['m'], i));
    }
    printf("\n");

    printf("O ");
    for (i = 0; i < bitmapGetLength(tabela['o']); i++)
    {
        printf("%d", bitmapGetBit(tabela['o'], i));
    }
    printf("\n");

    printf("E ");
    for (i = 0; i < bitmapGetLength(tabela['e']); i++)
    {
        printf("%d", bitmapGetBit(tabela['e'], i));
    }
    printf("\n");

    printf("S ");
    for (i = 0; i < bitmapGetLength(tabela['s']); i++)
    {
        printf("%d", bitmapGetBit(tabela['s'], i));
    }
    printf("\n");

    printf("ESPAÇO ");
    for (i = 0; i < bitmapGetLength(tabela[' ']); i++)
    {
        printf("%d", bitmapGetBit(tabela[' '], i));
    }
    printf("\n");

    return 0;
}

// retorna a quantidade de caracteres presentes no vetor
int contaCaracteres(FILE *arquivo, int *V)
{
    char c = '\0';
    int d = 0;

    while (fscanf(arquivo, "%c", &c) == 1)
    {
        int d = (int)c;
        V[d]++;
    }

    int qtd;

    for (int i = 0; i < TAM_VETOR; i++)
    {
        if (V[i] != 0)
        {
            qtd++;
        }
    }

    return qtd;
}

void imprimeVetorFrequencia(int *V)
{

    for (int i = 0; i < TAM_VETOR; i++)
    {
        if (V[i] != 0)
        {
            printf("%c: %d\n", i, V[i]);
        }
    }

    printf("\n");
}
