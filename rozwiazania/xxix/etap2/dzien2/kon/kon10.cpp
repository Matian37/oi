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
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
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

const int N = 1e6+5, M = 6e6+5;

vector<int> g[N];
pair<char, int> zap[N];

int nr[N], w[N], parent[N], fp[N], token = 5;

namespace ec
{
    ii wstp[M];
    vector<int> ord, f, fp;
    bitset<M> visited;

    void dfs(int v)
    {
        visited[v] = true;

        wstp[v].fir = len(ord);
        ord.push_back(v);

        for (auto i : g[v])
            dfs(i);

        wstp[v].sec = len(ord);
        ord.push_back(v);
    }

    void init()
    {
        ord.reserve(2*token);
        ord.push_back(0);

        for (int i = 1; i < token; i++)
            if (!visited[i])
                dfs(i);
        f.resize(len(ord), 0);
    }

    void update(int a, int x)
    {
        while (a < len(f))
        {
            f[a] += x;
            a += a & -a;
        }
    }

    int __query(int a)
    {
        int r = 0;

        while (a > 0)
        {
            r += f[a];
            a -= a & -a;
        }

        return r;
    }

    inline int query(int a, int b)
    {
        return __query(b) - __query(a - 1);
    }
}

namespace sol
{
    int q;
    
    void read()
    {
        cin >> q;

        for (int i = 0; i < q; i++)
            cin >> zap[i].fir >> zap[i].sec;
    }

    void initTree()
    {
        w[1] = 2, w[2] = 1;
        g[1].push_back(3), parent[3] = 1;   
        g[2].push_back(4), parent[4] = 2;
        nr[1] = 3;
        nr[2] = 4;

        for (int i = 0, vert = 3; i < q; i++)
        {
            auto[type, val] = zap[i];

            if (type == '?') continue;
            if (type == 'Z')
            {
                nr[vert] = token;
                parent[token] = parent[nr[val]];
                g[parent[nr[val]]].push_back(token);

                token++;
            }
            else
            {
                w[nr[val]] = token + 1;
                w[token + 1] = nr[val];

                g[nr[val]].push_back(token);
                parent[token] = nr[val];

                nr[val] = token;

                g[token + 1].push_back(token + 2);
                parent[token + 2] = token + 1;

                nr[vert] = token + 2;

                token += 3;
            }
            vert++;
        }
    }
    
    void solve()
    {
        initTree();
        ec::init();

        for (int i = 1; i <= token; i++)
            if (parent[i] == 0) fp[i] = i;
            else fp[i] = fp[parent[i]];

        #define update(x, y, z) ec::update(ec::wstp[x].fir, y),\
                                ec::update(ec::wstp[x].sec, z)

        update(1, 1, -1);
        update(2, 1, -1);

        nr[1] = 3;
        nr[2] = 4;
        w[1] = 2, w[2] = 1;

        token = 5;

        for (int i = 0, vert = 3; i < q; i++)
        {
            auto[type, val] = zap[i];

            if (type == 'Z')
            {
                nr[vert] = token;

                update(w[fp[token]], 1, -1);
                if (fp[token] != parent[token]) update(w[parent[token]], 1, -1);

                token++; 
            }
            else if (type == 'W')
            {
                w[nr[val]] = token + 1;
                w[token + 1] = nr[val];

                nr[val] = token;
                nr[vert] = token + 2;

                update(parent[token], 1, -1);
                update(parent[token + 2], 1, -1);

                token += 3;
            }
            else
            {
                cout << ec::query(1, ec::wstp[nr[val]].fir) << '\n';
            }

            vert += (type != '?');
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