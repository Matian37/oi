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
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

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



const int N = 1e6+5;
pair<char,ii> t[N];
int result[N];
int n;

vector<int> g[2*N];
int vert;

#define pl(x) (n+(x))
#define addEdge(x,y) g[x].push_back(y), g[y].push_back(x)

inline void fail()
{
    cout << "NIE\n0\n";
    exit(0);
}

namespace init
{
    vector<int> wstp[N];
    bitset<N> visited, blocked;

    bool obvious()
    {
        queue<int> q;

        for (int i = 1; i <= n; i++)
        {
            if (t[i].fir == 'T')
                q.push(i);
            else
                wstp[t[i].sec.fir].push_back(i),
                wstp[t[i].sec.sec].push_back(i);
        }

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            if (visited[acc]) continue;
            visited[acc] = true;

            if (t[acc].fir == 'N')
                if (blocked[t[acc].sec.fir]) 
                    swap(t[acc].sec.fir, t[acc].sec.sec);

            if (blocked[t[acc].sec.fir]) return false;

            result[acc] = t[acc].sec.fir;
            blocked[t[acc].sec.fir] = true;

            for (auto i : wstp[t[acc].sec.fir])
                if (!visited[i])
                    q.push(i);
        }

        return true;
    }

    void init()
    {
        if (!obvious()) fail();

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                addEdge(pl(i), t[i].sec.fir),
                addEdge(pl(i), t[i].sec.sec);
    }
}

namespace sol
{
    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> t[i].fir;

            if (t[i].fir == 'T')
                cin >> t[i].sec.fir;
            else
                cin >> t[i].sec.fir >> t[i].sec.sec;
        }
    }

    int visited[2*N], token;

    int dfs(int v)
    {
        visited[v] = token;

        int cnt = (v <= n ? 1 : -1);

        for (auto i : g[v])
            if (visited[i] != token)
                cnt += dfs(i);
        return cnt;
    }

    ii ng[N];
    int sng[N], png[N];

  
    void solve()
    {
        init::init();

        if ((int)(init::visited.count()) == n)
        {
            cout << "TAK\n";
            for (int i = 1; i <= n; i++)
                cout << result[i] << '\n';
            return;
        }

        ++token;
        for (int i = 1; i <= n; i++)
            if (!init::blocked[i] && visited[i] != token)
                if (dfs(i) < 0) 
                    fail();
        
        uint r = 1;

        ++token;

        for (int i = 1; i <= n; i++)
            if (!init::blocked[i] && visited[i] != token)
                r = (r * 2) % MOD, dfs(i);
        
        cout << "NIE\n";
        cout << r << '\n';
        return;
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