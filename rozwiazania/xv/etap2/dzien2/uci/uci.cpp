//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

// best primes in te galaxy
#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define len(x) (int)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct chash
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    const int N = 1e2+3;
    int dp[N][N][N][4][2];
    ii X[N][N], Y[N][N];
    // x1, x2, y1
    string t[N];
    int n, m, k;
    pll p;

    void read()
    {
        cin >> n >> m >> k;
        cin >> p.fir >> p.sec;

        for (int i = 1; i <= n; i++)
        {
            cin >> t[i];
            t[i] = '_' + t[i];
        }
    }

    int x1, x2, y1, y2;
    bool curr, prev;

    inline __attribute__((always_inline)) void compute()
    {   
        if (t[y2][x1] == '+')
        {
            dp[x1][x2][y2][0][curr] = dp[x1][x2][y2][0][prev];

            if (Y[y2][x1].fir <= y1 && (p.fir != x1 || p.sec > y2 || p.sec <= y1))
            {
                if (x1 == p.fir && y1 == p.sec)
                    dp[x1][x2][y2][0][curr]++;
                else 
                    dp[x1][x2][y2][0][curr] += dp[x1+1][x2][y2][1][prev];
            }

            dp[x1][x2][y2][0][curr] %= k;
        }
        else dp[x1][x2][y2][0][curr] = 0;

        if (t[y1][x1] == '+')
        {
            dp[x1][x2][y2][1][curr] = dp[x1][x2 - 1][y2][1][prev];

            if (X[y1][x1].sec >= x2 && (p.sec != y1 || p.fir >= x2 || p.fir < x1))
            {
                if (x2 == p.fir && y1 == p.sec)
                    dp[x1][x2][y2][1][curr]++;
                else 
                    dp[x1][x2][y2][1][curr] += dp[x1][x2][y2][2][prev];
            }
            
            dp[x1][x2][y2][1][curr] %= k;
        }
        else dp[x1][x2][y2][1][curr] = 0;

        if (t[y1][x2] == '+')
        {
            dp[x1][x2][y2][2][curr] = dp[x1][x2][y2 - 1][2][prev];

            if (Y[y1][x2].sec >= y2 && (p.fir != x2 || p.sec < y1 || p.sec >= y2))
            {
                if (x2 == p.fir && y2 == p.sec)
                    dp[x1][x2][y2][2][curr]++;
                else 
                    dp[x1][x2][y2][2][curr] += dp[x1][x2 - 1][y2][3][prev];
            }

            dp[x1][x2][y2][2][curr] %= k;
        }
        else dp[x1][x2][y2][2][curr] = 0;

        if (t[y2][x2] == '+')
        {
            dp[x1][x2][y2][3][curr] = dp[x1 + 1][x2][y2][3][prev];
            
            if (X[y2][x2].fir <= x1 && (p.sec != y2 || p.fir <= x1 || p.fir > x2))
            {
                if (x1 == p.fir && y2 == p.sec)
                    dp[x1][x2][y2][3][curr]++;
                else
                    dp[x1][x2][y2][3][curr] += dp[x1][x2][y2 - 1][0][prev];
            }

            dp[x1][x2][y2][3][curr] %= k;
        }
        else dp[x1][x2][y2][3][curr] = 0;
    }

    void init()
    {
        for (int i = 1; i <= n; i++)
        {
            X[i][m + 1].sec = m;

            for (int j = m; j >= 1; j--)
            {
                if (t[i][j] == '*')
                    X[i][j].sec = j-1;
                else
                    X[i][j].sec = X[i][j + 1].sec;
            }

            X[i][0].fir = 0;

            for (int j = 1; j <= m; j++)
            {
                if (t[i][j] == '*')
                    X[i][j].fir = j+1;
                else
                    X[i][j].fir = X[i][j - 1].fir;
            }     
        }

        // doesnt work
        for (int i = 1; i <= m; i++)
        {
            Y[n + 1][i].sec = n;

            for (int j = n; j >= 1; j--)
            {
                if (t[j][i] == '*')
                    Y[j][i].sec = j-1;
                else
                    Y[j][i].sec = Y[j + 1][i].sec;
            }

            Y[0][i].fir = 0;

            for (int j = 1; j <= n; j++)
            {
                if (t[j][i] == '*')
                    Y[j][i].fir = j+1;
                else
                    Y[j][i].fir = Y[j - 1][i].fir;
            }     
        }
    }

    void solve()
    {
        if ((n == 1 && m == 1) || (p == pll{1,n}))
        {
            cout << 1 << '\n';
            return;
        }

        init();

        for (int i = 0; i < 4; i++)
            dp[p.fir][p.fir][p.sec][i][0] = 1;

        for (int i = 3; i <= n + m; i++)
        {
            curr = i % 2, prev = !curr;

            for (int j = max(1, i - n); j <= min(m, i - 1); j++)
                for (x1 = 1, x2 = j; x2 <= m; x1++, x2++)
                    for (y1 = 1, y2 = i - j; y2 <= n; y1++, y2++)
                        compute();
        }

        cout << dp[1][m][n][0][(n+m)%2] << '\n';
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