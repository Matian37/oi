//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
#define ii pair<int,int>
#define pll pair<long long, long long>
#define pul pair<unsigned long long, unsigned long long>
#define Tak cout << "TAK" << '\n';
#define Nie cout << "NIE" << '\n';

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

const int base = 300001; //

int roz[base], kr[base];
int n, m;

void read()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> roz[i];
    for (int i = 0; i < m; i++)
        cin >> kr[i];
}

int binsearch(int high, int sajz)
{
    if (high == -1)
        return -1;

    int low = 0, med;

    while (low != high)
    {
        med = (low + high) / 2;
        if (roz[med] >= sajz)
            low = med + 1;
        else    
            high = med;
    }

    if (roz[low] >= sajz)    
        return low;
    return low - 1;
}

int solve()
{
    for (int i = 1; i <= n; i++)
        roz[i] = min(roz[i - 1], roz[i]);
    

    int high = n - 1;
    int result;

    for (int i = 0; i < m; i++)
    {
        int pos = binsearch(high, kr[i]);
        result = pos;

        if (pos == -1)
            continue;
        high = pos - 1;
    }

    return result + 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}