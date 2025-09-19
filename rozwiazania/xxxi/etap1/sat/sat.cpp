//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD1 1000000007LL
#define MOD2 1000000009LL
#define MOD3 1000000021LL
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'
#define min3(x, y, z) min(x, min(y, z))
#define max3(x, y, z) max(x, max(y, z))
#define h1 first.first
#define h2 first.second
#define h3 second

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;
typedef pair<ii, int> HASH;

/*
   Stan pierwotny -> (<n + 1, 2n>, {1, 2, 3, ... , n}) dla satelit
   Stan odwrocony -> (<1, n>, {n + 1, n + 2, n + 3, ... , 2n}) dla satelit
*/

vector<vector<int>> columns, rows;
vector<int> g[2005], wolne;
char solution[2005][2005]; // {satelita, kod}
bool rotated = false;
int n, p, m;

void readInt(int& a)
{
    char r = getchar();

    while (r <= 32) r = getchar();

    a = 0;

    while (r > 32)
    {
        a = a * 10 + int(r - '0');
        r = getchar();
    }
}

void printInt(int a)
{
    string r = to_string(a);

    for (int i = 0; i < r.size(); i++) putchar(r[i]);
}

void printChar(char a)
{
    putchar(a);
}

bool isGreaterThan(ii& a, ii& b)
{
    if (a.first > b.first) return true;
    else if (a.first == b.first && a.second > b.second) return true;
    return false;
}

