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
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

bool op[1000005];
string r[1000005];

int n;

void read()
{
    cin >> n;
    n--;
    for (int i = 1; i <= n; i++) 
    {char a; cin >> a; op[i] = (a == '+' ? true : false);}
}

void solve()
{
    bool dod = false;

    for (int i = n; i >= 1; i--)
    {
        if (op[i])
        {
            if (dod) r[i] = "-";
            else {r[i] = "-)"; dod = true;};
        }
        else
        {
            if (dod) {r[i] = "-("; dod = false;}
            else r[i] = "-";
        }
    }

    for (int i = 1; i <= n; i++) cout << r[i];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}