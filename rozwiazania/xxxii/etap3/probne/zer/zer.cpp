#include <bits/stdc++.h>
#include "zerlib.h"

using namespace std;

vector<int> r;
int val = 2;

int main()
{
    int n = daj_n();

    r.resize(n, 2);

    for (int i = 1; i < n; i++)
    {
        r[i] = suma(0, i);

        if (r[i] == 0)
            val = 0;
        else if (r[i] == 2)
            val = 1;
    }

    if (val == 2) 
        val = (suma(1, 2) == 2 ? 0 : 1);
    r[0] = val;

    for (int i = 1; i < n; i++)
    {
        if (r[i] == 1) r[i] = 1 - val;
        else if (r[i] == 2) r[i] = 1;
        else r[i] = 0;
    }

    odpowiedz(r);
}