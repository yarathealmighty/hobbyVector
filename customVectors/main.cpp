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
        for (int j = 0; j <3; ++j) {
            elements[i][j] = 3-j;
        }
    }

    std::cout << "---------------------[constructor]---------------------" << std::endl;

    //constructor testing (success)
    CustomMatrix cm(elements, 3, 3);
    std::cout << std::string(cm) << std::endl;
    cm.coutPrint();

    std::cout << "---------------------[split()]-------------------------" << std::endl;

    //split testing (success)
    for(int i=0;i<3;i++){
        std::cout << std::string(cm.split(true)[i]) << std:: endl;
    }
    std::cout << "---------------------[split()]-------------------------" << std::endl;

    //split testing (success)
    for(int i=0;i<3;i++){
        std::cout << std::string(cm.split()[i]) << std:: endl;
    }

    std::cout << "---------------------[find()]--------------------------" << std::endl;

    //find testing (success)
    int asd1[] = {2,2,2};
    CustomVector cv1(asd1,3);
    std::cout << cm.find(cv1,true)+1 << ".column" << std::endl;

    std::cout << "---------------------[find()]--------------------------" << std::endl;

    //find testing (success)
    int asd2[] = {3,2,1};
    CustomVector cv2(asd2,3);
    std::cout << cm.find(cv2)+1 << ".row" << std::endl;

    std::cout << "---------------------[sort() and sorted()]-------------" << std::endl;

    //sort and sorted testing (success)
    std::cout << "before: " << std::endl;
    cm.coutPrint();
    std::cout << std::endl << "after: " << std::endl;
    cm.sort();
    cm.coutPrint();

    std::cout << "---------------------[scalar operators]----------------" << std::endl;

    //sAdd (success)
    cm.sAdd(1);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sSubtract (success)
    cm.sSubtract(1);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sMultiple (success)
    cm.sMultiple(2);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sDivide (success)
    cm.sDivide(2);
    cm.coutPrint();

    std::cout << "---------------------[addEmptyRow()]-------------------" << std::endl;

    //addEmptyRow (success, but gets memory leak)
    cm.addEmptyRow();
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

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
