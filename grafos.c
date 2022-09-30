#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
// MAX é para o valor infinito que vai nas funções!!

typedef struct item {
  int num;         // vértice
  int P_Aresta;       // valor do peso e aresta
  struct item *prox;  // arestas
  struct item *baixo; // vértice
} item;

typedef struct {
  int qtdV;    // qtd de vértice
  item *ini;  // inicio
} ListaDinamica; // grafo

typedef struct fila {
  int num;
  struct fila *prox;
} fila;

typedef struct {
  int qtd;
  fila *ini; // Remove no INICIO
  fila *fim;    // Insere no FIM
} FilaDinamica;

int VAresta(ListaDinamica *L, int v1, int v2, int peso);
void InAOrd(ListaDinamica *L, item *C, item *V);
int InVertice(ListaDinamica *L, int n);
void InPrVertice(ListaDinamica *L, item *c);
void InFimVertice(ListaDinamica *L, item *c);
int InformaPosicao(ListaDinamica *L, int Vinicio);
void InsereFila(FilaDinamica *F, int value);
int RemoveFila(FilaDinamica *F);
void InVerticeOrdenado(ListaDinamica *L, item *C);
void RemoveAresta(ListaDinamica *Lista, item *V, int n);
int InformaGrauVertice(ListaDinamica *L, int V);
void MatrizAdjacencia(ListaDinamica *L);
void FuncTeste(ListaDinamica *L);
void LD(ListaDinamica *L);
void Free_All(ListaDinamica *L);
int **AlocaMatrizDinamica(int l, int c);
void printaMatriz(int l, int c, int **matriz);
void FreeMatrizDinamica(int l, int **M);
int buscaLinha(int valor, int l, int c, int **M);
item *RetornaArestasDadoVertice(ListaDinamica *L, int Vinicio);
void GrafoComp(ListaDinamica *L);
item *ArestaNov(int value, int peso);
item *VerticeNov(int value);
item *ReturnAnt(ListaDinamica *L, int v1);
int VRemV(ListaDinamica *L, int v1);
int VRemA(ListaDinamica *L, int v1, int v2);
int **BuscaEmLargura(ListaDinamica *L, int Vinicio);
int Verifica_e_BuscaLargura(ListaDinamica *L, int Vinicio);
int VerificaGrafoConexo(ListaDinamica *L);
int BuscaEmProfundidade(ListaDinamica *L);
void DFS_VISIT(int **M, int u, ListaDinamica *L);
int AlgoritmoPrim(ListaDinamica *L, int Vinicio);
int Extract_MIN(FilaDinamica *F, int **Key);
int Informa_Num_Esta_Fila(FilaDinamica *F, int num);
void printaFila(FilaDinamica *F);
// =============================================================================

int tempo = 0;

