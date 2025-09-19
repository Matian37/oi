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

const int N = 1e6+5;
int t[N], pref[N], n, q;

int real_value[N];

#define lng(a, b) ((b)-(a)+1)
#define get_pref0(v, a, b) (lng(a,b) - (tree[v][b].pr - tree[v][(a) - 1].pr))
#define get_pref1(v, a, b) (tree[v][b].pr - tree[v][(a) - 1].pr)
#define get_prefr(v, a, b) (tree[v][b].rpr - tree[v][(a) - 1].rpr)

namespace wt
{
    #ifdef LOCAL
    const int base = 1 << 5; // to be fixed
    #else
    const int base = 1 << 20;
    #endif

    #define pr first
    #define rpr second

    vector<ii> tree[base * 2];

    void add(int v, int a, int b, int x)
    {
        int mid = (a + b + 1) / 2;

        tree[v].push_back({tree[v].back().pr + (x >= mid),
                           tree[v].back().rpr + real_value[x]});

        if (a == b) return;
        if (x >= mid) add(v * 2 + 1, mid, b, x);
        else add(v * 2, a, mid - 1, x);
    }

    void init()
    {
        for (int i = 0; i < base * 2; i++)
            tree[i].push_back({0,0});

        for (int i = 1; i <= n; i++) 
            add(1, 0, n, (i%2) * t[i]);
    }

    int va, vb, a, b;

    int __query(int v, int k)
    {
        if (tree[v].size() == 1 || k <= 0) 
            return 0;
        if (va == vb) 
            return (va == 0 ? 0 : real_value[va] * min(k, get_prefr(v, a, b)/real_value[va]));

        int z1 = get_pref1(v, a, b),
            a1 = get_pref1(v, 1, a-1) + 1,
            b1 = get_pref1(v, 1, b);
        
        if (z1 <= k)
        {
            int right = (z1 > 0 && get_pref1(v, a, b) != 0 ? get_prefr(v*2+1, a1, b1) : 0);

            if (get_pref0(v, a, b) == 0)
                return right;
            
            a = get_pref0(v, 1, a-1) + 1,
            b = get_pref0(v, 1, b);
            vb = (va + vb + 1) / 2 - 1;

            return right + __query(v * 2, k - z1);
        }

        a = a1;
        b = b1;
        va = (va + vb + 1) / 2;

        return (z1 == 0 ? 0 : __query(v * 2 + 1, k));
    }

    inline int query(int __a, int __b, int k)
    {
        va = 0, vb = n, a = __a, b = __b;
        return __query(1, k);
    }
}

namespace sol
{
    void read()
    {
        cin >> n >> q;

        for (int i = 1; i <= n; i++)
        {
            cin >> t[i];
            pref[i] = pref[i - 1] + t[i];
        }
    }

    void skaluj()
    {
        map<int,int> tmp;

        for (int i = 1; i <= n; i++)
            tmp[t[i]];

        int lic = 0;
        for (auto &i : tmp)
        {
            ++lic;
            i.sec = lic;
            real_value[lic] = i.fir;
        }
        real_value[0] = 0;

        for (int i = 1; i <= n; i++)
            t[i] = tmp[t[i]];
    }

    int binsearch(int* p, int start, int meta, int k)
    {
        int low = start, high = meta, med;

        while (low != high)
        {
            med = (low + high) / 2;
            if (p[med] < k) low = med + 1;
            else high = med;
        }

        return low;
    }
    
    void solve()
    {
        skaluj();
        wt::init();
        
        for (int i = 1; i <= q; i++)
        {
            int a, b, k;
            cin >> a >> b >> k;

            int start = binsearch(pref, 1, n, a),
                meta = binsearch(pref, 1, n, b);

            if (k == 0 || start == meta)
            {
                if (start == meta && start % 2)
                    cout << (b-a+1) << '\n';
                else
                    cout << "0\n";
                continue;
            }
            else if (meta - start == 1)
            {
                int s1 = (start % 2) * lng(a, pref[start]), 
                    s2 = (meta % 2) * lng(pref[start]+1, b);
                cout << (s1 + s2) << '\n';
                continue;
            }
        
            int cnt1 = (lng(start + 1, meta - 1) + 1) / 2;
            int odp[3] = {};

            for (int j = 0; j < min(3,k+1); j++)
                odp[j] = wt::query(start + 1, meta - 1, min(cnt1, (k - j) / 2));
            
            int l = (start % 2) * lng(a,pref[start]),
                r = (meta % 2) * lng(pref[meta - 1] + 1, b);

            if (k >= 1) odp[1] += max(l, r);
            if (k >= 2) odp[2] += l+r;

            cout << *max_element(odp,odp+3) << '\n';
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