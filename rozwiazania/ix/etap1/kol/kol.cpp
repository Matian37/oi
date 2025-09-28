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

int n, m, z;

const int base = 1 << 16;

int tree1[base * 2], tree2[base * 2];

void read()
{
    cin >> n >> m >> z;
}

void push(int v, int a, int b)
{
    tree2[v * 2] += tree2[v];
    tree2[v * 2 + 1] += tree2[v];
    tree1[v * 2] += tree2[v];
    tree1[v * 2 + 1] += tree2[v];
    tree2[v] = 0;
}

int query(int v, int a, int b, int p, int k)
{
    if (b < p || k < a)
        return 0;
    if (p <= a && b <= k)
        return tree1[v];
    int low = a, mid = (a + b) / 2, high = b;

    push(v, a, b);

    return max(query(v * 2, a, mid, p, k), query(v * 2 + 1, mid + 1, b, p, k));
}

void update(int v, int a, int b, int p, int k, int val)
{
    if (b < p || k < a)
        return;
    if (p <= a && b <= k)
    {
        tree1[v] += val;
        tree2[v] += val;
    }
    else
    {
        int low = a, mid = (a + b) / 2, high = b;

        push(v, a, b);

        update(v * 2, a, mid, p, k, val);
        update(v * 2 + 1, mid + 1, b, p, k, val);

        tree1[v] = max(tree1[v * 2], tree1[v * 2 + 1]);
    }
}

void solve()
{
    int a, b, k;
    cin >> a >> b >> k;

    if (query(1, 1, base, a, b - 1) + k > m)
    {
        cout << "N\n";
        return;
    }

    update(1, 1, base, a, b - 1, k);

    cout << "T\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();

    while (z--)
    {
        solve();
    }
    


}