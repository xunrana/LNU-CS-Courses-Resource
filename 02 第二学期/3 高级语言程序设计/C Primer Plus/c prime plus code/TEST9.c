#include <stdio.h>

void display_menu() {
    printf("主菜单\n");
    printf("------\n");
    printf("1、录入学生信息\n");
    printf("2、查询学生信息\n");
    printf("3、修改学生信息\n");
    printf("4、显示学生信息\n");
    printf("0、退出\n");
    printf("请输入选择:0~4\n");
}

int main() {
    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("是否确认退出？(1:确认/0:取消)\n");
                int confirm;
                scanf("%d", &confirm);
                if (confirm) {
                    printf("谢谢使用！\n");
                    return 0;
                }
                break;
            case 1:
                printf("输入学生信息\n");
                // TODO: 录入学生信息的代码
                break;
            case 2:
                printf("查询学生信息\n");
                // TODO: 查询学生信息的代码
                break;
            case 3:
                printf("修改学生信息\n");
                // TODO: 修改学生信息的代码
                break;
            case 4:
                printf("显示学生信息\n");
                // TODO: 显示学生信息的代码
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
    }
    return 0;
}

