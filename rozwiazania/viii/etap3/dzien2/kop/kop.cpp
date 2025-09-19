//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

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

struct event
{
    int x1, x2, y;
    bool rem;
};

bool comp(const event& a, const event& b)
{
    if (a.y != b.y) return a.y > b.y;
    if (a.rem != b.rem) return a.rem < b.rem;
    if (a.x1 != b.x1) return a.x1 < b.x1;
    return a.x2 < b.x2;
}

const int base = 1 << 17, zero = 65535;

int valueTree[base * 2], updateTree[base * 2];
vector<event> ev;

int s, w, n;
int pQ, kQ, valQ;

void push(int v, int a, int b)
{
    updateTree[v * 2] += updateTree[v];
    updateTree[v * 2 + 1] += updateTree[v];

    valueTree[v * 2] += updateTree[v];
    valueTree[v * 2 + 1] += updateTree[v];

    updateTree[v] = 0;
}

int query(int v, int a, int b)
{
    if (b < pQ || a > kQ) return 0;
    if (pQ <= a && b <= kQ) return valueTree[v];

    int low = a, mid = (a + b) / 2, high = b;

    push(v, a, b);

    return max(query(v * 2, a, mid), query(v * 2, mid + 1, b));
}

void update(int v, int a, int b)
{
    if (b < pQ || kQ < a)
        return;
    if (pQ <= a && b <= kQ)
    {
        valueTree[v] += valQ;
        updateTree[v] += valQ;
        return;
    }
    int low = a, mid = (a + b) / 2, high = b;

    push(v, a, b);

    update(v * 2, low, mid);
    update(v * 2 + 1, mid + 1, high);

    valueTree[v] = max(valueTree[v * 2], valueTree[v * 2 + 1]);
}

void read()
{
    cin >> s >> w >> n;

    for (int i = 0; i < n; i++)
    {
        ii v;
        cin >> v.first >> v.second;

        ev.push_back({v.first, v.first + s, v.second, false});
        ev.push_back({v.first, v.first + s, v.second - w, true});
    }
}

void solve()
{
    int r = 0;

    sort(ev.begin(), ev.end(), comp);

    for (auto i : ev)
    {
        pQ = zero + i.x1, kQ = zero + i.x2, valQ = (!i.rem ? 1 : -1);

        update(1, 0, base - 1);

        pQ = 0, kQ = base - 1;

        int anws = query(1, 0, base - 1);

        r = max(r, anws);
    }

    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}