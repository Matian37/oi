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
    using hm = cc_hashmap_safe<int,pbds::null_type,chash>;

    const int N = 1e5+5;
    hm g[N];
    vector<ii> edges;
    int n, m;

    void read()
    {
        cin >> n >> m;

        edges.clear();
        for (int i = 1; i <= n; i++)
            g[i].clear(); // unsafe?

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].insert(b);
            g[b].insert(a);

            edges.push_back({a, b});
        }
    }
    
    bool solve()
    {
        #define conn(a, b) int(g[a].find(b) != g[a].end())

        for (auto[x,y] : edges)
        {
            int sm = len(g[x]) < len(g[y]) ? x : y;

            for (auto a : g[sm])
            {
                if (!conn(x, a)) continue;
                if (!conn(y, a)) continue;

                int sk = sm;

                if (len(g[a]) < len(g[sk]))
                    sk = a;

                for (auto j : g[sk])
                {
                    if (j == x || j == y || j == a)
                        continue;
                        
                    int res = conn(x, j) + conn(y, j) + conn(a, j);
    
                    if (res == 2)
                    {
                        cout << "TAK\n";
                        cout << x << ' ' << y << ' ' << a << ' ' << j << '\n';
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    int z;
    cin >> z;

    while (z--)
    {
        sol::read();

        if (!sol::solve()) 
            cout << "NIE\n";
    }
}