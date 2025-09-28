//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

ll primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int lic[10];
ll best = 1, r = 1, n;

void read()
{
    cin >> n;
}

ll dziel()
{
    ll roz = 1;

    for (int i = 0; i < 10; i++)
        roz *= lic[i] + 1;

    return roz;
}

void solve(ll num)
{
    if (num > n)
        return;
    if (num * 2 > n)
    {
        ll dzielniki = dziel();

        if (dzielniki > best)
        {
            best = dzielniki;
            r = num;
        }
        else if (dzielniki == best && num < r)
        {
            r = num;
        }
        return;
    }

    int value = -1, minn = INT32_MAX, pusty = -1;

    for (int i = 0; i < 10; i++)
    {
        if (lic[i] == 0)
        {
            if (pusty == -1)
                pusty = i;
            continue;
        }

        if (lic[i] < minn)
        {
            minn = lic[i];
            value = i;
        }
    }

    if (minn != INT32_MAX)
    {
        lic[value]++;
        solve(num * primes[value]);
        lic[value]--;
    }

    if (pusty != -1)
    {
        lic[pusty]++;
        solve(num * primes[pusty]);
        lic[pusty]--;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve(1);
    cout << r;
}