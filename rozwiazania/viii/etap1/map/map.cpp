#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define ii pair<int,int>
#define pll pair<ll,ll>
#define pull pair<ull,ull>
#define min3(x,y,z) min(x, min(y, z))

int f[255][255], sol[255][255], pref[255][255];
int n, r;

void read()
{
    cin >> n >> r;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> f[i][j];
}

void solve()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] +  f[i][j];
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sol[i][j] = pref[min(i + r, n)][min(j + r, n)] - pref[min(i + r, n)][max(j - r - 1, 0)] - pref[max(i - r - 1, 0)][min(j + r, n)] + pref[max(i - r - 1, 0)][max(j - r - 1, 0)];   
        
            cout << sol[i][j] << ' ';
        }
        cout << '\n';
    }


}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}