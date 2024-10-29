#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista* criarLista() {
    return NULL;
}

Lista* inserirLista (Lista* lista, int valor) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo -> info = valor;
    novo -> prox = NULL;

    if (lista == NULL) {
        return novo;
    } else {
        Lista* atual = lista;
        while (atual -> prox != NULL) {
            atual = atual -> prox;
        }
        atual -> prox = novo;
        return lista;
    }
}

Lista* inserirListaOrdenada(Lista* lista, int valor) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo -> info = valor;
    novo -> prox = NULL;

    if (lista == NULL || lista->info >= valor) {
        novo -> prox = lista;
        return novo;
    } else {
        Lista* atual = lista;
        while (atual -> prox != NULL && atual -> prox -> info < valor) {
            atual = atual -> prox;
        }
        novo -> prox = atual -> prox;
        atual -> prox = novo;
        return lista;
    }
}

void exibirLista(Lista* lista) {
    while (lista != NULL) {
        printf("%d", lista -> info);
        lista = lista -> prox;
    }
    printf("\n");
}

int verificarLista(Lista* lista) {
    return lista == NULL;
}

Lista* buscarLista(Lista* lista, int valor) {
    while (lista != NULL && lista -> info != valor) {
        lista = lista -> prox;
    }
    return lista;
}

Lista* excluirLista(Lista* lista, int valor) {
    if (lista == NULL) return NULL;

    if (lista -> info == valor) {
        Lista* temp = lista;
        lista = lista -> prox;
        free(temp);
        return lista;
    } else {
        Lista* atual = lista;
        while (atual->prox != NULL && atual -> prox -> info != valor) {
            atual = atual->prox;
        }
        if (atual -> prox != NULL) {
            Lista* temp = atual -> prox;
            atual -> prox = atual -> prox -> prox;
            free(temp);
        }
        return lista;
    }
}

void liberarLista(Lista* lista) {
    while (lista != NULL) {
        Lista* temp = lista;
        lista = lista -> prox;
        free(temp);
    }
}

int main() {
    Lista* minhaLista = criarLista();

    minhaLista = inserirLista(minhaLista, 5);
    minhaLista = inserirLista(minhaLista, 10);
    minhaLista = inserirLista(minhaLista, 15);

    printf("Lista original: ");
    exibirLista(minhaLista);

    minhaLista = inserirListaOrdenada(minhaLista, 7);
    minhaLista = inserirListaOrdenada(minhaLista, 3);

    printf("Lista ordenada: ");
    exibirLista(minhaLista);

    if (verificarLista(minhaLista) == 0) {
        printf("A lista nao esta vazia.\n");
    } else {
        printf("A lista esta vazia.\n");
    }

    Lista* busca = buscarLista(minhaLista, 10);
    if (busca != NULL) {
        printf("Elemento 10 encontrado.\n");
    } else {
        printf("Elemento 10 nao encontrado.\n");
    }

    minhaLista = excluirLista(minhaLista, 10);

    printf("Lista apos exclusao: ");
    exibirLista(minhaLista);

    liberarLista(minhaLista);

    return 0;
}