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

int n, K, *D;

namespace tree
{
    vector<pair<ii,vector<ii>>> sqt;
    // wsk, val

    int sq;

    void init()
    {
        sq = sqrt(n);
        sqt.resize((n + sq - 1) / sq + 1);
        
        for (int i = 0; i < n; i++)
            sqt[i / sq].sec.push_back({D[i],i});

        for (int i = 0; i <= n / sq; i++)
        {
            sort(all(sqt[i].second));
            sqt[i].fir = {isize(sqt[i].sec)-1,0};
        }
    }

    template<typename T>
    struct fqueue
    {
        vector<T> v;
        int i = 0, j = 0;

        fqueue(int s)
        {
            v.reserve(s);
            i = 0, j = -1;
        }

        inline void clear()
        {
            i = 0, j = -1;
        }

        inline void push(T& b)
        {
            v[++j] = b;
        }

        inline void push(T b)
        {
            v[++j] = b;
        }

        inline void pop()
        {
            i++;
        }

        inline bool empty()
        {
            return i > j;
        }

        T front()
        {
            return v[i];
        }
    };

    fqueue<ii> q(550);

    void updateSQ(int sq, int a, int b)
    {
        q.clear();

        int j = 0;
        
        for (int i = 0; i < sqt[sq].sec.size(); i++)
        {
            auto acc = sqt[sq].sec[i];

            if (acc.sec < a || acc.sec > b)
            {
                while (!q.empty())
                {
                    if (q.front().fir > acc.fir) break;
                    sqt[sq].sec[j++] = q.front();
                    q.pop();
                }
                sqt[sq].sec[j++] = acc;
            }
            else
                q.push({acc.fir + 1, acc.sec});
        }

        while (!q.empty())
        {
            sqt[sq].sec[j++] = q.front();
            q.pop();
        }
    }

    void update(int a, int b)
    {
        if (a / sq == b / sq)
        {
            updateSQ(a / sq, a, b);
            return;
        }

        int A = a + (sq - a % sq) % sq,
            B = b - (b + 1) % sq;

        A /= sq;
        B /= sq;

        if (a % sq != 0)
            updateSQ(A - 1, a, b);

        for (int i = A; i <= B; i++)
            sqt[i].fir.sec++;

        if (b % sq != sq - 1)
            updateSQ(B + 1, a, b);
    }

    int Query(int sq, int a, int b)
    {
        int r = 0;

        for (auto i : sqt[sq].sec)
        {
            if (a > i.sec) continue;
            if (b < i.sec) continue;
            if (i.fir + sqt[sq].fir.sec < K) continue;
            r++;
        }
        
        return r;
    }

    int query(int a, int b)
    {
        if (a / sq == b / sq)
            return Query(a / sq, a, b);

        int A = a + (sq - a % sq) % sq,
            B = b - (b + 1) % sq;
        
        A /= sq;
        B /= sq;

        int r = 0;

        if (a % sq != 0)
            r += Query(A - 1, a, b);

        for (int i = A; i <= B; i++)
        {
            #define j (sqt[i].fir.fir)
            #define dod (sqt[i].fir.sec)

            while (j >= 0)
            {
                if (sqt[i].sec[j].fir + dod < K) break;
                j--;
            }


            r += isize(sqt[i].sec) - j - 1;

            #undef j
            #undef dod
        }

        if (b % sq != sq - 1)
            r += Query(B + 1, a, b);

        return r;
    }
}

void inicjuj(int _n, int _k, int *_D)
{
    n = _n;
    K = _k;
    D = _D;

    tree::init();
}

void podlej(int a, int b)
{
    tree::update(a, b);    
}

int dojrzale(int a ,int b)
{
    return tree::query(a, b);
}