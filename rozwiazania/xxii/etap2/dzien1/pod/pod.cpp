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
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

// best primes in te galaxy
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

const int N = 1e6+5, LG = 20;

namespace tree
{
    const int base = 1 << 20;

    struct info
    {
        int min, max, sum;
    };

    info treeV[base * 2];
    bool treeQ[base * 2];

    constexpr info DEF = {INF,-INF,0};

    inline info join(info a, info b)
    {
        return {min(a.min, b.min), max(a.max, b.max), a.sum + b.sum};
    }

    void init()
    {
        for (int i = base * 2 - 1; i >= base; i--)
            treeV[i] = {i - base, i - base, 1};
        for (int i = base - 1; i >= 0; i--)
            treeV[i] = join(treeV[i * 2], treeV[i * 2 + 1]);
    }

    void __push(int v)
    {
        if (!treeQ[v]) return;

        treeV[v * 2] = treeV[v * 2 + 1] = DEF;
        treeQ[v * 2] = treeQ[v * 2 + 1] = true;
        treeQ[v] = false;
    }

    int p, k;

    void __update(int v, int a, int b)
    {
        if (b < p || a > k)
            return;
        if (p <= a && b <= k)
        {
            treeV[v] = DEF;
            treeQ[v] = true;
            return;
        }

        int mid = (a + b) / 2;

        __push(v);
        __update(v * 2, a, mid);
        __update(v * 2 + 1, mid + 1, b);

        treeV[v] = join(treeV[v * 2], treeV[v * 2 + 1]);
    }

    void update(int _p, int _k) {p = _p, k = _k; __update(1, 0, base - 1);}

    info __query(int v, int a, int b)
    {
        if (b < p || a > k)
            return DEF;
        if (p <= a && b <= k)
            return treeV[v];

        int mid = (a + b) / 2;

        __push(v);
        return join(__query(v * 2, a, mid), __query(v * 2 + 1, mid + 1, b));
    }

    info query(int _p, int _k)
    {
        p = _p, k = _k; 
        return __query(1, 0, base - 1);
    }
}

struct sparse_table
{
    int t[N][LG];

    void init(int *__t, int n)
    {
        for (int i = 0; i < n; i++)
            t[i][0] = __t[i];
        
        for (int i = 1; i < LG; i++)
            for (int j = 0; j <= n - (1 << i); j++)
                t[j][i] = min(t[j][i - 1], t[j + (1 << (i - 1))][i - 1]);
    }

    inline int query(int a, int b)
    {
        int lg = __lg(b-a+1);
        return min(t[a][lg], t[b - (1 << lg) + 1][lg]);
    }
};

namespace sol
{
    int t[N], left[N];
    int n, k;

    void read()
    {
        cin >> n >> k;

        for (int i = 0; i < n; i++)
            cin >> t[i];
        for (int i = n - 1; i >= 0; i--)
            left[t[i]] = i;
    }

    sparse_table jumpLeft;

    int leftEl[N];

    void init()
    {
        for (int i = 0; i < n; i++)
            leftEl[i] = left[t[i]];

        jumpLeft.init(leftEl, n);
        tree::init();
    }

    int last[N];
    
    void solve()
    {
        init();

        pair<ll,int> r = {0, n};
        // solutions, difference

        for (int i = n - 1; i > 0; i--)
        {
            if (last[t[i]] != 0)
                tree::update(i, last[t[i]] - 1);
            last[t[i]] = i;

            int accEnd = [&]()
            {   
                int low = i, high = n, med;

                while (low != high)
                {
                    med = (low + high) / 2;

                    if (jumpLeft.query(i, med) >= i) low = med + 1;
                    else high = med;
                }

                return low - 1;
            }();


            if (accEnd < i) 
                continue;
            
            // query
            tree::info l, ri;
            l = ri = tree::DEF;

            l = tree::query(i, min(accEnd, i + n / 2 - 1));
            int lenl = l.max - i + 1, lenr = n;

            if (i + n / 2 <= accEnd)
            {
                ri = tree::query(i + n / 2, accEnd);
                lenr = ri.min - i + 1;
            }

            r.first += l.sum + ri.sum;
            r.second = min({r.second, abs(n - 2 * lenl), abs(n - 2 * lenr)});
        }

        cout << r.first << ' ' << r.second << '\n';
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