#include <string>
#include "../03_vplQueue01/array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);

    /*
        *The range-based for loop is more concise and easier to read. It is commonly used when you need to iterate through all elements of a container without modifying the container itself.
        *This is equivalent to:
        *for (std::string::size_type i = 0; i < texto.size(); ++i) {
        char c = texto[i];
        // Process c
        }
    */
    for (char c : texto) {
            if (c == '<') {
                if (!fila.empty()) {
                    fila.dequeue();
                }
            } else if (c == '>') {
                if (!fila.empty()) {
                    fila.enqueue(fila.back());
                }
            } else {
                fila.enqueue(c);
            }
        }

    return fila;
}
