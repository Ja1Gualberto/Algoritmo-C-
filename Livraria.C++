#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

#define MAX_LIVROS 10
#define MAX_USUARIOS 10
#define MAX_EMPRESTIMOS 3
#define PRAZO_DEVOLUCAO 15

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct Livro {
    int id;
    time_t emprestimo_data;
    bool disponivel;
    string nome_livro;
    string autor;
    double preco;
};

struct Usuario {
    int id;
    string cpf;
    vector<int> livros_emprestados;
    int num_livros_emprestado;
    string nome_usuario;
    time_t datas_emprestimos;
};

vector<Livro> livros;
vector<Usuario> usuarios;

void cadastrarLivro() {
    if (livros.size() < MAX_LIVROS) {
        Livro novoLivro;
        novoLivro.id = livros.size() + 1;
        
        cout << "Informe o nome do livro: ";
        cin >> novoLivro.nome_livro;
        cout << "Informe o valor do livro: ";
        cin >> novoLivro.preco;
        cout << "Informe o nome do autor: ";
        cin >> novoLivro.autor;

        novoLivro.disponivel = true;
        time(&novoLivro.emprestimo_data);
        livros.push_back(novoLivro);

        cout << "Cadastro realizado\n";
    } else {
        cout << "Limite maximo de livros atingido\n";
    }
}

void cadastrarUsuario() {
    if (usuarios.size() < MAX_USUARIOS) {
        Usuario novoUsuario;
        novoUsuario.id = usuarios.size() + 1;

        cout << "Informe o nome do usuario: ";
        cin >> novoUsuario.nome_usuario;

        novoUsuario.num_livros_emprestado = 0;
        cout << "Informe o CPF do usuario: ";
        cin >> novoUsuario.cpf;

        usuarios.push_back(novoUsuario);
        cout << "Cadastro realizado\n";
    } else {
        cout << "Limite de usuarios atingido\n";
    }
}

void emprestimoLivros() {
    cout << "Livros disponiveis no estoque:\n";
    for (const auto& livro : livros) {
        if (livro.disponivel) {
            cout << livro.id << " - " << livro.nome_livro << "\n";
        }
    }

    int idLivro, idUsuario;
    cout << "Informe o ID do livro: ";
    cin >> idLivro;
    cout << "Informe o ID do usuario: ";
    cin >> idUsuario;

    if (idLivro < 1 || idLivro > livros.size() || !livros[idLivro - 1].disponivel) {
        cout << "Livro indisponivel no momento ou ID invalido\n";
        return;
    }
    if (usuarios[idUsuario - 1].num_livros_emprestado >= MAX_EMPRESTIMOS) {
        cout << "Você atingiu o número máximo de empréstimos\n";
        return;
    }

    livros[idLivro - 1].disponivel = false;
    usuarios[idUsuario - 1].livros_emprestados.push_back(idLivro);
    time(&usuarios[idUsuario - 1].datas_emprestimos);
    usuarios[idUsuario - 1].num_livros_emprestado++;
    cout << "Livro emprestado!\n";
}

void mostrarLivrosDisponiveis() {
    cout << "Livros em estoque:\n";
    for (const auto& livro : livros) {
        if (livro.disponivel) {
            cout << livro.id << " - " << livro.nome_livro << " - " << livro.autor << " - " << livro.preco << "\n";
        }
    }
}

void mostrarUsuariosCadastrados() {
    cout << "Usuarios Cadastrados\n";
    for (const auto& usuario : usuarios) {
        cout << "ID: " << usuario.id << "\n";
        cout << "Nome: " << usuario.nome_usuario << "\n";
        cout << "CPF: " << usuario.cpf << "\n";
        cout << "Número de livros emprestados: " << usuario.num_livros_emprestado << "\n\n";
    }
}

void atualizarLivro() {
    int idLivro;
    cout << "Qual é o ID do livro que deseja alterar: ";
    cin >> idLivro;

    for (auto& livro : livros) {
        if (livro.id == idLivro) {
            cout << "Informe o novo nome do livro: ";
            cin >> livro.nome_livro;
            cout << "Informe o novo nome do autor: ";
            cin >> livro.autor;
            cout << "Informe o novo valor do livro: ";
            cin >> livro.preco;
            cout << "Livro atualizado\n";
            return;
        }
    }
    cout << "Livro não encontrado\n";
}

