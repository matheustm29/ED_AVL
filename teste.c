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
        return 0;
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
    No* x = y->esquerdo;
    No* T2 = x->direito;

    x->direito = y;
    y->esquerdo = T2;

    y->altura = maximo(altura(y->esquerdo), altura(y->direito)) + 1;
    x->altura = maximo(altura(x->esquerdo), altura(x->direito)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
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
        return 0;
    return altura(N->esquerdo) - altura(N->direito);
}


No* novoNo(int info) {
    No* no = (No*)malloc(sizeof(No));
    no->info = info;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    return no;
}

No* inserir(No* no, int info) {
    if (no == NULL)
        return novoNo(info);

    if (info < no->info)
        no->esquerdo = inserir(no->esquerdo, info);
    else if (info > no->info)
        no->direito = inserir(no->direito, info);
    else
        return no;

    no->altura = 1 + maximo(altura(no->esquerdo), altura(no->direito));

    int balanceamento = obterBalanceamento(no);

    if (balanceamento > 1 && info < no->esquerdo->info)
        return rotacaoDireita(no);

    if (balanceamento < -1 && info > no->direito->info)
        return rotacaoEsquerda(no);

    if (balanceamento > 1 && info > no->esquerdo->info) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && info < no->direito->info) {
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    return no;
}

No* minimo(No* no) {
    No* atual = no;

    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;

    return atual;
}


No* remover(No* raiz, int chave) {
    
    if (raiz == NULL)
        return raiz;

    if (chave < raiz->info)
        raiz->esquerdo = remover(raiz->esquerdo, chave);
    else if (chave > raiz->info)
        raiz->direito = remover(raiz->direito, chave);
    else {
        //Caso 1: Nó com apenas um filho ou sem filho
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL)) {
            No* temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            // Caso de nenhum filho
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else  // Caso de um filho
                *raiz = *temp; 

            free(temp);
        } else {
            //Caso 2: nó com dois filhos: Obtém o sucessor em-ordem (menor na subárvore direita)
            No* temp = minimoValorNo(raiz->direito);
            raiz->info = temp->info;
            raiz->direito = remover(raiz->direito, temp->info);
        }
    }

    if (raiz == NULL)
        return raiz;

    //Passo 2: Atualiza a altura do nó atual
    raiz->altura = 1 + maximo(altura(raiz->esquerdo), altura(raiz->direito));

    //Passo 3: Obtém o fator de balanceamento deste nó
    int balanceamento = obterBalanceamento(raiz);

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && obterBalanceamento(raiz->esquerdo) >= 0)
        return rotacaoDireita(raiz);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && obterBalanceamento(raiz->esquerdo) < 0) {
        raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo);
        return rotacaoDireita(raiz);
    }

    // Caso Direita-Direita
    if (balanceamento < -1 && obterBalanceamento(raiz->direito) <= 0)
        return rotacaoEsquerda(raiz);

    // Caso Direita-Esquerda
    if (balanceamento < -1 && obterBalanceamento(raiz->direito) > 0) {
        raiz->direito = rotacaoDireita(raiz->direito);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
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

    raiz = inserir(raiz, 100);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 200);
    raiz = inserir(raiz, 150);
    raiz = inserir(raiz, 140);
    raiz = inserir(raiz, 170);
    raiz = inserir(raiz, 160);
    raiz = inserir(raiz, 250);
    raiz = inserir(raiz, 300);

    printf("Arvore AVL antes da remocao:\n");
    imprimirArvore(raiz, 0);

    raiz = remover(raiz, 200);

    printf("\nArvore AVL aposs a remocao do no 20:\n");
    imprimirArvore(raiz, 0);

    return 0;
}