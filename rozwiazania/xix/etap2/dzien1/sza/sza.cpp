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

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int P = 1e6 + 5, N = 1e3 + 5, W = 1e5;

namespace sol
{
    struct info
    {
        int a, b, c;
    };

    struct zap
    {
        int m, k, s;
    };

    info t[N];
    zap q[P];
    bitset<P> sol;

    vector<ii> events;
    int n, p, maksVal;

    void read()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cin >> t[i].c >> t[i].a >> t[i].b;

            events.push_back({t[i].a, i});
            events.push_back({t[i].b, i});
        }

        cin >> p;

        for (int i = 0; i < p; i++)
        {
            cin >> q[i].m >> q[i].k >> q[i].s;

            events.push_back({q[i].m, i + INF});
            maksVal = max(maksVal, q[i].k);
        }
        maksVal = min(W, maksVal);
    }
    
    bool comp(const ii& a, const ii& b)
    {
        if (a.first != b.first) return a.first < b.first;

        int typa = (a.second >= INF ? 2 : (t[a.second].a == a.first ? 1 : 0)),
            typb = (b.second >= INF ? 2 : (t[b.second].a == b.first ? 1 : 0));

        return typa < typb;
    }

    int ls[W + 5], cl[W + 5];

    inline void addElement(int val, int b)
    {
        for (int i = W; i >= val; i--)
        {
            ls[i] += ls[i - val];
            cl[i] = max(cl[i], min(cl[i - val], b));
        }
    }

    inline void removeElement(int val, int b)
    {
        for (int i = val; i <= W; i++)
            ls[i] -= ls[i - val];
    }

    inline bool query(int k, int d)
    {
        return cl[k] > d && ls[k] != 0;
    }

    void solve()
    {
        cl[0] = INF;
        ls[0] = 1;

        sort(all(events), comp);

        for (auto i : events)
        {
            if (i.second >= INF)
            {
                i.second -= INF;
                sol[i.second] = query(q[i.second].k, i.first + q[i.second].s);
            }
            else
            {
                if (t[i.second].a == i.first) addElement(t[i.second].c, t[i.second].b);
                else removeElement(t[i.second].c, t[i.second].b);
            }
        }

        for (int i = 0; i < p; i++)
            cout << (sol[i] ? "TAK" : "NIE") << '\n';
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