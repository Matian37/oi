//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<uint,uint> uii;
typedef pair<ll,ll> pll;
typedef pair<ull,ull> pull;

#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())

const int N = 5e5 + 5;

#define DLIMIT {1,1'000'000'000}
#define ULIMIT {1'000'000'000,1}

namespace sol
{
    struct comp
    {
        bool operator()(const ii& a, const ii& b) const
        {
            return (ll)a.first * (ll)b.second < (ll)b.first * (ll)a.second;
        }
    };

    bool cmp(ii a, ii b)
    {
        return (ll)a.first * (ll)b.second < (ll)a.second * (ll)b.first;
    }

    multiset<ii, comp> p, k;
    ii t[N], oldt[N];
    // s, d
    int n, q;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> oldt[i].first >> oldt[i].second;
            swap(oldt[i].first, oldt[i].second);
        }
        
        for (int i = 1; i <= n; i++)
        {   
            int c;
            cin >> c;

            t[i] = oldt[c];
        }

        cin >> q;
    }

    inline void skroc(ii& a)
    {
        int gcd = __gcd(a.first, a.second);

        a.first /= gcd;
        a.second /= gcd;
    }

    inline void normalize(ii& a)
    {
        if (a.second < 0)
            a.first *= -1, a.second *= -1;

        int gcd = __gcd(abs(a.first), abs(a.second));

        a.first /= gcd;
        a.second /= gcd;
    }

    inline ii intersection(ii& a, ii& b)
    {
        if (a == b) return {INT32_MAX, INT32_MAX};
        if (a.first == b.first) return {INT32_MIN, INT32_MIN};

        ii r = {b.second - a.second, a.first - b.first};

        normalize(r);

        return r;
    }

    inline pair<ii,ii> getRange(int a, int b)
    {
        ii r = intersection(t[a], t[b]);

        switch (r.first)
        {
            case INT32_MAX:
                return {DLIMIT, ULIMIT};
            case INT32_MIN:
                if (t[a].second < t[b].second)
                    return {DLIMIT, ULIMIT};
                return {ULIMIT, DLIMIT};
            
            default:
                if (t[a].first > t[b].first)
                    return {DLIMIT,r};
                return {r,ULIMIT};
        }
    }

    inline void addRange(pair<ii,ii> r)
    {
        p.insert(r.first);
        k.insert(r.second);
    }

    inline void removeRange(pair<ii,ii> r)
    {
        auto pos = p.find(r.first);
        p.erase(pos);

        pos = k.find(r.second);
        k.erase(pos);
    }

    void printResult()
    {
        auto P = *prev(p.end()), K = *k.begin();

        if (cmp(K, P)) cout << "NIE\n";
        else if (cmp(K, DLIMIT)) cout << "NIE\n";
        else if (cmp(ULIMIT, P)) cout << "NIE\n";
        else if (cmp(ULIMIT, K)) cout << "1000000000/1\n" << '\n';
        else 
        {
            skroc(K);
            cout << K.first << '/' << K.second << '\n'; 
        }
    }

    void solve()
    {
        if (n == 1)
        {
            cout << "1000000000/1\n" << '\n';

            for (int i = 0; i < q; i++)
            {
                int a, b;
                cin >> a >> b;
                cout << "1000000000/1\n" << '\n';
            }
            return;
        }

        for (int i = 1; i < n; i++)
            addRange(getRange(i, i + 1));

        printResult();

        for (int i = 0; i < q; i++)
        {
            int a, b;
            cin >> a >> b;

            if (a == b)
            {
                printResult();
                continue;
            }

            if (a > b) swap(a, b);

            if (a > 1) removeRange(getRange(a - 1, a));
            if (a < n) removeRange(getRange(a, a + 1));
            if (b > 1 && b - 1 != a) removeRange(getRange(b - 1, b));
            if (b < n && b + 1 != a) removeRange(getRange(b, b + 1));

            swap(t[a], t[b]);

            if (a > 1) addRange(getRange(a - 1, a));
            if (a < n) addRange(getRange(a, a + 1));
            if (b > 1 && b - 1 != a) addRange(getRange(b - 1, b));
            if (b < n && b + 1 != a) addRange(getRange(b, b + 1));

            printResult();
        }
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::solve();
}