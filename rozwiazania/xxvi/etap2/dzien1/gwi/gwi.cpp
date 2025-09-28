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

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007ULL
#define MOD2 1000000403ULL
#define MOD3 1000000787ULL
#define MOD4 1000001447ULL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct Hashfn
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

    string jump = "";
    int diff[N];
    int n, start, p, k;
    ull cost = 0;

    void read()
    {
        cin >> n >> start;

        p = 1, k = n;

        if (start == 1) p++;

        n--;
        
        for (int i = 0; i < n; i++)
        {
            int l, r;
            cin >> l >> r;

            jump += (l < r ? 'L' : 'P');
            cost += min(l, r);

            diff[i] = abs(l - r);
        }
    }

    inline int dist(int acc, char type)
    {
        return max(0,(type == 'L' ? acc - p - (int)(p <= start && start < acc) :
                                    k - acc - (int)(acc < start && start <= k)));
    }
    
    void jumps(int x, char type, int& acc, vector<int>& r)
    {
        if (x == 0) return;

        stack<int> tmp;

        int j, way;

        if (type == 'L') j = p, way = 1;
        else j = k, way = -1;

        for (int lic = x; lic; j += way)
        {
            if (j == start) continue;
            tmp.push(j);
            lic--;
        }

        acc = j - way;

        if (type == 'L') p = (j == start ? j + way : j);
        else k = (j == start ? j + way : j);

        while(tmp.size())
        {
            r.push_back(tmp.top());
            tmp.pop();
        }
    }

    void solve()
    {
        vector<int> r;

        #define odw() (type == 'L' ? 'P' : 'L')

        r.reserve(n + 1);
        r.push_back(start);

        int acc = start;

        for (int i = 0; i < n; i++)
        {
            char type = jump[i];
            int cnt = 1, d = dist(acc, type), minCost = i, oldi = i;
            bool fit = true;

            while (i != n - 1)
            {
                if (cnt > d) {fit = false; break;}
                if (jump[i + 1] != type) break;

                cnt++;
                i++;

                if (diff[minCost] >= diff[i]) minCost = i;
                if (cnt > d) {fit = false; break;}
            }

            if (cnt > d) fit = false;

            if (fit)
            {
                jumps(i - oldi + 1, type, acc, r);
                continue;
            }

            cost += diff[minCost];

            jumps(minCost - oldi, type, acc, r);

            if (i - minCost != 0 || i == n - 1)
            {
                if (type == 'L')
                {
                    acc = k;
                    r.push_back(acc);
                    k = (k - 1 == start ? k - 2 : k - 1);
                }
                else
                {
                    acc = p;
                    r.push_back(acc);
                    p = (p + 1 == start ? p + 2 : p + 1);
                }

                if (i != n - 1)
                {
                    if (jump[i + 1] == type)
                    {
                        i = minCost;
                        continue;
                    }
                }

                jumps(i - minCost, type, acc, r);
            }
            else
            {
                jump[i] = odw();
                i--;
            }
        }

        cout << cost << '\n';

        for (auto i : r) cout << i << ' ';
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