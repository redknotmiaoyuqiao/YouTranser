#include "EyerURLUtil.hpp"

#include <string.h>
#include <stdio.h>

namespace Eyer
{
    EyerURLUtil::EyerURLUtil(const EyerString & _baseUrl)
    {
        baseUrl = _baseUrl;
    }

    EyerURLUtil::~EyerURLUtil()
    {

    }

    EyerString EyerURLUtil::GetAbsolutePath(const EyerString & relativePath)
    {
        int size = baseUrl.Split(nullptr, "/");
        if(size <= 0){
            return baseUrl;
        }

        Eyer::EyerString * strList = new Eyer::EyerString[size];
        size = baseUrl.Split(strList, "/");

        EyerString dirPath;
        for(int i=0;i<size - 1;i++){
            dirPath = dirPath + strList[i] + "/";
        }

        delete [] strList;


        return dirPath + relativePath;
    }
}