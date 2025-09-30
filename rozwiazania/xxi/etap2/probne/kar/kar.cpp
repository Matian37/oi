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

struct TreeInfo
{
    int l[2], r[2];
    bool poss[2][2];
};


namespace tree
{
    int base;
    TreeInfo tree[1<<21];

    #define NEVER TreeInfo{{-1, -1}, {INF, INF},{{0,0}, {0,0}}}
    #define ALWAYS TreeInfo{{INF, INF}, {-1, -1}, {{1, 1}, {1, 1}}}

    void init(int n)
    {
        base = 1<<(__lg(n)+1);
        fill(tree, tree+base*2, ALWAYS);
    }

    TreeInfo merge(TreeInfo& a, TreeInfo& b)
    {
        TreeInfo def = NEVER;

        bool done = false;

        for (int i = 0; i < 4; i++)
        {
            if (!a.poss[i & 1][i >> 1])
                continue;

            for (int j = 0; j < 4; j++)
            {
                if (!b.poss[j & 1][j >> 1])
                    continue;
                if (a.r[i >> 1] > b.l[j & 1])
                    continue;

                done = true;
                def.poss[i & 1][j >> 1] = true;
            }
        }

        if (done)
        {
            for (int i = 0; i < 2; i++)
                def.l[i] = a.l[i], 
                def.r[i] = b.r[i];
        }

        return def;
    }

    void update(int x, ii val)
    {
        int tval[] = {val.fir, val.sec};

        x += base;

        tree[x] = {
            {val.fir, val.sec}, 
            {val.fir, val.sec}, 
            {{0,0},{0,0}}
        };
        for (int i = 0; i < 4; i++)
            tree[x].poss[i & 1][i >> 1] = tval[i & 1] <= tval[i >> 1];

        x /= 2;

        while (x != 0)
        {
            tree[x] = merge(tree[x*2], tree[x*2+1]);
            x /= 2;
        }
    }

    inline bool possible()
    {
        return tree[1].l[0] != -1;
    }
}

namespace sol
{
    int n;

    void read()
    {
        cin >> n;

        tree::init(n);

        for (int i = 1; i <= n; i++)
        {
            ii a;
            cin >> a.fir >> a.sec;
            tree::update(i, a);
        }
    }
    
    void solve()
    {
        int q;
        cin >> q;

        while (q--)
        {
            int a, b;
            cin >> a >> b;

            auto l = tree::tree[a + tree::base].l,
                 r = tree::tree[b + tree::base].l;

            ii x = {l[0], l[1]}, y = {r[0], r[1]};

            tree::update(a, y);
            tree::update(b, x);

            cout << (tree::possible() ? "TAK\n" : "NIE\n");
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