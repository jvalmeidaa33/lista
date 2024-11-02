#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fruta {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct fruta *prox;
};

typedef struct fruta Fruta;

Fruta* criarLista() {
    return NULL;
}

Fruta* cadastrarFruta(Fruta* lista, int codigo, char* nome, int quantidade, float preco) {
    Fruta* atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            printf("Erro: Codigo ja existente!\n");
            return lista;
        }
        atual = atual->prox;
    }

    Fruta* nova = (Fruta*) malloc(sizeof(Fruta));
    nova->codigo = codigo;
    strcpy(nova->nome, nome);
    nova->quantidade = quantidade;
    nova->preco = preco;
    nova->prox = lista;
    printf("Fruta cadastrada com sucesso!\n");
    return nova;
}

void listarFrutas(Fruta* lista) {
    if (lista == NULL) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }
    
    Fruta* atual = lista;
    printf("Frutas cadastradas:\n");
    while (atual != NULL) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
               atual->codigo, atual->nome, atual->quantidade, atual->preco);
        atual = atual->prox;
    }
}

Fruta* buscarFruta(Fruta* lista, int codigo) {
    Fruta* atual = lista;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }
    printf("Fruta com codigo %d nao encontrada.\n", codigo);
    return NULL;
}

void alterarFruta(Fruta* lista, int codigo) {
    Fruta* fruta = buscarFruta(lista, codigo);
    if (fruta != NULL) {
        printf("Digite o novo nome da fruta: ");
        scanf(" %[^\n]s", fruta->nome);
        printf("Digite a nova quantidade da fruta: ");
        scanf("%d", &fruta->quantidade);
        printf("Digite o novo preço da fruta: ");
        scanf("%f", &fruta->preco);
        printf("Fruta alterada com sucesso!\n");
    } else {
        printf("Fruta com código %d não encontrada.\n", codigo);
    }
}

Fruta* excluirFruta(Fruta* lista, int codigo) {
    if (lista == NULL) {
        printf("Nenhuma fruta cadastrada.\n");
        return lista;
    }

    Fruta* atual = lista;
    Fruta* anterior = NULL;

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Fruta com codigo %d nao encontrada.\n", codigo);
    } else if (atual->quantidade > 0) {
        printf("Erro: Nao foi possível excluir a fruta, pois ainda ha %d em estoque.\n", atual->quantidade);
    } else {
        if (anterior == NULL) {
            lista = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
        printf("Fruta excluida com sucesso!\n");
    }

    return lista;
}

void venderFruta(Fruta* lista, int codigo, int quantidade) {
    Fruta* fruta = buscarFruta(lista, codigo);
    if (fruta == NULL) {
        printf("Fruta com codigo %d nao encontrada.\n", codigo);
        return;
    }

    if (fruta->quantidade < quantidade) {
        printf("Erro: Quantidade em estoque insuficiente para venda.\n");
        return;
    }

    fruta->quantidade -= quantidade;
    float valorVenda = fruta->preco * quantidade;

    FILE* arquivo = fopen("vendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }
    fprintf(arquivo, "Codigo: %d, Nome: %s, Quantidade Vendida: %d, Valor Total: %.2f\n",
            fruta->codigo, fruta->nome, quantidade, valorVenda);
    fclose(arquivo);

    printf("Venda realizada com sucesso! Quantidade restante: %d\n", fruta->quantidade);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Fruta* lista = criarLista();
    int opcao, codigo, quantidade;
    char nome[50];
    float preco;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar fruta\n");
        printf("2. Listar frutas\n");
        printf("3. Buscar fruta\n");
        printf("4. Alterar fruta\n");
        printf("5. Excluir fruta\n");
        printf("6. Vender fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                printf("Digite o codigo da fruta: ");
                scanf("%d", &codigo);
                limparBuffer();
                printf("Digite o nome da fruta: ");
                scanf(" %[^\n]s", nome);
                printf("Digite a quantidade da fruta: ");
                scanf("%d", &quantidade);
                printf("Digite o preco da fruta: ");
                scanf("%f", &preco);
                lista = cadastrarFruta(lista, codigo, nome, quantidade, preco);
                break;
            case 2:
                listarFrutas(lista);
                break;
            case 3:
                printf("Digite o codigo da fruta a buscar: ");
                scanf("%d", &codigo);
                Fruta* fruta = buscarFruta(lista, codigo);
                if (fruta) {
                    printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
                           fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
                }
                break;
            case 4:
                printf("Digite o codigo da fruta a alterar: ");
                scanf("%d", &codigo);
                alterarFruta(lista, codigo);
                break;
            case 5:
                printf("Digite o codigo da fruta a excluir: ");
                scanf("%d", &codigo);
                lista = excluirFruta(lista, codigo);
                break;
            case 6:
                printf("Digite o codigo da fruta a vender: ");
                scanf("%d", &codigo);
                printf("Digite a quantidade a vender: ");
                scanf("%d", &quantidade);
                venderFruta(lista, codigo, quantidade);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 7);

    return 0;
}
