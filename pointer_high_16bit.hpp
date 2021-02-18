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

template <class T, class F>
struct pointer
{
    union
    {
        T *p;
        struct
        {
            int _no_use1 : 32;
            short _no_use2 : 16;
            F _f;
        } flags;
    };

    explicit pointer(T *_p, F &&_f)
    {
        static_assert(sizeof(F) <= 2);
        p = _p;
        flags._f = _f;
    }
    explicit pointer(T *_p, F &_f)
    {
        static_assert(sizeof(F) <= 2);
        p = _p;
        flags._f = _f;
    }
    explicit pointer(F &&_f)
    {
        static_assert(sizeof(F) <= 2);
        p = nullptr;
        flags._f = _f;
    }
    explicit pointer(F &_f)
    {
        static_assert(sizeof(F) <= 2);
        p = nullptr;
        flags._f = _f;
    }
    explicit pointer()
    {
        static_assert(sizeof(F) <= 2);
        p = nullptr;
    }

    //get
    T *operator->()
    {
        intptr_t p3 = (reinterpret_cast<intptr_t>(p) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }
    T *get()
    {
        intptr_t p3 = (reinterpret_cast<intptr_t>(p) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }
    T *get() const
    {
        intptr_t p3 = (reinterpret_cast<intptr_t>(p) << 16) >> 16;
        return reinterpret_cast<T *>(p3);
    }

    typename std::conditional<!std::is_void<T>::value, T, int>::type &
    operator*() //[[nodiscard]]
    {
        if constexpr (std::is_void<T>::value)
        {
            return 0;
        }
        else
        {
            auto pp = get();
            return *pp; ////
        }
    }
    void operator=(const T *_p)
    {
        F _f = flags._f;
        p = _p;
        flags._f = _f;
    }
    void operator=(T *_p)
    {
        F _f = flags._f;
        p = _p;
        flags._f = _f;
    }

    F &operator()()
    {
        return flags._f;
    }
    const F &operator()() const
    {
        return flags._f;
    }

    void operator=(const F &_f)
    {
        flags._f = _f;
    }
};
