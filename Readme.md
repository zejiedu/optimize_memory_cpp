
> In this project， provided two way for easy and free to use the high 16 bits of C pointer

- 48bit pointer
- 64bit pointer with 16bit container

> 在本工程中，提供2种方法，可以方便地利用C指针闲置高16bit存取数据。

- 48bit指针
- 64位指针，带16bit的容器

# Using the extra 16 bits in 64-bit pointers

The AMD64 architecture defines a 64-bit virtual address format, of which the low-order 48 bits are used in current implementations (...) The architecture definition allows this limit to be raised in future implementations to the full 64 bits, extending the virtual address space to 16 EB (2^64 bytes). This is compared to just 4 GB (2^32 bytes) for the x86.

The high order bits are reserved in case the address bus would be increased in the future, so you can't use it simply 

In the first implementations of the architecture, only the least significant 48 bits of a virtual address would actually be used in address translation (page table lookup). Further, bits 48 through 63 of any virtual address must be copies of bit 47 (in a manner akin to sign extension), or the processor will raise an exception. Addresses complying with this rule are referred to as "canonical form."

As the CPU will check the high bits even if they're unused, they're not really "irrelevant". You need to make sure that the address is canonical before using the pointer. Some other 64-bit architectures like ARM64 have the option to ignore the high bits, therefore you can store data in pointers much more easily.

That said, in x86_64 you're still free to use the high 16 bits if needed, but you have to check and fix the pointer value by sign-extending before dereferencing it.

Note that casting the pointer value to long is not the correct way to do because long is not guaranteed to be wide enough to store pointers. You need to use uintptr_t or intptr_t.

# 在64位指针中使用额外的16位 

AMD64体系结构定义了一种64位虚拟地址格式，当前实现中使用其中的低阶48位（...）体系结构定义允许在将来的实现中提高此限制到完整的64位，将虚拟地址空间扩展到16 EB（2^64 个字节）。相比之下，x86仅4 GB（2^32 字节）。

保留高阶位，以防将来将来增加地址总线时使用，所以您不能简单地使用它.

在该体系结构的第一个实现中，实际上只有虚拟地址的最低有效48位将用于地址转换（页表查找）中。此外，任何虚拟地址的第48位到第63位必须是第47位的副本（以类似于 sign extension 的方式），否则处理器将引发异常。符合此规则的地址称为"规范形式"。

因为CPU会检查高位，即使它们是未使用，它们并不是真正无关紧要的。在使用指针之前，您需要确保地址是规范的。其他一些64位体系结构（例如ARM64）可以选择忽略高位，因此您可以更轻松地将数据存储在指针中。

也就是说，在x86_64中，如果需要，您仍然可以自由使用高16位，但是必须在取消引用之前通过符号扩展来检查并修复指针值。


#  48bit pointer 
```cpp
//file  test_ptr48.cpp
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
    my_ptr->a = 100;
    my_ptr->b = 20;
    my_ptr->c = 30.8;  

    cout << "Test point get:              a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;
    cout << "Test point call fun:         " << my_ptr->say() << endl;

    Data data2{1, 1, 1.4};
    my_ptr = &data2;
    cout << "Test point `=` :             a:" << my_ptr->a << "   b:" << my_ptr->b << "  c:" << my_ptr->c << endl;

    auto org_p = my_ptr.get();
    cout << "Test org point :             a:" << org_p->a << "   b:" << org_p->b << "  c:" << org_p->c << endl;

    auto value = *my_ptr;
    cout << "Test point expr '*ptr' :     a:" << value.a << "   b:" << value.b << "  c:" << value.c << endl;

    return 0;
}
```


# 64bit pointer with 16bit container   

```cpp
//file: test_pointer_high16bit.cpp
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

```