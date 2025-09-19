#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 +5;

int fu[N], ranks[N];

int find(int v)
{
    if (fu[v] == v) return v;
    return fu[v] = find(fu[v]);
}

void Union(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (ranks[a] < ranks[b])
    {
        fu[a] = b;
        ranks[b] += ranks[a];
    }
    else
    {
        fu[b] = a;
        ranks[a] += ranks[b];
    }
}

vector<int> g[N];
int n, m;

void read()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }
}

int low[N], visited[N], token = 0, c = 0, id = 0;

void dfs(int v, int p)
{
    visited[v] = true;
    low[v] = ++id;

    int wstpp = 0;
    bool self = false;

    for (auto i : g[v])
    {
        if (i == v) self = true;
        if (i == p) wstpp++;
    }
    
    if (wstpp > 1)
    {
        Union(v, p);
        low[v] = low[p];
    }

    for (auto i : g[v])
    {
        if (i == p) continue;
        if (visited[i] == token)
        {
            if (low[v] > low[i])
            {
                low[v] = low[i];
                Union(v, i);
            }
            continue;
        }
        dfs(i, v);

        if (low[i] < low[v])
        {
            low[v] = low[i];
            Union(i, v);
        }
    }

    if (ranks[find(v)] == 1 && !self)
        c++;
}

void solve()
{
    ++token;

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == token) continue;
        dfs(i, -1);
    }

    int q;
    cin >> q;

    cout << n - c;
}

int main()
{
    read();

    for (int i = 1; i <= n; i++)
    {
        fu[i] = i;
        ranks[i] = 1;
    }

    solve();
}