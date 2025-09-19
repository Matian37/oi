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

namespace math
{
    int totient(int x)
    {
        int val = 1;

        for (int i = 1; i <= sqrt(x); i++)
        {
            if (x % i != 0) continue;

            val *= (i - 1);
            x /= i;

            while (x % i == 0)
            {
                val *= i;
                x /= i;
            }
        }

        return val;
    }

    int fastpow(ll a, ll b, ll m)
    {
        ll r = 1;

        while (b != 0)
        {
            if (b % 2 == 1)
                r = (r * a) % m;
            a = (a * a) % m;
            b /= 2;
        }

        return int(r);
    }
};

namespace circle
{
    set<ii> ranges;

    inline __attribute__((always_inline)) void _modify(set<ii>::iterator it, ii value)
    {
        ranges.erase(it);
        ranges.insert(value);
    }

    void init(int n)
    {
        ranges.insert({0, n - 1});
    }

    bool apply_range(int a, int b)
    {
        if (a <= b)
        {
            while (ranges.size())
            {
                if (ranges.begin()->sec >= a) 
                    break;
                ranges.erase(ranges.begin());
            }

            if (ranges.size())
                if (ranges.begin()->fir < a)
                    _modify(ranges.begin(), {a, ranges.begin()->sec});

            while (ranges.size())
            {
                auto it = prev(ranges.end());
                if (it->fir <= b) 
                    break;
                ranges.erase(it);
            }

            if (ranges.size())
            {
                auto it = prev(ranges.end());
                if (b < it->sec)
                    _modify(it, {it->fir, b});
            }
        }
        else
        {
            swap(a, b);
            a++;
            b--;

            if (a > b)
                return true;

            vector<set<ii>::iterator> its;

            auto _it = ranges.upper_bound({a, INF+1});
            if (_it != ranges.begin()) _it--;

            for (auto it = _it; it != ranges.end(); it++)
            {
                if (it->first > b)
                    break;
                if (it->second < a)
                    continue;
                its.push_back(it);
            }

            if (its.empty()) return true;
            for (int i = 1; i < len(its) - 1; i++)
                ranges.erase(its[i]);

            ii left = *its.front(), right = *its.back();

            ranges.erase(its.front());
            if (len(its) != 1) ranges.erase(its.back());

            if (left.first < a)
                ranges.insert({left.first, a - 1});
            if (right.second > b)
                ranges.insert({b + 1, right.second});
        }

        return ranges.size();
    }

    bool is_in(int x)
    {
        if (ranges.empty())
            return false;

        auto it = ranges.upper_bound({x, INF + 1});

        if (it == ranges.begin())
            return false;

        it--;
        
        return inRange(x, it->fir, it->sec);
    }

    int count()
    {
        int cnt = 0;

        for (auto i : ranges)
        {
            cnt += i.sec-i.fir+1;
        }

        return cnt;
    }
}

namespace sol
{
    ll n, a, b, p, m;
    string s;

    void read()
    {
        cin >> n >> a >> b >> p >> m >> s;
    }

    void solve()
    {
        if (m > n)
        {
            cout << 0 << '\n';
            return;
        }

        circle::init(int(n));

        for (ll i = 0; i < m; i++)
        {
            #define mod(x, y) ((y + (x) % y) % y)

            ll l, r;

            if (s[i] == '0')
                l = mod(-a * i, n), r = mod(p - 1 - a * i, n);
            else
                l = mod(p - a * i, n), r = mod(n - 1 - a * i, n);

            if (!circle::apply_range(int(l), int(r)))
            {
                cout << 0 << '\n';
                return;
            }
        }

        int res = circle::count();

        for (int i = int(n - 1); i > n - m; i--)
        {
            ll r = (a * i + b) % n;

            if (circle::is_in(int(r))) res--;
        }

        cout << res << '\n';
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