#include <bits/stdc++.h>


#define len(x) int(x.size())
#define leng(x) int(g[x].size())
#define lenrg(x) int(rg[x].size())

using namespace std;

const int N = 1e3+5;
list<int> g[N], rg[N];
stack<int> ord;

void dfs(int v)
{
    while (g[v].size())
    {
        auto vert = g[v].front();
        g[v].pop_front();
        dfs(vert);
    }

    ord.push(v);
}

bool possible(int n)
{
    if (leng(1) != lenrg(1) + 1)
        return false;

    for (int i = 2; i < n; i++)
        if (leng(i) != lenrg(i))
            return false;

    
    if (leng(n) + 1 != lenrg(n) && leng(n) != 0)
        return false;

    dfs(1);
    
    if (len(ord) != n)
        return false;
    else
    {
        cout << "NIE\n";
        return true;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n == 1)
    {
        cout << "NIE\n";
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;

        for (int j = 0; j < k; j++)
        {
            int x;
            cin >> x;

            g[i].push_back(x);
            rg[x].push_back(i);
        }
    }

    if (possible(n))
        return 0;
    if (ord.size() == 0)
        dfs(1);

    ord.pop();
    while (ord.size())
    {
        cout << ord.top() << ' ';
        ord.pop();
    }
    cout << "0\n";
}