int main(void) {
  int op;
  int retorno;

  ListaDinamica Grafo;
  LD(&Grafo);

  FuncTeste(&Grafo);

  do {
    printf("\n1.  Inserir vértices \n2.  Inserir Arestas \n3.  Visualizar "
           "Grafo\n");
    printf("4.  Remover vértices \n5.  Remover Arestas \n6.  Informar grau de um vértices\n");
    printf("7.  Informar se o Grafo e conexo \n8.  Matriz de Adjacencia\n");

    printf("\n9. Sair\n");
    printf("\nOpcões: ");
    scanf("%d", &op);

    switch (op) {
    case 1: // Inserir Vertices
    {
      int v;
      printf("Insira um número para o vértice que seja maior que zero: ");
      scanf("%d", &v);

      retorno = InVertice(&Grafo, v);
      if (retorno == (-1)) {
        printf("Vértice repetido !!!\n");
      } else {
        printf("Vértice criada !!!\n");
      }
      break;
    }

    case 2: // Inserir Arestas
    {

      int v1, v2, peso;
      printf("Informe a vértice de Origem: ");
      scanf("%d", &v1);
      printf("Informe a vértice de Destino: ");
      scanf("%d", &v2);

      do {
        printf("Informe o peso da aresta: ");
        scanf("%d", &peso);
      } while (peso <= -1);

      retorno = VAresta(&Grafo, v1, v2, peso);
      if (retorno == -1) {
        printf("OPS! Já existe aresta ligando os pontos %d e %d.\n", v1, v2);
      } else if (retorno == -2) {
        printf("OPS! Não existe os vértice %d ou %d ou ambos.\n", v1, v2);
      } else if (retorno == -3) {
        printf("OPS! No Grafo não pode ter laco (V1 = V2).\n");
      } else if (retorno == -4) {
        printf("OPS! A quantidade de vértice é insuficientes para criar "
               "aresta.\n");
      } else {
        printf("Aresta criada com sucesso !!!\n");
      }
      break;
    }

    case 3: // Visualizar Grafo
    {
      if (Grafo.qtdV == 0) {
        printf("Grafo esta vazio !!!\n");
      } else {
        GrafoComp(&Grafo);
      }
      break;
    }

    case 4: // Remover vértice
    {
      int v1;
      printf("Informe o vértice que deseja tirar: ");
      scanf("%d", &v1);

      retorno = VRemV(&Grafo, v1);
      if (retorno == (-1)) {
        printf("OPS!! A vértice informado não existe no Grafo !!!\n");
      }

      else {
        printf("Vértice removida com sucesso !!!\n");
      }
      break;
    }

    case 5: // Remover Arestas
    {
      int v1, v2;
      printf("Informe a vértice de Origem da Aresta a ser removida: ");
      scanf("%d", &v1);
      printf("Informe o Vertice de Destino da Aresta a ser removida: ");
      scanf("%d", &v2);

      retorno = VRemA(&Grafo, v1, v2);
      if (retorno == -3) {
        printf("OPS! V1 e V2 são iguais !!!\n");
      }

      else if (retorno == -2) {
        printf("OPS! Não existe asd vértices %d ou %d ou ambos.\n", v1, v2);
      }

      else if (retorno == -1) {
        printf("OPS! Não existe aresta entre os vértices %d e %d.\n", v1, v2);
      }

      else {
        printf("Aresta removida com sucesso !!!\n");
      }
      break;
    }

    case 6: // Informar grau de um vertice
    {
      int v1;
      printf("Informe o número do vértices para consultar seu grau: ");
      scanf("%d", &v1);
      retorno = InformaGrauVertice(&Grafo, v1);

      if (retorno == -1) {
        printf("ERRO! Não existe esse vértices no Grafo.\n");
      }

      else {
        printf("O grau da vértices %d e: %d\n", v1, retorno);
      }
      break;
    }

    case 7: // Informar se o grafo e conexo
    {
      retorno = VerificaGrafoConexo(&Grafo);

      if (retorno == -2) {
        printf("Grafo Vazio !!!\n");
      }

      else if (retorno == -1) {
        printf("\n Usando a Busca em Largura para determinar: Grafo NÃO "
               "CONEXO!!!\n");
      }

      else {
        printf(
            "\n Usando a Busca em Largura para determinar: Grafo Conexo !!!\n");
      }
      break;
    }

      case 8: // Converter grafo para Matriz de Adjacencia
        {
            if (Grafo.qtdV == 0)
            {
                printf("Grafo Vazio !!!\n");
            }
            else
            {
                MatrizAdjacencia(&Grafo);
            }
            break;
        }

    
        

    case 10: // Sair
    {
      Free_All(&Grafo);
      break;
    }

    default: {
      printf("Opcção invalida !!!\n");
      break;
    }
    }
  } while (op != 8);
  return 0;
}

