//
// Mateusz Pietrowcow
//
 
#pragma GCC optimize("O3,fast-math,unroll-loops")

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

namespace fastio
{
    char rbuff[10'000'005], wbuff[16'000'005];

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
    const int K = 2'000'005;

    ii ans[K];

    int n, q;
    string s;
    int sum;

    void read()
    {
        fastio::readInt(n);
        fastio::readInt(q);
        fastio::readString(s, n);

        for (int i = 0; i < n; i++)
        {
            s[i] = (s[i] == 'T' ? 2 : 1);
        }
    }

    int maks[2];

    void goDown(int a, int b)
    {
        int __sum = 0;

        for (int i = a; i <= b; i++)
            __sum += s[i];
        
        maks[__sum % 2] = __sum;
        
        ans[__sum] = {a, b};

        while (__sum > 2)
        {
            if (s[a] == 2)
                a++;
            else if (s[b] == 2)
                b--;
            else
                a++,b--;

            __sum -= 2;
            ans[__sum] = {a,b};
        }
    }

    void preprocess()
    {
        goDown(0, n - 1);

        int a = int(s.find(1)), b = int(s.rfind(1));

        if (s.find(1) == s.npos)
            return;

        if (n - 1 - b < a) b--, a = 0;
        else a++, b = n - 1;

        if (a > b) return;

        goDown(a, b);
    }

    void solve()
    {
        preprocess();
    
        while (q--)
        {
            int k;
            fastio::readInt(k);

            if (maks[k % 2] < k)
            {
                for (auto i : {'N', 'I', 'E', '\n'})
                    fastio::writeChar(i);
            }
            else
            {
                fastio::writeInt(ans[k].fir + 1);
                fastio::writeChar(' ');
                fastio::writeInt(ans[k].sec + 1);
                fastio::writeChar('\n');
            }
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