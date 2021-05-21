#include <bits/stdc++.h>
using namespace std;
#define rep(i, j) for (int i = 0; i < j; i++)
#define INF 2e9
#define all(v) v.begin(), v.end()
#define el '\n'
typedef long long ll;

#include "Cube.h"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Length;
    vector<int> Process;
    cin >> Length;
    rep(i, Length)
    {
        int input;
        cin >> input;
        Process.push_back(input);
    }

    Cube cube;
    cube.ExeProcess(Process);
    cube.ShowAll();

    return 0;
}