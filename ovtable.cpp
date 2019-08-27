/*
*
* This lets us override the virtual table pointer of the object and call arbitrary functions.
* We override/replace it with our own table pointer..
*
*/

#include <iostream>
#include <cstring>


class Pclass{
    public:
        virtual void VFunc1(){
            std::cout << " VFunc1" << std::endl;
        }

        virtual void VFunc2(){
            std::cout << "VFunc2" << std::endl;
        }

        virtual void VFunc3(){
            std::cout << "VFunc3" << std::endl;
        }

};

class Cclass : public Pclass{
    public:
        void VFunc1(){
            std::cout << "VFunc1" << std::endl;
        }
        void VFunc2(){
            std::cout << "VFunc2" << std::endl;
        }
        void VFunc3(){
            std::cout << "VFunc3" << std::endl;
        }

};

typedef void(*vfunction)();

struct FakeVTable{
    vfunction virtual1;
    vfunction virtual2;
    vfunction virtual3;
};

void fakev1(){
    std::cout << "fake vcall number: 1" << std::endl; 
};

void fakev2(){
    std::cout << "fake vcall number: 2" << std::endl; 
};

void fakev3(){
    std::cout << "fake vcall number: 3" << std::endl; 
};



int main(void){

    std::cout << "replacing the first bytes of 'sizeof(void*)' object with our own table pointer." << std::endl;
    Cclass c_ClassObject;
    Pclass* p_ClassPtr = &c_ClassObject;

    FakeVTable customVtable;
    customVtable.virtual1 = fakev1;
    customVtable.virtual2 = fakev2;
    customVtable.virtual3 = fakev3;

    FakeVTable* tablePtr = &customVtable;
    std::memcpy(p_ClassPtr, &tablePtr, sizeof(void*));

    p_ClassPtr->VFunc1();
    p_ClassPtr->VFunc2();
    p_ClassPtr->VFunc3();
    return 0;
}
