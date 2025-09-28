#include <bits/stdc++.h>
#include "skalib.h"

using namespace std;

typedef unsigned long long ull;

ull wynik = 0;

int main()
{
    ull n = daj_ograniczenie();


    mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());
    uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < 4; i++)
        zapytaj(dis(rng));
    odpowiedz(dis(rng));
}