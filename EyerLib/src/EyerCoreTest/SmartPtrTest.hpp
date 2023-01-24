#ifndef EYERLIB_SMARTPTRTEST_HPP
#define EYERLIB_SMARTPTRTEST_HPP

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"

class A
{
public:
    A()
    {
        EyerLog("A()\n");
    }

    ~A()
    {
        EyerLog("~A()\n");
    }
};

TEST(SmartPtr, SmartPtrTest){
    A * a = new A();
    Eyer::EyerSmartPtr<A> smartPtr(a);
    EyerLog("Count: %d\n", smartPtr.GetRefCount());

    Eyer::EyerSmartPtr<A> smartPtrB = smartPtr;
    EyerLog("Count: %d\n", smartPtr.GetRefCount());

}

TEST(SmartPtr, SmartPtrTest2){
    EyerLog("=============SmartPtrTest2=============\n");
    Eyer::EyerSmartPtr<A> a(new A());
    Eyer::EyerSmartPtr<A> b(new A());
    Eyer::EyerSmartPtr<A> c = b;

    for(int i=0;i<100;i++){
        if(i % 2 == 0){
            c = a;
            ASSERT_EQ(c, a);
            ASSERT_NE(c, b);
        }
        else{
            c = b;
            ASSERT_EQ(c, b);
            ASSERT_NE(c, a);
        }
    }
}


TEST(SmartPtr, SmartPtrTest3) {
    EyerLog("=============SmartPtrTest3=============\n");
    Eyer::EyerSmartPtr<A> a(new A());
    Eyer::EyerSmartPtr<A> b(nullptr);

    b = a;
    ASSERT_EQ(b, a);

    Eyer::EyerSmartPtr<A> SmartNULL(nullptr);
    b = SmartNULL;

    ASSERT_EQ(b, nullptr);

    Eyer::EyerSmartPtr<A> smartPtrNull(nullptr);
    ASSERT_EQ(smartPtrNull, nullptr);
    for(int i=0;i<10;i++){
        if(i % 2 == 0){
            Eyer::EyerSmartPtr<A> tempPtr(new A());
            smartPtrNull = tempPtr;
        }
    }

    ASSERT_NE(smartPtrNull, nullptr);
}

TEST(SmartPtr, SmartPtrTest4)
{
    Eyer::EyerSmartPtr<A> a(new A());
    Eyer::EyerSmartPtr<A> b;

    b = a;
    ASSERT_EQ(b, a);
}

#endif //EYERLIB_SMARTPTRTEST_HPP
