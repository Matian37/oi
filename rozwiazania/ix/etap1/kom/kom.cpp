#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

vector<int> G[30005];
int jump[16][30005], depth[30005];

void readGraph(int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void jump_dfs(int i, int p)
{
    depth[i] = depth[p] + 1;
    jump[0][i] = p;

    for (int j = 1; j <= 15; j++)
        jump[j][i] = jump[j - 1][jump[j - 1][i]];

    for (int j : G[i])
        if (j != p)
            jump_dfs(j, i);
}

int lca(int a, int b)
{
    int sum = 0;

    if (depth[a] < depth[b])
        swap(a, b);

    if (a == b)
        return 0;

    for (int i = 15; i >= 0; i--)
    {
        if (depth[jump[i][a]] >= depth[b])
        {
            a = jump[i][a];
            sum += 1 << i;
        }
    }

    for (int i = 15; i >= 0; i--)
    {
        if (jump[i][a] != jump[i][b])
        {
            a = jump[i][a];
            b = jump[i][b];
            sum += 1 << (i + 1);
        }
    }

    if (a == b)
        return sum;

    return sum + 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n;
    cin >> n;

    readGraph(n, n - 1);

    jump_dfs(1, 0);

    int q;
    cin >> q;

    int sum = 0, acc = 1;

    while (q--)
    {
        int a;
        cin >> a;

        sum += lca(acc, a);
        acc = a;
    }

    cout << sum;

}