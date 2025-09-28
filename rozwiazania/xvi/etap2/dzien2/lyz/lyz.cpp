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

#define pbds __gnu_pbds
#define cxx __gnu_cxx
#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() chrono::high_resolution_clock::now().time_since_epoch().count()
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

const int N = 2e5 + 5, base = 1 << 18;

namespace tree
{
    struct info
    {
        ll pref, suff, res, sum;
    };

    info tree[base * 2];

    ll query()
    {
        return tree[1].res;
    }

    void update(int a, ll v)
    {
        a += base;

        tree[a] = {v, v, v, v};
        a /= 2;

        while (a != 0)
        {
            ll r;

            if (tree[a * 2].suff < 0 && tree[a * 2 + 1].pref < 0) 
                r = max(tree[a * 2].suff, tree[a * 2 + 1].pref);
            else 
                r = max(0LL, tree[a * 2].suff) + max(0LL, tree[a * 2 + 1].pref);

            tree[a].res = max({tree[a * 2].res, tree[a * 2 + 1].res, r});
            tree[a].sum = tree[a * 2].sum + tree[a * 2 + 1].sum;
            tree[a].pref = max(tree[a * 2].pref, tree[a * 2].sum + tree[a * 2 + 1].pref);
            tree[a].suff = max(tree[a * 2 + 1].suff, tree[a * 2].suff + tree[a * 2 + 1].sum);
        
            a /= 2;
        }
    }
}

namespace sol
{
    ll t[base];

    int n, m, k, d;

    void read()
    {
        cin >> n >> m >> k >> d;

        int lg = 1 << (__lg(n) + (int)(n != 1 << __lg(n)));

        for (int i = 0; i < lg; i++)
        {
            tree::update(i, -k);
            t[i] = -k;
        }
    }
    
    void solve()
    {
        while (m--)
        {
            int a;
            ll b;
            cin >> a >> b;

            tree::update(a, t[a] + b);

            t[a] += b;

            if (tree::query() <= (ll)d * k)
                cout << "TAK\n";
            else
                cout << "NIE\n";
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