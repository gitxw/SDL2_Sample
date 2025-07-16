#pragma once

#include <string>

/// <summary>
/// 编码器工具
/// </summary>
class SGE_Encoder {

public:
    // 判断一个字符串是否为utf-8编码
    // 注意：纯ASCII字符串将判为false
    // 注意：本函数的判断结果并非完全正确
    static bool is_utf8_str(const std::string& str);

    // 检查环境是否为utf-8（编译时使用/utf-8参数），如果不是则为本地代码页
    static bool is_env_utf8();

    // UTF8编码的字符串转为UTF16编码的字符串
    static std::wstring UTF8_To_UTF16(const std::string& source);
    // UTF16编码的字符串转为UTF8编码的字符串
    static std::string UTF16_To_UTF8(const std::wstring& source);

    // GBK编码的字符串转为UTF16编码的字符串
    static std::wstring GBK_To_UTF16(const std::string& source);
    // UTF16编码的字符串转为GBK编码的字符串
    static std::string UTF16_To_GBK(const std::wstring& source);

    // GBK编码的字符串转为UTF8编码的字符串
    static std::string GBK_To_UTF8(const std::string& source);
    // UTF8编码的字符串转为GBK编码的字符串
    static std::string UTF8_To_GBK(const std::string& source);

    // 本地代码页字符串转为UTF16编码的字符串
    static std::wstring ANSI_To_UTF16(const std::string& source);
    // UTF16编码的字符串转为本地代码页字符串
    static std::string UTF16_To_ANSI(const std::wstring& source);

    // 本地代码页字符串转为UTF8编码的字符串
    static std::string ANSI_To_UTF8(const std::string& source);
    // UTF8编码的字符串转为本地代码页字符串
    static std::string UTF8_To_ANSI(const std::string& source);

    // 指定代码页字符串转为UTF16编码的字符串
    static std::wstring CP_To_UTF16(const std::string& source, unsigned int code_page);
    // UTF16编码的字符串转为指定代码页字符串
    static std::string UTF16_To_CP(const std::wstring& source, unsigned int code_page);

    // 指定代码页字符串转为UTF8编码的字符串
    static std::string CP_To_UTF8(const std::string& source, unsigned int code_page);
    // UTF8编码的字符串转为指定代码页字符串
    static std::string UTF8_To_CP(const std::string& source, unsigned int code_page);

    // 本地代码页字符串转为Env编码的字符串
    //   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
    //   本地代码页：指与当前操作系统的区域设置相关的语言的代码页，例如简体中文为cp936
    //   由于opencv、windows API（的A版本函数）等C++库，只支持本地代码页编码，所以在调用后，可能含有中文的字符串的返回值或返回参数一般需要经过本函数转换字符串的编码格式。
    static std::string ANSI_To_Env(const std::string& source);
    // Env编码的字符串转为本地代码页字符串
    //   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
    //   本地代码页：指与当前操作系统的区域设置相关的语言的代码页，例如简体中文为cp936
    //   由于opencv、windows API（的A版本函数）等C++库，只支持本地代码页编码，所以在调用时，可能含有中文的字符串参数一般需要经过本函数转换字符串的编码格式。
    static std::string Env_To_ANSI(const std::string& source);

    // UTF8字符串转为Env编码的字符串
    //   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
    //   由于某些C++库，只支持UTF8编码，所以在调用后，可能含有中文的字符串的返回值或返回参数一般需要经过本函数转换字符串的编码格式。
    static std::string UTF8_To_Env(const std::string& source);
    // Env编码的字符串转为UTF8字符串
    //   Env编码：指的是C++的开发环境是否用/utf-8编译，直接影响C++字符串的字面量是utf-8编码还是用本地代码页编码。它由is_env_utf8动态取得。
    //   由于某些C++库，只支持UTF8编码，所以在调用时，可能含有中文的字符串参数一般需要经过本函数转换字符串的编码格式。
    static std::string Env_To_UTF8(const std::string& source);
};
