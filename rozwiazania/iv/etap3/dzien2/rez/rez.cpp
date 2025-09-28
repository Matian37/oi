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

const int N = 1e4 + 5;

namespace sol
{
    pair<ii,int> tp[N], tk[N];
    int dp[N];
    int n, bestdp;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> tp[i].first.first >> tp[i].first.second,
            tp[i].second = i,
            tk[i] = tp[i];
    }
    
    bool comp(const pair<ii,int>& a, const pair<ii,int>& b)
    {
        if (a.first.second != b.first.second) return a.first.second < b.first.second;
        return a.first.first < b.first.first;
    }

    #define len(a) ((a).second-(a).first)

    void solve()
    {
        sort(tp+1,tp+(n+1));
        sort(tk+1,tk+(n+1),comp);

        int r = 0;

        for (int i = 1, j = 0; i <= n; i++)
        {
            while (tk[j + 1].first.second <= tp[i].first.first)
            {
                j++;
                bestdp = max(bestdp, dp[tk[j].second]);
            }
            
            dp[tp[i].second] = bestdp + len(tp[i].first);
            r = max(dp[tp[i].second], r);
        }

        cout << r;
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