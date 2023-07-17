#include <iostream> 
#include <string>   
#include <vector>   

using namespace std; 

// Declaracão da classe abstrata IProduto, que define a interface com a funcão calcularTotalItem().
class IProduto {
public:
    virtual double calcularTotalItem() const = 0; // Funcão virtual pura que será implementada nas classes derivadas.
};

// Declaracão da classe base Produto, com atributos nome e valor.
class Produto {
protected:
    string nome;   // Atributo que armazena o nome do produto.
    double valor;  // Atributo que armazena o valor do produto.

public:
    Produto(string nome, double valor) // Construtor da classe Produto.
        : nome(nome), valor(valor) {}  // Inicializacão dos atributos nome e valor.

    double getValor() const {   // Funcão que retorna o valor do produto.
        return valor;
    }

    string getNome() const {   // Funcão que retorna o nome do produto.
        return nome;
    }
};

// Declaracão da classe ProdutoEstoque, que representa um produto em estoque. Ela herda de Produto e implementa IProduto.
class ProdutoEstoque : public Produto, public IProduto {
private:
    int quantidade; // Atributo que armazena a quantidade em estoque.

public:
    ProdutoEstoque(string nome, double valor, int quantidade) // Construtor da classe ProdutoEstoque.
        : Produto(nome, valor), quantidade(quantidade) {}    // Inicializacão dos atributos nome, valor e quantidade.

    int getQuantidade() const {   // Funcão que retorna a quantidade em estoque do produto.
        return quantidade;
    }

    void setQuantidade(int novaQuantidade) {   // Funcão que define uma nova quantidade em estoque do produto.
        quantidade = novaQuantidade;
    }

    double calcularTotalItem() const override {   // Implementacão da funcão calcularTotalItem da interface IProduto.
        return valor * quantidade;   // Retorna o valor total do produto multiplicado pela quantidade em estoque.
    }
};

// Declaracão da classe ProdutoCarrinho, que representa um produto no carrinho de compras. Ela herda de Produto e implementa IProduto.
class ProdutoCarrinho : public Produto, public IProduto {
private:
    int quantidade; // Atributo que armazena a quantidade do produto no carrinho.

public:
    ProdutoCarrinho(string nome, double valor, int quantidade) // Construtor da classe ProdutoCarrinho.
        : Produto(nome, valor), quantidade(quantidade) {}    // Inicializacão dos atributos nome, valor e quantidade.

    int getQuantidade() const {   // Funcão que retorna a quantidade do produto no carrinho.
        return quantidade;
    }

    double calcularTotalItem() const override {   // Implementacão da funcão calcularTotalItem da interface IProduto.
        return valor * quantidade;   // Retorna o valor total do produto multiplicado pela quantidade no carrinho.
    }
};

// Declaracão da classe EstoqueProdutos, que representa o estoque de produtos, com um vetor de ProdutoEstoque.
class EstoqueProdutos {
private:
    vector<ProdutoEstoque> estoque; // Vetor que armazena os produtos em estoque.

public:
    void adicionaProduto(const ProdutoEstoque& produto) {   // Funcão para adicionar um produto ao estoque.
        estoque.push_back(produto);    // Adiciona o produto no final do vetor estoque.
    }

    ProdutoEstoque* buscaProduto(const string& nome) {   // Funcão para buscar um produto pelo nome no estoque.
        for (auto& produto : estoque) {    // Percorre o vetor de produtos em estoque.
            if (produto.getNome() == nome) {   // Se o nome do produto atual for igual ao nome buscado.
                return &produto;    // Retorna um ponteiro para o produto encontrado.
            }
        }
        return nullptr;   // Caso não encontre o produto, retorna nullptr (ponteiro nulo).
    }
};

