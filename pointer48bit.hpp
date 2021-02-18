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
#include <string.h>

template <class T>
class ptr48
{
    char _ptr[6]{0, 0, 0, 0, 0, 0};

public:
    explicit ptr48(T *_p)
    {
        void *p_src = static_cast<void *>(&_p);
        void *p_dst = static_cast<void *>(_ptr);
        memcpy(p_dst, p_src, 6);
    }
    explicit ptr48() {}

    //get
    T *operator->()
    {
        intptr_t p3 = ((*reinterpret_cast<const intptr_t *>(_ptr)) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }
    T *get()
    {
        intptr_t p3 = ((*reinterpret_cast<const intptr_t *>(_ptr)) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }
    T *get() const
    {
        intptr_t p3 = ((*reinterpret_cast<const intptr_t *>(_ptr)) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }

    T *operator()()
    {
        return get();
    }
    const T *operator()() const
    {
        return get();
    }

    typename std::conditional<!std::is_void<T>::value, T, int>::type &
    operator*()
    {
        if constexpr (std::is_void<T>::value)
        {
            return 0;
        }
        else
        {
            auto pp = get();
            return *pp;
        }
    }
    void operator=(const T *_p)
    {
        void *p_src = static_cast<void *>(&_p);
        void *p_dst = static_cast<void *>(_ptr);
        memcpy(p_dst, p_src, 6);
    }
    void operator=(T *_p)
    {
        void *p_src = static_cast<void *>(&_p);
        void *p_dst = static_cast<void *>(_ptr);
        memcpy(p_dst, p_src, 6);
    }
    typename std::conditional<!std::is_void<T>::value, T, int>::type &
    operator[](int idx)
    {
        if constexpr (std::is_void<T>::value)
        {
            return 0;
        }
        else
        {
            auto pp = get();
            return pp[idx];
        }
    }
};
