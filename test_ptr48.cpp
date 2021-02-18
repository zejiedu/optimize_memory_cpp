/*******************************************************************
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 ******************************************************************/

#include <iostream>
#include "pointer48bit.hpp"

using namespace std;

struct FF
{
    short a : 4;
    short b : 4;
    short c : 4;
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 1;
    bool b4 : 1;
};

struct Data
{
    int a = 12;
    int b = 23;
    double c = 23.5;
    std::string say()
    {
        return "  I'm data.";
    }
};

struct A
{
    ptr48<Data> ptr;
    FF f{3, 3, 5, 1, 1, 1, 1};
};

struct B
{
    ptr48<Data> ptr;
    ptr48<Data> ptr2;
};

struct C
{
    ptr48<Data> ptr;
    short d;
};

int main()
{
    void *void_p = malloc(20);
    Data data;
    Data *p = &data;

    cout << "A size: " << sizeof(A) << endl;
    cout << "B size: " << sizeof(B) << endl;
    cout << "C size: " << sizeof(C) << endl;

    cout << "ptr48<Data> size: " << sizeof(ptr48<Data>) << endl;

    //ptr48<Data, FF> my_p(p, std::move(flags));
    ptr48<Data> my_ptr(p);

    //Test pointer
    //可以像一个普通的指针向成员赋值
    my_ptr->a = 100;
    my_ptr->b = 20;
    my_ptr->c = 30.8;
    //可以像一个普通的指针去获取成员
    cout << "Test point get:              a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;
    //可以像一个普通的指针去调用成员函数
    cout << "Test point call fun:         " << my_ptr->say() << endl;
    //如同普通指针一样赋值
    Data data2{1, 1, 1.4};
    my_ptr = &data2;
    cout << "Test point `=` :             a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;
    //获取原始指针
    auto org_p = my_ptr.get();
    cout << "Test org point :             a:" << org_p->a << "   b:" << org_p->b << "  c:" << org_p->c << endl;
    //利用指针获取原始对象
    auto value = *my_ptr;
    cout << "Test point expr '*ptr' :     a:" << value.a << "   b:" << value.b << "  c:" << value.c << endl;

    return 0;
}
