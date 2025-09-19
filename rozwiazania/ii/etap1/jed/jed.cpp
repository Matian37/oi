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

namespace sol
{
    const int N = 2e4 + 5;

    
    int sajz[N], prv[N];

    void read()
    {
    }

    string solveQuery(int n)
    {
        for (int i = 0; i < n; i++)
            sajz[i] = 0, prv[i] = -1;
        
        struct info
        {
            int fir, sec, thr;
        };

        queue<info> q;

        q.push({1, 1, -1});

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            if (acc.sec > 100) continue;
            if (sajz[acc.fir] != 0) continue;

            sajz[acc.fir] = acc.sec;
            prv[acc.fir] = acc.thr;

            if (acc.fir == 0) break;

            int val = (acc.fir * 10) % n;

            if (sajz[val] == 0)
                q.push({val, acc.sec + 1, acc.fir});
            
            val = (val + 1) % n;

            if (sajz[val] == 0)
                q.push({val, acc.sec + 1, acc.fir});
        }

        if (sajz[0] == 0) 
            return "BRAK";

        string result = "";

        int acc = 0;

        while (acc != -1)
        {
            result += ((prv[acc] * 10) % n == acc ? '0' : '1');
            acc = prv[acc];
        }

        reverse(all(result));

        return result;
    }
    
    void solve()
    {
        int q;
        cin >> q;

        while (q--)
        {
            int k;
            cin >> k;

            cout << solveQuery(k) << '\n';
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