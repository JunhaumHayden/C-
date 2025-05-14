#include <iostream>
using namespace std;

// Para acessar namespace deve-se chamar o seu nome.
    // Declaracao de um namespace
    namespace geometria {
        const double PI = 3.14159265358979323846;
        double areaCirculo(double raio) {
            return PI * raio * raio;
        }
        double perimetroCirculo(double raio) {
            return 2 * PI * raio;
        }
    }
    
int main() {
    cout << "\t Hello, World! \a\a\a" << endl; // o \a é o beep
    //          Hello, World! 
    cout << "\" Hello, World! \a\a\a. \" " << endl;
    //" Hello, World! . " 
    cout << "Hello\n, World \n !!!!!!!!!!!!.\n" << endl;
    // Hello
    //, World 
    //!!!!!!!!!!!!.
    cout << "Hello\t, World \t !!!!!!!!!!!!.\t"; //tabulação
    // Hello	, World 	 !!!!!!!!!!!!.

    char sons = '\a'; // o \a é o beep armazenado na variável sons
    cout << sons << endl; // o \a é o beep
    char bs = '\b'; // o \b é o backspace armazenado na variável bs obs: ' para caracter e " para string
    cout << bs << endl; // o \b é o backspace
    cout << "ZZzzzZZZZzzz";
    cout << bs; // o \b é o backspace
    cout << bs; // move o cursor para o primeiro caracter
    cout << "Informe o seu nome: ";
    string nome;
    cin >> nome;
    cout << "Ola " << nome << endl;
    cout << "Fim do programa";

    // O namespace é uma maneira de organizar o código e evitar conflitos de nomes.
    // Ele permite agrupar funções, classes e variáveis relacionadas em um único escopo.
    // Isso é especialmente útil em projetos grandes ou quando se utiliza bibliotecas de terceiros.
    // Por exemplo, se tivermos duas funções com o mesmo nome em diferentes partes do código,
    // o uso de namespaces nos permite diferenciá-las.
    // Aqui, criamos um namespace chamado "geometria" que contém funções para calcular a área e o perímetro de um círculo.
    // O namespace é definido com a palavra-chave "namespace" seguida pelo nome do namespace.
    // Dentro do namespace, podemos definir variáveis, funções e classes como faríamos normalmente.
    // O namespace é encerrado com uma chave de fechamento.
    // Para usar as funções dentro do namespace, precisamos especificar o nome do namespace seguido de dois pontos e o nome da função.
    // Isso é chamado de operador de resolução de escopo.
    // O operador de resolução de escopo é representado por dois pontos (::) e é usado para acessar membros de um namespace ou classe.
    // O operador de resolução de escopo é usado para acessar membros de um namespace ou classe.
    // O operador de resolução de escopo é representado por dois pontos (::) e é usado para acessar membros de um namespace ou classe.
    // Existem duas maneiras de acessar o namespace:

    // 1. Usando o operador de resolução de escopo (::)
    double raio = geometria::areaCirculo(5.0);
    cout << "Area do circulo: " << raio << endl;
    double perimetro = geometria::perimetroCirculo(5.0);
    cout << "Perimetro do circulo: " << perimetro << endl;
    // 2. Usando a diretiva using namespace
    using namespace geometria;
    double area = areaCirculo(5.0);
    cout << "Area do circulo: " << area << endl;
    double perimetro2 = perimetroCirculo(5.0);
    cout << "Perimetro do circulo: " << perimetro2 << endl;
    // 3. Usando a diretiva using

}