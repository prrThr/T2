#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct Nodo {
    string nome;
    int codigo, q_estoque, q_vendida = 0;
    float preco;
    struct Nodo *proximo;
} Produto;

int funcao_opcao();
void inclusao(Produto **);
void consulta(Produto *);
void destroilista(Produto **);

int main() {
    Produto *lista = NULL;
    int opcao;

    do {

        opcao = funcao_opcao();
        system("cls");

        switch (opcao) {
        case 1:
            inclusao(&lista);
            break;

        case 2:
            consulta(lista);
            break;

            /*
            case 3:
                exclusao();
                break;

            case 4:
                venda();
                break;

            case 5:
                relatorio_estoque();
                break;

            case 6:
                relatorio_vendas();
                break;
            */

        case 7:
            cout << "Saindo..." << endl;
            break;
        }
        
        system("cls");
    } while (opcao != 7);

    destroilista(&lista);
    return 0;
}

int funcao_opcao() {
    int escolha;
    do {
        cout << "Digite a opcao desejada: " << endl;
        cout << "1 - Incluir um produto na lista" << endl;
        cout << "2 - Consultar um produto" << endl;
        cout << "3 - Excluir um produto" << endl;
        cout << "4 - Vender um produto" << endl;
        cout << "5 - Relatorio de estoque" << endl;
        cout << "6 - Relatorio de vendas" << endl;
        cout << "7 - Sair" << endl;
        cin >> escolha;
    } while (escolha < 1 or escolha > 7);
    return escolha;
}

// ---------- Incluir ---------- //
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
    cout << "Codigo do produto: " << p->codigo << endl;

    cout << "Quantidade de unidades no estoque: ";
    cin >> p->q_estoque;

    cout << "Preco de venda: ";
    cin >> p->preco;

    if (*lista == NULL)
        *lista = p; // Conecta o novo nodo ao inicio da lista
    else
        p_aux->proximo = p;
    p_aux = p;

    cout << "Inclusao confirmada!";
}

// ---------- Consulta ---------- //
void consulta(Produto *lista) {
    Produto *p;
    while (lista != NULL) {
        p = lista;

        cout << "Nome: " << lista->nome << endl;
        cout << "Codigo: " << lista->codigo << endl;
        cout << "Preco: " << lista->preco << endl;
        cout << "Quantidade no estoque: " << lista->q_estoque << endl;
        cout << "Quantidade vendida:" << lista->q_vendida << endl;

        lista = lista->proximo;
    }
}

//---------- Liberar memória ---------- //
void destroilista(Produto **lista) { // ponteiro de ponteiro
    Produto *p;
    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->proximo;
        delete p;
    }
}
