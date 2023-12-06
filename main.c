#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[10];
} Veiculo;

typedef struct Nodo {
    Veiculo veiculo;
    struct Nodo* proximo;
} Nodo;

Nodo* inicializaLista() {
    return NULL;
}

Nodo* adicionaVeiculo(Nodo* lista, Veiculo veiculo) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->veiculo = veiculo;
    novoNodo->proximo = lista;
    return novoNodo;
}

void listaProprietariosDiesel2010OuPosterior(Nodo* lista) {
    Nodo* atual = lista;

    printf("\nProprietários de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    
    while (atual != NULL) {
        if (strcmp(atual->veiculo.combustivel, "diesel") == 0 && atual->veiculo.ano >= 2010) {
            printf("%s\n", atual->veiculo.proprietario);
        }
        atual = atual->proximo;
    }
}

void listaPlacasJ0_2_4_7(Nodo* lista) {
    Nodo* atual = lista;

    printf("\nPlacas que começam com 'J' e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários:\n");
    
    while (atual != NULL) {
        if (atual->veiculo.placa[0] == 'J' &&
            (atual->veiculo.placa[6] == '0' || atual->veiculo.placa[6] == '2' ||
             atual->veiculo.placa[6] == '4' || atual->veiculo.placa[6] == '7')) {
            printf("Placa: %s | Proprietário: %s\n", atual->veiculo.placa, atual->veiculo.proprietario);
        }
        atual = atual->proximo;
    }
}

void listaModeloCorVogalSomaPar(Nodo* lista) {
    Nodo* atual = lista;

    printf("\nModelo e cor dos veículos cujas placas têm a segunda letra vogal e a soma dos valores numéricos é par:\n");
    
    while (atual != NULL) {
        char segundaLetraPlaca = atual->veiculo.placa[1];
        int somaNumerosPlaca = atoi(atual->veiculo.placa + 3);

        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' || segundaLetraPlaca == 'I' ||
             segundaLetraPlaca == 'O' || segundaLetraPlaca == 'U') && somaNumerosPlaca % 2 == 0) {
            printf("Modelo: %s | Cor: %s\n", atual->veiculo.modelo, atual->veiculo.cor);
        }
        atual = atual->proximo;
    }
}

Nodo* trocaProprietarioSemZeroNoChassi(Nodo* lista, char novoProprietario[50], char chassi[20]) {
    Nodo* atual = lista;

    while (atual != NULL) {
        if (strstr(atual->veiculo.chassi, "0") == NULL) { // Se não contém dígito zero no chassi
            if (strcmp(atual->veiculo.chassi, chassi) == 0) {
                strcpy(atual->veiculo.proprietario, novoProprietario);
                printf("Proprietário alterado com sucesso!\n");
                return lista;
            }
        }
        atual = atual->proximo;
    }

    printf("Carro com chassi %s não encontrado ou possui dígito zero na placa.\n", chassi);
    return lista;
}


int main() {
    Nodo* lista = inicializaLista();
    int opcao;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Adicionar veículo\n");
        printf("2. Listar proprietários de carros diesel de 2010 ou posterior\n");
        printf("3. Listar placas começando com 'J' e terminando com 0, 2, 4 ou 7\n");
        printf("4. Listar modelo e cor de veículos com placas específicas\n");
        printf("5. Trocar proprietário por chassi\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Veiculo novoVeiculo;
                printf("Proprietário: ");
                scanf("%s", novoVeiculo.proprietario);
                printf("Combustível (álcool, diesel, gasolina): ");
                scanf("%s", novoVeiculo.combustivel);
                printf("Modelo: ");
                scanf("%s", novoVeiculo.modelo);
                printf("Cor: ");
                scanf("%s", novoVeiculo.cor);
                printf("Número do chassi: ");
                scanf("%s", novoVeiculo.chassi);
                printf("Ano: ");
                scanf("%d", &novoVeiculo.ano);
                printf("Placa: ");
                scanf("%s", novoVeiculo.placa);

                lista = adicionaVeiculo(lista, novoVeiculo);
                break;
            }
            case 2:
                listaProprietariosDiesel2010OuPosterior(lista);
                break;
            case 3:
                listaPlacasJ0_2_4_7(lista);
                break;
            case 4:
                listaModeloCorVogalSomaPar(lista);
                break;
            case 5: {
                char novoProprietario[50];
                char chassi[20];
                printf("Digite o novo proprietário: ");
                scanf("%s", novoProprietario);
                printf("Digite o número do chassi: ");
                scanf("%s", chassi);

                lista = trocaProprietarioSemZeroNoChassi(lista, novoProprietario, chassi);
                break;
            }
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);


    Nodo* atual = lista;
    Nodo* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
