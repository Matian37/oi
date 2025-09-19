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

namespace sol
{
    const int N = 2e2+5, K = 2e4+5;

    struct move
    {
        int x;

        move(){x=0;}

        move(int w, int k)
        {
            x = (w << 15) + k;
        }

        ii get()
        {
            return {x>>15,x%(1<<15)};
        }
    };

    ii b[N];
    pair<int,move> dp[K][N];
    int n, k, token = 0;

    void read()
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> b[i].fir;
        for (int i = 0; i < n; i++)
            cin >> b[i].sec;
        cin >> k;
    }

    inline void __attribute__((always_inline)) iter(int w, int __w, int __k)
    {
        if (w == 0 || w > k) return;

        ++token;

        int curr = token, last = token - 1;

        for (int i = 0; i < w; i++)
            dp[i][curr] = dp[i][last];
        for (int i = w; i <= k; i++)
        {
            if (__k + dp[i - w][last].fir < dp[i][last].fir)
                dp[i][curr] = {dp[i - w][last].fir + __k, move(__w, __k)};
            else 
                dp[i][curr] = dp[i][last];
        }
    }

    hashmap_prime<int,int,chash> id;
    int lic[N]; 
    
    void solve()
    {
        for (int i = 0; i <= k; i++)
            dp[i][0] = dp[i][1] = {INF, move(0,0)}; 
        dp[0][0] = {0,move(0,0)};

        for (int i = 0; i < n; i++)
        {
            int done = 0;

            for (int j = 0; j < __lg(b[i].sec); j++)
            {
                iter((1<<j)*b[i].fir, b[i].fir, (1<<j));
                done += (1<<j);
            }
            iter(b[i].fir * (b[i].sec - done), b[i].fir, (b[i].sec - done));
        }

        for (int i = 0; i < n; i++)
            id[b[i].fir] = i;

        int curr = token;

        cout << dp[k][curr].fir << '\n';

        while (k != 0)
        {
            move mv = dp[k][curr].sec;
            lic[id[mv.get().first]] += mv.get().second;
            k -= mv.get().first * mv.get().second;
            curr--;
        }

        for (int i = 0; i < n; i++)
            cout << lic[i] << ' ';
        cout << '\n';
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