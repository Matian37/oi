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

int t[2505];

struct Node
{
    Node *left, *right;
    int num;

    Node() : left(NULL), right(NULL){};
};

queue<int> q;

void create(Node* v, int depth)
{
    if (q.front() == depth)
    {
        q.pop();
        return;
    }
    v->left = new Node();
    v->right = new Node();
    
    create(v->left, depth + 1);
    create(v->right, depth + 1);
}

Node* root = new Node();
Node* rootroot = new Node();

int num = 1;

void printGen(Node *parent, Node *v)
{
    cout << parent->num << ' ';
    v->num = num;
    num++;

    if (v->left != NULL)
        printGen(v, v->left);
    if (v->right != NULL)
        printGen(v, v->right);
}

void printNaw(Node *v)
{
    if (v == NULL)
        return;

    cout << '(';
    printNaw(v->left);
    printNaw(v->right);
    cout << ')';
}

bool isCorrect(int n)
{
    int nodes = 1, level = 0;

    while (n != 0)
    {
        n -= t[level];
        nodes -= t[level];
        level++;
        nodes *= 2;
    }

    if (nodes < 0 || nodes > 0)
        return false;
    return true;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        t[a]++;
        q.push(a);
    }

    if (!isCorrect(n))
    {
        Nie
        return 0;
    }

    create(root, 0);

    rootroot->num = 0;

    printGen(rootroot, root);
    cout << '\n';
    printNaw(root);
}