// =======================================================================================
void FuncTeste(ListaDinamica *L) {

  InVertice(L, 1);
  InVertice(L, 2);
  InVertice(L, 3);
  InVertice(L, 4);
  InVertice(L, 5);
  InVertice(L, 6);
  InVertice(L, 7);
  InVertice(L, 8);
  InVertice(L, 9);
  InVertice(L, 10);

  VAresta(L, 1, 5, 7);
  VAresta(L, 1, 4, 9);
  VAresta(L, 1, 67, 10);
  VAresta(L, 1, 4, 8);
  VAresta(L, 1, 4, 9);
  VAresta(L, 1, 1, 8);

  VAresta(L, 2, 37, 4);
  VAresta(L, 2, 48, 5);
  VAresta(L, 2, 9, 9);
  VAresta(L, 2, 10, 9);

  VAresta(L, 3, 4, 1);
  VAresta(L, 3, 5, 4);

  VAresta(L, 4, 5, 3);

  VAresta(L, 5, 6, 18);

  VAresta(L, 6, 7, 9);
  VAresta(L, 6, 8, 9);

  VAresta(L, 7, 8, 3);
  VAresta(L, 7, 9, 6);

  VAresta(L, 8, 9, 4);
  VAresta(L, 8, 10, 2);

  VAresta(L, 9, 10, 2);
}

void LD(ListaDinamica *L) {
  L->qtdV = 0;
  L->ini = NULL;
}

void Free_All(ListaDinamica *L) {
  item *AuxV, *AuxA,
      *InicioA; // Ponteiro inicio A é para criar um inicio para arestas
  while (L->ini !=
         NULL) // Loop responsavel por dar free em todos os vértices do grafo
  {
    AuxV = L->ini;
    InicioA = AuxV->prox;
    while (InicioA != NULL) {
      AuxA = InicioA;
      InicioA = AuxA->prox;
      free(AuxA);
      AuxA = NULL;
    }
    L->ini = AuxV->baixo;
    free(AuxV);
    AuxV = NULL;
  }
}

void GrafoComp(ListaDinamica *L) // Função usada na "main" case 3
{
  item *auxV = L->ini;
  item *auxA;
  printf("Vértices   x   Arestas\n");
  while (auxV != NULL) {
    auxA = auxV;
    printf("   %2d:", auxV->num);
    if (auxA->prox == NULL) {
      printf("   NULL\n");
    } else {
      auxA = auxV->prox;
      while (auxA != NULL) {
        printf(" %d -->", auxA->num);
        auxA = auxA->prox;
      }
      printf(" NULL\n");
    }
    auxV = auxV->baixo;
  }
}

item *VerticeNov(int value) // Usada na função "Inserir Vértice"
{
  item *aux;
  aux = malloc(sizeof(item));
  aux->num = value;
  aux->P_Aresta = -1;
  aux->prox = NULL;
  aux->baixo = NULL;
  return aux;
}

item *ArestaNov(int value, int peso) // Usada na Função "VAresta"
{
  item *aux;
  aux = malloc(sizeof(item));
  aux->num = value;
  aux->P_Aresta = peso;
  aux->prox = NULL;
  aux->baixo = NULL;
  return aux;
}

item *ReturnAnt(ListaDinamica *L,
                          int v1) // Funcao usada em "VRemV"
{
  item *C = L->ini;
  while (C->baixo->num != v1) {
    C = C->baixo;
  }
  return C;
}
void printaFila(FilaDinamica *F) {
  if (F->qtd != 0) {
    fila *aux = F->ini;
    while (aux != NULL) {
      printf("%d ", aux->num);
      aux = aux->prox;
    }
  }
}

int InVertice(ListaDinamica *L, int n) {
  item *aux;
  if (L->qtdV != 0) {
    int i;
    aux = L->ini;
    for (i = 0; i < L->qtdV; i++) {
      if (aux->num == n) {
        return -1;
      }
      aux = aux->baixo;
    }
  }

  aux = VerticeNov(n);
  InVerticeOrdenado(L, aux);
  return 1;
}

void InPrVertice(ListaDinamica *L, item *c) {
  L->qtdV++;
  c->baixo = L->ini;
  L->ini = c;
}

