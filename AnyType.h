#pragma once
#include <utility>
#include <exception>

class AnyType {
public:
    enum class Type {
        None,
        Bool,
        Char,
        SignedChar,
        UnsignedChar,
        WChar,
        Char16,
        Char32,
        Short,
        UnsignedShort,
        Int,
        UnsignedInt,
        Long,
        UnsignedLong,
        LongLong,
        UnsignedLongLong,
        Float,
        Double,
        LongDouble
    };

private:
    union Value {
        bool b;
        char c;
        signed char sc;
        unsigned char uc;
        wchar_t wc;
        char16_t c16;
        char32_t c32;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long l;
        unsigned long ul;
        long long ll;
        unsigned long long ull;
        float f;
        double d;
        long double ld;
    } value{};

    Type type = Type::None;

public:
    AnyType() = default;
    AnyType(const AnyType &other) = default;
    AnyType(AnyType &&other) noexcept { Swap(*this, other); }

    AnyType& operator=(const AnyType &other) {
        if (this != &other) {
            value = other.value;
            type = other.type;
        }
        return *this;
    }

    AnyType& operator=(AnyType &&other) noexcept {
        if (this != &other) {
            this->Destroy();
            Swap(*this, other);
        }
        return *this;
    }

    AnyType(const bool b) { *this = b; }
    AnyType(const char c) { *this = c; }
    AnyType(const signed char sc) { *this = sc; }
    AnyType(const unsigned char uc) { *this = uc; }
    AnyType(const wchar_t wc) { *this = wc; }
    AnyType(const char16_t c16) { *this = c16; }
    AnyType(const char32_t c32) { *this = c32; }
    AnyType(const short s) { *this = s; }
    AnyType(const unsigned short us) { *this = us; }
    AnyType(const int i) { *this = i; }
    AnyType(const unsigned int ui){ *this = ui; }
    AnyType(const long l) { *this = l; }
    AnyType(const unsigned long ul) { *this = ul; }
    AnyType(const long long ll) { *this = ll; }
    AnyType(const unsigned long long ull) { *this = ull; }
    AnyType(const float f) { *this = f; }
    AnyType(const double d) { *this = d; }
    AnyType(const long double ld) { *this = ld; }

    AnyType& operator=(const bool b) { this->type = Type::Bool; this->value.b = b; return *this; }
    AnyType& operator=(const char c) { this->type = Type::Char; this->value.c = c; return *this; }
    AnyType& operator=(const signed char sc) { this->type = Type::SignedChar; this->value.sc = sc; return *this; }
    AnyType& operator=(const unsigned char uc) { this->type = Type::UnsignedChar; this->value.uc = uc; return *this; }
    AnyType& operator=(const wchar_t wc) { this->type = Type::WChar; this->value.wc = wc; return *this; }
    AnyType& operator=(const char16_t c16) { this->type = Type::Char16; this->value.c16 = c16; return *this; }
    AnyType& operator=(const char32_t c32) { this->type = Type::Char32; this->value.c32 = c32; return *this; }
    AnyType& operator=(const short s) { this->type = Type::Short; this->value.s = s; return *this; }
    AnyType& operator=(const unsigned short us) { this->type = Type::UnsignedShort; this->value.us = us; return *this; }
    AnyType& operator=(const int i) { this->type = Type::Int; this->value.i = i; return *this; }
    AnyType& operator=(const unsigned int ui) { this->type = Type::UnsignedInt; this->value.ui = ui; return *this; }
    AnyType& operator=(const long l) { this->type = Type::Long; this->value.l = l; return *this; }
    AnyType& operator=(const unsigned long ul) { this->type = Type::UnsignedLong; this->value.ul = ul; return *this; }
    AnyType& operator=(const long long ll) { this->type = Type::LongLong; this->value.ll = ll; return *this; }
    AnyType& operator=(const unsigned long long ull) { this->type = Type::UnsignedLongLong; this->value.ull = ull; return *this; }
    AnyType& operator=(const float f) { this->type = Type::Float; this->value.f = f; return *this; }
    AnyType& operator=(const double d) { this->type = Type::Double; this->value.d = d; return *this; }
    AnyType& operator=(const long double ld) { this->type = Type::LongDouble; this->value.ld = ld; return *this; }

    void Destroy() {
        this->type = Type::None;
    }

    static void Swap(AnyType& lhs, AnyType& rhs) {
        std::swap(lhs.value, rhs.value);
        std::swap(lhs.type, rhs.type);
    }

    Type GetType() const {
        return type;
    }

    bool ToBool() const {
        if (type != Type::Bool) throw std::bad_cast();
        return value.b;
    }

    char ToChar() const {
        if (type != Type::Char) throw std::bad_cast();
        return value.c;
    }

    signed char ToSignedChar() const {
        if (type != Type::SignedChar) throw std::bad_cast();
        return value.sc;
    }

    unsigned char ToUnsignedChar() const {
        if (type != Type::UnsignedChar) throw std::bad_cast();
        return value.uc;
    }

    wchar_t ToWChar() const {
        if (type != Type::WChar) throw std::bad_cast();
        return value.wc;
    }

    char16_t ToChar16() const {
        if (type != Type::Char16) throw std::bad_cast();
        return value.c16;
    }

    char32_t ToChar32() const {
        if (type != Type::Char32) throw std::bad_cast();
        return value.c32;
    }

    short ToShort() const {
        if (type != Type::Short) throw std::bad_cast();
        return value.s;
    }

    unsigned short ToUnsignedShort() const {
        if (type != Type::UnsignedShort) throw std::bad_cast();
        return value.us;
    }

    unsigned int ToUnsignedInt() const {
        if (type != Type::UnsignedInt) throw std::bad_cast();
        return value.ui;
    }

    int ToInt() const {
        if (type != Type::Int) throw std::bad_cast();
        return value.i;
    }

    long ToLong() const {
        if (type != Type::Long) throw std::bad_cast();
        return value.l;
    }

    unsigned long ToUnsignedLong() const {
        if (type != Type::UnsignedLong) throw std::bad_cast();
        return value.ul;
    }

    long long ToLongLong() const {
        if (type != Type::LongLong) throw std::bad_cast();
        return value.ll;
    }

    unsigned long long ToUnsignedLongLong() const {
        if (type != Type::UnsignedLongLong) throw std::bad_cast();
        return value.ull;
    }

    float ToFloat() const {
        if (type != Type::Float) throw std::bad_cast();
        return value.f;
    }

    double ToDouble() const {
        if (type != Type::Double) throw std::bad_cast();
        return value.d;
    }

    long double ToLongDouble() const {
        if (type != Type::LongDouble) throw std::bad_cast();
        return value.ld;
    }
};
