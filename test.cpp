#include <bits/stdc++.h>

class Base
{
    char* str;
    public:
        Base()
        {
            str = new char[10];
        }
        Base(int a)
        {
            str = new char[a];
        }
        ~Base()
        {
            delete[] str;
        }

};

class Derived
{
    Base b;
    public:
        Derived(int a)
        {
            b = Base(a);
        }
};

int main()
{   
    Derived d(5);

    return 0;
}