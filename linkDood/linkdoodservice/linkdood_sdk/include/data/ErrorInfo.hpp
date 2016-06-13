#pragma once

#include <string>
namespace service
{
	class ErrorInfo
    {
    public:
        ErrorInfo() : m_code(0)
        {

        }

		ErrorInfo(int code):m_code(code){}

//         ErrorInfo(int code, const char* str)
//             :m_code(code), m_msg(str)
//         {
//         }
// 
//         ErrorInfo(int code, const std::string& str)
//             :m_code(code), m_msg(str)
//         {
// 
//         }

//         ErrorInfo(const sdk::Error& error)
//         {
//             m_code = error.code();
//             m_msg = error.what();
//         }
// 
//         /// 可以附加错误信息
//         ErrorInfo(const sdk::Error& error, const std::string& str)
//         {
//             m_code = error.code();
//             m_msg = error.what();
//             if (m_msg.empty()) m_msg = str;
//         }

        operator bool()
        {
            return m_code != 0;
        }

        int code() const
        {
            return m_code;
        }

        const std::string& what() const
        {
            return m_msg;
        }

    private:
        int m_code;     //错误码
        std::string m_msg;//错误信息
    };
}