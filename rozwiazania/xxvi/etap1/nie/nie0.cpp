//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000
#define ii pair<int,int>
#define pll pair<long long, long long>
#define pul pair<unsigned long long, unsigned long long>
#define Tak cout << "TAK" << '\n';
#define Nie cout << "NIE" << '\n';

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;

using namespace std;

list<int> wstp[4];

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    for (int i = 0; i < b.size(); i++)
    {
        if (b[i] == 'A')
            wstp[0].push_back(i);
        else if (b[i] == 'C')
            wstp[1].push_back(i);
        else if (b[i] == 'G')
            wstp[2].push_back(i);
        else
            wstp[3].push_back(i);
    }

    int j = -1;

    string result = "";

    for (int i = 0; i < a.size(); i++)
    {
        int type = a[i] == 'A' ? 0 : (a[i] == 'C' ? 1 : (a[i] == 'G' ? 2 : 3));

        while (wstp[type].size())
        {
            if (wstp[type].front() > j)
                break;
            wstp[type].pop_front();
        }

        if (!wstp[type].size())
            continue;
        result += a[i];
        j = wstp[type].front();
    }

    cout << result;
}