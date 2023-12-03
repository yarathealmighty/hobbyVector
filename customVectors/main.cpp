//
// Created by yarr on 2023. 12. 02..
//

#include <bits/stdc++.h>
#include "CustomMatrix.h"
#define TESTING

using namespace std;

int main() {
#ifdef TESTING
    int** elements = new int*[3];
    for (int i = 0; i < 3; ++i) {
        elements[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            elements[i][j] = j+1;
        }
    }

    CustomMatrix cm(elements, 3, 3);
    std::cout << std::string(cm) << std::endl;
    cm.coutPrint();

    for (int i = 0; i < 3; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
#endif
    return 0;
}
