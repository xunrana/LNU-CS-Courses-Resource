#include <stdio.h>
#include <string.h>

// 去除字符串两端的空格、制表符和换行符
char* strtrim(char* str) {
    char* end;

    // 去除开头的空格、制表符和换行符
    while (*str == ' ' || *str == '\t' || *str == '\n') {
        str++;
    }

    // 如果字符串为空，则直接返回
    if (*str == '\0') {
        return str;
    }

    // 去除结尾的空格、制表符和换行符
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        end--;
    }
    *(end + 1) = '\0';

    return str;
}

// 判断评判系统返回的值
char* judge_system(const char* correct_output, const char* user_output) {
    if (strcmp(correct_output, user_output) == 0) {
        return "Accepted";
    } else if (strcmp(strtrim((char*)correct_output), strtrim((char*)user_output)) == 0) {
        return "Presentation Error";
    } else {
        return "Wrong Answer";
    }
}

int main() {
    int T;
    scanf("%d", &T);  // 测试数据组数
    getchar();  // 读取换行符

    char correct_output[5001];  // 正确的输出文件
    char user_output[5001];  // 用户结果文件

    for (int i = 0; i < T; i++) {
        // 读取正确的输出文件
        fgets(correct_output, sizeof(correct_output), stdin);
        correct_output[strcspn(correct_output, "\n")] = '\0';  // 去除换行符

        // 读取用户结果文件
        fgets(user_output, sizeof(user_output), stdin);
        user_output[strcspn(user_output, "\n")] = '\0';  // 去除换行符

        // 判断评判系统返回的值
        char* result = judge_system(correct_output, user_output);
        printf("%s\n", result);
    }

    return 0;
}


