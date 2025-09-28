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

struct hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int N = 1e4 + 5;

namespace sol
{
    set<int> g[N];
    ii edge[N];
    int cnt[N];
    bitset<N> result;
    int n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 1; i <= m; i++)
        {
            cin >> edge[i].fir >> edge[i].sec;

            g[edge[i].fir].insert(i);
            g[edge[i].sec].insert(i);
        }
    }
    
    set<ii> pq;

    void solve()
    {
        for (int i = 1; i <= n; i++)
            pq.insert({isize(g[i]), i});
        
        int k = 0;

        while (!pq.empty())
        {
            auto[stp, v] = *pq.begin();
            pq.erase(pq.begin());

            for (auto i : g[v])
            {
                int a = v,
                    b = (edge[i].fir == a ? edge[i].sec : edge[i].fir);

                pq.erase({isize(g[b]), b});

                g[b].erase(i);

                result[i] = (edge[i].fir == a);

                pq.insert({isize(g[b]), b});

            }

            k = max(stp, k);

            cnt[v] = stp;
        }

        cout << k << '\n';
        for (int i = 1; i <= m; i++)
            cout << result[i] << '\n';
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