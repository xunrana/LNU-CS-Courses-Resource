#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 包含自定义头文件
#include "SystemControl.h"
#include "GetTarget.h"
#include "IsWon.h"

// 定义棋盘大小为15x15的二维数组
char Gomoku[15][15];

signed main(int argc, char *argv[]) 
{
    // 设置颜色，0表示默认颜色
    Color(0);
    // 打印游戏标题和提示信息
    printf("\n\n\n\n\n\n\n\n\n\n\n      				五子棋   P1使用↑↓←→，P2使用WSAD，Enter下棋\n"); 
    printf("     				-----------Press Any Key to Start-----------");
    // 等待用户按任意键开始
    getch();
    // 清除屏幕
    Clear();
    // 游戏是否结束的标志，0表示未结束
    int IsOver=0;
    // 初始化棋盘，所有位置置为'.'表示空位
    memset(Gomoku,0,sizeof(Gomoku));
    for(int tmp=0;tmp<15;tmp++)
    {
        for(int tmp2=0;tmp2<15;tmp2++)
        {
            Gomoku[tmp][tmp2]='.';
        } 
    }
    // 游戏主循环
    while(IsOver==0)
    {
        // 玩家1的回合
        Gotoxy(0,0); // 将光标移动到左上角
        Clear(); // 清除屏幕
        for(int i=0;i<5;i++)	printf("\n"); // 打印5行空行
        for(int tmp=0;tmp<15;tmp++)
        {	
            for(int i=0;i<[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬;i++)	printf("  "); // 打印[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬个空格，用于对齐
            for(int tmp2=0;tmp2<15;tmp2++)
            {
                printf("%c ",Gomoku[tmp][tmp2]); // 打印棋盘
            } 
            printf("\n");
        }
        // 获取玩家1的输入
        int* GOT=Get_Target(1,Gomoku);
        int Got_X=GOT[0]; int Got_Y=GOT[1];
        Gomoku[Got_X][Got_Y]='O'; // 将玩家1的棋子'O'放在指定位置
        // 检查玩家1是否胜利
        if(check_win(Gomoku,Got_X,Got_Y,'O')==1)
        {
            Gotoxy(0,[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬); // 将光标移动到第[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬行
            printf("Player 1 Won!\n"); // 打印胜利信息
            break; // 跳出循环，游戏结束
        }
        // 玩家2的回合
        Gotoxy(0,0); // 将光标移动到左上角
        Clear(); // 清除屏幕
        for(int i=0;i<5;i++)	printf("\n"); // 打印5行空行
        for(int tmp=0;tmp<15;tmp++)
        {
            for(int i=0;i<[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬;i++)	printf("  "); // 打印[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬个空格，用于对齐
            for(int tmp2=0;tmp2<15;tmp2++)
            {
                printf("%c ",Gomoku[tmp][tmp2]); // 打印棋盘
            } 
            printf("\n");
        }
        // 获取玩家2的输入
        GOT=Get_Target(2,Gomoku);
        Got_X=GOT[0]; Got_Y=GOT[1];
        Gomoku[Got_X][Got_Y]='X'; // 将玩家2的棋子'X'放在指定位置
        // 检查玩家2是否胜利
        if(check_win(Gomoku,Got_X,Got_Y,'X')==1)
        {
            Gotoxy(0,[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬); // 将光标移动到第[[濮撳悕宸茶劚鏁廬宸茶劚鏁廬行
            printf("Player 2 Won!\n"); // 打印胜利信息
            break; // 跳出循环，游戏结束
        }
    }
    // 暂停系统，等待用户按键后退出
    system("pause");
    return 0;
}

