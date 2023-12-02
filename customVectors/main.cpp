//
// Created by yarr on 2023. 12. 02..
//

#include <bits/stdc++.h>
#include "CustomVector.h"
#define TESTING

using namespace std;

int main(){
#ifdef TESTING
    int elements[] = {2,4,6,8};
    CustomVector cv(elements,4);
    cout << string(cv) << endl;
    cout << int(cv) << endl;
    CustomVector cv2(elements,4);
    cv2.sDivide(2);
    cout << string(cv2) << endl;
    cout << int(cv2) << endl;

    cout << string(cv+=cv2) << endl;
    cout << string(cv2<<5) << endl;
    cout << string(cv2>>2) << endl;
#endif
    return 0;
}
