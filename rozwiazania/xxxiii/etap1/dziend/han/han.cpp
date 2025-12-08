//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <queue>

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

namespace sol
{
    const int N = 1e6+5;
    vector<int> t[N];
    int m;

    void read()
    {
        int _n;
        cin >> _n >> m;

        for (int i = 0; i < m; i++)
        {
            int k;
            cin >> k;

            t[i].reserve(k);

            for (int j = 0; j < k; j++)
            {
                int c;
                cin >> c;
                t[i].push_back(c);
            }

            sort(all(t[i]));
        }
    }
    
    int wsk[N];

    void put_on(int x, vector<ii> add)
    {
        priority_queue<ii, vector<ii>, greater<ii>> pq;

        for (int i = 0; i < m; i++)
            if (t[i].size() && i != x)
                pq.push({t[i].front(), i});

        vector<ii> odp(add.begin(), add.end());

        while (len(pq))
        {
            auto curr = pq.top();
            pq.pop();

            odp.push_back({curr.sec, x});
            wsk[curr.sec]++;

            if (wsk[curr.sec] < len(t[curr.sec]))
                pq.push({t[curr.sec][wsk[curr.sec]], curr.sec});
        }

        cout << len(odp) << '\n';
        for (auto [a, b] : odp)
            cout << a+1 << ' ' << b+1 << '\n';
        exit(0);
    }

    void fail()
    {
        cout << "-1\n";
        exit(0);
    }

    void check_sorted()
    {
        int nm = -1;

        for (int i = 0; i < m; i++)
        {
            if (t[i].empty()) continue;
            if (nm != -1) return;
            nm = i;
        }

        cout << "0\n";
        exit(0);
    }

    void solve()
    {
        // Case: 0
        check_sorted();

        int lowest = m;
        t[m].push_back(INF);

        // Case: N-S, S -> size of column of lowest guy
        for (int i = 0; i < m; i++)
            if (t[i].size())
                if (t[lowest].back() > t[i].back())
                    lowest = i;

        for (int i = 0; i < m; i++)
        {
            if (i == lowest)    
                continue;
            if (t[i].empty())
                continue;
            if (t[lowest].back() < t[i].front())
                continue;
            lowest = m;
            break;
        }

        if (lowest != m)
            put_on(lowest, {});

        // Case: N
        for (int i = 0; i < m; i++)
            if (t[i].empty())
                put_on(i, {});

        // Case: N + S, S -> some size of some column
        lowest = 0;
        for (int i = 1; i < m; i++)
            if (t[i].back() < t[lowest].back())
                lowest = i;

        int sm = INF;
        int smi = -1;

        for (int i = 0; i < m; i++)
        {
            if (t[i].front() < t[lowest].back())
                continue;
            if (i == lowest)
                continue;
            if (len(t[i]) > sm)
                continue;
            sm = len(t[i]);
            smi = i;
        }

        if (smi != -1)
        {
            vector<ii> moves;

            t[lowest].insert(t[lowest].end(), all(t[smi]));

            for (int i = 0; i < len(t[smi]); i++)
                moves.push_back({smi, lowest});

            t[smi].clear();

            put_on(smi, moves);
        }

        fail();
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