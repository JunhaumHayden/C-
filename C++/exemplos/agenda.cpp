#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Contato {
    string nome;
    string telefone;
    string email;
};

void adicionarContato(vector<Contato>& agenda) {
    Contato novo;
    cout << "Nome: ";
    getline(cin, novo.nome);
    cout << "Telefone: ";
    getline(cin, novo.telefone);
    cout << "Email: ";
    getline(cin, novo.email);
    agenda.push_back(novo);
    cout << "Contato adicionado!\n";
}

void listarContatos(const vector<Contato>& agenda) {
    cout << "\nLista de contatos:\n";
    for (const auto& contato : agenda) {
        cout << "Nome: " << contato.nome << "\nTelefone: " << contato.telefone
             << "\nEmail: " << contato.email << "\n---\n";
    }
}

void buscarContato(const vector<Contato>& agenda) {
    string busca;
    cout << "Digite o nome para busca: ";
    getline(cin, busca);
    bool encontrado = false;
    for (const auto& contato : agenda) {
        if (contato.nome.find(busca) != string::npos) {
            cout << "Encontrado: " << contato.nome << " - " << contato.telefone << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "Contato não encontrado.\n";
}

int main() {
    vector<Contato> agenda;
    int opcao;

    do {
        cout << "\n1. Adicionar Contato\n2. Listar Contatos\n3. Buscar Contato\n4. Sair\nEscolha: ";
        cin >> opcao;
        cin.ignore();  // Limpa o buffer

        switch (opcao) {
        case 1: adicionarContato(agenda); break;
        case 2: listarContatos(agenda); break;
        case 3: buscarContato(agenda); break;
        case 4: cout << "Saindo...\n"; break;
        default: cout << "Opção inválida.\n";
        }
    } while (opcao != 4);

    return 0;
}
