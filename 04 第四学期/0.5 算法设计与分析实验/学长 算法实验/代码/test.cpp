#include <iostream>
using namespace std;

int fun(int, int) {
    cout << "fun(int, int)" << endl;
    return 0;
}

int main() {
    int i, j, k = 0;
    for (j = 11;j <= 30;j++) {
        if(k % 10 == 0) {
            cout << endl;
        }
        for(int i = 2;i < j;i++) {
            if(!(j % i)) {
                break;
            }
            if(i == j - 1) {
                cout << j << "\t";
                k++;
            }
        }
    }
}