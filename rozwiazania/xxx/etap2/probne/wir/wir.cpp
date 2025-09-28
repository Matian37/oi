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
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int N = 7e2+5;

bitset<N> tmp[N];

void mult(bitset<N>& r, bitset<N>* t, int n)
{
    for (int i = 0; i < n; i++)
        tmp[0][i] = (r & t[i]).count() % 2;
    for (int i = 0; i < n; i++)
        r[i] = tmp[0][i];
}

void mult(bitset<N>* c, bitset<N>* w, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tmp[i][j] = (w[i] & c[j]).count() % 2;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[j][i] = w[i][j] = tmp[i][j];
}

namespace sol
{
    bitset<N> r;
    int n;
    ull d;

    void read()
    {
        cin >> n >> d;

        string c;
        cin >> c;

        for (int i = 0; i < n; i++)
            r[i] = (c[i]-'0');
    }

    bitset<N> col[N], wier[N];
    
    #define check(x,y) wier[x][y] = col[y][x] = 1

    void solve()
    {
        for (int i = 0; i < n - 1; i++)
            check(i+1,i);
        check(0,n-1);
        check(1,n-1);

        while (d != 0)
        {
            if (d % 2)
                mult(r, col, n);
            mult(col, wier, n);
            d /= 2;
        }

        for (int i = 0; i < n; i++)
            cout << r[i];
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