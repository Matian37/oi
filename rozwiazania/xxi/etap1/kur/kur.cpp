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

const int N = 5e5 + 10;
const int k = 25;

namespace sol
{
    ii zapq[N][k]; // bottleneck
    bitset<N> visitedPrefix;
    forward_list<int> event[N];
    ii zap[N];
    int t[N];

    int n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 1; i <= n; i++) cin >> t[i];

        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

        for (int i = 0; i < m; i++)
        {
            cin >> zap[i].first >> zap[i].second;
            
            event[zap[i].first - 1].push_front(i);
            event[zap[i].second].push_front(i);

            for (int j = 0; j < k; j++)
            {
                int c = zap[i].first + rng() % (zap[i].second - zap[i].first + 1);
                zapq[i][j] = {t[c], 0};
            }
        }
    }

    int lic[N];

    void init()
    {
        for (int i = 0; i <= n; i++)
        {
            lic[t[i]]++;

            for (auto j : event[i])
            {
                int val = (!visitedPrefix[j] ? -1 : 1);

                for (auto& l : zapq[j])
                    l.second += val * lic[l.first];
                visitedPrefix[j] = true;
            }
        }
    }

    void solve()
    {
        init();

        for (int i = 0; i < m; i++)
        {
            int ans = 0, dl = zap[i].second - zap[i].first + 1;

            for (auto j : zapq[i])
            {
                if (j.second <= dl / 2) continue;
                ans = j.first;
                break;
            }

            cout << ans << '\n';
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