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

struct dynamic_dq
{
    deque<ii> dq;
    int c;

    void add(int val, int x)
    {
        c += val;

        while (len(dq))
        {
            if (dq.back().fir <= val - c)
                break;
            dq.pop_back();
        }
        dq.push_back({val - c, x});
    }

    void rem(int x)
    {
        if (len(dq))
            if (dq.front().sec == x)
                dq.pop_front();
    }

    int query()
    {
        return dq.front().fir + c;
    }
};

namespace sol
{
    string s;
    int n, p, q, x, y;

    void read()
    {
        cin >> n >> p >> q >> x >> y;
        cin >> s;
    }

    dynamic_dq dq;

    ll solve()
    {
        int sum = (2 * (int)count(all(s), '+') - n), diff = (q-p) - sum;

        int i = n, j = 2 * n - 1;

        for (int k = j; k >= i; k--)
            dq.add(s[k % n] == '+' ? 1 : -1, k);

        ll best = INFLL;

        if (diff >= 0)
        {
            while (i != 0)
            {
                ll a = diff / 2 + 2 * max(0, (-(p + dq.query() + diff) + 1) / 2),
                   b = (n - i);
                
                best = min(best, a * x + b * y);

                i--;
                dq.add(s[i % n] == '+' ? 1 : -1,i);
                dq.rem(j);
                j--;
            }
            return best;
        }

        diff *= -1;

        int k = 2 * n, dod = 0;

        auto mv = [&]()
        {
            while (dod != diff / 2)
            {
                k--;
                dod += s[k % n] == '+';
                sum += (s[k % n] == '+' ? -1 : 1);
            }
        };

        mv();

        while (i != 0)
        {
            int minn = p + min(dq.query(), sum - (j-k+1));

            ll a = diff / 2 + (minn < 0 ? (-minn + 1) / 2 * 2 : 0), 
               b = (n - i);

            best = min(best, a * x + b * y);

            i--;
            sum += (s[i % n] == '+' ? 1 : -1);
            dq.add(s[i % n] == '+' ? 1 : -1, i);

            if (s[j % n] == '+') 
            {
                dod--;
                mv();
            }

            dq.rem(j--);
        }

        return best;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    cout << sol::solve() << '\n';
}