//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
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

vector<int> ev[1000];
int n;

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int t, x;
        cin >> t >> x;
        ev[t].push_back(x);
    }
}

int did = 0;
 
double solve(double pos, double res, int time)
{
    double r = res;

    for (auto i : ev[time])
    {
        r = min(r, abs((double)i - pos));
        did++;
    }

    if (did == n) 
    {
        for (auto i : ev[time]) did--;
        return r;
    }

    double best = 0;

    best = max(best, solve(pos - 1, r, time + 1));
    best = max(best, solve(pos - 0.5, r, time + 1));
    best = max(best, solve(pos, r, time + 1));
    best = max(best, solve(pos + 0.5, r, time + 1));
    best = max(best, solve(pos + 1, r, time + 1));

    for (auto i : ev[time]) did--;

    return min(r, best);
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    read();
    cout << solve(0, numeric_limits<double>::max(), 0);
}