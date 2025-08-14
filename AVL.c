#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sNoa
{
    char info;
    int chave;
    int altura;
    struct sNoa *esq;
    struct sNoa *dir;
} TNoa;

void buscar(TNoa *L, int chave)
{
    TNoa *topo;
    topo = L;

    if (topo == NULL)
    {
        printf("\nA arvore esta vazia!\n");
    }
    while (topo != NULL && topo->chave != chave)
    {

        if (topo->chave > chave)
            topo = topo->esq;
        else
            topo = topo->dir;
    }
    if (topo != NULL && topo->chave == chave)
        printf("\nO %d esta na arvore!\n", chave);
    else
        printf("\nO %d NAO esta na arvore!\n", chave);
}

void imprimir(TNoa *L, int nivel)
{
    if (L != NULL)
    {
        imprimir(L->dir, nivel + 2);

        for (int i = 0; i < nivel; i++)
        {
            printf("    ");
        }

        printf("(%d, %c)\n", L->chave, L->info);

        imprimir(L->esq, nivel + 2);
    }
}

TNoa *criar(char info, int chave)
{
    TNoa *novo;
    novo = (TNoa *)malloc(sizeof(TNoa));
    novo->info = info;
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;
    return (novo);
}

TNoa * rotacaoEsq(TNoa *L){
    TNoa *temp = L->dir;
    L->dir = temp->esq;
    temp->esq = L;
    atualizarAltura(L);
    atualizarAltura(temp);
    return temp;
}
TNoa * rotacaoDir(TNoa *L){
    TNoa *temp = L->esq;
    L->esq = temp->dir;
    temp->dir = L;
    atualizarAltura(L);
    atualizarAltura(temp);
    return temp;
}

TNoa* balanceamento(TNoa *L) {
    if (L == NULL)
        return;

    L->esq = balanceamento(L->esq); 
    L->dir = balanceamento(L->dir); 

    atualizarAltura(L);
    int fb = FB(L);
    
    if (fb >= 2 || fb <= -2){
        if (fb >= 2){
            if (FB(L->dir) > 0){
                L = rotacaoEsq(L);
            }
            else{
                L->dir = rotacaoDir(L->dir);
                L = rotacaoEsq(L);
            }
        }
        else{
            if (FB(L->esq) < 0){
                L = rotacaoDir(L);
            }
            else{
                L->esq = rotacaoEsq(L->esq);
                L = rotacaoDir(L);
            }
        }
    }
    return L;
}

TNoa *inserir(TNoa *L, char info, int chave)
{
    if (L == NULL)
        return criar(info, chave);

    if (chave <= L->chave)
        L->esq = inserir(L->esq, info, chave);
    else
        L->dir = inserir(L->dir, info, chave);

    atualizarAltura(L);

    return (balanceamento(L));
}

TNoa *retirar(int chave, TNoa *L)
{
    if (L == NULL)
    {
        printf("\nO %d NAO esta na arvore!\n", chave);
        return NULL;
    }

    if (chave < L->chave)
    {
        L->esq = retirar(chave, L->esq);
    }
    else if (chave > L->chave)
    {
        L->dir = retirar(chave, L->dir);
    }
    else
    {
        if (L->esq == NULL && L->dir == NULL)
        {
            free(L);
            printf("\nO %d foi retirado da arvore!\n", chave);
            return NULL;
        }
        else if (L->esq == NULL || L->dir == NULL)
        {
            TNoa *filho = (L->esq != NULL) ? L->esq : L->dir;
            free(L);
            printf("\nO %d foi retirado da arvore!\n", chave);
            return filho;
        }
        else
        {
            TNoa *tempant = L->esq, *temp = L->esq;
            while (temp->dir != NULL)
            {
                tempant = temp;
                temp = temp->dir;
            }
            L->chave = temp->chave;
            L->info = temp->info;
            tempant->dir = NULL;
            free(temp);
            printf("\nO %d foi retirado da arvore!\n", chave);
            return L;
        }
    }

    atualizarAltura(L);

    return (balanceamento(L));
}

void atualizarAltura(TNoa *L)
{
    if (L != NULL)
    {
        int alturaEsq = (L->esq != NULL) ? L->esq->altura : 0;
        int alturaDir = (L->dir != NULL) ? L->dir->altura : 0;
        L->altura = (alturaEsq > alturaDir ? alturaEsq : alturaDir) + 1;
    }
}

