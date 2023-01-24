#ifndef EYERLIB_MD5TEST_HPP
#define EYERLIB_MD5TEST_HPP

#include <gtest/gtest.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerGL/EyerGL.hpp"

TEST(EyerMD5, md5){
    Eyer::EyerString res = Eyer::EyerUtil::Md5(Eyer::EyerString("http://www.baidu.com"));
    EyerLog("res: %s\n", res.c_str());
}

#endif //EYERLIB_MD5TEST_HPP
