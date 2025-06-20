#!/bin/bash

input=dataset10000.txt
n=10000

# Tempo sequencial
seq_time=$(./program $input $n 1 1 | grep Tempo | awk '{print $2}')

# Tempo paralelo
par_time=$(./program $input $n 8 4 | grep Tempo | awk '{print $2}')

# Calcula speedup
speedup=$(echo "$seq_time / $par_time" | bc -l)

echo "Tempo sequencial: $seq_time"
echo "Tempo paralelo:   $par_time"
echo "Speedup:          $speedup"
