#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

pair<int, int> dp[2][800005];

int n, tl, az;

pair<int, int> minSol(pair<int, int> a, pair<int, int> b)
{
    bool first = a.first > tl && a.second > az, second = b.first > tl && b.second > az;

    if (first && second)
    {
        int sum1 = a.first + a.second, sum2 = b.first + b.second;

        if (sum1 < sum2)
            return a;
        return b;
    }
    else if (first)
        return a;
    return b;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cin >> tl >> az >> n;

    int roz = INT32_MAX, dal = 0;

    for (int i = 1; i <= n; i++)
    {
        int tp, ap, wp;
        cin >> tp >> ap >> wp;

        dal += wp;

        for (int j = 1; j < wp; j++)
            dp[i % 2][j] = dp[(i - 1) % 2][j];
        for (int j = wp; j <= dal; j++)
        {
            dp[i % 2][j] = minSol(dp[i % 2][j], {tp + dp[(i - 1) % 2][j - wp].first, ap + dp[(i - 1) % 2][j - wp].second});

            if (dp[i % 2][j].first >= tl && dp[i % 2][j].second >= az)
                roz = min(roz, j);
        }
    }

    cout << roz;

    return 0;
}