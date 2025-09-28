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

#define pbds __gnu_pbds
#define cxx __gnu_cxx
#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() chrono::high_resolution_clock::now().time_since_epoch().count()
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

namespace sol
{
    const int N = 2e6 + 5;
    ll pref[N];
    int n, d;
    ll p;

    void read()
    {
        cin >> n >> p >> d;

        for (int i = 1; i <= n; i++)
            cin >> pref[i], pref[i] += pref[i - 1];
    }

    deque<int> dq;

    void add(int a)
    {
        while (dq.size())
        {
            if (pref[dq.back()] - pref[dq.back() - d] > pref[a] - pref[a - d])
                break;
            dq.pop_back();
        }

        dq.push_back(a);
    }

    inline ll getMax()
    {
        if (dq.size()) return pref[dq.front()] - pref[dq.front() - d];
        return 0;
    }

    inline void rem(int a)
    {
        if (dq.size())
            if (dq.front() == a)
                dq.pop_front();
    }
    
    int solve()
    {
        if (n == d || n == 1) return n;

        int result = 0;

        for (int i = 1, j = d; j <= n; j++)
        {
            if (j - d + 1 >= i) add(j);

            #define value(x,y) (pref[(y)]-pref[(x)-1]-getMax())


            ll val = value(i, j);

            if (val <= p) result = max(result, j - i + 1);
            else
            {
                while (i < j)
                {
                    rem(i + d - 1);
                    i++;
                    
                    if (value(i, j) <= p) break;
                }
            }
        }

        return result;
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