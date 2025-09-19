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
#define inRange(x,a,b) (a <= x && x <= b)
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
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    ull X;

    void read()
    {
        cin >> X;
    }

    const int N = 100, K = 59;

    char res[N][N];

    void print()
    {
        cout << N << '\n';
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << res[i][j];
            cout << '\n';
        }
    }

    void construct()
    {
        ii pos = {0,0};
        
        for (int i = 0; i <= K; i++)
        {
            // i'm lazy
            if (i % 2 == 0)
            {
                res[pos.fir][pos.sec] = '.';
                res[pos.fir + 1][pos.sec] = '.';
                res[pos.fir + 2][pos.sec] = '.';
                res[pos.fir + 1][pos.sec + 1] = '.';
                res[pos.fir + 2][pos.sec + 1] = '.';
                pos = {pos.fir + 2, pos.sec + 1};
            }
            else
            {
                res[pos.fir][pos.sec] = '.';
                res[pos.fir][pos.sec + 1] = '.';
                res[pos.fir][pos.sec + 2] = '.';
                res[pos.fir + 1][pos.sec + 1] = '.';
                res[pos.fir + 1][pos.sec + 2] = '.';
                pos = {pos.fir + 1, pos.sec + 2};
            }
        }

        ull pot = 1;
        int x = 0;
        pos = {3, 0};

        while (x <= K)
        {
            if ((X & pot) == 0)
                goto nxt1;

            for (int i = pos.fir; i < 100; i++)
                res[i][pos.sec] = '.';

            nxt1:
            x += 2;
            pot *= 4;
            pos.fir += 3, pos.sec += 3;
        }
        for (int i = 0; i < 100; i++)
            res[99][i] = '.';
        
        pot = 2, x = 1, pos = {2,4};

        while (x <= K)
        {
            if ((X & pot) == 0)
                goto nxt2;

            for (int i = pos.sec; i < 100; i++)
                res[pos.fir][i] = '.';

            nxt2:
            x += 2;
            pot *= 4;
            pos.fir += 3, pos.sec += 3;
        }
        for (int i = 0; i < 100; i++)
            res[i][99] = '.';
    }
    
    void solve()
    {
        for (int i = 0; i < N; i++)
            fill(res[i], res[i]+N, '#');
        if (X == 0)
        {
            print();
            return;
        }
        construct();
        print();
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