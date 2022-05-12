#include <ctime>
#include <iostream>
using namespace std;

typedef struct Nodo {
    string nome;
    int codigo, q_estoque, q_vendida = 0;
    float preco;
    struct Nodo *proximo;
} Produto;

void inclusao(Produto **, Produto **);
void destroilista(Produto **, Produto**);

int main() {
    Produto *p_aux, *info = NULL;
    int opcao;

    cout << "Digite a opcao desejada: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
        inclusao(&info, &p_aux);
        break;

        /*     case 2:
                consulta();
                break;

            case 3:
                exclusao();
                break;

            case 4:
                venda();
                break;

            case 5:
                relatorio_estoque();
                break;

            case 5:
                relatorio_vendas();
                break; */

        return 0;
    }
}

void inclusao(Produto **info, Produto **p_aux) {
    Produto *p;
    p = new Produto; // aloca memoria p/ novo nodo
    string addProduto;

    if (p == NULL) {
        cout << "Sem memoria";
        cin.get();
        exit(1);
    }

    else {
        cout << "Insira o nome do produto: ";
        cin.ignore(); //! cin.ignore aqui!
        getline(cin, addProduto);

        while (p != NULL and p->nome != addProduto) {
            if (addProduto == p->nome) {
                cout << "Produto ja existente! ";
                return; //! TALVEZ NÃO FUNCIONE!
            } else
                p = p->proximo;
        }

        p->nome = addProduto;

        srand(time(NULL));
        p->codigo = rand() % 100 + 1;

        cout << "Quantidade de unidades no estoque: ";
        cin >> p->q_estoque;

        cout << "Preco de venda: ";
        cin >> p->preco;

        p->proximo = *info;

        if (info == NULL)
            *info = p; // conecta o novo nodo ao inicio da lista
        else
            *p_aux = p;

        cout << "Inclusao confirmada!";
    }
}

void destroilista(Produto **info) { // ponteiro de ponteiro
    Produto *p;
    while (*info != NULL) {
        p = *info;
        *info = (*info)->proximo;
        delete p;
    }
}
