//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

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
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using hashmap_bit = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmap_prime = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
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
    const int N = 1e6+5;
    priority_queue<ii, vector<ii>> pq;
    list<int> ind[N];
    int cnt[N];
    int n, s;

    void read()
    {
        cin >> n >> s;

        for (int i = 0; i < n; i++)
        {
            int c;
            cin >> c;

            c = (c + 1) % s;

            cnt[c]++;
            ind[c].push_back(i+1);
        }

        for (int i = 0; i < s; i++)
            if (cnt[i] != 0)
                pq.push({cnt[i], i});
    }
    
    vector<int> ord;
    int res = 0;

    inline int nxt(int c)
    {
        int val = ind[c].back();
        ind[c].pop_back();
        return val;
    }

    void solve()
    {
        int r = 0;

        while (!pq.empty())
        {
            auto acc = pq.top();
            pq.pop();

            if (r == s - 1)
                res++, r = 0;

            if ((r+acc.sec) % s != s - 1)
            {
                r = (r + acc.sec) % s;
                ord.push_back(nxt(acc.sec));
                acc.fir--;
            }
            else if (pq.empty())
            {
                r = (r + acc.sec) % s;
                ord.push_back(nxt(acc.sec));
                acc.fir--;
            }
            else
            {
                auto curr = pq.top();
                pq.pop();

                r = (r + curr.sec) % s;
                ord.push_back(nxt(curr.sec));
                curr.fir--;

                if (curr.fir != 0) pq.push(curr);
            }

            if (acc.fir != 0) pq.push(acc);
        }

        cout << res << '\n';

        for (int i = 0; i < n; i++)
            cout << ord[i] << ' ';
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