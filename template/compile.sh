#!/bin/bash

if [ "$2" == "fast" ];
then
    # 4 seconds
    echo "Fast compilation"
    g++ -o $1 $1.cpp -Og -ggdb3 -std=c++20
    exit 0
elif [ "$2" == "opt" ];
then
    # 4 seconds
    echo "Optimized compilation"
    g++ -o $1 $1.cpp -O3 -static -std=c++20
    exit 0
else
    echo "Debug compilation"

    # 6-7 second compliation
    g++ -o $1 $1.cpp -Og -ggdb3 --std=c++20 \
        -Wall -Wextra -Wshadow -Wconversion \
        -Wfloat-equal -Wfloat-conversion \
        -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_SANITIZE_VECTOR -D_GLIBCXX_PEDANTIC \
        -D_GLIBCXX_ASSERTIONS -D_FORTIFY_SOURCE=2 -DLOCAL -fsanitize=undefined
fi