void atualizarUsuario() {
    int idUsuario;
    cout << "Qual é o ID do usuário: ";
    cin >> idUsuario;

    for (auto& usuario : usuarios) {
        if (usuario.id == idUsuario) {
            cout << "Informe o novo nome do usuário: ";
            cin >> usuario.nome_usuario;
            cout << "Informe o novo CPF do usuário: ";
            cin >> usuario.cpf;
            return;
        }
    }
    cout << "Usuário não encontrado\n";
}

void excluirLivro() {
    int idLivro;
    cout << "Qual é o ID do livro que deseja excluir: ";
    cin >> idLivro;

    if (idLivro < 1 || idLivro > livros.size() || !livros[idLivro - 1].disponivel) {
        cout << "Esse livro não existe\n";
        return;
    }
    livros.erase(livros.begin() + idLivro - 1);
    for (int i = idLivro - 1; i < livros.size(); i++) {
        livros[i].id = i + 1;
    }
    cout << "Livro excluído com sucesso\n";
}

void excluirUsuario() {
    int idUsuario;
    cout << "Qual é o ID do usuário que deseja excluir: ";
    cin >> idUsuario;

    if (idUsuario < 1 || idUsuario > usuarios.size()) {
        cout << "Esse usuário não existe\n";
        return;
    }
    usuarios.erase(usuarios.begin() + idUsuario - 1);
    for (int i = idUsuario - 1; i < usuarios.size(); i++) {
        usuarios[i].id = i + 1;
    }
    cout << "Usuário excluído com sucesso\n";
}

void organizarLivrosPorNome() {
    std::sort(livros.begin(), livros.end(), [](const Livro& a, const Livro& b) {
        return a.nome_livro < b.nome_livro;
    });
    cout << "Livros organizados por nome:\n";
    for (const auto& livro : livros) {
        cout << livro.id << " - " << livro.nome_livro << " - " << livro.autor << " - " << livro.preco << "\n";
    }
}

void organizarLivrosPorID() {
    std::sort(livros.begin(), livros.end(), [](const Livro& a, const Livro& b) {
        return a.id < b.id;
    });
    cout << "Livros organizados por ID:\n";
    for (const auto& livro : livros) {
        cout << livro.id << " - " << livro.nome_livro << " - " << livro.autor << " - " << livro.preco << "\n";
    }
}

int main() {
    int op1, op2, op3;
    do {
        cout << "--------Menu-Livraria--------\n";
        cout << "01-Adicionar\n02-Visualizar\n03-Alterar\n0-Sair\n";
        cin >> op1;
        switch (op1) {
            case 1:
                do {
                    cout << "--------Menu-Adicionar--------\n";
                    cout << "01-Cadastrar Livros\n02-Cadastrar Usuario\n03-Emprestimo de Livro\n04-Devolver Livros\n0-Voltar\n";
                    cin >> op2;
                    switch (op2) {
                        case 1:
                            system("cls");
                            cadastrarLivro();
                            break;
                        case 2:
                            system("cls");
                            cadastrarUsuario();
                            break;
                        case 3:
                            system("cls");
                            emprestimoLivros();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opção invalida\n";
                            break;
                    }
                } while (op2 != 0);
                break;
            case 2:
                do {
                    cout << "--------Menu-Visualizar--------\n";
                    cout << "01-Consultar Livros Disponiveis\n02-Consultar Usuario\n03-Organizar Livros por Nome\n04-Organizar Livros por ID\n0-Voltar\n";
                    cin >> op2;
                    switch (op2) {
                        case 1:
                            system("cls");
                            mostrarLivrosDisponiveis();
                            break;
                        case 2:
                            system("cls");
                            mostrarUsuariosCadastrados();
                            break;
                        case 3:
                            system("cls");
                            organizarLivrosPorNome();
                            break;
                        case 4:
                            system("cls");
                            organizarLivrosPorID();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opção invalida\n";
                            break;
                    }
                } while (op2 != 0);
                break;
            case 3:
                do {
                    cout << "--------Menu-Alterar--------\n";
                    cout << "01-Alterar Livro\n02-Alterar Usuario\n03-Excluir Livro\n04-Excluir Usuario\n0-Voltar\n";
                    cin >> op3;
                    switch (op3) {
                        case 1:
                            system("cls");
                            atualizarLivro();
                            break;
                        case 2:
                            system("cls");
                            atualizarUsuario();
                            break;
                        case 3:
                            system("cls");
                            excluirLivro();
                            break;
                        case 4:
                            system("cls");
                            excluirUsuario();
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opção invalida\n";
                            break;
                    }
                } while (op3 != 0);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção invalida\n";
                break;
        }
    } while (op1 != 0);

    return 0;
}
