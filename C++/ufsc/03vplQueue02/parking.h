// Copyright [2024] <COLOQUE SEU NOME AQUI...>


void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    if (k < 1 || k > static_cast<int>(f->size())) {
        throw std::out_of_range("Not Found");
    }
    for (int i = 0; i < k; i++) {
        int dataTemp = f->dequeue();
        if (i != (k -1)) {
            f->enqueue(dataTemp);
        } else {
            break;
        }
    }
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    if (k < 1 || k > static_cast<int>(f->size())) {
        throw std::out_of_range("Not Found");
    }
    int elementToKeep;
    for (int i = 0; i < static_cast<int>(f->size()); i++) {
        int dataTemp = f->dequeue();
        if (i == (k -1)) {
            elementToKeep = dataTemp;
        }
    }
    f->enqueue(elementToKeep);
}

/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
