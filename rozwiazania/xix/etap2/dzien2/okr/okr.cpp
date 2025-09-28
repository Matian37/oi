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

#define MOD 1000000007LL
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

constexpr int N = 5e5 + 5;

namespace fastio
{
    char rbuffer[4'000'000'0], wbuffer[10'000'000];
    int rwsk, wwsk;

    void initRead()
    {
        fread(rbuffer, sizeof(char), sizeof(rbuffer), stdin);
    }

    void skip()
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
            a = a * 10 + (rbuffer[rwsk] - '0');
            rwsk++;
        }
    }

    void readString(string& s)
    {
        skip();

        while (rbuffer[rwsk] > ' ')
        {
            s += rbuffer[rwsk];
            rwsk++;
        }
    }

    char val[20];

    void printInt(int a)
    {
        if (a == 0)
        {
            wbuffer[wwsk++] = '0';
            wbuffer[wwsk++] = '\n';
            return;    
        }

        int wsk = -1;

        while (a != 0)
        {
            val[wsk + 1] = char('0' + a % 10);
            wsk++;
            a /= 10;
        }

        while (wsk >= 0)
        {
            wbuffer[wwsk++] = val[wsk--];
        }
        wbuffer[wwsk++] = '\n';
    }

    void print()
    {
        fwrite(wbuffer, sizeof(char), sizeof(char)*wwsk, stdout);
    }
}

namespace hashing
{
    ll p;
    ll h[N], power[N];

    void init(string& s, int n)
    {
        mt19937 rng(timeNow());

        p = uniform_int_distribution<int>(27, MOD - 2)(rng);

        power[0] = 1;

        for (int i = 0; i < n; i++)
        {
            h[i + 1] = (h[i] * p + (s[i] - 'a' + 1)) % MOD;
            power[i + 1] = (power[i] * p) % MOD;
        }
    }

    ll query(int a, int b)
    {
        ll r = h[b];

        return (MOD + (r - h[a - 1] * power[b - a + 1]) % MOD) % MOD;
    }
}

namespace sieve
{
    vector<ii> divisors[N];
    vector<int> primes;
    int t[N];

    void sieve()
    {
        for (int i = 2; i < N; i++)
        {
            if (t[i] == 0)
            {
                primes.push_back(i);
                t[i] = i;
            }

            for (int j = 0; j < isize(primes); j++)
            {
                if ((ll)i * primes[j] >= N) break;
                if (primes[j] > t[i]) break;
                t[i * primes[j]] = primes[j];
            }
        }
    }

    vector<ii>& getDivisors(int n)
    {
        int m = n;

        if (divisors[m].size() != 0)
            return divisors[m];
        
        divisors[m].reserve(__lg(n));

        divisors[m].push_back({t[n],1});

        n /= t[n];

        while (n != 1)
        {
            if (divisors[m].back().fir == t[n])
                divisors[m].back().sec++;
            else
                divisors[m].push_back({t[n], 1});

            n /= t[n];
        }

        return divisors[m];
    }
}

namespace sol
{
    int n;
    string s;

    void read()
    {
        fastio::readInt(n);
        s.reserve(n);
        fastio::readString(s);
    }
    
    void solve()
    {
        sieve::sieve();
        hashing::init(s, n);

        int q;
        fastio::readInt(q);

        while (q--)
        {
            int a, b;
            fastio::readInt(a);
            fastio::readInt(b);

            if (a == b)
            {
                int v = 1;
                fastio::printInt(v);
                continue;
            }

            int m=b-a+1;

            vector<ii>& div = sieve::getDivisors(m);

            int r = m;

            for (auto i : div)
            {
                while (i.sec != 0)
                {
                    r /= i.fir;
                    i.sec--;

                    if (hashing::query(a,a+(m-r)-1) != hashing::query(b-(m-r)+1,b))
                    {
                        r *= i.fir;
                        break;
                    }
                }
            }

            fastio::printInt(r);
        }
    }
};
 
int main()
{
    fastio::initRead();
    sol::read();
    sol::solve();
    fastio::print();
}