void InFimVertice(ListaDinamica *L, item *c) {

  int pos = L->qtdV;
  int cont = 0;
  item *aux = L->ini;
  while (cont < (pos - 1)) {
    aux = aux->baixo;
    cont++;
  }
  c->baixo = aux->baixo;
  aux->baixo = c;
  L->qtdV++;
}

void InVerticeOrdenado(ListaDinamica *L, item *C) {
  item *aux = L->ini;
  if (L->qtdV != 0) {
    while (aux->baixo != NULL) {
      aux = aux->baixo;
    }
  }

  if (L->ini == NULL) {
    InPrVertice(L, C);
  } else if (C->num < L->ini->num) {
    InPrVertice(L, C);
  } else if (C->num > aux->num) {
    InFimVertice(L, C);
  }

  else {
    item *auxa, *auxd;
    auxa = L->ini;
    auxd = auxa->baixo;
    while (auxd->num < C->num) {
      auxa = auxa->baixo;
      auxd = auxa->baixo;
    }
    C->baixo = auxa->baixo;
    auxa->baixo = C;
    L->qtdV++;
  }
}

int VAresta(ListaDinamica *L, int v1, int v2, int peso) {

  if (L->qtdV == 0 || L->qtdV == 1) {
    return -4;
  }

  if (v1 == v2) {
    return -3;
  }

  item *aux = L->ini;
  int cont = 0;
  while (aux != NULL) {
    if (aux->num == v1 || aux->num == v2) {
      cont++;
    }
    aux = aux->baixo;
  }
  if (cont != 2) {
    return -2;
  }

  // Verificar Se já existe essa aresta no Grafo
  aux = L->ini;
  cont = 0;
  while (aux->num != v1) {
    aux = aux->baixo;
  }
  while (aux != NULL) {
    if (aux->num == v2) {
      cont++;
    }
    aux = aux->prox;
  }
  if (cont != 0) {
    return -1;
  }
  aux = L->ini;
  while (aux->num != v1) {
    aux = aux->baixo;
  }
  item *nv;
  nv = ArestaNov(v2, peso);
  InAOrd(L, nv, aux);

  aux = L->ini;
  while (aux->num != v2) {
    aux = aux->baixo;
  }
  nv = ArestaNov(v1, peso);
  InAOrd(L, nv, aux);

  return 1;
}

void InAOrd(ListaDinamica *L, item *C, item *V) {

  if (V->prox == NULL) {
    V->prox = C;
  }

  else if (C->num < V->prox->num) {
    C->prox = V->prox;
    V->prox = C;
  }

  else {
    item *auxa = V->prox;

    while (V->prox != NULL) {
      V = V->prox;
    }

    if (C->num > V->num) {
      V->prox = C;
    }

    else {
      item *auxd;
      auxd = auxa->prox;
      while (auxd->num < C->num) {
        auxa = auxa->prox;
        auxd = auxa->prox;
      }
      C->prox = auxa->prox;
      auxa->prox = C;
    }
  }
}

int VRemV(ListaDinamica *L, int v1) {

  item *aux = L->ini;
  int cont = 0, i;

  for (i = 0; i < L->qtdV; i++) {
    if (aux->num == v1) {
      cont++;
      break;
    }
    aux = aux->baixo;
  }
  if (cont == 0) {
    return -1;
  }

  if (aux->prox != NULL) {
    int Aresta;
    while (aux->prox != NULL) {
      Aresta = aux->prox->num;
      VRemA(L, v1, Aresta);
    }
  }
  if (aux->prox == NULL) {
    if (L->qtdV == 1) {
      free(aux);
      aux = NULL;
      LD(L);
      return 1;
    }

    else if (L->qtdV == 2) {
      if (L->ini->num == v1) {
        L->ini = aux->baixo;
        aux->baixo = NULL;
      } else {
        L->ini->baixo = NULL;
      }
    }

    else if (aux->num == L->ini->num) {
      L->ini = aux->baixo;
      aux->baixo = NULL;
    }

    else {
      item *aux_Ant = ReturnAnt(L, v1);
      aux_Ant->baixo = aux->baixo;
      aux->baixo = NULL;
    }

    free(aux);
    aux = NULL;
    L->qtdV--;
    return 1;
  }
  return -1;
}

