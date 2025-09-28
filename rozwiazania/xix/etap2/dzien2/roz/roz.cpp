//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000ULL
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

vector<ull> fibb = {1, 2};
ull k;

void init()
{
    while (fibb[fibb.size() - 2] + fibb[fibb.size() - 1] <= INFL)
        fibb.push_back(fibb[fibb.size() - 2] + fibb[fibb.size() - 1]);
}

void read()
{
    cin >> k;
}

int solve()
{
    int c = 0;

    while (k != 0)
    {
        c++;

        if (*lower_bound(fibb.begin(), fibb.end(), k) == k)
            break;
        
        auto it = upper_bound(fibb.begin(), fibb.end(), k);
        ull upper = *it, lower = *(--it);
        ull left = k - lower, right = upper - k;

        if (*lower_bound(fibb.begin(), fibb.end(), left) == left) k = left;
        else if (*lower_bound(fibb.begin(), fibb.end(), left) == right) k = right;
        else if (left < right) k = left;
        else k = right;
    }
    
    return c;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    init();

    int q;
    cin >> q;

    while (q--)
    {
        read();
        cout << solve() << '\n';
    }
}