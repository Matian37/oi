#!/bin/bash

./compile.sh wzor fast
./compile.sh brut opt
./compile.sh gen opt

for ((i = 1; 1; i++))
do
    echo $i > files/ziarno.txt

    ./gen < files/ziarno.txt > files/wejscie.in
    ./brut < files/wejscie.in > files/b.out
    ./wzor < files/wejscie.in > files/w.out

    if diff -b files/b.out files/w.out > /dev/null
    then
        echo -ne "\rACCEPTED ${i}"
    else
        echo -ne "\rFAILED ${i}"
        break
    fi
done