int VRemA(ListaDinamica *L, int v1, int v2) {

  if (v1 == v2) {
    return -3;
  }

  item *aux = L->ini;
  int cont = 0;
  while (aux != NULL) {
    if (aux->num == v1 || aux->num == v2) {
      cont++;
    }
    aux = aux->baixo;
  }
  if (cont != 2) {
    return -2;
  }

  aux = L->ini;
  cont = 0;
  while (aux->num != v1) {
    aux = aux->baixo;
  }
  while (aux != NULL) {
    if (aux->num == v2) {
      cont++;
    }
    aux = aux->prox;
  }
  if (cont != 1) {
    return -1;
  }

  aux = L->ini;
  while (aux->num != v1) {
    aux = aux->baixo;
  }
  RemoveAresta(L, aux, v2);

  aux = L->ini;
  while (aux->num != v2) {
    aux = aux->baixo;
  }
  RemoveAresta(L, aux, v1);

  return 1;
}

void RemoveAresta(ListaDinamica *Lista, item *V,
                  int n) // Função usada na "VRemA"
{

  item *aux, *temp;
  aux = V;

  while (aux->prox->num != n) {
    aux = aux->prox;
  }
  temp = aux->prox;
  aux->prox = temp->prox;
  temp->prox = NULL;
  free(temp);
  temp = NULL;
}

int InformaGrauVertice(ListaDinamica *L, int V) {

  item *aux = L->ini;
  int cont = 0;

  while (aux != NULL) {
    if (aux->num == V) {
      cont++;
      break;
    }
    aux = aux->baixo;
  }

  if (cont == 0) {
    return -1;
  }

  if (aux->prox == NULL) {
    return 0;
  }

  cont = 0;
  while (aux->prox != NULL) {
    cont++;
    aux = aux->prox;
  }
  return cont;
}

void MatrizAdjacencia(ListaDinamica *L) {
  int TamanhoMatriz = L->qtdV + 1;

  int **MatrizAdj = AlocaMatrizDinamica(TamanhoMatriz, TamanhoMatriz);

  item *Aux = L->ini;
  int i;

  for (i = 1; i < TamanhoMatriz; i++) {
    MatrizAdj[0][i] = Aux->num;
    MatrizAdj[i][0] = Aux->num;
    Aux = Aux->baixo;
  }

  item *AuxA;
  Aux = L->ini;
  int linha = 1, coluna;

  while (Aux != NULL) {
    if (Aux->prox != NULL) {
      AuxA = Aux->prox;
      while (AuxA != NULL) {
        coluna =
            buscaLinha(AuxA->num, TamanhoMatriz, TamanhoMatriz, MatrizAdj);
        MatrizAdj[linha][coluna] = AuxA->P_Aresta;
        AuxA = AuxA->prox;
      }
    }
    Aux = Aux->baixo;
    linha++;
  }
  printf("\n  Matriz de Adjacencia\n\n");
  printaMatriz(TamanhoMatriz, TamanhoMatriz, MatrizAdj);
  FreeMatrizDinamica(TamanhoMatriz, MatrizAdj);
}

int **AlocaMatrizDinamica(int l, int c) {
  int i, j;
  int **m = (int **)malloc(l * sizeof(int *));
  for (i = 0; i < l; i++) {
    m[i] = (int *)malloc(c * sizeof(int));
    for (j = 0; j < c; j++) {
      m[i][j] = 0;
    }
  }
  return m;
}

