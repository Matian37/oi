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

const int N = 5e5+5;
int t[N];
ll pref[N];
int n;

namespace tree
{
    constexpr int base = 1 << 19;

    ll treeV[base * 2], treeQ[base * 2];

    void init(int v)
    {
        if (v >= base)
        {
            if (v - base >= n) treeV[v] = -INFLL;
            else treeV[v] = t[v - base] - pref[v - base];
            return;
        }

        init(v * 2);
        init(v * 2 + 1);

        treeV[v] = max(treeV[v * 2], treeV[v * 2 + 1]);
    }

    void push(int v)
    {
        treeV[v * 2] += treeQ[v];
        treeV[v * 2 + 1] += treeQ[v];
        treeQ[v * 2] += treeQ[v];
        treeQ[v * 2 + 1] += treeQ[v];
        treeQ[v] = 0;
    }

    int p, k;
    ll val;

    void __update(int v, int a, int b)
    {
        if (a > k || b < p) return;
        if (p <= a && b <= k)
        {
            treeV[v] += val;
            treeQ[v] += val;
            return;
        }
        int mid = (a + b) / 2;

        __update(v * 2, a, mid);
        __update(v * 2 + 1, mid + 1, b);

        treeV[v] = max(treeV[v * 2], treeV[v * 2 + 1]);
    }

    void update(int a, int b, ll __val)
    {
        p = a, k = b, val = __val;
        __update(1, 0, base - 1);
    }

    int query()
    {
        int v = 1;

        while (v < base)
        {
            push(v);

            v *= 2;
            if (treeV[v] <= 0) v++;
        }

        return v - base;
    }
}

namespace sol
{
    void read()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> t[i];
        
        for (int i = n - 2; i >= 0; i--)
            pref[i] = pref[i + 1] + t[i + 1];
    }
    
    void solve()
    {
        tree::init(1);

        ll r = pref[0] + t[0];

        vector<ll> v;
        v.reserve(n);
        v.push_back(r);

        for (int i = 1; i < n; i++)
        {
            int c = tree::query();

            if (c != 0)
                tree::update(0, c-1, t[c]);
            tree::update(c,c,-INFLL);

            r -= t[c];
            v.push_back(r);
        }

        for (int i = n - 1; i >= 0; i--)
            cout << v[i] << ' ';
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