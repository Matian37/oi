//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
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

int base, q;

int t[1000005];

void read()
{
    cin >> base >> q;

    for (int i = 0; i < base; i++)
        cin >> t[i];
}

ull pref[1000005];

void initSolve()
{
    ull sum = 0;

    for (int i = 0; i < base; i++)
        sum += (ull)(i) * (ull)t[i];

    int rem = (int)(sum % ((ull)(base - 1)));
    
    if (rem != 0)
        t[rem]--;

    for (int i = 0; i < base; i++)
        pref[i] = pref[max(i - 1, 0)] + (ull)t[i];
}


int solve(ull a)
{
    a++;
    if (pref[base - 1] < a)
        return -1;

    int low = 0, high = base - 1, med;

    while (low != high)
    {
        med = (low + high) / 2;

        if (pref[med] < a)
            low = med + 1;
        else
            high = med;
    }

    return low;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    initSolve();
    
    while (q--)
    {
        ull a;
        cin >> a;

        cout << solve(a) << '\n';
    }
}