//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("O3,fast-math,unroll-loops")

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

namespace fastio
{
    char rbuff[10'000'000], wbuff[40];

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

    void readString(string& s, int n)
    {
        s.reserve(n);
        nxt();

        for (int i = 0; i < n; i++)
            s += rbuff[r++];
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

    char tmp[12];

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

    void write()
    {
        fwrite(&wbuff, sizeof(char), w, stdout);
    }
}

namespace sol
{
    vector<ii> t;
    int k;

    void read()
    {
        fastio::read();
        fastio::readInt(k);

        t.reserve(1e6+1);

        for (int i = 1; i <= k; i++)
        {
            int x;
            fastio::readInt(x);

            while (x--)
            {
                int c;
                fastio::readInt(c);
                t.push_back({c, i});
            }
        }

        sort(all(t));
    }

    vector<ii> best;

    void solve()
    {
        best.reserve(3);

        for (auto i : t)
        {
            [&]()
            {
                bool did = [&]()
                {
                    for (int j = 0; j < isize(best); j++)
                        if (best[j].sec == i.sec)
                        {
                            best[j].fir = max(best[j].fir, i.fir);
                            return true;
                        }
                    return false;
                }();
                
                if (did) 
                    sort(all(best));
                else
                {
                    best.push_back(i);
                    sort(all(best));
                    if (best.size() > 3) best.erase(best.begin());
                }
            }();

            if (best.size() < 3) continue;

            if (best[0].fir + best[1].fir > best[2].fir)
            {
                for (auto[x, y] : best)
                {
                    fastio::writeInt(y);
                    fastio::writeChar(' ');
                    fastio::writeInt(x);
                    fastio::writeChar(' ');               
                }
                fastio::writeChar('\n');
                return;
            }
        }

        fastio::writeChar('N');
        fastio::writeChar('I');
        fastio::writeChar('E');
        fastio::writeChar('\n');
    }
};
 
int main()
{
    sol::read();
    sol::solve();
    fastio::write();
}