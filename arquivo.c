#include <stdio.h>
#include <stdlib.h>

void encherlista(int *lista, int vari)
{
    FILE *arq;
    if (vari == 1)
        arq = fopen("arq1.txt", "r");
    if (vari == 2)
        arq = fopen("arq2.txt", "r");
    if (arq != NULL)
    {
        int i = 0;
        while (fscanf(arq, "%d", &lista[i]) != EOF)
        {
            i++;
        }
        fclose(arq);
    }
    else
        printf("ERROR!");
}

void funcmerge(int *lista1, int *lista2, int *merge, int tam1, int tam2)
{
    int i, j;
    int k = 0;
    int repetido;

    for (i = 0; i < tam1; i++)
    {
        merge[k++] = lista1[i];
    }
    for (i = 0; i < tam2; i++)
    {
        repetido = 0;
        for (j = 0; j < k; j++)
        {

            if (lista2[i] == merge[j])
            {
                repetido = 1;
            }
        }
        if (!repetido)
        {
            merge[k++] = lista2[i];
        }
    }
}
void escreverarq(int *merge, int tam)
{
    FILE *arq;
    int i;

    arq = fopen("arqmerge.txt", "w");
    if (arq != NULL)
    {
        for (i = 0; i < tam; i++)
        {
            if (merge[i] != 0){
                printf("%d\n", merge[i]);
                fprintf(arq, "%d\n", merge[i]);
            }
        }
        fclose(arq);
    }
    else
        printf("ERROR!");
}

int main()
{
    printf("INICIANDO...");
    int numeros1[10], numeros2[10], merge[20] = {0}, i, j, tam, temp, vari, tam1, tam2;
    vari = 1;
    encherlista(&numeros1, vari);
    vari = 2;
    encherlista(&numeros2, vari);
    tam1 = sizeof(numeros1) / sizeof(numeros1[0]);
    tam2 = sizeof(numeros2) / sizeof(numeros2[0]);
    funcmerge(&numeros1, &numeros2, &merge, tam1, tam2);
    printf("\n");
    tam = sizeof(merge) / sizeof(merge[0]);
    for (i = 0; i < tam - 1; i++)
    {
        for (j = i + 1; j < tam; j++)
        {
            if (merge[j] < merge[i])
            {
                temp = merge[j];
                merge[j] = merge[i];
                merge[i] = temp;
            }
        }
    }
    escreverarq(&merge, tam);
    printf("ENCERRANDO COM SUCESSO...");
}