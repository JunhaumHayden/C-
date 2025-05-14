#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class Cenario {
  public:
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
    }
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
    string proxima_tag(string& texto, size_t& pos) {
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (pos < texto.length() && texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }
    string proximo_conteudo(string& texto, size_t& pos) {
        string txt = "";
        while (pos < texto.length() && texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (pos < texto.length() && texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }
    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
            if (tag.empty()) break;
        }
        return proximo_conteudo(texto, pos);
    }
    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};
// Função para validar o XML
bool validar_xml(string& texto) {
    stack<string> tag_stack;
    size_t pos = 0;

    while (pos < texto.length()) {
        if (texto[pos] != '<') {
            pos++;
            continue;
        }

        pos++;
        if (pos >= texto.length()) return false;

        bool is_closing = false;
        if (texto[pos] == '/') {
            is_closing = true;
            pos++;
        }

        string tag_name;
        while (pos < texto.length() && texto[pos] != '>') {
            tag_name += texto[pos];
            pos++;
        }
        pos++;

        if (tag_name.empty()) return false;

        if (is_closing) {
            if (tag_stack.empty() || tag_stack.top() != tag_name) {
                return false;
            }
            tag_stack.pop();
        } else {
            tag_stack.push(tag_name);
        }
    }

    return tag_stack.empty();
}
// Função para calcular a área a ser limpa
size_t calcular_area_limpa(const Cenario& cenario) {
    if (cenario.matriz.empty() || cenario.altura == 0 || cenario.largura == 0) {
        return 0;
    }
    // Verificar se a posição inicial é válida
    if (cenario.x >= cenario.altura || cenario.y >= cenario.largura) {
        return 0;
    }
    // Converter a matriz string para uma matriz 2D
    vector<vector<int>> matriz(cenario.altura, vector<int>(cenario.largura, 0));
    for (size_t i = 0; i < cenario.altura; i++) {
        for (size_t j = 0; j < cenario.largura; j++) {
            size_t index = i * cenario.largura + j;
            if (index < cenario.matriz.size()) {
                matriz[i][j] = cenario.matriz[index] - '0';
            }
        }
    }
    // Verificar se a posição inicial é área limpa
    if (matriz[cenario.x][cenario.y] != 1) {
        return 0;
    }
    // Inicializar estruturas para BFS
    vector<vector<bool>> visitado(cenario.altura, vector<bool>(cenario.largura, false));
    queue<pair<size_t, size_t>> fila;
    size_t area = 0;
    // Adicionar posição inicial
    fila.push(make_pair(cenario.x, cenario.y));
    visitado[cenario.x][cenario.y] = true;
    // Direções para vizinhança-4
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    while (!fila.empty()) {
        pair<size_t, size_t> atual = fila.front();
        fila.pop();
        size_t x = atual.first;
        size_t y = atual.second;
        area++;

        for (int i = 0; i < 4; i++) {
            size_t nx = x + dx[i];
            size_t ny = y + dy[i];
            // Verificar limites e se é uma célula válida (1) e não visitada
            if (nx < cenario.altura && ny < cenario.largura &&
                matriz[nx][ny] == 1 && !visitado[nx][ny]) {
                visitado[nx][ny] = true;
                fila.push(make_pair(nx, ny));
            }
        }
    }

    return area;
}

int main() {
    string filename;
    std::cin >> filename;
    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }
    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }
    // Parte 1: Validar XML
    if (!validar_xml(texto)) {
        cout << "erro" << endl;
        return 0;
    }
    // Parte 2: Processar cenários e calcular áreas
    vector<Cenario> cenarios;
    size_t pos = 0;
    // Encontrar todos os cenários no arquivo
    while (pos < texto.length()) {
        size_t inicio_cenario = texto.find("<cenario>", pos);
        if (inicio_cenario == string::npos) break;

        Cenario c(texto, inicio_cenario);
        cenarios.push_back(c);
        pos = c.indice_final;
    }
    // Calcular e imprimir a área para cada cenário
    for (const auto& cenario : cenarios) {
        cout << cenario.nome << " " << calcular_area_limpa(cenario) << endl;
    }

    return 0;
}