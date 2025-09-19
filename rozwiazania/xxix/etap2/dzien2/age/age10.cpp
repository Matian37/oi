//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <bits/extc++.h>

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

template<int K>
struct veck
{
    ii t[K] = {};
    int sajz = 0;

    void add(int val, int ind)
    {
        if (sajz < 2)
        {
            t[sajz++] = {val, ind};

            if (sajz == 2 && t[0].fir > t[1].fir)
                swap(t[0], t[1]);
        }
        else
        {
            if (val <= t[0].fir) return;

            if (val <= t[1].fir) 
            {
                t[0] = {val, ind};
                return;
            }

            t[0] = t[1];
            t[1] = {val, ind};
        }
    }
};

namespace sol
{
    #define STAY 0
    #define UP 1
    #define DOWN 2

    const int N = 5e5+5;
    vector<int> g[N];
    bitset<N> agent;
    int n, k;

    void read()
    {
        cin >> n >> k;

        for (int i = 0; i < k; i++)
        {
            int c;
            cin >> c;
            agent[c] = true;
        }

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int dp[N][3];
    int val[N];

    void dfs(int v)
    {
        veck<2> downs;

        int sum = 0;

        for (auto i : g[v]) 
        {
            dfs(i);

            val[i] = max(dp[i][UP], dp[i][STAY]);
            sum += val[i];

            if (agent[i]) continue;
            downs.add(dp[i][DOWN], i);
        }

        dp[v][STAY] = sum;

        for (auto i : g[v])
            if (!agent[i])
                self(max, dp[v][agent[v] ? STAY : DOWN], (sum - val[i]) + 1 + dp[i][DOWN]);

        if (agent[v])
            return;

        for (auto i : g[v])
        {
            if (dp[i][UP] != 0 || agent[i])
            {
                self(max, dp[v][UP], (sum - val[i]) + dp[i][UP] + 1);

                for (int _j = 0; _j < downs.sajz; _j++)
                {
                    auto j = downs.t[_j];

                    if (i == j.sec) continue;

                    self(max, dp[v][STAY], 2 + dp[i][UP] + j.fir + (sum - val[i] - val[j.sec]));
                }
            }
        }
    }
    
    void solve()
    {
        function<void(int,int)> p_dfs = [&](int v, int p)
        {
            vector<int>::iterator x = g[v].end();

            for (auto it = g[v].begin(); it != g[v].end(); it++)
            {
                if (*it == p)
                {
                    x = it;
                    continue;
                }
                p_dfs(*it, v);
            }

            if (x != g[v].end())
                g[v].erase(x);
        };
        p_dfs(1, 0);
        dfs(1);

        cout << 2*(n-k) - dp[1][STAY] << '\n';
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