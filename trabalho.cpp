#include <cstdlib>
#include <ctime>
#include <iostream>
// temos que adicionar aquele negocio do enter para ele mostrar certinho na tela as coisas e nao ficar limpando
// eu adicionei as funcoes de exclusao mas acho que nao esta certo. também mudei a de consulta, agora ela procura pelo codigo.
// fechar lista
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
void exclusao(Produto **);                         // nao esta funcionando
void exclusao_nome(Produto *, string, Produto **); // nao esta funcionando
void exclusao_codigo(Produto *, int, Produto **);  // nao esta funcionando

int main() {
    Produto *lista = NULL, p_aux;
    int opcao;
    do {

        opcao = funcao_opcao();
        // system("cls");

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
            /*
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

        // system("cls");
    } while (opcao != 7);

    destroilista(&lista);
    return 0;
}

int funcao_opcao() {
    int escolha;
    do {
        // system("cls");
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

    procurar = *lista;
    while (procurar != NULL) {
        if (procurar->nome == addProduto) {
            cout << "Produto ja existente! ";
            return;
        }
        procurar = procurar->proximo;
    }

    p->nome = addProduto;
    srand(time(NULL));
    p->codigo = rand() % 100 + 1;
    cout << "Codigo do produto: " << p->codigo << endl;
    cout << "Quantidade de unidades no estoque: ";
    cin >> p->q_estoque;
    cout << "Preco de venda: ";
    cin >> p->preco;

    p->proximo = NULL;
    if (*lista == NULL) {
        *lista = p; // Conecta o novo nodo ao inicio da lista
        cout << "Inclusao confirmada!" << endl;
        return;
    }
    p_aux = *lista;
    while (p_aux->proximo != NULL) {
        p_aux = p_aux->proximo;
    }
    p_aux->proximo = p; // inclui novo nodo, sem necessidade alterar ptr_lista
    cout << "Inclusao confirmada!" << endl;
}

// ---------- Consulta ---------- //
void consulta(Produto *lista) {
    int codigo;
    char continuar;
    Produto *p = lista;
    if (lista == NULL) {
        cout << "Nenhum produto cadastrado. Voltando ao menu..." << endl; // fazer aquilo de apertar enter para continuar, para a mensagem aparecer na tela
        return;
    }
    cout << "Informe o codigo do produto que deseja consultar: ";
    cin >> codigo;
    while (lista != NULL and p->codigo != codigo) {
        p = p->proximo;
    }
    if (p != NULL) // encontrou elemento
    {
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
    } else
        cout << "Produto inexistente" << endl;
    do {
        cout << "Pressione ENTER para continuar: " << endl;
        continuar = cin.get();
    } while (continuar != '\n');
}

//---------- Liberar memória ---------- //
void destroilista(Produto **lista) // ponteiro de ponteiro
{
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
    else // se a lista não esta vazia
    {
        do {
            cout << "Deseja procurar pelo codigo ou nome do produto?" << endl;
            cout << "1. Codigo" << endl;
            cout << "2. Nome" << endl;
            cin >> opcao;
        } while (opcao < 1 or opcao > 2);
        if (opcao == 1) {
            cout << "informe o codigo do produto que deseja excluir: ";
            // verificar se o produto existe
            cin >> codigo;
            exclusao_codigo(p, codigo, lista);
        } else {
            cout << "informe o nome do produto que deseja excluir: ";
            // verificar se o produto existe
            getline(cin, produto);
            exclusao_nome(p, produto, lista);
        }
    }
}
void exclusao_nome(Produto *p, string produto, Produto **lista) {
    Produto *pant = NULL;
    char opcao2;

    if (p->nome == produto) {
        cout << "Elemento encontrado!" << endl;
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
        do {
            cout << "Confirma exclusao: S(sim) / N(nao)?" << endl;
            opcao2 = toupper(cin.get());
        } while (opcao2 != 'S' or opcao2 != 'N');
        if (opcao2 == 'S') {
            *lista = p->proximo; // exclusao do 1o nodo
            delete p;            // libera memória do nodo excluido
            cout << "exclusao confirmada!" << endl;
            return;
        } else
            cout << "Exclusao nao realizada" << endl;
        return;
    }
    pant = *lista;
    p = p->proximo; // tipo um i++
    while (p != NULL and p->nome != produto) {
        pant = p;
        p = p->proximo;
    }
    if (p != NULL) // achou elemento pra excluir
    {
        cout << "Elemento encontrado!" << endl;
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
        do {
            cout << "Confirma exclusao: S(sim) / N(nao)?" << endl;
            opcao2 = toupper(cin.get());
        } while (opcao2 != 'S' or opcao2 != 'N');
        if (opcao2 == 'S') {
            pant->proximo = p->proximo; // conecta nodos ant e post
            delete p;                   // libera memória do nodo excluido
            cout << "exclusao confirmada!" << endl;
        } else
            cout << "Exclusao nao realizada" << endl;
    }
}

void exclusao_codigo(Produto *p, int codigo, Produto **lista) {
    Produto *pant = NULL;
    char opcao2;

    if (p->codigo == codigo) {
        cout << "Elemento encontrado!" << endl;
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
        do {
            cout << "Confirma exclusao: S(sim) / N(nao)?" << endl;
            opcao2 = toupper(cin.get());
        } while (opcao2 != 'S' or opcao2 != 'N');
        if (opcao2 == 'S') {
            *lista = p->proximo; // exclusao do 1o nodo
            delete p;            // libera memória do nodo excluido
            cout << "exclusao confirmada!" << endl;
            return;
        } else
            cout << "Exclusao nao realizada" << endl;
        return;
    }
    pant = *lista;
    p = p->proximo; // tipo um i++
    while (p != NULL and p->codigo != codigo) {
        pant = p;
        p = p->proximo;
    }
    if (p != NULL) // achou elemento pra excluir
    {
        cout << "Elemento encontrado!" << endl;
        cout << "Nome: " << p->nome << endl;
        cout << "Codigo: " << p->codigo << endl;
        cout << "Preco: " << p->preco << endl;
        cout << "Quantidade no estoque: " << p->q_estoque << endl;
        cout << "Quantidade vendida:" << p->q_vendida << endl;
        do {
            cout << "Confirma exclusao: S(sim) / N(nao)?" << endl;
            opcao2 = toupper(cin.get());
        } while (opcao2 != 'S' or opcao2 != 'N');
        if (opcao2 == 'S') {
            pant->proximo = p->proximo; // conecta nodos ant e post
            delete p;                   // libera memória do nodo excluido
            cout << "exclusao confirmada!" << endl;
        } else
            cout << "Exclusao nao realizada" << endl;
    }
}