int buscaLinha(int valor, int l, int c, int **M) {
  int i;
  for (i = 1; i < l; i++) {
    if (M[i][0] == valor) {
      return i;
    }
  }
  return -1;
}

void printaMatriz(int l, int c,
                  int **matriz) // Função usada em "MatrizAdjacencia"
{
  int i, j;
  for (i = 0; i < l; i++) {
    printf("  ");
    for (j = 0; j < c; j++) {
      printf("%2d ", matriz[i][j]);
    }
    printf("\n");
  }
}

void FreeMatrizDinamica(int l, int **M) {
  int i;
  for (i = 0; i < l; i++) {
    free(M[i]);
  }
  free(M);
  M = NULL;
}

int Verifica_e_BuscaLargura(ListaDinamica *L, int Vinicio) {

  if (L->qtdV == 0) {
    return -2;
  }

  item *aux = L->ini;
  int cont = 0;
  while (aux != NULL) {
    if (aux->num == Vinicio) {
      cont++;
      break;
    }
    aux = aux->baixo;
  }

  if (cont == 0) {
    return -1;
  }

  int **retorno;
  retorno = BuscaEmLargura(L, Vinicio);

  FreeMatrizDinamica(3, retorno);
  retorno = NULL;
  return 0;
}

int **BuscaEmLargura(ListaDinamica *L,
                     int Vinicio) // Função usada em "Verifica_e_BuscaLargura"
{
  int tamGrafo = L->qtdV;

  int **matriz = AlocaMatrizDinamica(3, tamGrafo);
  int i;
  for (i = 0; i < tamGrafo; i++) // Inicializando os vetores com:
  {
    matriz[1][i] = -1;
    matriz[0][i] = -1;
    matriz[2][i] = 0;
  }

  int posicao = InformaPosicao(L, Vinicio);

  matriz[1][posicao] = -1;
  matriz[0][posicao] = 0;
  matriz[2][posicao] = 1;

  FilaDinamica Q;
  Q.qtd = 0;
  Q.ini = NULL;
  Q.fim = NULL;

  InsereFila(&Q, Vinicio);
  int u, v;
  int posu, posv;
  item *aux;
  while (Q.qtd != 0) {
    u = RemoveFila(&Q);
    posu = InformaPosicao(L, u);
    aux = RetornaArestasDadoVertice(L, u);
    while (aux != NULL) {
      v = aux->num;
      posv = InformaPosicao(L, v);
      if (matriz[2][posv] == 0) {
        matriz[2][posv] = 1;
        matriz[0][posv] = matriz[0][posu] + 1;
        matriz[1][posv] = u;
        InsereFila(&Q, v);
      }
      matriz[2][posu] = 2;
      aux = aux->prox;
    }
  }

  aux = L->ini;
  printf("\n BUSCA EM LARGURA");
  printf("\n Vertice   D  Pai\n");
  for (i = 0; i < tamGrafo; i++) {
    printf("   %2d     %2d   %2d\n", aux->num, matriz[0][i],
           matriz[1][i]); //
    aux = aux->baixo;
  }
  printf(
      "\nSe (d) for  (-1) o grafo não e conexo !!!\n");
  printf("Se o pai tiver mais que um (-1) quer dizer que o Grafo não e conexo !!!\n");
  printf("O pai for (-1)  não existe.\n");

  return matriz;
}

item *RetornaArestasDadoVertice(ListaDinamica *L,
                                int Vinicio) // Função usada em "BuscaEmLargura"
{
  item *Aux = L->ini;
  while (Aux->num != Vinicio) {
    Aux = Aux->baixo;
  }
  return Aux->prox;
}

int InformaPosicao(ListaDinamica *L, int Vinicio) {
  item *aux = L->ini;
  int cont = 0;

  while (aux->num != Vinicio) {
    cont++;
    aux = aux->baixo;
  }
  return cont;
}

