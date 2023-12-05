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

    std::cout << "---------------------[split(true)]-------------------------" << std::endl;

    //split testing (success)
    for(int i=0;i<3;i++){
        std::cout << std::string(cm.split(true)[i]) << std:: endl;
    }
    std::cout << "---------------------[split()]-------------------------" << std::endl;

    //split testing (success)
    for(int i=0;i<3;i++){
        std::cout << std::string(cm.split()[i]) << std:: endl;
    }

    std::cout << "---------------------[find(cv1,true)]--------------------------" << std::endl;

    //find testing (success)
    int asd1[] = {2,2,2};
    CustomVector cv1(asd1,3);
    std::cout << cm.find(cv1,true)+1 << ".column" << std::endl;

    std::cout << "---------------------[find(cv2)]--------------------------" << std::endl;

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
/*
    std::cout << "---------------------[scalar operators (2)]----------------" << std::endl;

    //sAdd (success)
    cm.sAdd(2);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sSubtract (success)
    cm.sSubtract(2);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sMultiple (success)
    cm.sMultiple(2);
    cm.coutPrint();

    std::cout << "-------------------------------------------------------" << std::endl;

    //sDivide (success)
    cm.sDivide(2);
    cm.coutPrint();
*/
    std::cout << "---------[BELOW THIS NEEDS EXTENSIVE TESTING]----------" << std::endl;
    std::cout << "---------------------[addEmptyRow()]-------------------" << std::endl;

    //addEmptyRow (success)
    cm.addEmptyRow();
    cm.coutPrint();

    std::cout << "---------------------[addRow(cv2)]---------------------" << std::endl;

    //addRow (success)
    cm.addRow(cv2);
    cm.coutPrint();

    std::cout << "---------------------[removeLastRow()]-----------------" << std::endl;

    //removeLastRow (success)
    cm.removeLastRow();
    cm.coutPrint();

    std::cout << "---------------------[removeRow(3)]---------------------" << std::endl;

    //removeRow (success)
    cm.removeRow(cm.row(3));
    cm.coutPrint();

    std::cout << "---------------------[addEmptyColumn()]----------------" << std::endl;

    //addEmptyColumn (success)
    cm.addEmptyColumn();
    cm.coutPrint();

    std::cout << "---------------------[addColumn(cv1)]---------------------" << std::endl;

    //addColumn (success)
    cm.addColumn(cv1);
    cm.coutPrint();

    std::cout << "---------------------[removeColumn(3)]------------------" << std::endl;

    //removeColumn (success)
    cm.removeColumn(cm.column(3));
    cm.coutPrint();

    std::cout << "---------------------[removeLastColumn()]--------------" << std::endl;

    //removeLastColumn (success)
    cm.removeLastColumn();
    cm.coutPrint();

    std::cout << "---------------------[operator*]-----------------------" << std::endl;

    //operator* (success)
    CustomMatrix cm1(3,2);
    CustomMatrix cm2(2,2);
    int elements1[2] = {1,2};
    CustomVector cva(elements1,2);
    int elements2[2] = {3,4};
    CustomVector cvb(elements2,2);
    int elements3[2] = {5,6};
    CustomVector cvc(elements3,2);
    int elements4[2] = {7,8};
    CustomVector cvd(elements4,2);
    cm1.setRow(0,cva);
    cm1.setRow(1,cvb);
    cm1.setRow(2,cva);
    cm2.setRow(0,cvc);
    cm2.setRow(1,cvd);
    cm1.coutPrint();
    std::cout << std::endl;
    cm2.coutPrint();
    std::cout << std::endl;
    CustomMatrix newCM=cm1*cm2;
    std::cout << std::string(newCM) << std::endl;
    newCM.coutPrint();


    std::cout << "-----------------[selfDeterminant()]-------------------" << std::endl;

    //determinant and selfDeterminant (success)
    int elements5[] = {1,2,3};
    CustomVector cve(elements5,3);
    int elements6[] = {4,5,6};
    CustomVector cvf(elements6,3);
    int elements7[] = {7,8,9};
    CustomVector cvg(elements7,3);
    CustomMatrix cm3(3,3);
    cm3.setRow(0,cve);
    cm3.setRow(1,cvf);
    cm3.setRow(2,cvg);
    int tmpcm3 = cm3.selfDeterminant();
    if(tmpcm3!=0){
        std::cout << tmpcm3 << std::endl;
    }

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
