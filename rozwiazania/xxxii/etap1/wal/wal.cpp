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
#define itr iterator

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

const int N = 2e5 + 5;
ii t[N];
int mp[N], n;

namespace hull
{
    vector<ii> hull;
    ii en, start, can;
    int slf = 0;

    vector<ii>& solve()
    {
        int lstart = 0, len = 0;

        for (int i = 1; i < n; i++)
        {
            if (t[i].fir > t[len].fir)
                len = i;
            if (t[i].sec > t[lstart].sec)
                lstart = i; 
        }

        start = t[lstart], en = t[len];

        hull.push_back(start);

        for (int i = start.fir + 1; i <= en.fir; i++)
        {
            while (hull.size() > 1)
            {
                if (hull.back().sec > mp[i]) break;
                hull.pop_back();
                slf++;
            }

            hull.push_back({i, mp[i]});
        }

        return hull;
    }
}

namespace sol
{
    void read()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cin >> t[i].fir >> t[i].sec;
            mp[t[i].fir] = t[i].sec;
        }
    }

    bool solve()
    {
        if (n == 1) return false;

        vector<ii>& h = hull::solve();

        sort(all(h));

        for (int i = 0; i < n; i++)
        {
            auto it = lower_bound(all(h), t[i]);

            bool good = false;

            if (it == h.end()) good = true;
            else if (*it != t[i]) good = true;

            if (!good) continue;

            if (t[i].fir < h.back().fir && t[i].sec > h.back().sec)
            {
                hull::slf++;
                break;
            }
            if (t[i].fir > h.front().fir && t[i].sec < h.front().sec)
            {
                hull::slf++;
                break;
            }
        }

        if (hull::slf != 0) return true;
        return (isize(h) + 1) % 2;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    cout << (sol::solve() ? "TAK" : "NIE") << '\n';
}