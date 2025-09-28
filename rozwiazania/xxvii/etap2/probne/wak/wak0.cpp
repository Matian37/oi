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

namespace sol
{
    const int N = 1e6+5;

    #define NULL_VERT 0

    map<int,int> nxt[N][2]; // vert, active
    vector<int> g[N];
    ll dp[N];
    ll w[N];
    int n;

    void read()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> w[i];

        for (int i = 1; i < n; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int root = NULL_VERT;
    ll val = -1;

    void build_vert(int v, int p, bool active)
    {
        ll sum = 0;

        if (active)
            for (auto i : g[v])
                if (i != p)
                    sum += w[i];

        dp[v] = 0;

        int vert = NULL_VERT;
        for (auto i : g[v])
        {
            if (i == p) continue;

            ll calc = active ? dp[i] + w[v] : sum - w[i] + dp[i];

            if (calc >= dp[v])
                dp[v] = calc, vert = i;
        }

        if (vert != NULL_VERT)
            nxt[v][active][p] = vert;
    }
    
    void build_dfs(int v, int p, bool active)
    {
        dp[v] = 0;

        for (auto i : g[v])
            if (i != p)
                build_dfs(i, v, !active);

        build_vert(v, p, active);
    }

    void travel_dfs(int v, int p, bool active)
    {
        if (dp[v] > val)
            val = dp[v], root = v;

        for (auto i : g[v])
        {
            if (i == p) continue;

            ll old_curr = dp[v],
               old_nxt = dp[i];

            build_vert(v, i, true);
            build_vert(i, 0, true);

            travel_dfs(i, v, !active);

            dp[i] = old_nxt;
            dp[v] = old_curr;
        }
    }

    void print()
    {
        vector<int> vertices = {root};

        int v = root, p = NULL_VERT;
        bool status = true;

        while (nxt[v][status][p] != NULL_VERT)
        {
            int move = nxt[v][status][p];

            if (!status)
            {
                for (auto i : g[v])
                {
                    if (i == p || i == move) continue;
                    vertices.push_back(i);
                    vertices.push_back(v);
                }
            }

            vertices.push_back(move);

            p = v;
            v = move;
            status = !status;
        }

        int times = (1 + len(vertices)) / 2;

        cout << val << '\n';
        cout << times  << '\n';

        for (int i = 0; i < 2 * times - 1; i++)
            cout << vertices[i] << ' ';
        cout << '\n';
    }

    void solve()
    {
        vector<int> check = {1};

        if (g[1].size())
            check.push_back(g[1][0]);

        for (auto i : check)
        {
            build_dfs(i, NULL_VERT, true);
            travel_dfs(i, NULL_VERT, true);
        }
        print();
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