// Declaracão da classe CarrinhoCompra, que representa o carrinho de compras, com um vetor de ProdutoCarrinho.
class CarrinhoCompra {
private:
    vector<ProdutoCarrinho> carrinho; // Vetor que armazena os produtos no carrinho.

public:
    void adicionaItem(EstoqueProdutos& estoque, const string& nome, int quantidade) {   // Funcão para adicionar um item ao carrinho a partir do estoque.
        ProdutoEstoque* produtoEstoque = estoque.buscaProduto(nome);    // Busca o produto no estoque pelo nome.

        if (produtoEstoque != nullptr) {   // Se o produto estiver disponível no estoque.
            if (produtoEstoque->getQuantidade() >= quantidade) {    // Se a quantidade desejada estiver disponível no estoque.
                carrinho.push_back(ProdutoCarrinho(nome, produtoEstoque->getValor(), quantidade));   // Adiciona o produto ao carrinho.
            } else {
                cout << "Quantidade insuficiente em estoque." << endl;   // Caso não haja quantidade suficiente no estoque, exibe mensagem de erro.
            }
        } else {
            cout << "Produto nao encontrado no estoque." << endl;   // Caso o produto não seja encontrado no estoque, exibe mensagem de erro.
        }
    }

    void finalizaCompra(EstoqueProdutos& estoque) {   // Funcão para finalizar a compra, atualizando o estoque e limpando o carrinho.
        for (const auto& item : carrinho) {   // Percorre o carrinho de compras.
            ProdutoEstoque* produtoEstoque = estoque.buscaProduto(item.getNome());   // Busca o produto no estoque pelo nome.

            if (produtoEstoque != nullptr) {   // Se o produto estiver disponível no estoque.
                int novaQuantidade = produtoEstoque->getQuantidade() - item.getQuantidade();   // Calcula a nova quantidade em estoque.
                produtoEstoque->setQuantidade(novaQuantidade);   // Atualiza a quantidade em estoque do produto.
            }
        }
        carrinho.clear();   // Limpa o carrinho, pois a compra foi finalizada.
    }

    double calculaTotal() const {   // Funcão para calcular o total da compra somando os valores dos itens no carrinho.
        double total = 0.0;   // Variável para armazenar o total da compra, inicializada em 0.

        for (const auto& item : carrinho) {   // Percorre o carrinho de compras.
            total += item.calcularTotalItem();   // Adiciona o valor total do item ao total da compra.
        }

        return total;   // Retorna o valor total da compra.
    }
};

// Funcão principal (main) onde o programa comeca sua execucão.
int main() {
    // Criacão do estoque e adicão de alguns produtos.
    EstoqueProdutos estoque;
    estoque.adicionaProduto(ProdutoEstoque("monitor", 500, 50));
    estoque.adicionaProduto(ProdutoEstoque("telefone", 150, 30));
	 estoque.adicionaProduto(ProdutoEstoque("teclado", 70, 50));
    estoque.adicionaProduto(ProdutoEstoque("telefone", 50, 30));
		
    // Criacão do carrinho de compras.
    CarrinhoCompra carrinho;

    int opcao;
    do {
        // Menu para interacão com o usuário.
        cout << "      ===== Menu =====" << endl;
        cout << "1. Adicionar produto ao carrinho" << endl;
        cout << "2. Calcular total da compra" << endl;
        cout << "3. Finalizar Compra" << endl;
        cout << "4. Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cout << "\n================================" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1: {
                // Opcão para adicionar produto ao carrinho.
                string nomeProduto;
                int quantidade;

                cout << "Digite o nome do produto: ";
                cin.ignore(); // Para limpar o buffer do teclado antes de ler a string.
                getline(cin, nomeProduto);

                cout << "Digite a quantidade: ";
                cin >> quantidade;

                carrinho.adicionaItem(estoque, nomeProduto, quantidade);
                break;
            }
            case 2: {
                // Opcão para calcular o total da compra.
                double total = carrinho.calculaTotal();
                cout << "\nTotal da compra: R$" << total << endl;
                break;
            }
            case 3:
                // Opcão para finalizar a compra, atualizando o estoque.
                carrinho.finalizaCompra(estoque);
                cout << "\n\nCompra finalizada com sucesso!\n\n";
                break;
            case 4:
                // Opcão para sair do programa.
                cout << "\nSaindo . . .";
                break;
            default:
                cout << "\nOpcão inválida. Tente novamente." << endl;
                break;
        }

        cout << endl;
    } while (opcao != 4);

    return 0;
}

