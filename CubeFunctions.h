#include <bits/stdc++.h>
using namespace std;
#define rep(i, j) for (int i = 0; i < j; i++)
#define all(v) v.begin(), v.end()
#define el '\n'

typedef array<array<array<int[3], 3>, 3>, 3> blocks;
#define Empty 0
#define White 1
#define Green 2
#define Orange 3
#define Red 4
#define Blue 5
#define Yellow 6

void BlocksDebug(blocks Blocks)
{
    char Colors[7] = {'E', 'W', 'G', 'O', 'R', 'B', 'Y'};
    rep(i, 3)
    {
        rep(j, 3)
        {
            rep(k, 3)
            {
                cout << "  (";
                rep(col, 2)
                {
                    cout << Colors[Blocks[i][j][k][col]];
                    cout << ", ";
                }
                cout << Colors[Blocks[i][j][k][2]] << ")";
            }
            cout << el;
        }
        cout << el;
    }
    cout << "---------------" << el;
    return;
}

//指定色のセンターキューブの座標を返す
vector<int> CenterPosition(int Color)
{
    //存在しない面を指定されたときはエラーを発生させる
    if (0 >= Color || Color > 6)
        throw("%d(Color) face does not exist.\n", Color);

    vector<int> center = {1, 1, 1};
    switch (Color)
    {
    case 1: //White:
        center[0]--;
        break;
    case 2: //Green:
        center[1]--;
        break;
    case 3: //Orange:
        center[2]--;
        break;
    case 4: //Red:
        center[2]++;
        break;
    case 5: //Blue:
        center[1]++;
        break;
    case 6: //Yellow:
        center[0]++;
        break;
    }
    return center;
}

