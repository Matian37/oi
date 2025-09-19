//
// Mateusz Pietrowcow
//

#pragma GCC optimize("O3,fast-math,unroll-loops")
 
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
#define int128 __int128_t;
#define uint128 __uint128_t;

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
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
    const int N = 251;
    vector<int> g[N];

    int n, m;
    int sa, sb;

    void read()
    {
        cin >> n >> m >> sa >> sb;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
        }
    }

    int dp[N][N][2];

    int solve()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j][0] = dp[i][j][1] = INF;

        struct info
        {
            int fir, sec;
            bool turn;
        };

        queue<info> q;

        q.push({sa,sb,0});
        dp[sa][sb][0] = 0;

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            if (acc.fir == acc.sec && !acc.turn)
                return dp[acc.fir][acc.sec][acc.turn];
            
            for (auto i : g[acc.turn ? acc.sec : acc.fir])
            {
                int& vis = (acc.turn ? dp[acc.fir][i][!acc.turn] :
                                       dp[i][acc.sec][!acc.turn]);
                
                if (vis != INF) continue;

                vis = dp[acc.fir][acc.sec][acc.turn] + (acc.turn); 

                if (acc.turn) q.push({acc.fir, i, false});
                else q.push({i, acc.sec, true});
            }
        }

        return INF;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    
    int r = sol::solve();

    if (r == INF) cout << "NIE\n";
    else cout << r << '\n';
}