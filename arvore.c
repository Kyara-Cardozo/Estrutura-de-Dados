#include <stdio.h>
#include <stdlib.h>

// Inserindo regra binária 
typedef struct no {
  int vl;
  struct no *dir, *esq;
} NoArv;

NoArv *inse(NoArv *raiz, int num) {
  if (raiz == NULL) {
    NoArv *aux = malloc(sizeof(NoArv));
    aux->vl = num;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
  } else {
    if (num < raiz->vl)
      raiz->esq = inse(raiz->esq, num);
    else
      raiz->dir = inse(raiz->dir, num);
    return raiz;
  }
}

// Mostrar de folhas
int folhasArvore(NoArv* raiz){
	if(raiz == NULL)
		return 0;
	else
		if(raiz->esq == raiz-> dir)
			return 1;
		else
			return folhasArvore(raiz->esq) + folhasArvore(raiz->dir);
}

// Total Nó
int qtd_nos(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + qtd_nos(raiz->esq) + qtd_nos(raiz->dir);
}

//Total Folhas
int qtd_folhas(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else if(raiz->esq == NULL && raiz->dir == NULL)
        return 1;
    else
        return qtd_folhas(raiz->esq) + qtd_folhas(raiz->dir);
     if (raiz) {
        printf("%d", raiz->vl);
        qtd_folhas(raiz->esq);
        qtd_folhas(raiz->dir);
  }
      if (raiz){
        qtd_folhas(raiz->dir);
        printf("%d", raiz->vl);
        qtd_folhas(raiz->esq);
      }
}

// Remover um Nó
NoArv* remover(NoArv *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->vl == chave) {
            // remover nós folhas (nós sem filhos)
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    NoArv *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->vl = aux->vl;
                    aux->vl = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esq = remover(raiz->esq, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    NoArv *aux;
                    if(raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->vl)
                raiz->esq = remover(raiz->esq, chave);
            else
                raiz->dir = remover(raiz->dir, chave);
            return raiz;
        }
    }
}


// Altura

int altura (NoArv* raiz){
	int e,d;

	if(raiz == NULL){
		return 0;		
	}
	e = altura(raiz->esq);
	d = altura(raiz->dir);

if(e > d){
		return e+1;		
	}
	return d+1;
}

// Buscando

NoArv *bus_1(NoArv *raiz, int num) {
  if (raiz) {
    if (num == raiz->vl)
      return raiz;
    else if (num < raiz->vl)
      return bus_1(raiz->esq, num);
    else
      return bus_1(raiz->dir, num);
  }
  return NULL;
}
//PreOrdem
void exibirPreOrdem (NoArv* raiz)
{
	if(raiz != NULL)
	{
		printf("%d ", raiz->vl);
		exibirPreOrdem(raiz->esq);
		exibirPreOrdem(raiz->dir);
	}
}

//InOrdem
void exibirInOrdem(NoArv* raiz) {
    if (raiz != NULL){
        exibirInOrdem(raiz->esq);
        printf("%d ", raiz->vl); 
        exibirInOrdem(raiz->dir);
    }
  }


//PosOrdem
void exibirPosOrdem (NoArv* raiz)
{
	if(raiz != NULL)
	{
		exibirPosOrdem(raiz->esq);
		exibirPosOrdem(raiz->dir);
		printf("%d ", raiz->vl);
	}
}

// Impressão

void imprimir_1(NoArv *raiz) {
  if (raiz) {
    printf("%d", raiz->vl);
    imprimir_1(raiz->esq);
    imprimir_1(raiz->dir);
  }
}

void imprimir_2(NoArv *raiz) {
  if (raiz) {
    imprimir_2(raiz->dir);
    printf("%d", raiz->vl);
    imprimir_2(raiz->esq);
  }
}

//Menos  Nó
void menorno(NoArv *raiz){
	if(raiz != NULL)
  {
		if((raiz)->esq == NULL){
		}
		menorno(raiz->esq);
	}
	else{
	}
}
//Maior Nó
void maiorno(NoArv *raiz){
	if(raiz != NULL){
		if((raiz)->esq == NULL){
		}
		maiorno(raiz->dir);
	}
	else{
	}
}


//Nivel
void nivel_No(NoArv *raiz, int nivel){ 
    if(raiz){
        nivel_No(raiz->esq, nivel + 1);
        printf("%d(%d) ", raiz->vl, nivel);
        nivel_No(raiz->dir, nivel + 1);
    }
}


int main() {
  NoArv *busca, *raiz = NULL;

  int op, vl;

  do {
    printf("\n\t0-Sair\n\t1-Inserir\n\t2-Imprimir\n\t3-Impressão PreOrdem,Inordem e PosOrdem\n\t4-Buscar\n\t5-Identificar Folhas\n\t6-Quantidade de Folhas\n\t7-Quantidade de Nós\n\t8- Altura do Nó\n\t9-Digite para remover\n\t10-Maior e Menor Nó\n\t11-N[ivel do Nó");
    scanf("%d", &op);

    switch (op) {
    case 1:
      printf("\n Informe um valor:\n");
      scanf("%d", &vl);
      raiz = inse(raiz, vl);
      break;

    case 2:

      printf("\n\tPrimeira impressao:\n\t");
      imprimir_1(raiz);
      printf("\n");
      printf("\n\tSegunda impressao:\n\t");
      imprimir_2(raiz);
      printf("\n");
      break;

    case 3:
        printf("\n\n\t\tPreOrdem\n\n");
				exibirPreOrdem(raiz);
				printf("\n\n\t\tInOrder\n\n");
				exibirInOrdem(raiz);
				printf("\n\n\t\tPosOrdem\n\n");
				exibirPosOrdem(raiz);
				break;
      
    case 4:
      printf("\n Informe um valor para buscar:");
      scanf("%d", &vl);
      busca = bus_1(raiz, vl);
      if (busca)
        printf("\n\tO valor %d foi encontrado!\n", busca->vl);
      else
        printf("\nValor digitado não encontrado :( \n");
      break;

    case 5:
      printf("\nAs folhas são: %d!\n", folhasArvore(raiz));
      break;

    case 6:
      printf("\nA quantidade de  Folhas é: %d!\n", qtd_folhas(raiz));
      break;

    case 7:
      printf("\nA quantidade de  Nós é: %d!\n", qtd_nos(raiz));
      break;


      case 8:
      printf("\nA altura do Nó é de: %d", altura(raiz));
      break;
      
    case 9:
      printf("\nDigite o número que vai ser removido:");
      scanf("%d", &vl);
      raiz = remover(raiz, vl);
      break;

      case 10:
      printf("\nO maior Nó: %d", maiorno (raiz));
      break;

     case 11:
      printf("\nO nível do Nó: %d", nivel_No(raiz));
      break;
     
    default:
      if (op != 0)
        printf("\nOpção invalida!\n");
    }
  } while (op != 0);
  return 0;
}