int altura(TNoa *L) {
    return (L == NULL) ? 0 : L->altura;
}
int FB(TNoa *L) {
    return (L == NULL) ? 0 : altura(L->dir) - altura(L->esq);
}

void espelho(TNoa *L)
{
    TNoa *aux;
    if (L != NULL)
    {
        espelho(L->esq);
        espelho(L->dir);
        aux = L->esq;
        L->esq = L->dir;
        L->dir = aux;
    }
}

void empilhar(TNoa **Pilha, TNoa **topo, TNoa *temp, int *quantpilha)
{
    Pilha[*quantpilha] = temp;
    (*quantpilha)++;
    *topo = temp;
}
void desempilhar(TNoa **Pilha, TNoa **topo, int *quantpilha)
{
    (*quantpilha)--;
    if (*quantpilha > 0)
        *topo = Pilha[*quantpilha - 1];
    else
        *topo = NULL;
}

int total(TNoa *L)
{
    int cont = 0;
    if (L != NULL)
    {
        cont = 1 + total(L->esq) + total(L->dir);
    }
    return cont;
}

void simetrico(TNoa *L)
{
    int cont = total(L);
    TNoa *Pilha[cont];
    TNoa *topo = L;
    TNoa *temp = L;
    int quantpilha = 0;
    empilhar(&Pilha, &topo, temp, &quantpilha);

    while (topo != NULL)
    {
        while (temp->esq != NULL)
        {
            temp = temp->esq;
            empilhar(&Pilha, &topo, temp, &quantpilha);
        }
        while (temp->dir == NULL)
        {
            desempilhar(&Pilha, &topo, &quantpilha);
            printf("%d ", temp->chave);
            temp = topo;
        }
        desempilhar(&Pilha, &topo, &quantpilha);
        printf("%d ", temp->chave);
        temp = temp->dir;
        empilhar(&Pilha, &topo, temp, &quantpilha);
    }
}

void menu()
{
    printf("Escolha uma opcao:\n");
    printf("(1) Inserir no\n");
    printf("(2) Buscar no\n");
    printf("(3) Imprimir arvore\n");
    printf("(4) Espelhar arvore\n");
    printf("(5) Simetrico\n");
    printf("(6) Total de nos\n");
    printf("(7) Verificar se a arvore e cheia\n");
    printf("(8) Retirar no\n");
    printf("(0) Sair\n");
}

int main(void)
{
    TNoa *L = NULL;
    char info;
    int chave, CHAVE, res;
    menu();
    scanf("%d", &res);
    while (res != 0)
    {

        if (res != 1 && res != 2 && res != 3 && res != 4 && res != 5 && res != 6 && res != 7 && res != 8)
        {
            printf("Opção invalida!\nSaindo...\n");
            break;
        }
        if (res == 1)
        {
            printf("Digite a informacao do no: ");
            scanf(" %c", &info);
            printf("Digite a chave do no: ");
            scanf("%d", &chave);
            L = inserir(L, info, chave);
            imprimir(L, 4);
        }
        if (res == 2)
        {
            printf("Digite a chave que deseja buscar: ");
            scanf("%d", &CHAVE);
            printf("\nBuscando chave %d...\n", CHAVE);
            buscar(L, CHAVE);
        }
        if (res == 3)
            imprimir(L, 4);

        if (res == 4)
        {
            espelho(L);
            imprimir(L, 4);
            printf("*Espelhada!*");
        }
        if (res == 5)
        {
            printf("Simetrico: ");
            simetrico(L);
        }
        if (res == 6)
            printf("Total de nos: %d\n", total(L));
        if (res == 7)
        {
            if (total(L) == 0)
                printf("A arvore esta vazia!\n");
            else if (total(L) == (1 << L->altura) - 1)
                printf("A arvore e cheia!\n");
            else
                printf("A arvore NAO e cheia!\n");
        }
        if (res == 8)
        {
            printf("Digite a chave que deseja retirar: ");
            scanf("%d", &CHAVE);
            printf("\nRetirando chave %d...\n", CHAVE);
            L = retirar(CHAVE, L);
            imprimir(L, 4);
        }

        printf("\n");
        printf("%d", L->altura);
        menu();
        scanf("%d", &res);
    }

    printf("\nFim!\n");

    return 0;
}