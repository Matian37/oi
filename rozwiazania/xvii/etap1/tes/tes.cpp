//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

vector<int> wstp[1000005];
int n;

void read()
{

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        wstp[a].push_back(i);
    }
}

void solve()
{
    int m;
    cin >> m;

    int pos = 0;
    bool poss = true;

    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;

        if (!poss)  
            continue;

        auto r = lower_bound(wstp[a].begin(), wstp[a].end(), pos + 1);

        if (r == wstp[a].end())
        {
            cout << "NIE\n";
            poss = false;
            continue;
        }

        pos = *r;
    }

    if (poss)
        cout << "TAK\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();

    int q;
    cin >> q;

    while (q--)
    {
        solve();
    }
    


}