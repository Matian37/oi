//
// Mateusz Pietrowcow
//
 
#include <algorithm>
#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <functional>

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

const int N = 5e5+5;

vector<int> g[N], rg[N];
int n, m;

namespace scc
{
    vector<int> _g[N], _rg[N];
    int _n, _m;

    bitset<N> visited;
    int color[N];
    vector<int> cans[N];

    void read()
    {
        cin >> _n >> _m;

        for (int i = 0; i < _m; i++)
        {
            int a, b;
            cin >> a >> b;
            _g[a].push_back(b);
            _rg[b].push_back(a);
        }
    }

    void init()
    {
        read();

        vector<int> verts;
        function<void(int)> v_dfs = [&](int v)
        {
            visited[v] = true;

            for (auto i : _g[v])
                if (!visited[i])
                    v_dfs(i);

            verts.push_back(v);
        };

        for (int i = 1; i <= _n; i++)
            if (!visited[i])
                v_dfs(i);

        int col = 0;
        function<void(int)> c_dfs = [&](int v)
        {
            color[v] = col;
            cans[col].push_back(v);

            for (auto i : _rg[v])
                if (color[i] == 0)
                    c_dfs(i);
        };

        reverse(all(verts));
        for (auto i : verts)
            if (color[i] == 0)
                col++, c_dfs(i);

        n = col;

        for (int i = 1; i <= _n; i++)
            for (auto j : _g[i])
                if (color[i] != color[j])
                    g[color[i]].push_back(color[j]),
                    rg[color[j]].push_back(color[i]),
                    m++;

        for (int i = 1; i <= n; i++)
            sort(all(g[i])), sort(all(rg[i]), greater<int>());
    }
}

namespace sol
{
    int is_bad[N];

    void solve()
    {
        for (int i = 1; i <= n; i++)
        {
            int bl = rg[i].size() ? rg[i][0] : 0, 
                sr = g[i].size() ? g[i][0] : n + 1;

            if (bl != i - 1)
                is_bad[bl+1]++,
                is_bad[i+1]--; //i
            
            if (sr != i + 1)
                is_bad[i]++,
                is_bad[sr]--; //sr+1
        }

        for (int i = 1; i <= n; i++)
            is_bad[i] += is_bad[i - 1];

        vector<int> solves;

        for (int i = 1; i <= n; i++)
            if (is_bad[i] == 0)
                for (auto j : scc::cans[i])
                    solves.push_back(j);

        sort(all(solves));

        cout << len(solves) << '\n';
        for (auto i : solves) cout << i << ' ';
        cout << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    scc::init();
    sol::solve();
}