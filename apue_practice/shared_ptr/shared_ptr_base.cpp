#include <iostream>
#include <memory>

class Base{
    public:
        void virtual dothings() = 0;
};

class Sub1 : public Base{
    public:
        void virtual dothings(){
            std::cout << "Sub1" << std::endl; 
        }
};

class Sub2 : public Base{
    public:
        void virtual dothings(){
            std::cout << "Sub2" << std::endl; 
        }
};

int main(){
    std::shared_ptr<Base> ptr1(new Sub1());
    std::shared_ptr<Base> ptr2(new Sub2());
    ptr1->dothings();
    ptr2->dothings();
    return 0;
}

