//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<uint,uint> uii;
typedef pair<ll,ll> pll;
typedef pair<ull,ull> pull;

#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

const int N = 6e2 + 5;
const int base = 1 << 10;

int pref[base * 2][N];
int n, k;

namespace tree
{
    int tree[base * 2][N];

    void init(int v)
    {
        if (v >= base)
        {
            for (int i = 0; i <= n + 1; i++)
                tree[v][i] = pref[v - base][i];
            return;
        }

        init(v * 2);
        init(v * 2 + 1);

        for (int i = 0; i <= n; i++)
            tree[v][i] = tree[v * 2][i] + tree[v * 2 + 1][i];
    }

    int query(int a, int b, int c, int d)
    {
        a += base - 1;
        b += base + 1;

        int r = 0;

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) 
                r += tree[a + 1][d] - tree[a + 1][c - 1];
            if (b % 2 == 1) 
                r += tree[b - 1][d] - tree[b - 1][c - 1];

            a /= 2;
            b /= 2;
        }

        return r;
    }
}

const int K = 51;

namespace sol
{
    ii dp[N][K];

    void read()
    {
        cin >> n >> k;

        for (int i = 1; i <= n - 1; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                cin >> pref[i][j];
                pref[i][j] += pref[i][j - 1];
            }

            for (int j = 0; j <= n; j++)
                pref[i][j] += pref[i - 1][j];
        }
    }
    
    void solve()
    {
        tree::init(1);

        for (int j = 0; j <= n; j++)
        {
            for (int l = 0; l <= k; l++)
                dp[j][l].first = INT32_MIN;
        }

        dp[n][0].first = 0;

        for (int l = 0; l <= k; l++)
        {
            for (int j = n; j > 1; j--)
            {
                for (int i = j - 1; i >= 1; i--)
                {
                    if (dp[j][l].first == INT32_MIN) continue;

                    int c = (pref[i][j] - pref[i][i]) - (pref[0][j] - pref[0][i]);

                    if (l < k)
                        if (dp[i][l + 1].first < dp[j][l].first + c)
                            dp[i][l + 1] = {dp[j][l].first + c, j};
                }
            }
        }

        int best = 0;

        for (int i = 1; i <= n; i++)
            if (dp[best][k].first < dp[i][k].first)
                best = i;
        
        int l = best, c = k;

        while (l != n)
        {
            cout << l << ' ';

            l = dp[l][c].second;

            c--;
        }
        cout << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::solve();
}