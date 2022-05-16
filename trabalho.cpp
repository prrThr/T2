#include <cstdlib>
#include <ctime>
#include <iostream>
// Adicionar os system("cls"), cin.ignore() e os "enters"
// Fazer os teste dos while's
// Tazer a subrotina de ordenação
using namespace std;

typedef struct Nodo {
    string nome;
    int codigo, q_estoque, q_vendida = 0;
    float preco;
    struct Nodo *proximo;
} Produto;

int funcao_opcao();
void mostrarInfos(Produto, char &, Produto **);
void continuar();
void inclusao(Produto **);
// void ordenar(string, Produto **); //! ARRUMAR
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
void mostrarInfos(Produto *p, char &opcao2, Produto **lista) {
    cout << "Elemento encontrado!" << endl;
    cout << "Nome: " << p->nome << endl;
    cout << "Codigo: " << p->codigo << endl;
    cout << "Preco: " << p->preco << endl;
    cout << "Quantidade no estoque: " << p->q_estoque << endl;
    cout << "Quantidade vendida:" << p->q_vendida << endl;
    do {
        cout << "Confirma exclusao: S(sim) / N(nao)?" << endl; // botar pra maiusculo
        cin >> opcao2;
        if (opcao2 != 's' and opcao2 != 'n')
            cout << "opcao invalida!" << endl;
    } while (opcao2 != 's' and opcao2 != 'n');
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

// ---------- Incluir ---------- //
void inclusao(Produto **lista) {
    Produto *p, *p_aux, *procurar;
    string addProduto;
    p = new Produto; // Aloca memoria para novo nodo

    if (p == NULL) {
        cout << "Sem memoria";
        cin.get();
        exit(1);
    }

    cin.ignore();
    cout << "Insira o nome do produto: ";
    getline(cin, addProduto);

    procurar = *lista;
    while (procurar != NULL) {
        if (procurar->nome == addProduto) {
            cout << "Produto ja existente! " << endl;
            return;
        }
        procurar = procurar->proximo;
    }
    p->nome = addProduto;

    // ordenar(addProduto, lista);

    srand(time(NULL));
    p->codigo = rand() % 100 + 1;
    cout << "Codigo do produto: " << p->codigo << endl;

    do {
        cout << "Quantidade de unidades no estoque: ";
        cin >> p->q_estoque;
    } while (p->q_estoque <= 0);

    do {
        cout << "Preco de venda: ";
        cin >> p->preco;
    } while (p->preco <= 0);

    p->proximo = NULL;
    if (*lista == NULL) { // incluir o primeiro

        *lista = p; // Conecta o novo nodo ao inicio da lista
        cout << "Inclusao confirmada!" << endl;
        return;
    }

    p_aux = *lista; // a partir do primeiro
    while (p_aux->proximo != NULL) {
        p_aux = p_aux->proximo;
    }
    p_aux->proximo = p; // inclui novo nodo, sem necessidade alterar a lista
    cout << "Inclusao confirmada!" << endl;
}

// ---------- Ordenar  ---------- //
/* void ordenar(string nome, Produto **lista) { //! ARRUMAR
    Produto *p, *paux, *aux;
    if (lista == NULL)
        return;
    while (p != NULL and nome[0] < p->nome[0]) {
        p = p->proximo;
    }
    if (p != NULL) // encontrou elemento
    {
        if (p->nome[0] == nome[0]) {
            for (int i = 1; i < nome.size(); i++)
                if (nome[i] > p->nome[i]) {
                    //*faz a alteração
                    paux->nome = nome;
                    aux = p;
                    p = paux;
                    paux = aux;
                    break;
                }
        }
        //*faz a alteração
        paux->nome = nome;
        aux = p;
        p = paux;
        paux = aux;
    }
    return;
}
 */

// ---------- Consulta ---------- //
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
    } while (codigo <= 0);
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

//---------- Liberar memória ---------- //
void destroilista(Produto **lista) {
    Produto *p;
    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->proximo;
        delete p;
    }
}

//---------- Excluir ---------- //
void exclusao(Produto **lista) {
    Produto *p;
    p = *lista;
    string produto;
    int codigo, opcao;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else { // Se a lista não esta vazia
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
            } while (codigo <= 0);
            exclusao_codigo(p, codigo, lista);
        }

        else {
            cout << "informe o nome do produto que deseja excluir: ";
            cin.ignore();
            getline(cin, produto);
            exclusao_nome(p, produto, lista);
        }
    }
}

void exclusao_aux1(Produto *p, Produto **lista, char opcao2) {
    mostrarInfos(p, opcao2, lista);
    if (opcao2 == 's') {
        *lista = p->proximo; // exclusao do 1o nodo
        delete p;            // libera memória do nodo excluido
        cout << "exclusao confirmada!" << endl;
        return;
    } else
        cout << "Exclusao nao realizada" << endl;
    return;
}
void exclusao_aux2(Produto *p, Produto **lista, char opcao2, Produto *pant) {
    if (p != NULL) { // achou elemento pra excluir
        mostrarInfos(p, opcao2, lista);

        if (opcao2 == 's') {
            pant->proximo = p->proximo; // conecta nodos ant e post
            delete p;                   // libera memória do nodo excluido
            cout << "exclusao confirmada!" << endl;
        } else {
            cout << "Exclusao nao realizada" << endl;
            return;
        }
    } else
        cout << "Produto nao encontrado" << endl;
}

void exclusao_nome(Produto *p, string produto, Produto **lista) {
    Produto *pant = NULL;
    char opcao2;

    if (p->nome == produto)
        exclusao_aux1(p, lista, opcao2);

    pant = *lista;
    p = p->proximo; // tipo um i++
    while (p != NULL and p->nome != produto) {
        pant = p;
        p = p->proximo;
    }

    exclusao_aux2(p, lista, opcao2, pant);
}

void exclusao_codigo(Produto *p, int codigo, Produto **lista) {
    Produto *pant = NULL;
    char opcao2;

    if (p->codigo == codigo)
        exclusao_aux1(p, lista, opcao2);

    pant = *lista;
    p = p->proximo; // tipo um i++
    while (p != NULL and p->codigo != codigo) {
        pant = p;
        p = p->proximo;
    }

    exclusao_aux2(p, lista, opcao2, pant);
}

// ---------- Relatorio Estoque ---------- //
void relatorio_estoque(Produto *lista) {
    Produto *p = lista;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else { // se a lista nao esta vazia
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

// ---------- Relatorio Vendas ---------- //
void relatorio_vendas(Produto *lista) {
    Produto *p = lista;

    if (p == NULL)
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl;
    else { // se a lista nao esta vazia
        while (p != NULL) {
            cout << "-------------------------" << endl;
            cout << "Codigo: " << p->codigo << endl;
            cout << "Quantidade vendida: " << p->q_vendida << endl;
            cout << "Total da venda: R$" << p->q_vendida * p->preco << endl;
            p = p->proximo;
        }
    }
}

// ---------- Vendas ---------- //
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
            cout << "Confirmar venda?: S(sim) / N(nao)"; // botar pra maiusculo
            cin.ignore();
            cin.get(opcao2);
            if (opcao2 != 's' and opcao2 != 'n')
                cout << "opcao invalida!" << endl;
        } while (opcao2 != 's' and opcao2 != 'n');
        if (opcao2 == 's') {
            p->q_vendida += qtde_venda;
            cout << "Venda realizada!" << endl;
        } else
            cout << "Venda nao realizada!" << endl;

        return;
    }
    cout << "Produto inexistente" << endl;
}
