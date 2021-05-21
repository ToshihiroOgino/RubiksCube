#include <bits/stdc++.h>
using namespace std;
#define rep(i, j) for (int i = 0; i < j; i++)
#define all(v) v.begin(), v.end()
#define el '\n'

#include "CubeFunctions.h"

#define Empty 0
#define White 1
#define Green 2
#define Orange 3
#define Red 4
#define Blue 5
#define Yellow 6

class Cube
{
public:
    const int CubeSize = 3;
    array<array<array<int[3], 3>, 3>, 3> Blocks;
    int MoveTime;
    Cube()
    {
        Init();
    }
    void ExeProcess(vector<int> process)
    {
        //回転番号をすべて確認する
        rep(i, process.size())
        {
            if (process[i] <= 0 || process[i] >= 13)
                throw("%d(Color) face does not exist.\n", process[i]);
        }
        //実行
        rep(i, process.size())
        {
            int move = process[i];
            if (move <= 6) //時計回り
                _Rotate(Blocks, move);
            else //半時計回り
            {
                move -= 6;
                rep(j, 3) _Rotate(Blocks, move);
            }

            //回転回数加算
            MoveTime++;
        }
    }
    //キューブを初期状態に戻す
    void Init()
    {
        MoveTime = 0;
        //キューブの色をすべてデフォルトに戻す
        Blocks = DefaultBlocks();
    }
    //coutですべての状態を表示する
    void ShowAll()
    {
        rep(i, 6) Show(i + 1, Blocks);
    }
    void ShowDetail()
    {
        BlocksDebug(Blocks);
    }
};