//
// Created by Yuqiao Miao on 2021/6/6.
//

#include "EyerSharedCount.hpp"

namespace Eyer
{
    EyerSharedCount::EyerSharedCount()
    {
        count = 0;
    }

    EyerSharedCount::~EyerSharedCount()
    {

    }

    long EyerSharedCount::Add()
    {
        count++;
        return count;
    }

    long EyerSharedCount::Reduce()
    {
        count--;
        return count;
    }

    long EyerSharedCount::Get()
    {
        return count;
    }
}