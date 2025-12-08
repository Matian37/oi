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

namespace tree
{
    const int base = 1 << 20; // it can be shortened
    ll treeQ[base * 2], treeV[base * 2];

    int p, k, val;

    void _update(int v, int a, int b)
    {
        if (k < a || b < p) 
            return;
        if (p <= a && b <= k)
        {
            treeV[v] += val;
            treeQ[v] += val;
            return;
        }

        treeV[v*2] += treeQ[v];
        treeV[v*2+1] += treeQ[v];
        treeQ[v*2] += treeQ[v];
        treeQ[v*2+1] += treeQ[v];
        treeQ[v] = 0;

        int mid = (a + b) / 2;

        _update(v*2, a, mid);
        _update(v*2+1, mid+1, b);

        treeV[v] = max(treeV[v*2], treeV[v*2+1]);
    }

    void update(int a, int b, int c)
    {
        if (a > b) return;
        p = a, k = b, val = c;
        _update(1, 0, base - 1);
    }

    ll query()
    {
        return treeV[1];
    }
}

namespace dt
{
    int cnt[N*N];

    void add(int x)
    {
        tree::update(1, x, 1);

        cnt[x]++;

        if (cnt[x] == 1)
            tree::update(x, x, x-1);
    }

    void rem(int x)
    {
        tree::update(1, x, -1);

        cnt[x]--;

        if (cnt[x] == 0)
            tree::update(x, x, -(x-1));
    }

    ll query()
    {
        return tree::query();
    }
}

namespace sol
{
    string t[N];

    int n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < n; i++)
            cin >> t[i];
    }

    ii moves[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int cost[N][N];

    void bfs()
    {
        queue<pair<int,ii>> q;
        q.push({0,{0, 0}});

        while (len(q))
        {
            auto curr = q.front();
            q.pop();

            if (cost[curr.sec.fir][curr.sec.sec] != 0)
                continue;
        
            cost[curr.sec.fir][curr.sec.sec] = curr.fir;

            for (auto i : moves)
            {
                int X = curr.sec.fir + i.fir, 
                    Y = curr.sec.sec + i.sec;

                if (X < 0 || X >= n)
                    continue;
                if (Y < 0 || Y >= n)
                    continue;
                
                if (cost[X][Y])
                    continue;
                if (t[X][Y] == '#')
                    continue;
                if (X == 0 && Y == 0)
                    continue;

                q.push({curr.fir + 1, {X, Y}});
            }
        }
    }

    void solve()
    {
        bfs();

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (t[i][j] == 'F')
                    dt::add(cost[i][j]);

        cout << dt::query() << '\n';

        while (m--)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;

            bool fort = t[a][b] == 'F';

            if (fort)
            {
                dt::rem(cost[a][b]);
                t[a][b] = '.';
            }
            else 
            {
                dt::add(cost[a][b]);
                t[a][b] = 'F';
            }

            cout << dt::query() << '\n';
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