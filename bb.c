#include <stdio.h>
#include <stdlib.h>

int prox_mult(int elem, int pot){
  int resp = 0;
  while(resp <= elem) resp += pot;
  return resp;
}

int bb(FILE *fp, int elem, int tipo){
  int ini, fim, meio, elem_meio;
  ini = ftell(fp);
  fseek(fp, 0L, SEEK_END);
  fim = ftell(fp) - tipo;
  while(ini <= fim){
    //meio = (fim + ini) / 2;
    //if((meio % tipo) != 0) meio = prox_mult(meio, tipo);
    meio = ((((ini + fim) / tipo)) / 2) * tipo;
    fseek(fp, meio, SEEK_SET);
    fread(&elem_meio, tipo, 1, fp);
    printf("ini = %d\tfim = %d\tmeio = %d\telem = %d\n", ini, fim, meio, elem_meio);
    if(elem_meio == elem) return meio;
    if(elem_meio < elem) ini = meio + tipo;
    if(elem_meio > elem) fim = meio - tipo;
  }
  return -1;
}

int main (int argc, char** argv){
  FILE *fp = fopen(argv[1], "wb");
  if(!fp) exit(1);
  int n;
  scanf("%d", &n);
  if(n <= 0) exit(1);
  int i = 1, vet[n], elem;
  scanf("%d", &vet[0]);
  while(i < n){
    scanf("%d", &elem);
    if(elem > vet[i-1]) vet[i++] = elem;
  }
  fwrite(vet, sizeof(int), n, fp);
  fclose(fp);
  printf("Digite o valor a ser procurado: ");
  scanf("%d", &elem);
  fp = fopen(argv[1], "rb");
  int pos = bb (fp, elem, sizeof(int));
  rewind(fp);
  int resp[n];
  fread(resp, sizeof(int), n, fp);
  for(i = 0; i < n; i++) printf("%d ", resp[i]);
  printf("\n");
  fclose(fp);
  if (pos >= 0) printf("%d e o %ld-esimo elemento do meu arquivo (%d)\n", elem, pos/sizeof(int) + 1, pos);
  else printf("Elemento nao encontrado.\n");
  return 0;
}
