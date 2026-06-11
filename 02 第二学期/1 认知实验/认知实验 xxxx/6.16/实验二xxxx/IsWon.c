#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//检查一个方向上是否有五连子
int check_line(char board[15][15], int x, int y, char piece, int dx, int dy) {
    int count = 0; //记录连续同色棋子的个数
    //向两个反方向遍历
    for (int i = -4; i <= 4; i++) {
        //计算当前点的坐标
        int nx = x + i * dx;
        int ny = y + i * dy;
        //判断是否越界a
        if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) {
            continue;
        }
        //判断是否与当前落子颜色相同
        if (board[nx][ny] == piece) {
            count++;
        } else {
            count = 0;
        }
        //判断是否达到五连子
        if (count == 5) {
            return 1;
        }
    }
    return 0;
}

//检查当前落子是否胜利
int check_win(char board[15][15], int x, int y, char piece) {
    //检查水平方向
    if (check_line(board, x, y, piece, 1, 0)) {
        return 1;
    }
    //检查垂直方向
    if (check_line(board, x, y, piece, 0, 1)) {
        return 1;
    }
    //检查左斜方向
    if (check_line(board, x, y, piece, -1, 1)) {
        return 1;
    }
    //检查右斜方向
    if (check_line(board, x, y, piece, 1, 1)) {
        return 1;
    }
    return 0;
}


