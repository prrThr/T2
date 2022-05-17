#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

typedef struct Nodo {
    string nome;
    int codigo, q_estoque, q_vendida = 0;
    float preco;
    struct Nodo *proximo;
} Produto;

int funcao_opcao();
void mostrarInfos(Produto, char &);
void continuar();
void inclusao(Produto **);
void ordenar(string, Produto **);
void consulta(Produto *);
void destroilista(Produto **);
void exclusao(Produto **);
void exclusao_aux1(Produto *, Produto **, char);
void exclusao_aux2(Produto *, Produto **, char, Produto *);
void exclusao_nome(Produto *, string, Produto **);
void exclusao_codigo(Produto *, int, Produto **);
void vendas(Produto *);
void relatorio_estoque(Produto *);
void relatorio_vendas(Produto *);

int main() {
    Produto *lista = NULL, p_aux;
    int opcao;

    do {
        system("cls");
        opcao = funcao_opcao();
        system("cls");

        switch (opcao) {
        case 1:
            inclusao(&lista);
            break;

        case 2:
            consulta(lista);
            break;

        case 3:
            exclusao(&lista);
            break;

        case 4:
            vendas(lista);
            break;

        case 5:
            relatorio_estoque(lista);
            break;

        case 6:
            relatorio_vendas(lista);
            break;

        case 7:
            cout << "Saindo..." << endl;
            break;
        }

        cin.ignore();
        continuar();

    } while (opcao != 7);

    destroilista(&lista);
    return 0;
}

// ---------- Mostrar Infos ----------//
void mostrarInfos(Produto *p, char &opcao2, bool &mostrar) {
    mostrar = false;
    cout << "Elemento encontrado!" << endl;
    cout << "Nome: " << p->nome << endl;
    cout << "Codigo: " << p->codigo << endl;
    cout << "Preco: " << p->preco << endl;
    cout << "Quantidade no estoque: " << p->q_estoque << endl;
    cout << "Quantidade vendida:" << p->q_vendida << endl;
    do {
        cout << "Confirmar exclusao: S(sim) / N(nao)?" << endl;
        opcao2 = toupper(cin.get());
        if (opcao2 != 'S' and opcao2 != 'N')
            cout << "opcao invalida!" << endl;
    } while (opcao2 != 'S' and opcao2 != 'N');
}

// ---------- Continuar ----- //
void continuar() {
    char continuar;
    do {
        cout << "\nPressione ENTER para continuar: ";
        continuar = cin.get();
    } while (continuar != '\n');
}

// ---------- Menu ---------- //
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

// --------------- Incluir --------------- //
void inclusao(Produto **lista) {
    Produto *p, *p_aux, *procurar, *pant;
    string addProduto;
    bool ultimo = true;
    p = new Produto; // Aloca memoria para novo nodo

    p_aux = *lista;
    pant = *lista;

    if (p == NULL) {
        cout << "Sem memoria";
        cin.get();
        destroilista(lista);
        exit(1);
    }

    cin.ignore();
    cout << "Insira o nome do produto: ";
    getline(cin, addProduto);

    procurar = *lista;
    while (procurar != NULL) {
        if (procurar->nome == addProduto) {
            cout << "Produto ja existente! Pressione enter!" << endl; //! PROBLEMA AQUI
            delete p;
            return;
        }
        procurar = procurar->proximo;
    }

    p->nome = addProduto;

    // --------------- ORDENAR --------------- //
    if (*lista == NULL) {
        p->proximo = NULL;
        *lista = p;

    } else if (p->nome < p_aux->nome) {
        p->proximo = p_aux;
        *lista = p;

    } else {

        while (p_aux != NULL) {
            if (p->nome < p_aux->nome) {
                while (pant->proximo != p_aux)
                    pant = pant->proximo;
                pant->proximo = p;
                p->proximo = p_aux;
                ultimo = false;
                break;
            }
            p_aux = p_aux->proximo;
        }

        p_aux = *lista;

        if (ultimo == true) {
            while (p_aux->proximo != NULL) // Fazendo o 'pant' virar o antes de 'p'
                p_aux = p_aux->proximo;
            p_aux->proximo = p;
            p->proximo = NULL;
        }
    }
    // --------------- FIM ORDENAR  ---------------  //

    srand(time(NULL));
    p->codigo = rand() % 500 + 1;
    cout << "Codigo do produto: " << p->codigo << endl;

    do {
        cout << "Quantidade de unidades no estoque: ";
        cin >> p->q_estoque;
    } while (p->q_estoque <= 0);

    do {
        cout << "Preco de venda: ";
        cin >> p->preco;
    } while (p->preco <= 0);

    cout << "Inclusao confirmada!" << endl;
}

// --------------- Consulta --------------- //
void consulta(Produto *lista) {
    int codigo;
    Produto *p = lista;

    if (lista == NULL) {
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
        return;
    }

    cout << "Informe o codigo do produto que deseja consultar: ";
    do {
        cin >> codigo;
    } while (codigo <= 0 or codigo > 500);
    while (p != NULL and p->codigo != codigo)
        p = p->proximo;

    if (p != NULL) { // encontrou elemento
        cout << "----------------------" << endl;
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << " unid." << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
        cout << "----------------------" << endl;
        return;
    }

    cout << "Produto inexistente" << endl;
}

//--------------- Liberar memória --------------- //
void destroilista(Produto **lista) {
    Produto *p;
    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->proximo;
        delete p;
    }
}

