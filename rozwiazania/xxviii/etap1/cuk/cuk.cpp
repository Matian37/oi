//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define ii pair<int, int>

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

int t[300005][3];
ll dp[300005][2][2][2];
int n;

struct info
{
    int i;
    bool first, second, third;
    ll result;
};

struct compare
{
    bool operator()(const info &a, const info &b)
    {
        if (a.result != b.result)
            return a.result > b.result;
        return a.i > b.i;
    }
};

ll BFS(int a, int b, int c)
{
    priority_queue<info, vector<info>, compare> pq;
    pq.push({0, 0, 0, 0, 0});

    while (!pq.empty())
    {
        auto acc = pq.top();
        pq.pop();

        if (dp[acc.i][acc.first][acc.second][acc.third] != LLONG_MAX)
            continue;
        dp[acc.i][acc.first][acc.second][acc.third] = acc.result;

        if (acc.i != n)
        {
            pq.push({acc.i + 1, 1, acc.second, acc.third, acc.result + (ll)t[acc.i][1] + (ll)t[acc.i][2]});
            pq.push({acc.i + 1, acc.first, 1, acc.third, acc.result + (ll)t[acc.i][2] + (ll)t[acc.i][0]});
            pq.push({acc.i + 1, acc.first, acc.second, 1, acc.result + (ll)t[acc.i][1] + (ll)t[acc.i][0]});
        }
    }

    ll minn = LLONG_MAX;

    for (int i = a; i <= 1; i++)
        for (int j = b; j <= 1; j++)
            for (int k = c; k <= 1; k++)
                minn = min(minn, dp[n][i][j][k]);
    return minn;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cin >> n;

    int zero1 = 0, zero2 = 0, zero3 = 0;

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 3; i++)
            cin >> t[j][i];
        if (t[j][0] == 0)
            zero1++;
        if (t[j][1] == 0)
            zero2++;
        if (t[j][2] == 0)
            zero3++;
    }

    for (int i = 0; i <= n; i++)
        for (int k = 0; k < 2; k++)
            for (int l = 0; l < 2; l++)
                for (int r = 0; r < 2; r++)
                    dp[i][k][l][r] = LLONG_MAX;
    cout << BFS(zero1 == n ? 0 : 1, zero2 == n ? 0 : 1, zero3 == n ? 0 : 1);
}