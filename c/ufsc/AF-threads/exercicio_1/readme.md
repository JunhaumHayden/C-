# Exercício 1
Escreva um programa que receba dois números como argumento na linha de comando (use argc e argv da função main) que representam um número de threads (n_threads) e o número de incrementos (n_loops) que as n_threads farão em uma variável global. O programa deve criar n_threads threads que paralelamente incrementam n_loops vezes, em um laço, uma variável global chamada contador_global. Siga essas instruções detalhadas:

O programa deve receber os valores de n_threads em argv[1] e n_loops em argv[2].
Isso já vem implementado no código inicial!
A variável global deve se chamar contador_global e deve ser inicializada com 0.
O programa deve criar n_threads threads.
Cada thread deve realizar n_loops incrementos em contador_global.
n_loops incrementos significa fazer ++contador_global  n_loops vezes
n_loops deve ser passado como argumento da função executada pela thread (via pthread_create()).
Não crie uma variável global para esse fim!
A thread principal deve esperar o término de todas as outras threads (pthread_join()).
Após o término das demais, a thread principal deve imprimir o valor do contador e o valor esperado, conforme esse exemplo (n_threads=1, n_loops=32023):
Contador: 32023 
Esperado: 32023
Execute este programa e vá aumentando o número de threads a cada execução (ex.: 2, 5, 10, 20, 30, 40, ...). Observe o que acontece com o valor do contador_global conforme o número de threads aumenta. Observe também o que acontece quando o valor de n_loops aumenta. Reflita sobre os seguintes pontos:

Qual a relação entre n_threads e a diferença entre "Contador" e "Esperado"?
Qual a relação entre n_loops e a diferença entre "Contador" e "Esperado"?
Existe alguma regra ou padrão na diferença entre "Contador" e "Esperado"?