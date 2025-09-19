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

struct hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    char rbuffer[2000100], wbuffer[100];
    int rwsk, wwsk;

    inline void skip()
    {
        while (rbuffer[rwsk] <= ' ')
            rwsk++;
    }

    void readInt(int& a)
    {
        skip();

        a = 0;

        while (rbuffer[rwsk] > ' ')
        {
            a = a * 10 + (rbuffer[rwsk++] - '0');
        }
    }

    char buff[100];

    void writeInt(int& a)
    {
        int wsk = -1;

        while (a != 0)
        {
            buff[++wsk] = char('0' + (a % 10));
            a /= 10;
        }

        while (wsk >= 0)
        {
            wbuffer[wwsk++] = buff[wsk--];
        }
    }

    void read()
    {
        fread(rbuffer, sizeof(char), sizeof(rbuffer), stdin);

        vector<int> v;

        v.reserve(1e6);

        int c;
        readInt(c);

        while (c != 0)
        {
            v.push_back(c);
            readInt(c);
        }

        sort(all(v));

        int n = isize(v);

        bool did = false;

        for (int i = 2; i < n; i++)
        {
            if (v[i - 2] + v[i - 1] <= v[i])
            continue;

            writeInt(v[i - 2]);
        wbuffer[wwsk++] = ' ';
            writeInt(v[i - 1]);
        wbuffer[wwsk++] = ' ';
            writeInt(v[i]);
            wbuffer[wwsk++] = '\n';
            
            did = true;
            break;
        }

        if (!did)
        {
            wbuffer[wwsk++] = 'N';
            wbuffer[wwsk++] = 'I';
            wbuffer[wwsk++] = 'E';
            wbuffer[wwsk++] = '\n';
        }

        fwrite(wbuffer, sizeof(char), sizeof(char) * wwsk, stdout);
    }
    
    void solve()
    {
    }
};
 
int main()
{ 
    sol::read();
    sol::solve();
}