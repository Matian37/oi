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

vector<ii> ranges;
int n;

void read()
{
    cin >> n;

    while (n--)
    {
        ii a;
        cin >> a.first >> a.second;

        ranges.push_back(a);
    }
}

void solve()
{
    sort(ranges.begin(), ranges.end());

    int p = 0, k = 0;

    for (auto i : ranges)
    {
        if (k < i.first)
        {
            if (p != 0)
                cout << p << ' ' << k << '\n';
            p = i.first;
            k = i.second;
        }
        else
            k = max(k, i.second);
    }
    cout << p << ' ' << k << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}