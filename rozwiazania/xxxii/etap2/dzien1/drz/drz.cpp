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

// best primes in the galaxy
#define MOD 1000000000000000003ULL

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

const int N = 21;
constexpr int MAX_BASE = 1 << 20;

ull P[N], p;

#define intify(x) (x-'a'+1)
#define mod(x) ull((x)%MOD)

#define unsafe_mult(x,y) (uint128(x) * uint128(y))
#define mult(x,y) mod(unsafe_mult(x,y))

#define merge(x,y,l) mod(unsafe_mult(min(x,y), P[l]) + max(x,y))


struct tree
{
    int base;
    ull tree[MAX_BASE * 2];

    void init(int n, string& s)
    {
        base = 1<<n;

        function<int(int)> _init = [&](int v)
        {
            if (v >= base)
            {
                if (v - base < len(s))
                    tree[v] = intify(s[v - base]);
                return 0;
            }

            _init(v*2); 
            int l = 1 + _init(v*2+1);

            tree[v] = merge(tree[v * 2], tree[v * 2 + 1], l);

            return l;
        };
        _init(1);
    }
    
    void update(int v, char c)
    {
        v += base;
        tree[v] = intify(c);
        v /= 2;

        int lng = 1;
        while (v != 0)
        {
            tree[v] = merge(tree[v*2], tree[v*2+1], lng);
            v /= 2;
            lng++;
        }
    }

    ull hash()
    {
        return tree[1];
    }
};

namespace sol
{
    tree tn, ta;
    
    int n, q;

    void read()
    {
        cin >> n >> q;

        mt19937 rng(timeNow());

        p = uniform_int_distribution<ull>(2,MOD-2)(rng);
        P[0] = 1;
        P[1] = p;

        for (int i = 1; i <= n; i++)
            P[i + 1] = mult(P[i], P[i]);

        string name;
        cin >> name;
        tn.init(n, name);

        string anc;
        cin >> anc;
        ta.init(n, anc);
    }
    
    void solve()
    {
        #define print() cout << (ta.hash() == tn.hash() ? "TAK\n" : "NIE\n")

        print();
        while (q--)
        {
            int t;
            cin >> t;

            int v;
            char c;
            cin >> v >> c;
            v--;

            if (t == 1) tn.update(v, c);
            else ta.update(v, c);

            print();
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