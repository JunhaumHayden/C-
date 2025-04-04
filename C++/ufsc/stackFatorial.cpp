#include <iostream>
#include "./vplExercicioPilha01/h02.h"

using namespace std;


int fat_iterativo(int n) {  // mais eficiente
	int f = 1;
	for (int i = 2; i <= n; i++) {
		f = f * i;
	}
	return f;
}

int fat(int n) {  // recursivo
	if (n == 0 || n == 1) {
		return 1;
	} else {
		return n * fat(n-1);
	}
}

int fat_pilha_v1(int n) {  // recursivo transformado em nao recursivo
	structures::ArrayStack<int> p(1000);
	int f = 1;
	while (n > 1) {
	    p.push(n);
	    n--;
    }
	while (!p.empty()) {
	    f = f * p.pop();
    }
	return f;
}

int fat_pilha_v2(int n) {  // pilha
	structures::ArrayStack<int> p(1000);
	int f = 1;
	p.push(n);
	while (!p.empty()) {
	    n = p.pop();
        if (n > 1) {
            f = f * n;
            p.push(n-1);
        }
    }
	return f;
}

int fat_pilha_v3(int n) {  // pilha
	structures::ArrayStack<int> p(1000);
	int f;
	bool caso_base = false;
	p.push(n);
	while (!p.empty()) {
		n = p.top();
		if (n == 0 || n == 1) {
			p.pop();
			caso_base = true;
			f = 1;
		} else if (caso_base) {
	        n = p.pop();
	        f = f * n;
	    } else {
	        p.push(n-1);
		}
    }
	return f;
}

int main() {
	int f1, f2, f3, f4, f5;
	int n = 5;
	
    f1 = fat_iterativo(n);
    cout << "fat-iter(" << n << ") = " << f1 << endl;

    f2 = fat(n);
    cout << "fat-recu(" << n << ") = " << f2 << endl;

    f3 = fat_pilha_v1(n);
    cout << "fat-pil1(" << n << ") = " << f3 << endl;

    f4 = fat_pilha_v2(n);
    cout << "fat-pil2(" << n << ") = " << f4 << endl;

    f5 = fat_pilha_v3(n);
    cout << "fat-pil3(" << n << ") = " << f5 << endl;

    return 0;
}
