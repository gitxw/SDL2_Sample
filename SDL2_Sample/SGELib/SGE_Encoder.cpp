//////////////////////////////////////////////////////////////////////////////////////////////////
// 本文件中的函数来源于网络
// https://blog.csdn.net/CharlesSimonyi/article/details/8722859
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "SGE_Encoder.h"

#include <Windows.h>

// 判断一个字符串是否为utf-8编码
bool SGE_Encoder::is_utf8_str(const std::string& str)
{
    bool is_utf8 = false;
    unsigned char* start = (unsigned char*)str.c_str();
    unsigned char* end = (unsigned char*)start + str.length();
    while (start < end) {
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
        {
            start++;
        } else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
        {
            is_utf8 = false;
            break;
        } else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
        {
            is_utf8 = true;
            if (start >= end - 1)
                break;
            if ((start[1] & (0xC0)) != 0x80) {
                is_utf8 = false;
                break;
            }
            start += 2;
        } else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符
        {
            is_utf8 = true;
            if (start >= end - 2)
                break;
            if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80) {
                is_utf8 = false;
                break;
            }
            start += 3;
        } else if (*start < (0xF8)) // (11111000): 此范围内为4字节UTF-8字符
        {
            is_utf8 = true;
            if (start >= end - 3)
                break;
            if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80 || (start[3] & (0xC0)) != 0x80) {
                is_utf8 = false;
                break;
            }
            start += 4;
        } else {
            is_utf8 = false;
            break;
        }
    }
    return is_utf8;
}

// 检查环境是否为utf-8（编译时使用/utf-8参数）
bool SGE_Encoder::is_env_utf8()
{
    static bool ret_val = std::string("中国") == std::string(u8"中国");
    return ret_val;
}

std::wstring SGE_Encoder::UTF8_To_UTF16(const std::string& source)
{
    unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
    if (len == 0)
        return std::wstring();
    wchar_t* buffer = new wchar_t[len];
    ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, buffer, len);

    std::wstring dest(buffer);
    delete[] buffer;
    return dest;
}

std::string SGE_Encoder::UTF16_To_UTF8(const std::wstring& source)
{
    unsigned long len = ::WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL, NULL, NULL);
    if (len == 0)
        return std::string();
    char* buffer = new char[len];
    ::WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, buffer, len, NULL, NULL);

    std::string dest(buffer);
    delete[] buffer;
    return dest;
}

std::wstring SGE_Encoder::GBK_To_UTF16(const std::string& source)
{
    unsigned int GBK = 936;
    return CP_To_UTF16(source, GBK);
}

std::string SGE_Encoder::UTF16_To_GBK(const std::wstring& source)
{
    unsigned int GBK = 936;
    return UTF16_To_CP(source, GBK);
}

std::string SGE_Encoder::GBK_To_UTF8(const std::string& source)
{
    unsigned int GBK = 936;
    return CP_To_UTF8(source, GBK);
}

std::string SGE_Encoder::UTF8_To_GBK(const std::string& source)
{
    unsigned int GBK = 936;
    return UTF8_To_CP(source, GBK);
}

// 本地代码页字符串转为UTF16编码的字符串
std::wstring SGE_Encoder::ANSI_To_UTF16(const std::string& source)
{
    unsigned int codePage = GetACP();
    return CP_To_UTF16(source, codePage);
}

// UTF16编码的字符串转为本地代码页字符串
std::string SGE_Encoder::UTF16_To_ANSI(const std::wstring& source)
{
    unsigned int codePage = GetACP();
    return UTF16_To_CP(source, codePage);
}

// 本地代码页字符串转为UTF8编码的字符串
std::string SGE_Encoder::ANSI_To_UTF8(const std::string& source)
{
    unsigned int codePage = GetACP();
    return CP_To_UTF8(source, codePage);
}

// UTF8编码的字符串转为本地代码页字符串
std::string SGE_Encoder::UTF8_To_ANSI(const std::string& source)
{
    unsigned int codePage = GetACP();
    return UTF8_To_CP(source, codePage);
}

// 指定代码页字符串转为UTF16编码的字符串
std::wstring SGE_Encoder::CP_To_UTF16(const std::string& source, unsigned int code_page)
{
    unsigned long len = ::MultiByteToWideChar(code_page, NULL, source.c_str(), -1, NULL, NULL);
    if (len == 0)
        return std::wstring();
    wchar_t* buffer = new wchar_t[len];
    ::MultiByteToWideChar(code_page, NULL, source.c_str(), -1, buffer, len);

    std::wstring dest(buffer);
    delete[] buffer;
    return dest;
}

