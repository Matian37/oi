//
// Mateusz Pietrowcow
//
 
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<uint,uint> uii;
typedef pair<ll,ll> pll;
typedef pair<ull,ull> pull;

#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

const int N = 3e6 + 5;

deque<uint> dqmin, dqmax;

uint getMin()
{
    return dqmin.front();
}

uint getMax()
{
    return dqmax.front();
}

void addMin(uint v)
{
    while (dqmin.size())
    {
        if (dqmin.back() <= v) break;
        dqmin.pop_back();
    }

    dqmin.push_back(v);
}

void remMin(uint v)
{
    if (dqmin.front() != v) return;
    dqmin.pop_front();
}

void addMax(uint v)
{
    while (dqmax.size())
    {
        if (dqmax.back() >= v) break;
        dqmax.pop_back();
    }

    dqmax.push_back(v);
}

void remMax(uint v)
{
    if (dqmax.front() != v) return;
    dqmax.pop_front();
}

namespace sol
{
    uint t[N];
    uint T;
    int n;

    void read()
    {
        cin >> T >> n;
    }

    void solve()
    {
        int r = 1;

        for (int i = 0, j = 0; j < n; j++)
        {
            cin >> t[j];

            addMax(t[j]);
            addMin(t[j]);

            uint L = max(0, (int)t[j] - (int)T),
                 R = t[j] + T;

            while (getMin() < L || getMax() > R)
            {
                remMin(t[i]);
                remMax(t[i]);
                i++;
            }

            r = max(r, j - i + 1);
        }

        cout << r;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::solve();
}