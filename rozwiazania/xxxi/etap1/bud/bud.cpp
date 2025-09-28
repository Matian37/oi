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

int pref[1505][1505];
int n, m;

void read()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char add;
            cin >> add;
            add = (add == 'X') ? 1 : 0;
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + add;
        }
    }
}


vector<ii> positionsKol, positionsWier;

// a - gory, b - dolny
int getRectangle(ii a, ii b)
{
    if (b.first < 0 || b.second < 0 || a.first < 0 || a.second < 0)
        return 1;

    return pref[b.first][b.second] 
         - pref[b.first][a.second - 1] - pref[a.first - 1][b.second] 
         + pref[a.first - 1][a.second - 1];
}

void gen(int len)
{
    positionsKol.clear();
    positionsWier.clear();

    for (int i = 1; i <= n; i++)
    {
        for (int j = n; j >= len; j--)
        {
            if (getRectangle({j - len + 1, i}, {j, i}) == 0)
            {
                positionsKol.push_back({j, i});
            }
            if (getRectangle({i, j - len + 1}, {i, j}) == 0)
            {
                positionsWier.push_back({i, j});
            }
        }
    }
}

bool brut(int len)
{
    for (auto i : positionsKol)
    {
        for (auto j : positionsWier)
        {
            ii a = {i.first - len + 1, i.second}, b = i,
                c = {j.first, j.second - len + 1,}, d = j;
            
            if ((c.first > b.first || a.first > d.first) || (a.second > d.second || c.second > b.second))
                    return true;
        }

        for (auto j : positionsKol)
        {
            ii a = {i.first - len + 1, i.second}, b = i,
                c = {j.first  - len + 1, j.second}, d = j;

            if (a.second != c.second || (c.first > b.first || d.first < a.first))
                return true;
        }
    }

    for (auto i : positionsWier)
    {
        for (auto j : positionsWier)
        {
            ii a = {i.first, i.second - len + 1}, b = i,
                c = {j.first, j.second - len + 1}, d = j;

            if (a.first != c.first || (c.second > b.second || d.second < a.second))
            {
                return true;
            }
        }
    }

    return false;
}

int solve()
{
    if (m == 1)
    {
        int low = 0, high = n + 1, med;

        while (low != high)
        {
            med = (low + high) / 2;
            gen(med);

            if (positionsKol.size() == 0 && positionsWier.size() == 0)
                high = med;
            else
                low = med + 1;
        }   

        return max(0, low - 1);
    }

    int low = 0, high = n + 1, med;

    while (low != high)
    {
        med = (low + high) / 2;
        gen(med);

        if (brut(med))
            low = med + 1;
        else
            high = med;
    }
    
    return max(0, low - 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    cout << solve();
}