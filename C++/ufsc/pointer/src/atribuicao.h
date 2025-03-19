int atribuicao() {
    int *p1, *p2, x;
    x = 4; // x recebe o valor 4.

    p1 = &x; // p1 passa a apontar para x.
    p2 = p1; // p2 recebeu o valor de p1, que é o endereço de x, ou seja: p2 também aponta para x.

    printf("Imprime o endereco: %p\n", p2); // Imprime o endereço de x.
    printf("Imprime o valor apontado por p2: %i\n", *p2); // Imprime o valor apontado por p2, ou seja: o valor de x.

    return 0;
}