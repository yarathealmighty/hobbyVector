//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#include "FractionException.h"
#include "CustomVectorException.h"

using namespace std;

void CMtesting() {
    //todo write testing ui
}

void CVtesting() {
    //construct/find/sort/sum/sAdd/sSubtract/sMultiple/sDivide/rowMultiple/rowDivide/</==/+=/-=/<</>>/++/--/[]/swap
    //todo write testing ui
    string s;
    bool op;
    cout << "construct/find/sort/sum/sAdd/sSubtract/sMultiple/sDivide/rowMultiple/rowDivide/</==/+=/-=/<</>>/++/--/[]/swap are valid inputs for a command" << endl;
    cin >> s;
    int n,a,b;
    CustomVector v1,v2,v3;
    try{
        if(s=="construct"){
            cout << "default/param/ref" << endl;
            cin >> s;
            if(s=="default"){
                v1 = CustomVector();
            }
            if(s=="param"){
                cout << "length: ";
                cin >> n;
                Fraction* elements = new Fraction[n];
                for(int i=0;i<n;i++){
                    cout << "a/b: ";
                    cin >> a >> b;
                    Fraction tmp(a,b);
                    elements[i] = tmp;
                }
                v1 = CustomVector(elements,n);
                delete[] elements;
            }
            if(s=="ref"){
                cout << "length: ";
                cin >> n;
                Fraction* elements = new Fraction[n];
                for(int i=0;i<n;i++){
                    cout << "a b: ";
                    cin >> a >> b;
                    Fraction tmp(a,b);
                    elements[i] = tmp;
                }
                v1 = CustomVector(elements,n);
                v2 = CustomVector(v1);
                delete[] elements;
            }
        }
        if(s=="find"){
            cout << "length: ";
            cin >> n;
            Fraction* elements = new Fraction[n];
            for(int i=0;i<n;i++){
                cout << "a b: ";
                cin >> a >> b;
                Fraction tmp(a,b);
                elements[i] = tmp;
            }
            v1 = CustomVector(elements,n);
            cout << "The element you'd like to be found: ";
            cin >> a >> b;
            Fraction tmp(a,b);
            cout << "The index of the element is: " << v1.find(tmp)+1 << endl;
            delete[] elements;
        }
        if(s=="sort"){

        }
        if(s=="sum"){

        }
        if(s=="sAdd"){

        }
        if(s=="sSubtract"){

        }
        if(s=="sMultiple"){

        }
        if(s=="sDivide"){

        }
        if(s=="rowMultiple"){

        }
        if(s=="rowDivide"){

        }
        if(s=="<"){

        }
        if(s=="=="){

        }
        if(s=="+="){

        }
        if(s=="-="){

        }
        if(s=="<<"){

        }
        if(s==">>"){

        }
        if(s=="++"){

        }
        if(s=="--"){

        }
        if(s=="[]"){

        }
        if(s=="swap"){

        }
        cout << "length of v1: " << int(v1) << endl;
        cout << "elements of v1: " << std::string(v1) << endl;
        cout << "length of v2: " << int(v2) << endl;
        cout << "elements of v2: " << std::string(v2) << endl;
        cout << "length of v3: " << int(v3) << endl;
        cout << "elements of v3: " << std::string(v3) << endl;
    } catch (CustomVectorException& cve){
        cout << cve.what() << endl;
    }
}

void Ftesting(){
    //construct/simple/+=/+/-=/-/*=/*/ /= / / /</<=/>/>=/==/!=/=
    string s;
    bool op;
    cout << "construct/simple/+=/+/-=/-/*=/*/ /= / / /</<=/>/>=/==/!=/= are valid inputs for a command" << endl;
    cin >> s;
    int a,b,c,d;
    Fraction f,g,h;
    try{
    if(s=="construct"){
        cout << "default/2/ref are valid inputs for a command" << endl;
        cin >> s;
        if(s=="default"){
            f = Fraction();
        }
        if(s=="2"){
            cout << "x y is a valid input where x,y are both integers" << endl;
            cin >> a >> b;
            f = Fraction(a,b);
        }
        if(s=="ref"){
            cout << "x y is a valid input where x,y are both integers" << endl;
            cin >> a >> b;
            Fraction tmp(a,b);
            f = tmp;
        }
    }
    if(s=="simple"){
        cout << "x y is a valid input where x,y are both integers" << endl;
        cin >> a >> b;
        f = Fraction(a,b);
        f.simplify();
    }
    if(s=="+="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f+=g;
        h = f;
    }
    if(s=="+"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h = f+g;
    }
    if(s=="-="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f-=g;
        h = f;
    }
    if(s=="-"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f-g;
    }
    if(s=="*="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f*=g;
        h = f;
    }
    if(s=="*"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f*g;
    }
    if(s=="/="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f/=g;
        h = f;
    }
    if(s=="/"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f/g;
    }
    if(s=="<="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f<=g;
    }
    if(s=="<"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f<g;
    }
    if(s==">="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f>=g;
    }
    if(s==">"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f>g;
    }
    if(s=="=="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f==g;
    }
    if(s=="!="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f!=g;
    }
        cout << "numerator/denominator: " << std::string(h) << endl;
        cout << "float form: " << h.floatValue() << endl;
        cout << "int form: " << int(h) << endl;
    } catch (FractionException& fe){
        cout << fe.what() << endl;
    }
}

int main() {
//#define TESTING
#ifdef TESTING
    string s;
    cout << "cm for CustomMatrix, cv for CustomVector and f for Fraction testing" << endl;
    cin >> s;
    if(s=="cm") {
        CMtesting();
    }
    if(s=="cv") {
        CVtesting();
    }
    if(s=="f") {
        Ftesting();
    }
#endif

    //testing reduceable()
    CustomMatrix cm(eye(5));
    Fraction tmp(1, 6);
    Fraction one(1);
    Fraction zero(0);

    cm.sMultiple(tmp);
    cm.coutPrint();
    cout << "lower-triangle matrix? " << cm.lowerTriangle() << endl;

    cm[0][1] = tmp;
    cm.coutPrint();
    cout << "lower-triangle matrix? " << cm.lowerTriangle() << endl;

    cm[0][1] = zero;
    for(int i=0;i<cm.getRows();i++){
        cm[i][i] = zero;
        if(i!=0){
            cm[i][i-1] = one;
        }
    }
    cm.coutPrint();
    cout << "strictly lower-triangle matrix? " << cm.strictLowerTriangle() << endl;


    return 0;
}
