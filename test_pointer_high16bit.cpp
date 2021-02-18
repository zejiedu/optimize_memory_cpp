/*******************************************************************
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-14
 * 
 * @copyright Copyright (c) 2019
 * 
 ******************************************************************/

#include <iostream>
#include "pointer_high_16bit.hpp"

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

int main()
{
    void *void_p = malloc(20);
    Data data;
    Data *p = &data;
    FF flags{3, 3, 5, 1, 1, 1, 1};
    cout << "original total size: " << sizeof(Data *) + sizeof(FF) << endl; // 10

    //pointer<Data, FF> my_p(p, std::move(flags));
    pointer<Data, FF> my_ptr(p, flags);
    cout << "original total size: " << sizeof(pointer<Data, FF>) << endl; // 8

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

    //Test Flags
    //test get flags
    auto ff = my_ptr();
    //获取高位数据的值
    cout << "Test get high 16bit:         a:" << ff.a << "   b:" << ff.b << "  c:" << ff.c
         << "   b1:" << ff.b1 << "   b2:" << ff.b2 << "   b3:" << ff.b3 << "   b4:" << ff.b4
         << endl;
    //测试高位数据的赋值运算
    //如同struct一样赋值
    FF flags2{1, 2, 3, 1, 1, 0, 1};
    my_ptr = flags2;
    auto ff2 = my_ptr();
    cout << "Test high 16bit expr ` = ` : a:" << ff2.a << "   b:" << ff2.b << "  c:" << ff2.c
         << "   b1:" << ff2.b1 << "   b2:" << ff2.b2 << "   b3:" << ff2.b3 << "   b4:" << ff2.b4 << endl;

    cout << "Test point `=` :             a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;

    Data data3{1, 77, 1.4};
    my_ptr = &data3;
    cout << "Test point `=` :             a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;

    auto ff3 = my_ptr();
    cout << "Test high 16bit expr ` = ` :  a:" << ff3.a << "   b:" << ff3.b << "  c:" << ff3.c
         << "   b1:" << ff3.b1 << "   b2:" << ff3.b2 << "   b3:" << ff3.b3 << "   b4:" << ff3.b4 << endl;
    my_ptr().c = 7;
    cout << "Test high 16bit expr ` = ` :  a:" << ff3.a << "   b:" << ff3.b << "  c:" << my_ptr().c
         << "   b1:" << ff3.b1 << "   b2:" << ff3.b2 << "   b3:" << ff3.b3 << "   b4:" << ff3.b4 << endl;
    union xx
    {
        xx(){};
        ~xx(){};
        pointer<Data, FF> my_ptr1;
        pointer<Data, FF> my_ptr2;
    } tmp;

    return 0;
}
