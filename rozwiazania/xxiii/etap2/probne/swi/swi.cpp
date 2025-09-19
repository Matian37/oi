//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

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
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using hashmap_bit = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmap_prime = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
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

namespace fu
{
    int fu[19][N], ranks[19][N];

    void init(int n)
    {
        for (int j = 0; j < 19; j++)
            for (int i = 1; i <= n; i++)
                fu[j][i] = i, ranks[j][i] = 1;
    }

    int find(int a, int l)
    {
        if (fu[l][a] == a)
            return a;
        return fu[l][a] = find(fu[l][a], l);
    }

    void Union(int a, int b, int l)
    {
        a = find(a, l), b = find(b, l);

        if (a == b) return;
        if (ranks[l][a] > ranks[l][b]) swap(a,b);

        ranks[l][b] += ranks[l][a];
        fu[l][a] = b;
    }
};

namespace sol
{
    int t[N];
    int n, m;

    void read()
    {
        cin >> n >> m;

        fu::init(n);

        for (int i = 0; i < m; i++)
        {
            int a, b, l;
            cin >> a >> b >> l;

            fu::Union(a, b, __lg(l));
            fu::Union((a+l)-(1<<__lg(l)), (b+l)-(1<<__lg(l)), __lg(l));
        }
    }
    
    void solve()
    {
        for (int i = __lg(n); i > 0; i--)
        {
            for (int j = 1; j <= n - (1<<i) + 1; j++)
            {
                int b = fu::find(j, i);

                if (j != b)
                {
                    fu::Union(j, b, i - 1);
                    fu::Union(j + (1 << (i-1)), b + (1 << (i-1)), i - 1);
                }
            }
        }

        int r = 0;

        for (int i = 1; i <= n; i++)
            r += (fu::find(i, 0) == i);
        cout << r << '\n';
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