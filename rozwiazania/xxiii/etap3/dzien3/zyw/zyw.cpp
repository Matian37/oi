//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <bits/extc++.h>

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

const int N = 1e3+5;

#define ind(a, b) ((a)*(m)+(b))
#define decode_n(x) ((x) / m)
#define decode_m(x) ((x) % m)
#define to_zyl(x) (x ? 'Z' : '.')

namespace fu
{
    int fu[N*N], ranks[N*N];

    void init(int n, int m)
    {
        for (int i = 0; i <= ind(n - 1, m - 1); i++)
        {
            fu[i] = i;
            ranks[i] = 1;
        }
    }

    int find(int x)
    {
        if (fu[x] == x) return x;
        return fu[x] = find(fu[x]);
    }

    bool Union(int a, int b)
    {
        a = find(a), b = find(b);

        if (a == b) return false;

        if (ranks[a] > ranks[b]) swap(a, b);

        ranks[b] += ranks[a];
        fu[a] = b;

        return true;
    }
}

namespace sol
{
    vector<ii> g[N*N];
    int n, m, res;

    #define add_edge(a, b, c) g[a].push_back({c, b}), g[b].push_back({c, a})

    void read()
    {
        cin >> n >> m;

        for (int j = 0; j < n; j++)
        {
            string s;
            cin >> s;

            for (int i = 0; i < m - 1; i++)
                add_edge(ind(j, i), ind(j, i + 1), (s[i] == 'C' ? -1 : 0));

            res += int(count(all(s), 'C'));
        }

        for (int j = 0; j < n - 1; j++)
        {
            string s;
            cin >> s;

            for (int i = 0; i < m; i++)
                add_edge(ind(j, i), ind(j + 1, i), (s[i] == 'C' ? -1 : 0));

            res += int(count(all(s), 'C'));
        }
    }
    
    priority_queue<pair<int,ii>> pq;

    bitset<N> hor[N], vert[N];

    void solve()
    {
        fu::init(n, m);

        for (int i = 0; i <= ind(n - 1, m - 1); i++)
            for (auto j : g[i])
                if (i < j.sec)
                    pq.push({j.fir, {i, j.sec}});

        int times = n*m-1;

        while (!pq.empty() && times)
        {
            auto curr = pq.top();
            pq.pop();

            if (!fu::Union(curr.sec.fir, curr.sec.sec))
                continue;

            #define upd(x) x[decode_n(curr.sec.fir)][decode_m(curr.sec.fir)] = true

            if (curr.sec.fir + 1 == curr.sec.sec) upd(hor);
            else upd(vert);


            res += curr.fir;
            times--;
        }

        #ifdef DLOCAL
        assert(times == 0);
        #endif

        cout << 2 * (n - 1) * (m - 1) + (n - 1) + (m - 1) - (n*m-1)
             << ' ' 
             << res 
             << '\n';

        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < m - 1; i++)
                cout << to_zyl(!hor[j][i]);
            cout << '\n';
        }

        for (int j = 0; j < n - 1; j++)
        {
            for (int i = 0; i < m; i++)
                cout << to_zyl(!vert[j][i]);
            cout << '\n';
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