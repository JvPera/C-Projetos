#include <stdio.h>
#include <stdlib.h>

typedef struct vizinho
{
    int id_vizinho;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo
{
    int id_vertice;
    TVizinho *vizinho;
    struct grafo *prox;
} TGrafo;

void menu()
{
    printf("\n\n");
    printf("Escolha uma opcao:\n");
    printf("1 - Adicionar vertice\n");
    printf("2 - Adicionar aresta\n");
    printf("3 - Remover aresta\n");
    printf("4 - Remover vertice\n");
    printf("5 - Imprimir grafo\n");
    printf("6 - Buscar vertice\n");
    printf("0 - Sair\n");
}
TGrafo *buscarvertice (TGrafo*G, int id_vertice){
    TGrafo * busca = G;
    while (busca != NULL && busca->id_vertice != id_vertice){
        busca = busca->prox;
    }
    return busca;
}

TGrafo *adicionarvertice (TGrafo *G, int id_vertice){
    TGrafo *p = buscarvertice(G,id_vertice);
    if (p==NULL){
        TGrafo *novo = (TGrafo*) malloc (sizeof(TGrafo));
        novo->id_vertice = id_vertice;
        novo->prox = G;
        novo->vizinho = NULL;
        G = novo;
    }
    else
        printf ("O vertice %d ja existe no grafo!\n", id_vertice);
    return G;
}

TVizinho *buscararesta (TGrafo *G, int v1, int v2){
    TGrafo *p1, *p2;
    TVizinho *vert = NULL;

    p1 = buscarvertice (G, v1);
    p2 = buscarvertice (G, v2);

    if (p1 != NULL && p2 != NULL){
        vert = p1->vizinho;
        while (vert != NULL && vert->id_vizinho != v2){
            vert = vert->prox;
        }
    }
    return vert;
}
TGrafo *adicionarsentido (TGrafo *G, int v1, int v2){
    TVizinho *vizinho = (TVizinho*) malloc (sizeof(TVizinho));
    TGrafo *p;
    p = buscarvertice(G, v1);
    vizinho->id_vizinho = v2;
    vizinho->prox = p->vizinho;
    p->vizinho = vizinho;

    return G;
}
TGrafo *adicionararesta (TGrafo *G, int v1, int v2){
    TGrafo *p1, *p2;
    TVizinho *v = buscararesta (G, v1, v2);
    if (v == NULL){
        adicionarsentido(G, v1, v2);
        adicionarsentido(G, v2, v1);
    }
    else
        printf ("Nao foi possivel! Tente novamente!\n");
    return G;
}
TGrafo *removeoaresta(TGrafo *G, int v1, int v2){
    TGrafo *p1, *p2;
    TVizinho *v = buscararesta (G, v1, v2);
    if (v != NULL){
        p1 = buscarvertice(G, v1);
        p2 = buscarvertice(G, v2);
        if (p1 != NULL && p2 != NULL){
            TVizinho *ant = NULL;
            TVizinho *atual = p1->vizinho;
            while (atual != NULL && atual->id_vizinho != v2){
                ant = atual;
                atual = atual->prox;
            }
            if (atual != NULL){
                if (ant == NULL)
                    p1->vizinho = atual->prox;
                else
                    ant->prox = atual->prox;
                free(atual);
            }
        }
    }
    return G;
}
TGrafo *removeovertice (TGrafo *G, int id_vertice){
    TGrafo *p = G, *fiscal = G;
    TGrafo *ant = NULL;
    TVizinho *v = NULL;
    int num = p->id_vertice;
    fiscal = G;
    while (fiscal != NULL) {
        G = removeoaresta(G, fiscal->id_vertice, id_vertice);
        fiscal = fiscal->prox;
    }

    while (p != NULL && p->id_vertice != id_vertice){
        ant = p;
        p = p->prox;
    }
    if (p != NULL){
        if (ant == NULL)
            G = p->prox;
        else
            ant->prox = p->prox;
        free(p);
    }

    return G;
}

void imprimir (TGrafo *G){
    TGrafo *p = G;
    TVizinho *v = NULL;
    while (p != NULL){
        printf ("Vertice (%d) = Vizinhos:", p->id_vertice);
        v = p->vizinho;
        while (v != NULL){
            printf (" %d ", v->id_vizinho);
            v = v->prox;
        }
        printf ("\n");
        p = p->prox;
    }
}

int main(){
    TGrafo *G = NULL;
    int res, id_vertice, id_vizinho;
    menu();
    scanf("%d", &res);
    while (res != 0)
    {
        switch (res)
        {
        case 1:
            printf("Digite o id do vertice: ");
            scanf("%d", &id_vertice);
            G = adicionarvertice (G, id_vertice);
            break;
        case 2:
            printf("Digite o id do vertice e o id do vizinho: ");
            scanf("%d %d", &id_vertice, &id_vizinho);
            G = adicionararesta(G, id_vertice, id_vizinho);
            break;
        case 3:
            printf("Digite o id do vertice e o id do vizinho: ");
            scanf("%d %d", &id_vertice, &id_vizinho);
            G = removeoaresta(G, id_vertice, id_vizinho);
            if (G != NULL)
                printf ("A aresta (%d, %d) foi removida com sucesso!\n", id_vertice, id_vizinho);
            else
                printf ("A aresta (%d, %d) NAO existe!\n", id_vertice, id_vizinho);
                
            break;
        case 4:
            printf("Digite o id do vertice: ");
            scanf("%d", &id_vertice);
            G = removeovertice(G, id_vertice);
            if (G != NULL)
                printf ("O vertice %d foi removido com sucesso!\n", id_vertice);
            else
                printf ("O vertice %d NAO existe!\n", id_vertice);
            
            break;
        case 5:
            imprimir(G);
            break;
        case 6: 
            printf("Digite o id do vertice: ");
            scanf("%d", &id_vertice);
            TGrafo *v = buscarvertice (G, id_vertice);
            if (v != NULL) printf ("O %d esta no grafo!\n", id_vertice);
            else printf ("O %d NAO esta no grafo!\n", id_vertice);

            break;
        default:
            printf("Opcao invalida!\n");
        }
        menu();
        scanf("%d", &res);
    }
} 
                                                                                                                    