//face面をtimes回、回転させる
void _Rotate(blocks &defbl, int face)
{
    blocks bl;
    rep(i, 3) rep(j, 3) rep(k, 3) rep(col, 3) bl[i][j][k][col] = defbl[i][j][k][col];

    int LockIndex;
    //センターキューブの位置を決定
    int center[3];
    vector<int> CP = CenterPosition(face);
    rep(i, 3)
    {
        center[i] = CP[i];
        //側面を記録する
        if (center[i] % 2 == 0)
            LockIndex = i;
    }
    //移動させるブロックの座標リストを作成 ListOfMoveBlocks
    //vector<vector<int[3]>> lomb;
    array<array<int[3], 3>, 3> lomb;
    rep(i, 3) rep(j, 3)
    {
        int height, width, depth, cola, colb;
        switch (face)
        {
        case 1: //White
            height = 0;
            width = j;
            depth = 2 - i;
            cola = 1;
            colb = 2;
            break;
        case 2: //Green
            height = i;
            width = 0;
            depth = j;
            cola = 0;
            colb = 2;
            break;
        case 3: //Orange
            height = i;
            width = 2 - j;
            depth = 0;
            cola = 0;
            colb = 1;
            break;
        case 4: //Red
            height = i;
            width = j;
            depth = 2;
            cola = 0;
            colb = 1;
            break;
        case 5: //Blue
            height = i;
            width = 2;
            depth = 2 - j;
            cola = 0;
            colb = 2;
            break;
        case 6: //Yellow
            height = 2;
            width = i;
            depth = j;
            cola = 1;
            colb = 2;
            break;
        }
        lomb[i][j][0] = height;
        lomb[i][j][1] = width;
        lomb[i][j][2] = depth;

        //基準面以外の色を入れ替える
        swap(bl[height][width][depth][cola], bl[height][width][depth][colb]);
    }

    int p1[3], p2[3], p3[3], p4[3];
    //時計回りに回転
    //角を時計回りに回す
    rep(i, 3) //角の座標
    {
        p1[i] = lomb[0][0][i]; //左上 bl[p1[0]][p1[1]][p1[2]][i]
        p2[i] = lomb[2][0][i]; //左下 bl[p2[0]][p2[1]][p2[2]][i]
        p3[i] = lomb[2][2][i]; //右下 bl[p3[0]][p3[1]][p3[2]][i]
        p4[i] = lomb[0][2][i]; //右上 bl[p4[0]][p4[1]][p4[2]][i]
    }
    rep(i, 3)
    {
        if (face == 1) //白面の回転
        {
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p4[0]][p4[1]][p4[2]][i]);
            swap(bl[p2[0]][p2[1]][p2[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
            swap(bl[p2[0]][p2[1]][p2[2]][i], bl[p4[0]][p4[1]][p4[2]][i]);
        }
        if (face >= 2) //白以外の面の回転
        {
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p2[0]][p2[1]][p2[2]][i]);
            swap(bl[p4[0]][p4[1]][p4[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
            swap(bl[p2[0]][p2[1]][p2[2]][i], bl[p4[0]][p4[1]][p4[2]][i]);
        }
    }

    //辺を時計回りに回す
    rep(i, 3) //辺の座標
    {
        p1[i] = lomb[1][0][i]; //左 bl[p1[0]][p1[1]][p1[2]][i]
        p2[i] = lomb[0][1][i]; //上 bl[p2[0]][p2[1]][p2[2]][i]
        p3[i] = lomb[1][2][i]; //右 bl[p3[0]][p3[1]][p3[2]][i]
        p4[i] = lomb[2][1][i]; //下 bl[p4[0]][p4[1]][p4[2]][i]
    }
    rep(i, 3)
    {
        if (face == 1) //白面の回転
        {
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p4[0]][p4[1]][p4[2]][i]);
            swap(bl[p2[0]][p2[1]][p2[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
        }
        if (face >= 2) //白以外の面の回転
        {
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p2[0]][p2[1]][p2[2]][i]);
            swap(bl[p4[0]][p4[1]][p4[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
            swap(bl[p1[0]][p1[1]][p1[2]][i], bl[p3[0]][p3[1]][p3[2]][i]);
        }
    }

    //結果を反映
    rep(i, 3) rep(j, 3) rep(k, 3) rep(col, 3) defbl[i][j][k][col] = bl[i][j][k][col];
    return;
}

//Blocksの状態を揃っている初期状態に戻す
blocks DefaultBlocks()
{
    blocks result;
    int CubeSize = 3;
    int colors[3] = {0, 0, 0}; //UD,FB,LR
    rep(i, CubeSize)
    {
        //上下の色を決定
        switch (i)
        {
        case 0:
            colors[0] = White;
            break;
        case 1:
            colors[0] = Empty;
            break;
        case 2:
            colors[0] = Yellow;
        default:
            break;
        }
        rep(j, CubeSize)
        {
            //前後の色を決定
            switch (j)
            {
            case 0:
                colors[1] = Green;
                break;
            case 1:
                colors[1] = Empty;
                break;
            case 2:
                colors[1] = Blue;
            default:
                break;
            }
            rep(k, CubeSize)
            {
                //左右の色を決定
                switch (k)
                {
                case 0:
                    colors[2] = Orange;
                    break;
                case 1:
                    colors[2] = Empty;
                    break;
                case 2:
                    colors[2] = Red;
                default:
                    break;
                }

                //i,j,kの位置のブロックに色を代入
                rep(face, 3) result[i][j][k][face] = colors[face];
            }
        }
    }
    return result;
}
//face色の面を表示する
void Show(int face, blocks Blocks)
{
    int LockIndex;
    //センターキューブの位置を決定
    int center[3];
    vector<int> CP = CenterPosition(face);
    rep(i, 3)
    {
        center[i] = CP[i];
        //側面を記録する
        if (center[i] % 2 == 0)
            LockIndex = i;
    }

    int result[3][3];
    int Top = 0;
    rep(i, 3) rep(j, 3)
    {
        int height, width, depth;
        switch (face)
        {
        case 1: //White
            Top = Blue;
            height = 0;
            width = 2 - i;
            depth = j;
            break;
        case 2: //Green
            Top = White;
            height = i;
            width = 0;
            depth = j;
            break;
        case 3: //Orange
            Top = White;
            height = i;
            width = 2 - j;
            depth = 0;
            break;
        case 4: //Red
            Top = White;
            height = i;
            width = j;
            depth = 2;
            break;
        case 5: //Blue
            Top = White;
            height = i;
            width = 2;
            depth = 2 - j;
            break;
        case 6: //Yellow
            Top = Green;
            height = 2;
            width = i;
            depth = j;
            break;
        }
        result[i][j] = Blocks[height][width][depth][LockIndex];
    }

    string Colors[7] = {"\033[105mE", "\033[97mW", "\033[32mG", "\033[35mO", "\033[31mR", "\033[34mB", "\033[33mY"};
    //結果表示
    cout << Colors[face] << "\033[0m  (" << Colors[Top] << "\033[0m side)" << el;
    rep(i, 3)
    {
        cout << "   ";
        rep(j, 3)
        {
            cout << Colors[result[i][j]] << "\033[0m, ";
        }
        cout << el;
    }
    cout << el;
    return;
}