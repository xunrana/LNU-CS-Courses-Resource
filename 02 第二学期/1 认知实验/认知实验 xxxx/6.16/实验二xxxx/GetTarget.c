#include <stdio.h> // 包含标准输入输出函数的头文件
#include <windows.h> // 包含 Windows API 的头文件
#include <conio.h> // 包含控制台输入输出函数的头文件
#include <string.h> // 包含字符串处理函数的头文件
#include <stdlib.h> // 包含标准库函数的头文件

#include "GetTarget.h" // 包含自定义头文件
#include "SystemControl.h" // 包含自定义头文件，用于控制台控制

// 获取玩家的目标位置
int* Get_Target(int Player, char Source[15][15])
{
    // 创建临时棋盘副本
    char gomoku[15][15];
    for(int tmp=0; tmp<15; tmp++)
    {
        for(int tmp2=0; tmp2<15; tmp2++)
        {
            gomoku[tmp][tmp2] = Source[tmp][tmp2]; // 复制棋盘数据
        }
    }
    static int ans[2] = {0, 0}; // 用于存储结果的静态数组
    char KeyBoardInput = 0; // 用于存储键盘输入
    int x = 0; int y = 0; // 初始化光标位置为 (0, 0)

    while(1) // 无限循环，直到玩家确认输入
    {
        KeyBoardInput = getch(); // 获取键盘输入
        if(KeyBoardInput == 13) // 如果按下 Enter 键
        {
            if(gomoku[x][y] != '.') // 检查当前位置是否为空
            {
                continue; // 如果当前位置非空，继续等待输入
            }
            ans[0] = x; // 保存 x 坐标
            ans[1] = y; // 保存 y 坐标
            return ans; // 返回结果
        }
        else if(Player == 1) // 如果是玩家1
        {
            switch(KeyBoardInput) // 根据键盘输入更新光标位置
            {
                case 72: x--; break; // 上箭头
                case 80: x++; break; // 下箭头
                case 75: y--; break; // 左箭头
                case 77: y++; break; // 右箭头
                default: break; // 其他按键不处理
            }
            // 确保光标位置在棋盘范围内循环
            if(x < 0)  x = 15 + x;
            if(x > 14) x = x - 15;
            if(y < 0)  y = y + 15;
            if(y > 14) y = y - 15;
            
            Clear(); // 清除屏幕
            
            // 打印当前棋盘和光标位置
            for(int i = 0; i < 5; i++) printf("\n");
            for(int tmp = 0; tmp < 15; tmp++)
            {
                for(int i = 0; i < [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬; i++) printf("  ");
                for(int tmp2 = 0; tmp2 < 15; tmp2++)
                {
                    if(tmp == x && tmp2 == y)
                    {
                        printf("O "); // 在光标位置打印 'O'
                        continue;
                    }
                    printf("%c ", gomoku[tmp][tmp2]); // 打印棋盘
                }
                printf("\n");
            }
            printf("\n\n\n");
            for(int i = 0; i < [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬; i++) printf("  ");
            printf("------------Now Player 1:x=%d y=%d", x, y); // 显示玩家1的当前光标位置
        }
        else if(Player == 2) // 如果是玩家2
        {
            switch(KeyBoardInput) // 根据键盘输入更新光标位置
            {
                case 's': x++; break; // 下移
                case 'w': x--; break; // 上移
                case 'a': y--; break; // 左移
                case 'd': y++; break; // 右移
                case 'S': x++; break; // 下移 (大写)
                case 'W': x--; break; // 上移 (大写)
                case 'A': y--; break; // 左移 (大写)
                case 'D': y++; break; // 右移 (大写)
                default: break; // 其他按键不处理
            }
            // 确保光标位置在棋盘范围内循环
            if(x < 0)  x = 15 + x;
            if(x > 14) x = x - 15;
            if(y < 0)  y = y + 15;
            if(y > 14) y = y - 15;
            
            Clear(); // 清除屏幕
            
            // 打印当前棋盘和光标位置
            for(int i = 0; i < 5; i++) printf("\n");
            for(int tmp = 0; tmp < 15; tmp++)
            {
                for(int i = 0; i < [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬; i++) printf("  ");
                for(int tmp2 = 0; tmp2 < 15; tmp2++)
                {
                    if(tmp == x && tmp2 == y)
                    {
                        printf("X "); // 在光标位置打印 'X'
                        continue;
                    }
                    printf("%c ", gomoku[tmp][tmp2]); // 打印棋盘
                }
                printf("\n");
            }
            printf("\n\n\n");
            for(int i = 0; i < [[濮撳悕宸茶劚鏁廬宸茶劚鏁廬; i++) printf("  ");
            printf("------------Now Player 2:x=%d y=%d", x, y); // 显示玩家2的当前光标位置
        }
    }
}

