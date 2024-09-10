#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int info; 
    struct No* esquerdo;
    struct No* direito;
    int altura;
} No;

int altura(No* N) {
    if (N == NULL)
        return 0;                                               // 1º Allan
    return N->altura;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->info = chave;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    return no;
}

No* rotacaoDireita(No* y) {
    printf("Rotacao direita\n");
    No* x = y->esquerdo;
    No* T2 = x->direito;
    /*
        Identificação:
            y = nó desbalanceado
            x = filho da esquerda                                           3º Allan
            t2 = filho da direita
    */

    x->direito = y;
    y->esquerdo = T2;

    /*
        Rotação
            x = nova raiz da subarvore
            y = filho da direita de x
            t2 = filho da esquerda de y
    */

   //Atualização das alturas
    y->altura = maximo(altura(y->esquerdo), altura(y->direito)) + 1;
    x->altura = maximo(altura(x->esquerdo), altura(x->direito)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    printf("Rotacao esquerda\n");
    No* y = x->direito;
    No* T2 = y->esquerdo;

    y->esquerdo = x;
    x->direito = T2;

    x->altura = maximo(altura(x->esquerdo), altura(x->direito)) + 1;
    y->altura = maximo(altura(y->esquerdo), altura(y->direito)) + 1;

    return y;
}

int obterBalanceamento(No* N) {
    if (N == NULL)
        return 0; //Se for vazio quer dizer q n tem subarvores, logo o fator de balanceamento é 0
    return altura(N->esquerdo) - altura(N->direito); //Calcula a altura das subarvores e subtrai

    /*
        Fator de balanceamento (> 0):
            -Subarvore esquerda é mais alta que da direita                                  2º Matheus
        Fator de balanceamento (< 0):
            -Subarvore direita é mais alta que da esquerda
    
    */ 
}

No* inserir(No* no, int info) {
    if (no == NULL) //Se for vazio insere no mesmo lugar
        return novoNo(info);

    if (info < no->info) //Se for menor tenta inserir na subarvore esquerda                 4º Fabio
        no->esquerdo = inserir(no->esquerdo, info);
    else if (info > no->info) //Se for maior tenta inserir na subarvore direita
        no->direito = inserir(no->direito, info);
    else
        return no; //Se o valor for igual a um inserido, simplesmente retorna o mesmo valor

    no->altura = 1 + maximo(altura(no->esquerdo), altura(no->direito)); //Atualização da altura (1+subarvore(esquerda/direita))

    int balanceamento = obterBalanceamento(no); //Se o fator de balanceamento for diferente de 1,0 e -1 a arvore esta desbalanceada

    if (balanceamento > 1 && info < no->esquerdo->info) { //Rotação a direita                 5ºJoao
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && info > no->direito->info) { //Rotação a esquerda
        return rotacaoEsquerda(no);
    }

    if (balanceamento > 1 && info > no->esquerdo->info) { //Rotação dupla direita
        printf("Rotacao dupla direita\n");
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && info < no->direito->info) { //Rotação dupla esquerda
        printf("Rotacao dupla esquerda\n");
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    return no;
}

void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info); //Imprime o nó atual
        preOrdem(raiz->esquerdo); // percorre toda subarvore esquerda               
        preOrdem(raiz->direito); // percorre toda a subarvore direita
    }
}

void imprimirArvore(No* raiz, int espaco) {
    int i;
    if (raiz == NULL)
        return;

    espaco += 5;

    imprimirArvore(raiz->direito, espaco);

    printf("\n");
    for (i = 5; i < espaco; i++)
        printf(" ");
    printf("%d\n", raiz->info);

    imprimirArvore(raiz->esquerdo, espaco);
}

int main() {
    No* raiz = NULL;
    int num;

    printf("Digite uma serie de numeros inteiros positivos (0 para finalizar):\n");

    while (1) {
        scanf("%d", &num);
        if (num == 0) {
            printf("\nPercurso em pre-ordem da arvore AVL:\n");
            preOrdem(raiz);
            printf("\n");
            break;
        }
        raiz = inserir(raiz, num);
        printf("Arvore AVL apos a insercao de %d:\n", num);
        imprimirArvore(raiz, 0);
    }

    return 0;
}