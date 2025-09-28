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
    const int N = 5e5 + 5;
    pll t[N];
    int ind[N];
    int n;
    pll s;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> t[i].fir;
        for (int i = 1; i <= n; i++)
        {
            cin >> t[i].sec;
            s.fir += t[i].fir;
            s.sec += t[i].sec;
        }
    }

    bool result[N];
    bool reversed;

    void print()
    {
        for (int i = 1; i <= n; i++)
            cout << (result[i] ^ reversed) << ' ';
        cout << '\n';
        exit(0);
    }

    multiset<ll> minb;
    
    void edg()
    {
        // 1111 case
        if (n == 1)
            print();

        // pd case
        [&]()
        {
            int indx = -1;

            for (int i = 1; i <= n; i++)
                if (2 * t[i].sec >= s.sec)
                    indx = i;

            if (indx == -1) return;
            result[indx] = true;

            print();
        }();
    }

    void solve()
    {
        for (int i = 1; i <= n; i++)
        {
            ind[i] = i;
            minb.insert(t[i].sec);
        }
        
        edg();

        sort(ind + 1, ind + (n + 1), [&](const int& a, const int& b)
        {
            return t[a] < t[b];
        });

        sort(t + 1, t + (n+1));

        pll sum{};

        for (int i = n; i >= 1; i--)
        {
            if (i == 1)
            {
                result[ind[i]] = 1;
                sum.fir += t[i].fir;
                sum.sec += t[i].sec;
                minb.erase(minb.find(t[i].sec));

                if (2 * sum.sec <= s.sec)
                    reversed = true;
                break;
            }

            if (2 * (sum.fir + t[i].fir) > (s.fir + t[i].fir))
                continue;
            
            sum.fir += t[i].fir;
            sum.sec += t[i].sec;
            minb.erase(minb.find(t[i].sec));
            result[ind[i]] = 1;

            if (2 * sum.sec >= s.sec - *minb.begin()) // zielone case
                break;
            if (2 * sum.fir >= s.fir - t[1].fir) // blue case
            {
                reversed = true;
                break;
            }
        }

        for (int i = 1; i <= n; i++)
            cout << (result[i] ^ reversed) << ' ';
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