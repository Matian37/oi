//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
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

list<int> level[1000005];
pair<int,int> g[1000001];
int n, dl[1000001], parent[1000001], id[1000001];

void read()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        g[i] = {a, b};
    }
}

int token = 0;

void dfs(int v, int p)
{
    parent[v] = p;

    if (dl[p] == 0 && dl[v] == 1) level[1].push_back(v);

    if (g[v].first != 0) 
    {
        dl[g[v].first] = (dl[v] == 0 ? 0 : dl[v] + 1);
        dfs(g[v].first, v);
    }
    if (g[v].second != 0)
    {
        dl[g[v].second] = dl[v] + 1;
        dfs(g[v].second, v);
    }
}

void setID(int h)
{
    if (level[h].size() == 0) return;

    ++token;

    for (auto i : level[h]) 
    {
        id[i] = token;

        if (g[i].first != 0)
            level[h + 1].push_back(g[i].first);
    }

    setID(h + 1);
    level[h + 1].clear();

    for (auto i : level[h])
    {
        if (g[i].second != 0)
            level[h + 1].push_back(g[i].second);
    }

    setID(h + 1);
    level[h + 1].clear();
}

void solve()
{
    dfs(1, 0);
    setID(1);

    int z;
    cin >> z;

    while (z--)
    {
        int a, b;
        cin >> a >> b;

        if (dl[a] == dl[b] && dl[a] == 0)
        {
            cout << "TAK\n";
        }
        else if (dl[a] != dl[b])
        {
            if (dl[a] > dl[b]) cout << "TAK\n";
            else cout << "NIE\n";
        }
        else
        {
            if (id[a] >= id[b]) cout << "TAK\n";
            else cout << "NIE\n";
        }
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    read();
    solve();
}