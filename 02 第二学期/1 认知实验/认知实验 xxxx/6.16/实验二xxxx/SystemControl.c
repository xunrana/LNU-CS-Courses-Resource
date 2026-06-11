#include "SystemControl.h" // 包含自定义头文件

#include <windows.h> // 包含 Windows API 的头文件
#include <stdlib.h> // 包含标准库函数的头文件
#include <conio.h> // 包含控制台输入输出函数的头文件
#include <stdio.h> // 包含标准输入输出函数的头文件

#include "SystemControl.h" // 再次包含自定义头文件，可能是为了确保头文件中的定义被包括

// 将光标移动到指定位置 (x, y)
void Gotoxy(int x, int y) 
{
    HANDLE hOut; // 定义句柄变量
    hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出的句柄
    COORD pos = {x, y}; // 定义坐标结构体并赋值
    SetConsoleCursorPosition(hOut, pos); // 设置控制台光标位置
}

// 清除屏幕内容
void Clear()
{
    system("cls"); // 使用系统命令清除屏幕
    return; // 返回
}

// 设置控制台颜色
void Color(int color)
{
    switch (color) // 根据传入的颜色值选择不同的设置
    {
        case 0: system("color E4"); break; // 设置为颜色方案 E4
        case 1: system("color 90"); break; // 设置为颜色方案 90
        case 2: system("color C1"); break; // 设置为颜色方案 C1
        case 3: system("color 30"); break; // 设置为颜色方案 30
        case 4: system("color E4"); break; // 设置为颜色方案 E4
        default: break; // 如果传入的颜色值不在上述范围内，不做任何操作
    }
    return; // 返回
}