void read()
{
    readInt(n);
    readInt(p);
    readInt(m);

    while (p--)
    {
        int a, b;
        readInt(a);
        readInt(b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

void init()
{
    for (int i = n + 1; i <= 2 * n; i++)
    {
        solution[i][i - n] = 'A';
        
        for (int j : g[i]) solution[j][i - n] = 'A';
    }
}

ii getMaxWier(vector<int>& v, int pos, int c)
{
    if (v.size() == 0) return {0, 0};
    if (pos > n) return {v.size(), v.size()};

    vector<int> a, b;

    for (int i : v)
    {
        if (solution[i][pos] == 'A') a.push_back(i);
        else b.push_back(i);
    }

    auto acc1 = getMaxWier(a, pos + 1, c + 1),
         acc2 = getMaxWier(b, pos + 1, c);

    return {max(acc1.first, acc2.first), acc1.second + acc2.second};
}

ii getMaxKol(vector<int>& v, int pos, int c)
{
    if (v.size() == 0) return {0, 0};
    if (pos > n) return {v.size(), v.size()};

    vector<int> a, b;

    for (int i : v)
    {
        if (solution[pos][i] == 'A') a.push_back(i);
        else b.push_back(i);
    }

    auto acc1 = getMaxKol(a, pos + 1, c + 1),
         acc2 = getMaxKol(b, pos + 1, c);

    return {max(acc1.first, acc2.first), acc1.second + acc2.second};
}

void rotuj()
{
    for (int i = n + 1; i <= 2 * n; i++)
    {
        solution[i][i - n] = 0;
        
        for (int j : g[i]) solution[j][i - n] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        solution[i + n][i] = 'A';

        for (int j : g[i]) solution[j - n][i] = 'A';
    }

    rotated = true;
}

void printOut()
{
    printInt(n + 1);
    printChar('\n');

    for (int i = (rotated ? n + 1 : 1); i <= (rotated ? 2 * n : n); i++)
    {
        for (int j = 1; j <= n + 1; j++) 
            printChar(solution[i][j] == 0 ? 'B' : 'A');
        printChar('\n');
    }

    for (int i = (rotated ? 1 : n + 1); i <= (rotated ? n : 2 * n); i++)
    {
        for (int j = 1; j <= n + 1; j++) 
            printChar(solution[i][j] == 0 ? 'C' : 'A');
        printChar('\n');
    }
}

void getKolumns(vector<int>& v, int pos)
{
    if (v.size() <= 1) return;
    if (pos > n) {columns.push_back(v); return;}

    vector<int> a, b;

    for (int i : v)
    {
        if (solution[pos][i] == 'A') a.push_back(i);
        else b.push_back(i);
    }

    getKolumns(a, pos + 1);
    getKolumns(b, pos + 1);
}

void getWiersze(vector<int>& v, int pos)
{
    if (v.size() <= 1) return;
    if (pos > n) {rows.push_back(v); return;}

    vector<int> a, b;

    for (int i : v)
    {
        if (solution[i][pos] == 'A') a.push_back(i);
        else b.push_back(i);
    }

    getWiersze(a, pos + 1);
    getWiersze(b, pos + 1);
}

void getKW(ii &k, ii &w)
{
    vector<int> v;
    for (int i = 1; i <= n; i++) v.push_back(i);
    k = getMaxKol(v, 1, 1);
    w = getMaxWier(v, 1, 1);
}

void join(vector<int>& kp, vector<int>&k ,int end, int pos)
{
    if (pos < end || kp.size() <= 1) return;

    vector<int> a, b;
    bool turn = true;

    for (int i : kp)
    {
        if (!turn)
        {
            solution[i + n][k[pos]] = 'A';
            a.push_back(i);
        }
        else
        {
            solution[i + n][k[pos]] = 0;
            b.push_back(i);
        }
        turn = !turn;
    }

    join(a, k, end, pos - 1);
    join(b, k, end, pos - 1);
}

void joinColumns(int k)
{
    vector<int> v;

    for (int i = 1; i <= n; i++) v.push_back(i);

    getKolumns(v, 1);

    int c = 0;

    bool did = false, add = false;  

    for (int i = 0; i < columns.size(); i++)
    {
        if (columns[i].size() <= 1) continue;
        if (columns[i].size() != k && add) continue;
        if (columns[i].size() == k && did && add) continue;

        if (columns[i].size() == 3)
        {

            for (int j = 1; j < 2; j++)
            {
                solution[columns[i][j] + n][columns[i][j]] = 0;
                solution[columns[i][j] + n][columns[i][0]] = 'A';
            }

            vector<int> k2;

            for (int j = 0; j < 2; j++) k2.push_back(columns[i][j]);

            join(k2, columns[i], 2, 2);

            wolne.push_back(columns[i][1]);
        }
        else if (columns[i].size() == 5)
        {
            for (int j = 1; j < 4; j++)
            {
                solution[columns[i][j] + n][columns[i][j]] = 0;
                solution[columns[i][j] + n][columns[i][0]] = 'A';
            }

            vector<int> k2;

            for (int j = 0; j < 4; j++) k2.push_back(columns[i][j]);

            join(k2, columns[i], 3, 4);

            for (int j = 3; j >= 3; j--)
            {
                for (int l = 1; l <= n; l++) solution[l][columns[i][j]] = 0;
            }

            wolne.push_back(columns[i][1]);
            wolne.push_back(columns[i][2]);
        }
        else if (columns[i].size() == 6)
        {
            for (int j = 1; j < 4; j++)
            {
                solution[columns[i][j] + n][columns[i][j]] = 0;
                solution[columns[i][j] + n][columns[i][0]] = 'A';
            }
            solution[columns[i][5] + n][columns[i][4]] = 'A';
            for (int j = 1; j <= n; j++) solution[j][columns[i][5]] = 0;

            vector<int> k2;

            for (int j = 0; j < 4; j++) k2.push_back(columns[i][j]);

            join(k2, columns[i], 4, 5);

            wolne.push_back(columns[i][1]);
            wolne.push_back(columns[i][2]);
            wolne.push_back(columns[i][3]);
        }
        else
        {
            int k2 = columns[i].size();

            for (int j = 1; j < k2; j++)
            {
                solution[columns[i][j] + n][columns[i][j]] = 0;
                solution[columns[i][j] + n][columns[i][0]] = 'A';
            }


            join(columns[i], columns[i], k2 - ceil(log2(k2)), k2 - 1);

            for (int j = k2 - 1; j >= k2 - ceil(log2(k2)); j--)
            {
                for (int l = 1; l <= n; l++) solution[l][columns[i][j]] = 0;
            }

            for (int j = 1; j < k2 - ceil(log2(k2)); j++)
                wolne.push_back(columns[i][j]);
        }

        if (columns[i].size() == k && !did) did = true;
        else add = true;

        if (did && add) break;
    }

    for (int i : wolne)
    {
        for (int j = 1; j <= n; j++) solution[j][i] = 0;
    }

    wolne.push_back(n + 1);
}

void repairDiv(vector<int>& v, int pos)
{
    if (pos == wolne.size() || v.size() <= 1) return;

    vector<int> a, b;

    bool turn = false;

    for (int i : v)
    {
        if (turn)
        {
            a.push_back(i);
            solution[i][wolne[pos]] = 'A';
        }
        else
        {
            b.push_back(i);
        }

        turn = !turn;
    }

    repairDiv(a, pos + 1);
    repairDiv(b, pos + 1);
}

void repair()
{
    vector<int> v;

    for (int i = 1; i <= n; i++) v.push_back(i);

    getWiersze(v, 1);

    for (auto& i : rows) repairDiv(i, 0);
}

void solve()
{
    init(); // O(N + P)
    ii k, w;
    getKW(k, w); // O(N^2)
    if (isGreaterThan(w, k)) {swap(k, w); rotuj();} // O(N + P)
    joinColumns(k.first); // O(N^2 + N)
    repair(); // O(N^2)
    printOut(); // O(N^2)
}

int main()
{
    ios_base::sync_with_stdio(0);

    read();
    solve();
}