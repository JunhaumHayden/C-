em C++ você usa template <typename T> sempre que precisar criar código genérico que funcione com diferentes tipos de dados.

No entanto, há algumas variações e boas práticas ao trabalhar com templates. Vou te mostrar quando e como usá-los corretamente.

1️⃣ Templates Básicos: Tipo Genérico T

Se você quer que apenas um tipo de dado seja genérico (por exemplo, uma classe ou função que funcione para int, double, std::string, etc.), use:

template <typename T>
class Exemplo {
private:
    T valor;
public:
    Exemplo(T v) : valor(v) {}  // Construtor genérico
    void mostrar() { std::cout << "Valor: " << valor << std::endl; }
};
✅ Agora você pode instanciar a classe para qualquer tipo de dado:

Exemplo<int> obj1(10);
Exemplo<double> obj2(3.14);
Exemplo<std::string> obj3("Teste");

obj1.mostrar(); // Valor: 10
obj2.mostrar(); // Valor: 3.14
obj3.mostrar(); // Valor: Teste
2️⃣ Templates com Múltiplos Parâmetros

Se precisar de mais de um tipo genérico, basta adicionar mais parâmetros typename:

template <typename T1, typename T2>
class Par {
private:
    T1 primeiro;
    T2 segundo;
public:
    Par(T1 p, T2 s) : primeiro(p), segundo(s) {}
    void mostrar() { std::cout << primeiro << " - " << segundo << std::endl; }
};
✅ Agora podemos criar pares de diferentes tipos:

Par<int, double> p1(10, 3.14);
Par<std::string, char> p2("Letra", 'A');

p1.mostrar();  // 10 - 3.14
p2.mostrar();  // Letra - A
3️⃣ Templates com Parâmetros Não-Tipo (int, size_t, etc.)

Se precisar de um valor fixo, como tamanho de um array, use um parâmetro de template numérico:

template <typename T, int N>
class Vetor {
private:
    T elementos[N];
public:
    void preencher(T valor) {
        for (int i = 0; i < N; ++i) elementos[i] = valor;
    }
    void mostrar() {
        for (int i = 0; i < N; ++i) std::cout << elementos[i] << " ";
        std::cout << std::endl;
    }
};
✅ Agora o tamanho é definido na instância:

Vetor<int, 5> v1;
v1.preencher(7);
v1.mostrar();  // 7 7 7 7 7
📌 Importante: O parâmetro N precisa ser uma constante conhecida em tempo de compilação.

4️⃣ Templates de Função

Se precisar de uma função genérica, basta usar template antes da função:

template <typename T>
T soma(T a, T b) {
    return a + b;
}
✅ Chamada automática com diferentes tipos:

std::cout << soma(3, 5) << std::endl;       // 8
std::cout << soma(2.5, 1.5) << std::endl;   // 4.0
std::cout << soma<std::string>("A", "B") << std::endl; // AB
📌 Resumo: Quando usar template?

Cenário	Exemplo
Classe genérica	template <typename T>
Múltiplos tipos genéricos	template <typename T1, typename T2>
Tamanho fixo como parâmetro	template <typename T, int N>
Funções genéricas	template <typename T> T soma(T a, T b);
📌 Use template sempre que quiser reusar código para diferentes tipos sem duplicação. Isso torna seu código mais flexível e modular.