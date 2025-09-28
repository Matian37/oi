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
    size_t operator()(const ull& a) const
    {
        const static ull rng = timeNow() ^ (ull)(make_unique<char>().get());
        return a ^ rng;
    }

    size_t operator()(const pair<ull, bool>& a) const
    {
        const static ull rng = timeNow() ^ (ull)(make_unique<char>().get());
        return ((a.fir ^ rng) << 1) + ull(a.sec);
    }
};

void read_bytes(ull& x)
{
    string _x;
    cin >> _x;

    x = 0;

    for (int i = 0; i < len(_x); i++)
        x = x * 2 + (_x[i] - '0');
}

namespace sol
{
    gp_hashmap_safe<ull, pbds::null_type, chash> excl;

    ull x, y;
    int n, k;

    void read()
    {
        cin >> n >> k;

        read_bytes(x);
        read_bytes(y);

        for (int i = 0; i < k; i++)
        {
            ull a;
            read_bytes(a);
            excl.insert(a);
        }
    }

    set<pair<ull, bool>> vis;
    
    bool check()
    {
        #define if_404(A, B) (B.find(A) != B.end())

        queue<pair<ull, bool>> q;

        q.push({x, false});
        q.push({y, true});

        int l[2] = {1, 1};

        while (q.size())
        {
            if (l[0] == 0 || l[1] == 0)
                return false;

            auto curr = q.front();
            q.pop(), l[curr.sec]--;

            if (if_404(curr, vis))
                continue;
            if (if_404(make_pair(curr.fir, !curr.sec), vis))
                return true;

            vis.insert(curr);

            for (int i = 0; i < n; i++)
            {
                pair<ull, bool> nxt = {curr.fir ^ (1ULL<<i), curr.sec};

                if (if_404(nxt.fir, excl)) continue;
                if (if_404(nxt, vis)) continue;

                q.push(nxt), l[nxt.sec]++;
            }
        }

        return false;
    }

    void solve()
    {
        cout << (check() ? "TAK" : "NIE") << '\n';
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