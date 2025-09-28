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

namespace fastio
{
    char rbuff[2'000'0060], wbuff[32];

    int r, w;

    void read()
    {
        fread(&rbuff, sizeof(char), sizeof(rbuff), stdin);
    }

    void nxt()
    {
        while (rbuff[r] <= ' ')
            r++;
    }

    void readInt(int& a)
    {
        a = 0;
        nxt();

        while (rbuff[r] > ' ')
            a = a * 10 + (rbuff[r++] - '0');
    }

    inline void writeChar(char a)
    {
        wbuff[w++] = a;
    }

    char tmp[24];

    void writeInt(int a)
    {
        if (a == 0)
        {
            writeChar('0');
            return;
        }

        int wsk = 0;

        while (a != 0)
        {
            tmp[wsk++] = char((a % 10) + (int)'0');
            a /= 10;
        }

        wsk--;

        while (wsk >= 0)
            writeChar(tmp[wsk--]);
    }

    void writeLL(ll a)
    {
        if (a == 0)
        {
            writeChar('0');
            return;
        }

        int wsk = 0;

        while (a != 0)
        {
            tmp[wsk++] = char((a % 10) + (int)'0');
            a /= 10;
        }

        wsk--;

        while (wsk >= 0)
            writeChar(tmp[wsk--]);
    }

    void write()
    {
        fwrite(&wbuff, sizeof(char), w, stdout);
    }
}

namespace sol
{
    int stp[N];
    vector<int> g[N];
    int n, l;

    void read()
    {
        fastio::readInt(n);
        fastio::readInt(l);

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            fastio::readInt(a);
            fastio::readInt(b);
            g[a].push_back(b);
            stp[a]++;
            g[b].push_back(a);
            stp[b]++;
        }
    }
    
    int sajz[N], parent[N], change[N];

    struct cmp
    {
        bool operator()(const ii& a, const ii& b) const
        {
            return a.fir < b.fir;
        }
    };

    multiset<ii, cmp> costs;

    int sajzDfs(int v, int p)
    {
        parent[v] = p;
        sajz[v] = 1;

        for (auto i : g[v])
            if (i != p)
                sajz[v] += sajzDfs(i, v);
        return sajz[v];
    }

    void push(int v)
    {
        int p = parent[v];

        change[p] += change[v];
        sajz[p] += change[v];
    }

    void solve()
    {
        if (l == 0)
        {
            cout << 0 << '\n';
            return;
        }
        if (n == 2)
        {
            cout << 2 << '\n';
            return;
        }

        int cen = 1;

        sajzDfs(1,1);

        for (int i = 1; i <= n; i++)
            if (sajz[i] < sajz[cen] && sajz[i] >= n / 2)
                cen = i;
        
        sajzDfs(cen,cen);

        int leaves = -2*l;

        for (int i = 1; i <= n; i++)
            if (stp[i] == 1) 
                leaves++, costs.insert({sajz[i], i});

        int result = n;

        while (leaves > 0)
        {
            auto curr = *costs.begin();
            costs.erase(costs.begin());

            int p = parent[curr.sec];

            if (stp[p] + (p == cen) == 2)
            {
                push(curr.sec);
                costs.insert({sajz[p],p});
                continue;
            }

            change[curr.sec] -= sajz[curr.sec];
            result -= sajz[curr.sec];
            stp[p]--;
            push(curr.sec);
            leaves--;
        }

        fastio::writeInt(result);
        fastio::writeChar('\n');
    }
};
 
int main()
{
    fastio::read();
    sol::read();
    sol::solve();
    fastio::write();
}