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

namespace tree
{
    const int base = 1<<17;

    int tree[base * 2];

    void update(int x, int v)
    {
        x += base;
        tree[x] = v;
        x /= 2;

        while (x != 0)
        {
            tree[x] = max(tree[x*2],tree[x*2+1]);
            x /= 2;
        }
    }

    int query(int a, int b)
    {
        a += base - 1;
        b += base + 1;

        int r = 0;

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) r = max(r, tree[a + 1]);
            if (b % 2 == 1) r = max(r, tree[b - 1]);

            a /= 2;
            b /= 2;
        }

        return r;
    }
};

namespace sol
{
    const int N = 1e5+5;
    pair<ii,int> p[N];
    int n, m, k;

    void read()
    {
        cin >> n >> m >> k;

        for (int i = 0; i < k; i++)
            cin >> p[i].fir.fir >> p[i].fir.sec >> p[i].sec;
    }

    void skaluj()
    {
        map<int,int> x, y;

        for (int i = 0; i < k; i++)
            x[p[i].fir.fir], y[p[i].fir.sec];

        int lic = 0;
        for (auto& i : x)
            i.second = lic++;

        lic = 0;
        for (auto& i : y)
            i.second = lic++;

        for (int i = 0; i < k; i++)
            p[i].fir.fir = x[p[i].fir.fir],
            p[i].fir.sec = y[p[i].fir.sec];
    }
    
    void solve()
    {
        skaluj();

        sort(p,p+k, [&](const pair<ii,int>& a, const pair<ii,int>& b)
        {
            if (a.fir.sec != b.fir.sec) return a.fir.sec < b.fir.sec;
            return a.fir.fir < b.fir.fir;
        });

        int best = 0;

        for (int i = 0; i < k; i++)
        {
            int curr = p[i].sec + tree::query(0, p[i].fir.fir);
            best = max(best, curr);
            tree::update(p[i].fir.fir, curr);
        }
        cout << best << '\n';
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