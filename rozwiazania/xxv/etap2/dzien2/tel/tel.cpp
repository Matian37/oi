//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
//using namespace __gnu_pbds;

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

int n, m;

namespace tree
{
    const int base = 1 << 19;

    ll treeVal[base * 2];
    pll treeQ[base * 2];
    // add val, add a

    inline ll getSum(ll a, ll b)
    {
        return ((b - a + 1) * (a + b)) / 2LL;
    }

    void push(int v, int a, int b)
    {
        int mid = (a + b) / 2;

        ll ns = (mid - a + 1);

        treeQ[v * 2].first += treeQ[v].first;
        treeQ[v * 2 + 1].first += treeQ[v].first;
        treeQ[v * 2].second += treeQ[v].second;
        treeQ[v * 2 + 1].second += treeQ[v].second;

        treeVal[v * 2] += treeQ[v].first * ns;
        treeVal[v * 2 + 1] += treeQ[v].first * ns;

        ll suml = getSum(a, mid),
           sumr = getSum(mid + 1, b);

        treeVal[v * 2] += treeQ[v].second * suml;
        treeVal[v * 2 + 1] += treeQ[v].second * sumr;

        treeQ[v] = {0, 0};
    }

    ll S, A, X;
    int p, k;
    bool side;

    void _update(int v, int a, int b)
    {
        if (a > k || b < p) return;
        if (p <= a && b <= k)
        {
            ll val1 = S + (side ? -1LL : 1LL) * A * X, val2 = (side ? 1LL : -1LL) * A;

            treeVal[v] += val1 * (b - a + 1);
            treeQ[v].first += val1;

            treeVal[v] += getSum(a, b) * val2;
            treeQ[v].second += val2;
        }
        else
        {
            int mid = (a + b) / 2;

            push(v, a, b);

            _update(v * 2, a, mid);
            _update(v * 2 + 1, mid + 1, b);

            treeVal[v] = treeVal[v * 2] + treeVal[v * 2 + 1];
        }
    }

    void update(int _s, int _a, int _x)
    {
        S = _s, A = _a, X = _x;

        int dist = abs(_s / _a);
        int l = max(1, _x - dist), r = min(_x + dist, n);

        p = l, k = _x - 1;
        side = false;

        if (p <= k) _update(1, 0, base - 1);

        p = _x, k = r;
        side = true;

        _update(1, 0, base - 1);
    }

    ll _query(int v, int a, int b)
    {
        if (b < p || a > k) return 0;
        if (p <= a && b <= k) return treeVal[v];

        push(v, a, b);

        int mid = (a + b) / 2;

        return _query(v * 2, a, mid) + _query(v * 2 + 1, mid + 1, b);
    }

    ll query(int a, int b)
    {
        p = a;
        k = b;

        return _query(1, 0, base - 1);
    }
}

namespace sol
{
    const int N = 3e5 + 5;
    ii t[N];

    void read()
    {
        cin >> n >> m;
    }
    
    void solve()
    {
        while (m--)
        {
            char op;
            cin >> op;

            switch (op)
            {
                case 'Z':
                    int l, r;
                    cin >> l >> r;

                    cout << tree::query(l, r) / (ll)(r - l + 1) << '\n';
                    
                    break;
                case 'P':
                    int x, s, a;
                    cin >> x >> s >> a;

                    t[x] = {s, -a};

                    tree::update(s, -a, x);

                    break;
                case 'U':
                    int X;
                    cin >> X;

                    tree::update(-t[X].first, -t[X].second, X);

                    break;
            }
        }
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