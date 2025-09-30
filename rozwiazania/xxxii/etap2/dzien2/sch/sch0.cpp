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
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace dt
{
    list<pll> t;
    ll shift, max_time;

    #define maxout() if (t.size()) self(max, max_time, shift + t.back().sec)

    void clear()
    {
        shift = max_time = 0;
        t.clear();
    }

    void _eat(ll l)
    {
        #define length(x) (x.sec-x.fir)

        while (l != 0 && len(t))
        {
            auto& curr = t.back();
            
            if (length(curr) <= l)
            {
                l -= length(curr);
                t.pop_back();
                continue;
            }
            
            curr.sec -= l;
        }
    }

    void resolve(ll l)
    {
        shift += max(1LL, l); // move++

        maxout();

        if (l < 0) _eat(-l);
        else t.push_front({-shift, -shift + l});

        maxout();
    }
}


namespace sol
{
    const int N = 1e6+5;
    ll pa[N], pb[N];
    int n;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> pa[i];
            pa[i] += pa[i - 1];
        }

        for (int i = 1; i <= n; i++)
        {
            cin >> pb[i];
            pb[i] += pb[i - 1];
        }
    }

    inline ll _pref(ll* p, int a, int b)
    {
        return p[b] - p[a - 1];
    }

    inline ll pref(int a, int b)
    {
        if (a > b) return 0;
        return _pref(pa, a, b) - _pref(pb, a, b);
    }

    inline ll swap_pref(int a, int b)
    {
        if (a > b) swap(a, b);
        return pref(a, b);
    }

    namespace sol_range
    {
        ll solve(vector<ll>& A, vector<ll>& B)
        {
            dt::clear();

            for (int i = 0; i < len(A) - 1; i++)
                dt::resolve(A[i] - B[i]);

            return dt::max_time;
        }
    }

    namespace split
    {
        ll res = 0;

        void compute(int start, int dir)
        {
            vector<ll> A, B;

            int end = (dir == 1 ? n : 1), 
                rend = (dir == 1 ? 1 : n);

            int pos = start;
            for (; pos != end + dir; pos += dir)
            {
                A.push_back(_pref(pa, pos, pos));
                B.push_back(_pref(pb, pos, pos));

                if (swap_pref(pos + dir, end) < 0)
                    continue;
                if (swap_pref(rend, pos - dir) < 0)
                    continue;
                pos += dir;
                break;
            }
            pos -= dir;

            if (start != end && start != rend)
            {
                A.front() = pref(start + dir, end);
                B.front() = 0;
            }
            if (pos != end && pos != start)
            {
                A.back() = 0;
                B.back() = pref(start, pos - dir);
            }

            self(max, res, sol_range::solve(A, B));
        }

        void solve()
        {
            if (pref(2, n) < 0) compute(1, 1);
            if (pref(1,n-1) < 0) compute(n, -1);

            for (int i = 2; i < n; i++)
                if (pref(1, i-1) < 0 && pref(i+1, n) < 0)
                    compute(i, -1), compute(i, 1);

            cout << res << '\n';
        }
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::split::solve();
}