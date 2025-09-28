//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007ULL
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

int n, m, h;

int solve()
{
    cin >> n >> m >> h;

    int minn = INT32_MAX;

    int t[n][m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            t[i][j] = INT32_MAX;

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            int a;
            cin >> a;

            minn = min(minn, a);

            t[i][j - 1] = min(t[i][j - 1], a);
            t[i][j] = a;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int a;
            cin >> a;

            minn = min(minn, a);

            t[j][i] = min(t[j][i], a);
            t[j - 1][i] = min(t[j - 1][i], a);
        }
    }

    ull r = 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            r = (r * (t[i][j] + 1)) % MOD;
    r = (r + h - minn) % MOD;

    return r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cout << solve();
}