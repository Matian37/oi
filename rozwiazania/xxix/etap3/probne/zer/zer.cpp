//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>
#include "zerlib.h"

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

vector<int> v;

int main()
{
    int n = daj_n();

    v.push_back(2);

    for (int i = 1; i < n; i++)
    {
        v.push_back(suma(0, i));

        if (v.back() == 0)
            v[0] = 0;
        else if (v.back() == 2)
            v[0] = 1;
    }

    if (v[0] == 2)
    {
        if (suma(1, 2) == 0)
            v[0] = 1;
        else
            v[0] = 0;
    }

    for (int i = 1; i < n; i++)
        v[i] -= v[0];
    odpowiedz(v);
}