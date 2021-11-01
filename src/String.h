#pragma once
#include <cstring>
#include <ostream>


class String
{
private:
    char* m_Buffer;
    int m_bSize;
public:
    String() {}
    String(const char* str) {
        m_bSize = strlen(str);
        m_Buffer = new char[m_bSize + 1];
        memcpy(m_Buffer, str, m_bSize);
        m_Buffer[m_bSize] = 0;
    }
    String(const String& other) :m_bSize(other.m_bSize) {
        m_Buffer = new char[m_bSize + 1];
        memcpy(m_Buffer, other.m_Buffer, m_bSize + 1);
    }

    String(String&& other) noexcept
    {
        m_bSize = other.m_bSize;
        m_Buffer = other.m_Buffer;

        other.m_bSize = 0;
        other.m_Buffer = nullptr;
    }

    ~String() {
        delete[] m_Buffer;
    }
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};
std::ostream& operator<<(std::ostream& stream, const String& string) {
    return stream << string.m_Buffer;
}