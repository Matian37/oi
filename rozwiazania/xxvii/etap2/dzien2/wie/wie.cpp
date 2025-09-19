//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;


#define int long long

using ll = long long;
//using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ll,ll>;
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
#define inRange(x,a,b) ((a) <= (x) && (x) <= (b))
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

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
        const static int rng = (int)timeNow() ^ (int)(ll)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace curr
{
    const int base = 1 << 20;
    pair<ll,int> tree[base * 2];

    void __add(int v, int r, int c)
    {
        v += base;

        while (v != 0)
        {
            tree[v].fir += r;
            tree[v].sec += c;
            v /= 2;
        }
    }

    inline void add(int r)
    {
        __add(r,r,1);
    }

    inline void rem(int r)
    {
        __add(r,-r,-1);
    }

    pair<ll,int> __sum(int v, int k)
    {
        if (k <= 0) return {0,0};
        if (tree[v].sec <= k) return tree[v];
        if (v >= base) return {(ll)(v-base) * k, k};
        
        auto r1 = __sum(v*2+1, k), r2 = __sum(v*2,k-r1.sec);

        return {r1.fir+r2.fir,r1.sec+r2.sec};
    }

    ll sum(int k)
    {
        return __sum(1, k).fir;
    }

    int size()
    {
        return tree[1].sec;
    }

    void clear()
    {
        fill(tree,tree+base*2,pair<ll,int>{0,0});
    }
};

namespace sol
{
    struct info
    {
        ll first; // pos
        int second; // height
        int third; // counts

        bool operator<(const info& a)
        {
            return first < a.first;
        }
    };

    const int N = 2e5+5;
    info kloc[N], __k[N];
    int n, __n;

    int H1, H2;
    ll N1, N2;
    ll full = 0, blocks = 0;

    inline ll dist(int a)
    {
        return max(0LL, (kloc[a + 1].fir - (kloc[a].fir + kloc[a].sec) + H1 - 1) / H1 * H1);
    }

    inline ll rest(int a)
    {
        return dist(a) % H2;
    }

    bool good()
    {
        ll p = N1 - blocks, q = N2;

        if (p >= 0) return true;

        ll f = min(full, q);
        p += f*(H2/H1);
        q -= f;

        if (p >= 0) return true;
        if (q == 0) return false;

        p += curr::sum((int)q) / H1;
        q = 0;

        return p >= 0;
    }

    void join()
    {
        n = 0;

        int i = 0, j;

        while (i < __n)
        {
            j = i;

            ll dist = __k[i].fir + __k[i].sec;

            while (j + 1 < __n)
            {
                if (dist < __k[j + 1].fir)
                    break;
                j++;
                dist = max(dist, __k[j].fir + __k[j].sec);
            }

            kloc[n++] = {__k[i].fir, dist-__k[i].fir, j-i+1};
            i = j + 1;
        }
    }

    ll solve()
    {
        sort(__k, __k + __n);
        join();
        full = blocks = 0;

        curr::clear();

        ll best = 0;

        int dl = kloc[0].third;

        for (int i = 0, j = 0; i < n; i++, j = max(i, j))
        {
            while (j + 1 < n)
            {
                ll d = dist(j), r = rest(j);

                curr::add((int)r);
                blocks += d / H1;
                full += d / H2;
                dl += kloc[j+1].third;

                if (!good())
                {
                    curr::rem((int)r);
                    blocks -= d / H1;
                    full -= d / H2;
                    dl -= kloc[j+1].third;
                    break;
                }

                j++;
            }

            best = max(best, N1+N2+dl);

            if (i + 1 <= j)
            {
                curr::rem((int)rest(i));
                blocks -= dist(i) / H1;
                full -= dist(i) / H2;
                dl -= kloc[i].third;
            }
        }

        return best;
    }

    void read()
    {
        cin >> __n;
        
        for (int i = 0; i < __n; i++)
            cin >> __k[i].fir >> __k[i].sec;
        cin >> N1 >> H1 >> N2 >> H2;

        if (H1 > H2) swap(H1, H2), swap(N1, N2);
    }

    void swp()
    {
        for (int i = 0; i < __n; i++)
            __k[i].fir = (__k[__n - 1].fir - __k[i].fir);
    }
};
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    
    ll r = sol::solve();
    sol::swp();
    cout << max(sol::solve(), r) << '\n';
}