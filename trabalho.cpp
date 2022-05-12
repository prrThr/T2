#include <ctime>
#include <iostream>
using namespace std;

typedef struct Nodo {
    string nome;
    int codigo, q_estoque, q_vendida = 0;
    float preco;
    struct Nodo *proximo;
} Produto;

void inclusao(Produto **);
void destroilista(Produto **);

int main() {
    Produto *lista = NULL;
    int opcao;

    cout << "Digite a opcao desejada: " << endl;
    cout << "1 - Incluir um produto na lista" << endl;
    cout << "2 - Consultar um produto" << endl;
    cout << "3 - Excluir um produto" << endl;
    cout << "4 - Vender um produto" << endl;
    cout << "5 - Relatorio de estoque" << endl;
    cout << "6 - Relatorio de vendas" << endl;
    cout << "7 - Sair" << endl;
    cin >> opcao;

    switch (opcao) {
    case 1:
        inclusao(&lista);
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

    destroilista(&lista);
}

void inclusao(Produto **lista) {
    Produto *p, *p_aux;
    p = new Produto; // Aloca memoria para novo nodo
    string addProduto;

    if (p == NULL) {
        cout << "Sem memoria";
        cin.get();
        exit(1);
    }

    cin.ignore(); //! cin.ignore aqui!
    cout << "Insira o nome do produto: ";
    getline(cin, addProduto);

  /*   while (p != NULL and p->nome != addProduto) { //! Arrumar
        p = p->proximo;
        if (p->nome == addProduto) {
            cout << "Produto ja existente! ";
            return; //! TALVEZ NÃO FUNCIONE!
        }
    } */

    

    p->nome = addProduto;

    srand(time(NULL));
    p->codigo = rand() % 100 + 1;

    cout << "Quantidade de unidades no estoque: ";
    cin >> p->q_estoque;

    cout << "Preco de venda: ";
    cin >> p->preco;

    if (lista == NULL)
        *lista = p; // conecta o novo nodo ao inicio da lista
    else
        p_aux->proximo = p;
    p_aux = p;

    cout << "Inclusao confirmada!";
}

void destroilista(Produto **lista) { // ponteiro de ponteiro
    Produto *p;
    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->proximo;
        delete p;
    }
}
