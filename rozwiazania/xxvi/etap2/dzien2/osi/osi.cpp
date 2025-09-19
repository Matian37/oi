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

struct edge
{
    int a, b, id;
    bool reversed;
};

#define left 1
#define right 2

list<edge> g[1000005];
vector<int> bridges;
int result[1000005], number[1000005], low[1000005];
bool visited[1000005], vis2[1000005];
int n, m, nastp = 1;

void read()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        g[a].push_back({a, b, i, false});
        g[b].push_back({b, a, i, true});
    }
}

int minn(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return min(a, b);
}

int lowDFS(int v, int last)
{
    number[v] = nastp++;
    visited[v] = true;
    low[v] = number[v];

    for (auto i : g[v])
    {
        if (i.id == last)
            continue;
        low[v] = minn(low[v], number[i.b]);
        
        if (!visited[i.b])
            low[v] = min(low[v], lowDFS(i.b, i.id));
    }

    if (low[v] == number[v] && last != -1)
        bridges.push_back(last);
    return low[v];
}

void solveDFS(int v)
{
    vis2[v] = true;

    for (auto i : g[v])
    {
        if (result[i.id] != 0)
            continue;

        if (!i.reversed)
            result[i.id] = right;
        else
            result[i.id] = left;

        solveDFS(i.b);
    }
}

void solve()
{
    int c = 0;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            lowDFS(i, -1);
            c++;
        }
    }

    for (int i : bridges)
        result[i] = right;

    for (int i = 1; i <= n; i++)
        if (!vis2[i])
            solveDFS(i);

    cout << c + bridges.size() << '\n';

    for (int i = 0; i < m; i++)
        cout << (result[i] == right ? '>' : '<');
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}