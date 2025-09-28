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
#define itr iterator
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
    char rbuff[6'000'006], wbuff[10];

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
    const int N = 1e5 + 5;
    int t[N];
    int n;

    void read()
    {
        fastio::read();
        fastio::readInt(n);

        n *= 2;

        for (int i = 0; i < n; i++)
            fastio::readInt(t[i]);
    }
    
    list<ii>::itr visited[N];
    list<ii> s;
    // val, ind

    void normalize(list<ii>::itr x)
    {
        while (x != s.end())
        {
            x->sec = (x == s.begin() ? 1 : prev(x)->sec + 1);
            x++;
        }
    }

    void resolve(list<ii>::itr x)
    {
        while (x != s.begin() && x != prev(s.end()))
        {
            if (*prev(x) != *next(x)) break;
            s.erase(prev(x));
            s.erase(next(x));
        }

        auto prv = (x == s.begin() ? s.end() : prev(x));

        s.erase(x);

        if (prv == s.end()) prv = s.begin();

        normalize(prv);
    }

    void solve()
    {
        vector<int> mv;

        for (int i = 0; i <= n / 2; i++)
            visited[i] = s.end();
        
        int i = 0;

        while (i < n)
        {
            if (visited[t[i]] == s.end())
            {
                s.push_back({t[i], isize(s) + 1});
                visited[t[i]] = prev(s.end());
                i++;

                continue;
            }

            auto it = prev(s.end());

            while (it->fir != t[i])
            {
                mv.push_back(it->sec);
                it--;
            }

            resolve(visited[t[i]]);

            i++;

            while (i < n && s.size())
            {
                if (t[i] != s.back().fir) break;
                s.pop_back();
                i++;
            }
        }

        fastio::writeInt(isize(mv));
        fastio::writeChar('\n');

        for (auto j : mv)
        {
            fastio::writeInt(j);
            fastio::writeChar('\n');
        }

        fastio::write();
    }
};
 
int main()
{
    sol::read();
    sol::solve();
}