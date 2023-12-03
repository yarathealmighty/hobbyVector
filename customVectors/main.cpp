//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#define TESTING

using namespace std;

void CMtesting() {
    int** elements = new int*[3];
    for (int i = 0; i < 3; ++i) {
        elements[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            elements[i][j] = j+1;
        }
    }

    //constructor testing (success)
    CustomMatrix cm(elements, 3, 3);
    std::cout << std::string(cm) << std::endl;
    cm.coutPrint();

    //split testing (success)
    for(int i=0;i<3;i++){
        std::cout << std::string(cm.split(true)[i]) << std:: endl;
    }

    //free up allocated elements
    for (int i = 0; i < 3; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

int main() {
#ifdef TESTING
    CMtesting();
#endif
    return 0;
}
