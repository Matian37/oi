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

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int N = 5e5 + 5; 
vector<int> g[N];
int n, q;

namespace sol
{
    int stp[N], parent[N];
    bitset<N> isBlack;
    int c = 0;

    void read()
    {
        cin >> n;

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    void dfs(int v, int p)
    {
        parent[v] = p;

        for (auto i : g[v])
        {
            if (i == p) continue;
            dfs(i, v);
        }
    }

    void solve()
    {
        g[0].push_back(1);
        g[1].push_back(0);

        isBlack[0] = true;
        stp[0] = 1;
        c++;

        for (int i = 1; i <= n; i++)
            stp[i] = isize(g[i]) - 1;

        dfs(1, 0);

        cin >> q;

        while (q--)
        {
            int v;
            cin >> v;

            bool isAdded = v > 0;
            v = abs(v);

            if (isAdded)
            {
                if (stp[v] != 0)
                {
                    if (isBlack[parent[v]]) c += stp[v] - 1;
                    else c += stp[v];
                }
                else if (isBlack[parent[v]]) c--;
                stp[parent[v]]--;
            }
            else
            {
                if (stp[v] != 0)
                {
                    if (isBlack[parent[v]]) c -= stp[v] - 1;
                    else c -= stp[v];
                }
                else if (isBlack[parent[v]]) c++;     
                stp[parent[v]]++;
            }

            isBlack[v].flip();

            cout << c << '\n';
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