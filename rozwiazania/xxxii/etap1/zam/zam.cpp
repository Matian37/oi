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

struct chash
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    list<char> l;
    string n, on;

    void read()
    {
        cin >> n;
        on = n;
    }
    
    void remZer()
    {
        while (l.front() == '0')
            l.pop_front();
    }

    int solve()
    {
        l.clear();
        for (auto i : n) 
            l.push_back(i);

        remZer();

        if (l.front() == '1' && isize(l) == 1)
        {
            return 0;
        }
        if (count(all(l), '0') == isize(l) - 1 && find(all(l), '1') != l.end())
        {
            return 1;
        }

        int c = 0, d = 0;

        for (auto i : l)
        {
            if (i != '0')
            {
                d++;
                if (i != '9') 
                    c++;
            }
        }

        int r = 0;

        while (d != isize(l) || c != 0)
        {
            if ('9' != l.back() && '0' != l.back())
            {
                c--;
                r += '9' - l.back();
                l.back() = '9';
            }

            if (d != isize(l) || c != 0)
            {
                l.push_back(l.front());
                l.pop_front();
                remZer();
                r++;
            }
        }

        return r + 2;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    ll result = sol::solve();

    int c = 5;

    for (int i = 0; i < isize(sol::n); i++)
    {
        c--;
        ll val = stoll(sol::on.substr(isize(sol::on) - i - 1, i + 1));

        sol::n[isize(sol::on) - i - 1] = '9';

        val = stoll(sol::n.substr(isize(sol::n) - i - 1, i + 1)) - val;

        ll nw = sol::solve() + val;

        result = min(result, nw);
        if (c == 0) break;
    }

    cout << result << '\n';
}