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

constexpr int N = 3e5+5, L = 1e9;

#define add(x, y) x = min(x + y, L)

namespace tree
{
    constexpr int base = 1 << (1+__lg(N));

    int tree[base * 2];

    void clear()
    {
        fill(tree, tree+(base*2), 0);
    }

    void update(int a, int b, int v)
    {
        a += base - 1;
        b += base + 1;

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) add(tree[a + 1], v);
            if (b % 2 == 1) add(tree[b - 1], v);
            a /= 2;
            b /= 2;
        }
    }

    int query(int a)
    {
        a += base;

        int r = 0;

        while (a != 0)
        {
            add(r, tree[a]);
            a /= 2;
        }

        return r;
    }
}

namespace sol
{
    pair<ii, int> zap[N];
    vector<int> apr[N];
    int owns[N], req[N];
    int n, m, q;

    void read()
    {
        cin >> n >> m;

        for (int i = 1; i <= m; i++)
        {
            cin >> owns[i];
            apr[owns[i]].push_back(i);
        }

        for (int i = 1; i <= n; i++)
            cin >> req[i];

        cin >> q;

        for (int i = 1; i <= q; i++)
            cin >> zap[i].fir.fir >> zap[i].fir.sec >> zap[i].sec;
    }

    ii rang[N];

    int sum(int k)
    {
        int res = 0;

        for (auto i : apr[k]) 
            add(res, tree::query(i));

        return res;
    }
    
    void solve()
    {
        for (int i = 1; i <= n; i++)
            rang[i] = {1, q+1};

        int iters = __lg(q+1) + min(1, __builtin_popcount(q+1));

        while (iters--)
        {
            tree::clear();

            vector<ii> mids;

            for (int i = 1; i <= n; i++)
                mids.push_back({(rang[i].fir + rang[i].sec) / 2, i});
            sort(all(mids));

            for (int i = 1, j = 0; i <= q; i++)
            {
                int A = zap[i].fir.fir,
                    B = zap[i].fir.sec, 
                    V = zap[i].sec;

                if (A > B)
                {
                    tree::update(1, B, V);
                    tree::update(A, m, V);
                }
                else
                    tree::update(A, B, V);

                while (j < len(mids))
                {
                    if (mids[j].fir >= i) break;
                    j++;
                }

                while (j < len(mids))
                {
                    if (mids[j].fir != i) break;

                    int comp = mids[j].sec;

                    if (sum(comp) >= req[comp])
                        rang[comp].sec = i;
                    else
                        rang[comp].fir = i+1;

                    j++;
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            #ifdef LOCAL
                assert(rang[i].fir == rang[i].sec);
            #endif

            cout << (rang[i].fir == q+1 ? "NIE" : to_string(rang[i].fir)) << '\n';
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