#ifndef	EYER_CORE_STRING_H
#define	EYER_CORE_STRING_H

#include <string>
#include <vector>

namespace Eyer {
    class EyerString
    {
    public:
        static EyerString Number(int8_t num);
        static EyerString Number(int16_t num);
        static EyerString Number(int32_t num);
        static EyerString Number(int64_t num);

        static EyerString Number(uint32_t num);
        static EyerString Number(uint64_t num);

        static EyerString Number(float num);
        static EyerString Number(double num);

        static EyerString Number(float num, EyerString format);
        static EyerString Number(int num, EyerString format);
        static EyerString Number(uint32_t num, EyerString format);

        static EyerString Sprintf(const EyerString format, ...);
        static EyerString FormatSec(int sec);

        static EyerString GetCWD();

        EyerString();
        EyerString(const EyerString & str);
        EyerString(const std::string & str);
        EyerString(const char str[]);
        ~EyerString();

        EyerString & operator = (const EyerString & s);
        EyerString & operator = (const std::string & str);
        EyerString & operator = (const char str[]);

        const EyerString operator + (const EyerString & s) const;
        const EyerString & operator += (const EyerString & s);

        bool operator == (const EyerString & s) const;
        bool operator > (const EyerString & s) const;
        bool operator < (const EyerString & s) const;

        int Split(EyerString * resArr, const EyerString & splitStr);
        int Replace(const EyerString & substr, const EyerString & replacement);

        bool IsEmpty() const;

        const char * c_str() const;

        bool StartWith(const EyerString & str) const;

    private:
        std::string origin_str;
        std::vector<EyerString> splitVec;
    };



    /*
    class EyerString
    {
    public:
        char * str = nullptr;
        int ClearStr();

    public:
        EyerString();
        EyerString(const char str[]);
        EyerString(const std::string & str);
        EyerString(const EyerString & str);
        ~EyerString();

        bool IsEmpty() const;

        EyerString & operator = (const EyerString & s);

        bool operator == (const EyerString & s) const;

        bool operator > (const EyerString & s) const;
        bool operator < (const EyerString & s) const;

        const EyerString operator + (const EyerString & s) const;
        const EyerString & operator += (const EyerString & s);

        int Replace(const EyerString & substr, const EyerString & replacement);
        int Split(EyerString * resArr, const EyerString & splitStr);

        static EyerString Sprintf(const EyerString & format, ...);

        static EyerString Number(float num, EyerString format = "%f");
        static EyerString Number(int num, EyerString format = "%d");
        static EyerString Number(uint32_t num, EyerString format = "%d");

        static EyerString Number(long num);
        static EyerString Number(double num);
        static EyerString Number(long long num);
        static EyerString Number(uint64_t num);

        static EyerString FormatSec(int sec);

        EyerString ReplaceAll(const EyerString & substr, const EyerString & replacement);

        const char * c_str() const;

    private:
        std::vector<EyerString> splitVec;
    };
     */
}

#endif
