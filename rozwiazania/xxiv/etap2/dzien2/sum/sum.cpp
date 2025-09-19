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
using int128 = __int128_t;
using uint128 = __uint128_t;

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INFULL 1'000'000'000'000'000'001ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    const int N = 200, M = 200, S = 200;

    ull dp[N + 1][M][S + 1];
    int pot[N+1];

    int s, m, q;

    void read()
    {
        cin >> s >> m >> q;
    }

    inline int getMod(int j, int c, int x)
    {
        return (m + j - (c * pot[x-1]) % m) % m;
    }

    void init()
    {
        dp[0][0][0] = 1;

        pot[0] = 1;
        for (int i = 1; i <= N; i++)
            pot[i] = (pot[i - 1] * 10) % m;

        for (int i = 0; i < 10; i++) 
            dp[1][i % m][i]++;
        
        for (int i = 2; i <= N; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int k = 0; k <= s; k++)
                {
                    for (int c = 0; c <= min(9,k); c++)
                    {
                        dp[i][j][k] += dp[i - 1][getMod(j,c,i)][k-c];
                        dp[i][j][k] = min(dp[i][j][k], INFULL);
                    }
                }
            }
        }
    }
    
    void solve()
    {
        init();

        while (q--)
        {
            ull k;
            cin >> k;

            if (dp[N][0][s] < k) {cout << "NIE\n"; continue;}

            int _n = N, _m = 0, _s = s;

            while (_n != 1)
            {
                if (dp[_n - 1][_m][_s] < k) break;
                _n--;
            }

            string result = "";

            while (_n != 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    ull val = dp[_n - 1][getMod(_m, i, _n)][_s - i];

                    if (val >= k)
                    {
                        result += char(i + '0');
                        _m = getMod(_m, i, _n);
                        _n--;
                        _s -= i;
                        break;
                    }
                    else k -= val;
                }
            }
            
            cout << result << '\n';
        }
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