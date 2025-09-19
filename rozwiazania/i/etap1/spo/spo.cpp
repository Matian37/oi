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
#define int128 __int128_t;
#define uint128 __uint128_t;

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace tree
{
    const int base = 1 << 14;

    int tree[base * 2];

    void update(int a, int val)
    {
        a += base;
        tree[a] = val;
        a /= 2;

        while (a != 0)
        {
            tree[a] = max(tree[a * 2], tree[a * 2 + 1]);
            a /= 2;
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
}

namespace sol
{
    vector<int> t;
    int n;

    void read()
    {
        cin >> n;

        t.resize(n);

        for (int i = 0; i < n; i++)
        {
            string c;
            cin >> c;

            c.erase(c.begin() + 2);

            t[i] = stoi(c) - 20000;
        }        
    }
    
    void solve()
    {
        for (int i = 0; i < n; i++)
        {
            int val = tree::query(t[i]+1, 10001) + 1;

            tree::update(t[i], val);
        }

        cout << (ull)tree::query(0, tree::base - 1) * 100ULL << '\n';
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