// UTF16编码的字符串转为指定代码页字符串
std::string SGE_Encoder::UTF16_To_CP(const std::wstring& source, unsigned int code_page)
{
    unsigned long len = ::WideCharToMultiByte(code_page, NULL, source.c_str(), -1, NULL, NULL, NULL, NULL);
    if (len == 0)
        return std::string();
    char* buffer = new char[len];
    ::WideCharToMultiByte(code_page, NULL, source.c_str(), -1, buffer, len, NULL, NULL);

    std::string dest(buffer);
    delete[] buffer;
    return dest;
}

// 指定代码页字符串转为UTF8编码的字符串
std::string SGE_Encoder::CP_To_UTF8(const std::string& source, unsigned int code_page)
{
    unsigned long len = ::MultiByteToWideChar(code_page, NULL, source.c_str(), -1, NULL, NULL);
    if (len == 0)
        return std::string();
    wchar_t* wide_char_buffer = new wchar_t[len];
    ::MultiByteToWideChar(code_page, NULL, source.c_str(), -1, wide_char_buffer, len);

    len = ::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
    if (len == 0) {
        delete[] wide_char_buffer;
        return std::string();
    }
    char* multi_byte_buffer = new char[len];
    ::WideCharToMultiByte(CP_UTF8, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

    std::string dest(multi_byte_buffer);
    delete[] wide_char_buffer;
    delete[] multi_byte_buffer;
    return dest;
}

// UTF8编码的字符串转为指定代码页字符串
std::string SGE_Encoder::UTF8_To_CP(const std::string& source, unsigned int code_page)
{
    unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
    if (len == 0)
        return std::string();
    wchar_t* wide_char_buffer = new wchar_t[len];
    ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);

    len = ::WideCharToMultiByte(code_page, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
    if (len == 0) {
        delete[] wide_char_buffer;
        return std::string();
    }
    char* multi_byte_buffer = new char[len];
    ::WideCharToMultiByte(code_page, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

    std::string dest(multi_byte_buffer);
    delete[] wide_char_buffer;
    delete[] multi_byte_buffer;
    return dest;
}

// 本地代码页字符串转为Env编码的字符串
//   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
//   本地代码页：指与当前操作系统的区域设置相关的语言的代码页，例如简体中文为cp936
//   由于opencv、windows API（的A版本函数）等C++库，只支持本地代码页编码，所以在调用后，可能含有中文的字符串的返回值或返回参数一般需要经过本函数转换字符串的编码格式。
std::string SGE_Encoder::ANSI_To_Env(const std::string& source)
{
    if (SGE_Encoder::is_env_utf8()) {
        return SGE_Encoder::ANSI_To_UTF8(source);
    } else {
        return source;
    }
}

// Env编码的字符串转为本地代码页字符串
//   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
//   本地代码页：指与当前操作系统的区域设置相关的语言的代码页，例如简体中文为cp936
//   由于opencv、windows API（的A版本函数）等C++库，只支持本地代码页编码，所以在调用时，可能含有中文的字符串参数一般需要经过本函数转换字符串的编码格式。
std::string SGE_Encoder::Env_To_ANSI(const std::string& source)
{
    if (SGE_Encoder::is_env_utf8()) {
        return SGE_Encoder::UTF8_To_ANSI(source);
    } else {
        return source;
    }
}

// UTF8字符串转为Env编码的字符串
//   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
//   由于某些C++库，只支持UTF8编码，所以在调用后，可能含有中文的字符串的返回值或返回参数一般需要经过本函数转换字符串的编码格式。
std::string SGE_Encoder::UTF8_To_Env(const std::string& source)
{
    if (SGE_Encoder::is_env_utf8()) {
        return source;
    } else {
        return SGE_Encoder::UTF8_To_ANSI(source);
    }
}

// Env编码的字符串转为UTF8字符串
//   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
//   由于某些C++库，只支持UTF8编码，所以在调用时，可能含有中文的字符串参数一般需要经过本函数转换字符串的编码格式。
std::string SGE_Encoder::Env_To_UTF8(const std::string& source)
{
    if (SGE_Encoder::is_env_utf8()) {
        return source;
    } else {
        return SGE_Encoder::ANSI_To_UTF8(source);
    }
}
