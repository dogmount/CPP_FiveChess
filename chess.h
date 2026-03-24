#pragma once
#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40

class chess
{
public:
    // 偶数为黑棋 奇数为白棋
    void chessManu()
    {
        // 调用系统窗口
        // initgraph(x, y);     // x横轴 y竖轴
        initgraph(1100, 1000); // 创建自定义窗口

        // 设置窗口背景颜色
        setbkcolor(RGB(164, 225, 202));
        cleardevice();

        // 绘制棋盘
        setlinecolor(BLACK);
        for (int i = 100; i <= 900; i += WIDTH)
        {
            line(100, i, 900, i);
            line(i, 100, i, 900);
        }

        // 输出信息
        // 设置字体颜色
        settextcolor(BLACK);
        outtextxy(920, 100, L"玩家1：黑棋");
        outtextxy(920, 200, L"玩家2：白棋");
        setfont(16, 0, L"宋体");
        outtextxy(920, 300, L"提示：");
        outtextxy(920, 350, L"四边框为边界，不可下棋");

        // 设置输出字体以及字体背景颜色
        setfont(48, 0, L"宋体");
        setfontbkcolor(WHITE);
        outtextxy(450, 50, L"五子棋");
    }

    void playChess()
    {
        // 鼠标信息
        MOUSEMSG mous;
        int x = 0, y = 0; // 坐标
        int a = 0, b = 0; // 行列

        // 持续下棋
        while (1)
        {
            mous = GetMouseMsg();
            // 获取离鼠标最近的点的坐标信息
            for (int i = 1; i < 20; i++)
            {
                for (int j = 1; j < 20; j++)
                {
                    if (abs(mous.x - i * WIDTH - 100) < 12 && abs(mous.y - j * WIDTH - 100) < 12)
                    {
                        x = i * WIDTH + 100;
                        y = j * WIDTH + 100;
                        a = i;
                        b = j;
                    }
                }
            }

            // 判断鼠标信息是否是左键单击
            if (mous.uMsg == WM_LBUTTONDOWN)
            {
                // 棋子重复下在一个位置上
                if (board[a][b] != 0)
                {
                    /*
                     使用宽字符字符串(L"")和MessageBoxW
                    MessageBoxW(NULL, L"中文内容", L"中文标题", MB_OK);

                    -------------------------------------------------------
                    或者
                    TEXT宏根据项目设置自动转换字符串类型
                    MessageBox(NULL, TEXT("中文内容"), TEXT("中文标题"), MB_OK);

                    在调用 MessageBox 时，为参数 uType 添加 ‌MB_SYSTEMMODAL‌ 标志。这会强制对话框成为系统模态窗口（System Modal），通常会自动置顶：
                    MB_OK | MB_SYSTEMMODAL  // 关键标志
                    */

                    // MessageBox函数有宽字符（wchar_t）版本，即MessageBoxW，它接受宽字符串（例如wchar_t*）作为参数。
                    MessageBoxW(NULL, L"这里已经有棋子了，请重新选择。", L"提示", MB_OK | MB_SYSTEMMODAL); // 弹出一个提示框
                    continue;                                                                              // 进入下一循环
                }

                // 判断黑白子
                if (count % 2 == 0)
                { //	偶数次 黑子
                    setfillcolor(BLACK);
                    solidcircle(x, y, 10);
                    board[a][b] = 1;
                }
                else
                { // 奇数次
                    setfillcolor(WHITE);
                    solidcircle(x, y, 10);
                    board[a][b] = 2;
                }
                count++;
            }
            if (judge(a, b))
            {
                if (count % 2 == 0)
                {
                    MessageBoxW(NULL, L"玩家2胜利。", L"游戏结束", MB_OK | MB_SYSTEMMODAL); // 弹出一个提示框
                    exit(0);
                }
                else
                {
                    MessageBoxW(NULL, L"玩家1胜利。", L"游戏结束", MB_OK | MB_SYSTEMMODAL); // 弹出一个提示框
                    exit(0);
                }
            }
        }
    }

    // 3.判断输赢
    int judge(int a, int b)
    {
        int i, j;
        int t = 2 - count % 2; // 1 判断黑子是否赢	2 判断白子是否赢

        // 横向
        for (i = a - 4, j = b; i <= a; i++)
        {
            if (i > 0 && i < 16 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
            {
                return 1;
            }
        }

        // 纵向
        for (i = a, j = b - 4; j <= b; j++)
        {
            if (j > 0 && j < 16 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
            {
                return 1;
            }
        }

        // 右下
        for (i = a - 4, j = b - 4; i <= a, j <= b; i++, j++)
        {
            if (i > 0 && i < 16 && j > 0 && j < 16 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
            {
                return 1;
            }
        }

        // 左下
        for (i = a - 4, j = b + 4; i <= a, j >= b; i++, j--)
        {
            if (i > 0 && i < 16 && j > 0 && j < 16 && t == board[i][j] && t == board[i + 1][j - 1] && t == board[i + 2][j - 2] && t == board[i + 3][j - 3] && t == board[i + 4][j - 4])
            {
                return 1;
            }
        }

        return 0;
    }

private:
    int count = 0;           // 偶数黑子，奇数白子
    int board[20][20] = {0}; //-1表示棋盘没有棋子状态
};