//---------------      Excluir --------------- //
void exclusao(Produto **lista) {
    Produto *p;
    p = *lista;
    string produto;
    int codigo, opcao;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else {
        do {
            cout << "Deseja procurar pelo codigo ou nome do produto?" << endl;
            cout << "1. Codigo" << endl;
            cout << "2. Nome" << endl;
            cin >> opcao;
        } while (opcao < 1 or opcao > 2);

        if (opcao == 1) {
            cout << "informe o codigo do produto que deseja excluir: ";
            do {
                cin >> codigo;
            } while (codigo <= 0 or codigo > 500);
            exclusao_codigo(p, codigo, lista);
        }

        else {
            cout << "Informe o nome do produto que deseja excluir: ";
            cin.ignore();
            getline(cin, produto);
            exclusao_nome(p, produto, lista);
        }
    }
}

void exclusao_aux1(Produto *p, Produto **lista, char opcao2, bool &mostrar) {
    mostrarInfos(p, opcao2, mostrar);
    if (opcao2 == 'S') {
        *lista = p->proximo;
        delete p;
        cout << "Exclusao confirmada!" << endl;
        return;
    } else
        cout << "Exclusao nao realizada!" << endl;
    return;
}
void exclusao_aux2(Produto *p, Produto **lista, char opcao2, Produto *pant, bool &mostrar) {
    if (p != NULL) {
        mostrarInfos(p, opcao2, mostrar);

        if (opcao2 == 'S') {
            pant->proximo = p->proximo;
            delete p;
            cout << "Exclusao confirmada!" << endl;
        } else {
            cout << "Exclusao nao realizada" << endl;
            return;
        }
    } else {
        if (mostrar == true)
            cout << "Produto nao encontrado" << endl;
    }
}

void exclusao_nome(Produto *p, string produto, Produto **lista) {
    bool mostrar = true;
    Produto *pant = NULL;
    char opcao2;

    if (p->nome == produto)
        exclusao_aux1(p, lista, opcao2, mostrar);

    pant = *lista;
    p = p->proximo;
    while (p != NULL and p->nome != produto) {
        pant = p;
        p = p->proximo;
    }

    exclusao_aux2(p, lista, opcao2, pant, mostrar);
}

void exclusao_codigo(Produto *p, int codigo, Produto **lista) {
    bool mostrar = true;
    Produto *pant = NULL;
    char opcao2;

    if (p->codigo == codigo) {
        cin.ignore();
        exclusao_aux1(p, lista, opcao2, mostrar);
    }

    pant = *lista;
    p = p->proximo;
    while (p != NULL and p->codigo != codigo) {
        pant = p;
        p = p->proximo;
    }

    exclusao_aux2(p, lista, opcao2, pant, mostrar);
}

// --------------- Relatorio Estoque --------------- //
void relatorio_estoque(Produto *lista) {
    Produto *p = lista;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else {
        while (p != NULL) {
            cout << "-------------------------" << endl;
            cout << "Nome: " << p->nome << endl;
            cout << "Codigo: " << p->codigo << endl;
            cout << "Preco: R$" << p->preco << endl;
            cout << "Quantidade no estoque: " << p->q_estoque << " unid." << endl;
            p = p->proximo;
        }
    }
}

// --------------- Relatorio Vendas --------------- //
void relatorio_vendas(Produto *lista) {
    Produto *p = lista;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else {
        while (p != NULL) {
            cout << "-------------------------" << endl;
            cout << "Codigo: " << p->codigo << endl;
            cout << "Quantidade vendida: " << p->q_vendida << endl;
            cout << "Total da venda: R$" << p->q_vendida * p->preco << endl;
            p = p->proximo;
        }
    }
}

// ------------------   Vendas  ------------------ //
void vendas(Produto *lista) {
    int qtde, qtde_venda = 0, codigo;
    Produto *p = lista;
    char opcao2;

    if (lista == NULL) {
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
        return;
    }

    cout << "Informe o codigo do produto que deseja realizar a venda: ";
    do {
        cin >> codigo;
    } while (codigo <= 0);

    while (p != NULL and p->codigo != codigo) {
        p = p->proximo;
    }
    if (p != NULL) { // encontrou elemento
        if ((p->q_estoque - p->q_vendida) == 0) {
            cout << "Produto fora de estoque!" << endl;
            return;
        }

        do {
            cout << "Informe a quantidade do produto '" << p->nome << "' vendidos(as): ";
            cin >> qtde;
        } while (qtde < 1);

        if (qtde > (p->q_estoque - p->q_vendida)) {
            cout << "Quantidade de produtos insuficiente." << endl;
            cout << "Quantidade de produtos no estoque: " << p->q_estoque - p->q_vendida << endl;
            qtde_venda = (p->q_estoque - p->q_vendida);
        } else {
            qtde_venda = qtde;
            cout << "Quantidade de produtos " << p->nome << " que irao ser vendidos: " << qtde_venda << endl;
            cout << "Preco de venda unitario do produto: R$ " << p->preco << endl;
            cout << "Preco total da venda: R$ " << p->preco * qtde_venda << endl;
        }

        do {
            cout << "Confirmar venda?: S(sim) / N(nao)";
            cin.ignore();
            opcao2 = toupper(cin.get());
            if (opcao2 != 'S' and opcao2 != 'N')
                cout << "opcao invalida!" << endl;
        } while (opcao2 != 'S' and opcao2 != 'N');

        if (opcao2 == 'S') {
            p->q_vendida += qtde_venda;
            cout << "Venda realizada!" << endl;
        } else
            cout << "Venda nao realizada!" << endl;

        return;
    }
    cout << "Produto inexistente" << endl;
}