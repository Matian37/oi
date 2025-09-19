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

int pref[50005];
int n;

void read()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> pref[i];
        pref[i] += pref[i - 1];
    }
}

int getMin(int a, int b)
{
    if (a > b)
        swap(a, b);
    return min(pref[b - 1] - pref[a - 1], pref[n] - (pref[b - 1] - pref[a - 1]));
}

int findSolution(int a)
{
    int sol1;

    int low = 1, pos = 1, high = n, pot = 1 << ((int)log2(high - low + 1)); 

    while (pot != 0)
    {
        int left = pos - pot < 1 ? INT32_MIN : getMin(a, pos - pot),
            right = pos + pot > n ? INT32_MIN : getMin(a, pos + pot);
        
        if (max(left, right) > getMin(a, pos))
        {
            if (left > right)
                pos -= pot;
            else
                pos += pot;
        }

        pot /= 2;
    }
    
    sol1 = getMin(a, pos);

    low = a + 1, pos = n, high = n, pot = 1 << ((int)log2(high - low + 1));

    while (pot != 0)
    {
        int left = pos - pot < 1 ? INT32_MIN : getMin(a, pos - pot),
            right = pos + pot > n ? INT32_MIN : getMin(a, pos + pot);
        
        if (max(left, right) > getMin(a, pos))
        {
            if (left > right)
                pos -= pot;
            else
                pos += pot;
        }

        pot /= 2;
    }

    return max(sol1, getMin(a, pos));
}

void solve()
{
    int maks = 0;

    for (int i = 1; i <= n; i++)
    {
        maks = max(maks, findSolution(i));
    }
    cout << maks;
}

int main()
{
    ios_base::sync_with_stdio(0);

    read();
    solve();
}