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
    const int N = 5e5 + 5;
    vector<int> g[N];
    int n;
    ll t[N];

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> t[i];
    
        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    ll brut(vector<pll>& v, ll sum)
    {
        struct cmp
        {
            bool operator()(const pll& a, const pll& b) const
            {
                if (a.first != b.first) return a.first < b.first;
                return a.second > b.second;
            }
        };

        multiset<pll,cmp> pq;

        for (int i = 0; i < isize(v); i++)
            pq.insert(v[i]);

        ll k = 0;

        while (sum != 0)
        {
            auto acc = *pq.begin();
            pq.erase(pq.begin());

            k = max(k, sum + acc.fir);

            sum -= acc.sec;
        }

        return k;
    }

    pll dfs(int v, int p)
    {
        if (g[v].size() == 1 && v != 1)
            return {1 + t[v], 2};

        vector<pll> vec;
        ll sum = 0;

        for (auto i : g[v])
        {
            if (i == p) continue;

            auto r = dfs(i, v);

            vec.push_back({r.fir - r.sec, r.sec});
            sum += r.sec;
        }

        sort(all(vec),[](const pll& a , const pll& b)
        {
            if (a.fir != b.fir) return a.fir < b.fir;
            return a.sec > b.sec;
        });

        ll low = brut(vec, sum);

        if (v != 1)
            return {max(low,t[v])+1, sum + 2};
        return {max(low,sum + t[v]),sum};
    }

    ll solve()
    {
        return dfs(1,0).fir;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    cout << sol::solve() << '\n';
}