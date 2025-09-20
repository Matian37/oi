//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <cmath>

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
using ld = long double;
using pld = pair<ld,ld>;
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

// best primes in the galaxy
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
#define lenl(x) (ll)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) y = x(y,z)


template <typename X, typename Y, typename Z>
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using gp_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

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
    const int N = 1e6+5;
    vector<int> g[N];
    int n, k;

    void read()
    {
        cin >> n >> k;

        for (int i = 1; i <= n; i++)
            g[i].clear();

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    double dp[N], sil[N];
    int sajz[N];
    
    inline double ncr(int _n, int _k)
    {
        return sil[_n] - sil[_k] - sil[_n - _k];
    }

    void init()
    {
        sil[0] = sil[1] = log(1);

        for (int i = 2; i <= n; i++)
            sil[i] = sil[i - 1] + log(i);
    }

    pair<double, int> sol[N];

    void dfs(int v, int p)
    {
        sol[v] = {dp[v], v};

        for (auto i : g[v])
        {
            if (i == p) continue;

            double pv = dp[v], pi = dp[i];
            int sv = sajz[v], si = sajz[i];

            // rem log(n)
            dp[v] -= sil[sajz[v] - 1];
            dp[i] -= sil[sajz[i] - 1];

            // sajz
            sajz[v] -= sajz[i];
            sajz[i] += sajz[v];

            // add log(n)
            dp[v] += sil[sajz[v] - 1];
            dp[i] += sil[sajz[i] - 1];

            // c
            dp[v] += sil[si];
            dp[i] -= sil[sajz[v]];

            // r
            dp[v] -= pi;
            dp[i] += dp[v];

            dfs(i, v);

            // revert changes
            dp[v] = pv, dp[i] = pi;
            sajz[v] = sv, sajz[i] = si;
        }
    }

    void solve()
    {
        init();

        function<void(int, int)> init_dfs = [&](int v, int p)
        {
            sajz[v] = 1;

            for (auto i : g[v])
            {
                if (i == p) continue;
                init_dfs(i, v);
                sajz[v] += sajz[i];
            }

            dp[v] = sil[sajz[v] - 1];

            for (auto i : g[v])
            {
                if (i == p) continue;
                dp[v] += dp[i] - sil[sajz[i]];
            }
        };
        init_dfs(1, 0);

        dfs(1, 0);
        /*for (int i = 1; i <= n; i++)
        {
            init_dfs(i, 0);
            sol[i] = {dp[i], i};
        }*/

        sort(sol+1,sol+(n+1), greater<pair<double, int>>());

        for (int i = 1; i <= k; i++)
            cout << sol[i].sec << ' ';
        cout << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        sol::read();
        sol::solve();
    }
}