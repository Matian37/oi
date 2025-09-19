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

struct chash
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int N = 505;

unordered_set<int, chash> og[N];
vector<int> g[N];
bitset<N> removed, isArt, isVert;
int n, m;

namespace fastio
{
    char rbuffer[2000000], wbuffer[2000000];
    int r, w;

    void read()
    {
        fread(rbuffer,sizeof(char),sizeof(rbuffer),stdin);
    }

    void nxt()
    {
        while (rbuffer[r] <= ' ')
            r++;
    }

    void readInt(int& a)
    {
        nxt();
        a = 0;

        while (rbuffer[r] > ' ')
        {
            a = a * 10 + (rbuffer[r] - '0');
            r++;
        }
    }

    char tmp[100];

    void writeInt(int a)
    {
        int p = -1;

        while (a != 0)
        {
            tmp[++p] = char(a % 10 + int('0'));
            a /= 10;
        }

        while (p >= 0)
            wbuffer[w++] = tmp[p--];
    }

    void writeChar(char a)
    {
        wbuffer[w++] = a;
    }

    void write()
    {
        fwrite(wbuffer,sizeof(char),w,stdout);
    }
}

namespace low
{
    int low[N], h[N], visited[N];
    int id = 0, token = 0;

    int dfs(int v, int p)
    {
        visited[v] = token;
        low[v] = h[v] = ++id;

        for (auto i : og[v])
        {
            if (i == p || removed[i]) continue;

            if (visited[i] != token) dfs(i, v);

            low[v] = min(low[v], low[i]);
        }

        return low[v];
    }

    void init()
    {
        ++token;
        id = 0;

        dfs(1, 0);

        for (int i = 1; i <= n; i++)
        {
            isArt[i] = false;

            for (auto j : og[i])
            {
                if (removed[j]) continue;
                if (low[j] < h[i]) continue;
                isArt[i] = true;
                break;
            }
        }
    }
}

namespace sol
{
    int rm[N];

    void read()
    {
        fastio::read();

        fastio::readInt(n);
        fastio::readInt(m);

        for (int i = 0; i < m; i++)
        {
            int a, b;
            fastio::readInt(a);
            fastio::readInt(b);

            og[a].insert(b);
            og[b].insert(a);

            g[a].push_back(b);
            g[b].push_back(a);

            rm[a]++;
            rm[b]++;
        }
    }

    int solution[N];
    vector<int> vertices;
    set<int> neighbours;
    int leaves;

    int getVertice()
    {
        for (auto j : neighbours)
        {
            if (isArt[j]) continue;
            return j;
        }

        throw invalid_argument("No vertices to choose");
    }

    void solveP()
    {
        vertices.reserve(n);

        vertices.push_back(1);
        isVert[1] = true;

        for (auto i : g[1])
            neighbours.insert(i);

        for (int i = 2; i <= n; i++)
        {
            low::init();
            int v = getVertice();

            neighbours.erase(v);

            removed[v] = true;

            if (rm[v] == 1) leaves--;

            vertices.push_back(v);
            isVert[v] = true;

            for (auto j : g[v])
            {
                if (rm[j] == 0) continue;
                if (rm[j] == 2) leaves++;

                og[j].erase(v);
                neighbours.insert(j);

                --rm[j];
            }

            og[v].clear(); // buggable

            rm[v] = 0;

            solution[i] = v;
        }
    }

    void solve()
    {
        solution[1] = solution[n + 1] = 1;

        solveP();


        for (int i = 1; i <= n; i++)
        {
            fastio::writeInt(solution[i]);
            fastio::writeChar((i == n ? '\n' : ' '));
        }

        for (int i = n + 1; i >= 2; i--)
        {
            fastio::writeInt(solution[i]);
            fastio::writeChar((i == 2 ? '\n' : ' '));
        }

        fastio::write();
    }
};
 
int main()
{
    sol::read();
    sol::solve();
}