void InsereFila(FilaDinamica *F, int value) {

  fila *aux;
  aux = malloc(sizeof(fila));
  aux->num = value;
  aux->prox = NULL;

  if (F->qtd == 0) {
    F->ini = aux;
    F->fim = aux;
  } else {
    F->fim->prox = aux;
    F->fim = aux;
  }
  F->qtd++;
}

int RemoveFila(FilaDinamica *F) {
  int valor;
  if (F->qtd != 0) {
    valor = F->ini->num;
    fila *aux;
    if (F->qtd == 1) {
      aux = F->ini;
      free(aux);
      aux = NULL;
      F->qtd = 0;
      F->ini = NULL;
      F->fim = NULL;
    } else {
      aux = F->ini;
      F->ini = aux->prox;
      free(aux);
      aux = NULL;
      F->qtd--;
    }
  }
  return valor;
}

int VerificaGrafoConexo(ListaDinamica *L) {

  if (L->qtdV == 0) {
    return -2;
  }

  int **retorno, first, i;
  first = L->ini->num;

  retorno = BuscaEmLargura(L, first);

  for (i = 0; i < L->qtdV; i++) {
    if (retorno[2][i] == 0) {
      FreeMatrizDinamica(3, retorno);
      return -1;
    }
  }
  FreeMatrizDinamica(3, retorno);
  return 0;
}

int BuscaEmProfundidade(ListaDinamica *L) {
  tempo = 0;
  if (L->qtdV == 0) {
    return -1;
  }

  int tamGrafo = L->qtdV;

  int **Matriz;

  Matriz = AlocaMatrizDinamica(4, tamGrafo);
  int i;
  for (i = 0; i < tamGrafo; i++) {
    Matriz[0][i] = 0;
    Matriz[1][i] = -1;
  }

  int u, posu;
  item *aux = L->ini;
  while (aux != NULL) {
    u = aux->num;
    posu = InformaPosicao(L, u);

    if (Matriz[0][posu] == 0) {
      DFS_VISIT(Matriz, u, L);
    }
    aux = aux->baixo;
  }

  aux = L->ini;
  printf("\n   BUSCA EM PROFUNDIDADE");
  printf("\n Vertice   d     f    pai\n");
  for (i = 0; i < tamGrafo; i++) {
    printf("   %2d     %2d    %2d    %2d\n", aux->num, Matriz[2][i],
           Matriz[3][i], Matriz[1][i]);
    aux = aux->baixo;
  }
  printf("\nPai igual (-1) quer dizer que não tem.\n");

  FreeMatrizDinamica(4, Matriz);
  return 0;
}

void DFS_VISIT(int **M, int u, ListaDinamica *L) {

  int posu = InformaPosicao(L, u);
  int v, posv;

  M[0][posu] = 1;
  tempo = tempo + 1;
  M[2][posu] = tempo;

  item *auxA = RetornaArestasDadoVertice(L, u);
  while (auxA != NULL) {
    v = auxA->num;
    posv = InformaPosicao(L, v);
    if (M[0][posv] == 0) {
      M[1][posv] = u;
      DFS_VISIT(M, v, L);
    }
    auxA = auxA->prox;
  }
  M[0][posu] = 2;
  tempo = tempo + 1;
  M[3][posu] = tempo;
}

