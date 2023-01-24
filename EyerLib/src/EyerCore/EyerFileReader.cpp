#include "EyerFileReader.hpp"

namespace Eyer
{
    EyerFileReader::EyerFileReader(const EyerString & _path)
        : path(_path)
    {

    }

    EyerFileReader::~EyerFileReader()
    {

    }

    EyerString EyerFileReader::ReadText()
    {
        EyerString str = 0;

        char buffer[1024] = {0};

        FILE * fp = fopen(path.c_str(), "r");

        if(fp == nullptr){
            return str;
        }

        int len;
        if(fp != NULL){
            while(fgets(buffer, 1024, fp) != NULL) {
                str += buffer;
            }
            fclose(fp);
        }

        return str;
    }
}