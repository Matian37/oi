//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include "ckollib.h"

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

int bytes[32];

vector<ii> unc;

void add(int krt)
{
    if (unc.size() == 0)
    {
        unc.push_back({krt,1});
        return;
    }
    else if (unc.size() == 1)
    {
        if (unc.back().first == krt) unc.back().second++;
        else unc.push_back({krt, 1});
    }
    else
    {
        if (unc.back().first == krt) unc.back().second++;
        else if (unc.front().first == krt) unc.front().second++;
    }
}

int main()
{
    int n, k;
    n = k = 0;

    uint val = karta();

    do
    {
        n++;
        add(val);

        for (int j = 0; j < 32; j++)
            bytes[j] += ((val >> j) & 1);
        val = karta();
    } while (val != 0);

    k = max(unc.front().second, unc.back().second);

    if (unc.size() == 1)
    {
        odpowiedz(unc.back().first);
        return 0;
    }

    uint r = 0;

    for (int i = 0; i < 32; i++)
    {
        bytes[i] = (bytes[i] % k == 0 ? 0 : 1);
        r += (uint)bytes[i] << i;
    }

    odpowiedz(r);
}