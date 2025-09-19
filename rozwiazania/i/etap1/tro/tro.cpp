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

struct ulamek
{
    int a, b;
};

bool mniej(const ulamek &a, const ulamek &b)
{
    if ((ull)a.a * (ull)b.b < (ull)b.a * (ull)a.b)  
        return true;
    return false;
}

ulamek min(const ulamek &a, const ulamek &b)
{
    if (a.a * b.b < b.a * a.b)  
        return a;
    return b;
}

ulamek max(const ulamek &a, const ulamek &b)
{
    if (a.a * b.b > b.a * a.b)  
        return a;
    return b;    
}

ulamek add(const ulamek &a, const ulamek &b)
{
    return {a.a * b.b + b.a * a.b, a.b * b.b};
}

void readUlamek(ulamek &a)
{
    string s;
    cin >> s;

    int j;

    for (int i = 1; i <= s.size(); i++)
    {
        if (s[i] == '/')
        {
            j = i;
            break;
        }
    }

    a.a = stoi(s.substr(0, j));
    a.b = stoi(s.substr(j + 1, (int)s.size() - j - 1));
}

ulamek minn[2], maks;

void read()
{
    int n;
    cin >> n;

    readUlamek(minn[0]);
    readUlamek(minn[1]);

    if (!mniej(minn[0], minn[1]))
        swap(minn[0], minn[1]);
    maks = minn[1];

    for (int i = 2; i < n; i++)
    {
        ulamek in;
        readUlamek(in);

        if (mniej(in, minn[0]))
        {
            minn[1] = minn[0];
            minn[0] = in;
        }
        else if (mniej(in, minn[1]))
        {
            minn[1] = in;
        }

        maks = max(maks, in);
    }

    if (mniej(maks, add(minn[0], minn[1])))
        cout << "TAK\n";
    else
        cout << "NIE\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
}