int AlgoritmoPrim(ListaDinamica *L, int Vinicio) {

  int retorno = VerificaGrafoConexo(L);

  if (retorno == -2) {
    return -2;
  }

  if (retorno == -1) {
    return -1;
  }
  printf("\n\nBusca em largura para determinar o Grafo Conexo !!!\n");
  printf("Como o Grafo é CONEXO o ALGORITMO DE PRIM DO GRAFO E:\n");

  int cont = 0;
  item *aux = L->ini;
  while (aux != NULL) {
    if (aux->num == Vinicio) {
      cont++;
      break;
    }
    aux = aux->baixo;
  }

  if (cont == 0) {
    return -3;
  }
  int tamGrafo = L->qtdV;
  int **key, i;

  key = AlocaMatrizDinamica(3, tamGrafo);

  aux = L->ini;
  for (i = 0; i < tamGrafo; i++) {
    key[0][i] = aux->num;
    key[1][i] = MAX;
    key[2][i] = -1;
    aux = aux->baixo;
  }

  int posicao;
  posicao = InformaPosicao(L, Vinicio);
  key[1][posicao] = 0;

  FilaDinamica Q;
  Q.qtd = 0;
  Q.ini = NULL;
  Q.fim = NULL;

  aux = L->ini;
  while (aux != NULL) {
    i = aux->num;
    InsereFila(&Q, i);
    aux = aux->baixo;
  }

  int u;
  int v, posv;

  while (Q.qtd != 0) {
    u = Extract_MIN(&Q, key);

    aux = RetornaArestasDadoVertice(L, u);
    while (aux != NULL) {
      v = aux->num;
      posv = InformaPosicao(L, v);

      if ((Informa_Num_Esta_Fila(&Q, v) == 1) &&
          aux->P_Aresta < key[1][posv]) {
        key[2][posv] = u;
        key[1][posv] = aux->P_Aresta;
      }
      aux = aux->prox;
    }
  }

  printf("\n PRIM");
  printf("\n Vértice   Pai   Key\n");
  for (i = 0; i < tamGrafo; i++) {
    printf("   %2d      %2d    %2d\n", key[0][i], key[2][i], key[1][i]);
  }
  printf("\nOBS: Pai igual (-1) quer dizer que não existe.\n");
  FreeMatrizDinamica(3, key);

  return 1;
}

int Extract_MIN(FilaDinamica *F, int **Key) {
  int valor;

  if (F->qtd != 0) {
    fila *aux;
    if (F->qtd == 1) {
      valor = F->ini->num;
      aux = F->ini;
      free(aux);
      aux = NULL;

      F->qtd = 0;
      F->ini = NULL;
      F->fim = NULL;
      return valor;
    }

    else {
      int menorV = -1, menorK, num;
      int i;

      aux = F->ini;
      do {
        num = aux->num;

        i = 0;
        while (Key[0][i] != num) {
          i++;
        }

        if (Key[1][i] != MAX) {
          menorV = Key[0][i];
          menorK = Key[1][i];
        } else {
          aux = aux->prox;
        }
      } while (menorV == (-1));

      aux = F->ini;
      while (aux != NULL) {
        num = aux->num;

        i = 0;
        while (Key[0][i] != num) {
          i++;
        }

        if (Key[1][i] < menorK) {
          menorK = Key[1][i];
          menorV = Key[0][i];
        }
        aux = aux->prox;
      }

      if (F->ini->num == menorV) {
        valor = F->ini->num;
        aux = F->ini;
        F->ini = aux->prox;
        free(aux);
        aux = NULL;

        F->qtd--;
        return valor;
      }

      else if (F->fim->num == menorV) {
        valor = F->fim->num;
        aux = F->fim;

        fila *anterior = F->ini;
        while (anterior->prox->num != F->fim->num) {
          anterior = anterior->prox;
        }

        F->fim = anterior;
        anterior->prox = NULL;
        free(aux);
        aux = NULL;

        F->qtd--;
        return valor;
      }

      else {
        aux = F->ini->prox;
        fila *auxA = F->ini;
        while (aux->num != menorV) {
          auxA = auxA->prox;
          aux = aux->prox;
        }
        valor = aux->num;
        auxA->prox = aux->prox;
        aux->prox = NULL;
        free(aux);
        aux = NULL;

        F->qtd--;
        return valor;
      }
    }
    return -1;
  }
  return -1;
}

int Informa_Num_Esta_Fila(FilaDinamica *F, int num) {
  
  if (F->qtd != 0) {
    fila *aux = F->ini;
    while (aux != NULL) {
      if (aux->num == num) {
        return 1;
      }
      aux = aux->prox;
    }
    return -1;
  }
  return -1;
}


