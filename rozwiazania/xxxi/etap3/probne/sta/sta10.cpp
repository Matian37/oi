#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5, base = 1 << 14;

int dp[N], t[N], tree[base * 2];

int n, m, k;

void update(int v, int p)
{
    v += base;

    if (tree[v] >= p) return;

    tree[v] = p;
    v /= 2;

    while (v != 0)
    {
        if (tree[v] < p)
            tree[v] = p;
        else
            break;
        v /= 2;
    }
}

int query(int a, int b)
{
    a += base - 1;
    b += base + 1;
    
    int r = 0;

    while (a / 2 != b / 2)
    {
        if (a % 2 == 0) r = max(r, tree[a + 1]);
        if (b % 2 == 1) r = max(r, tree[b - 1]);

        a /= 2;
        b /= 2;
    }

    return r;
}

void read()
{
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
        cin >> t[i];
}

int solve()
{
    int maks = 1;

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1 + max(query(0, t[i] - 1), query(t[i] + 1, m + 1));

        maks = max(maks, dp[i]);

        update(t[i], dp[i]);
    }

    return maks;
}

int main()
{
    read();
    cout << solve();
}