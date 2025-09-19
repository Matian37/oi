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
#define int128 __int128_t
#define uint128 __uint128_t

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
#define len(x) (int)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
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

namespace fastio
{
    char rbuff[2'000'0060], wbuff[2'000'0000];

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
    const int N = 1e6 + 5;
    bitset<N> visited, isBon;
    vector<ll> done;
    int last[N], pl[N];
    int n, m;

    void read()
    {
        fastio::readInt(n);

        for (int i = 0; i < n; i++)
        {
            int c;
            fastio::readInt(c);
            isBon[c] = true;
            m = max(m, c);
        }
    }
    
    void solve()
    {
        int q;
        fastio::readInt(q);

        ll id = 1;

        for (int i = 1; i <= q; i++)
        {
            #define pos last[x]

            int x;
            fastio::readInt(x);

            if (last[x] == 0) last[x] = x;
            
            ll oid = id;

            for (int k = x; k > 0 && pos <= m; pos += x)
            {
                if (visited[pos])
                    continue;

                if (isBon[pos])
                    done.push_back(id);

                visited[pos] = true;
                id++;
                k--;
            }

            id = oid + x;
            #undef pos
        }

        fastio::writeLL(len(done));
        fastio::writeChar('\n');

        for (int i = 0; i < len(done); i++)
        {
            fastio::writeLL(done[i]);
            fastio::writeChar('\n');
        }
    }
};
 
int main()
{
    fastio::read();
 
    sol::read();
    sol::solve();

    fastio::write();
}