#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

class Rational {
public:
    int num;
    int den;

    void reduce() {
        int temp = gcd(abs(num), abs(den));
        num /= temp;
        den /= temp;
    }

    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int num_) {
        num = num_;
        den = 1;
    }

    Rational(int num_, int denom_) {
        if (denom_ < 0) {
            num_ = -num_;
            denom_ = -denom_;
        }
        num = num_, den = denom_;
        reduce();
    }


    Rational(const Rational &e) : num(e.num), den(e.den) {}

    int numerator() const {
        return num;
    }

    int denominator() const {
        return den;
    }
};


Rational operator-(const Rational &v1) {
    return Rational(-v1.num, v1.den);
}

Rational &operator+(Rational &v1) {
    return v1;
}

bool operator==(const Rational &v1, const Rational &v2) {
    return (v1.den == v2.den) && (v1.num == v2.num);
}

bool operator!=(const Rational &v1, const Rational &v2) {
    return !(v1 == v2);
}

template<typename T1, typename T2>
Rational operator+(const T1 &v1_, const T2 &v2_) {
    Rational v1(v1_);
    Rational v2(v2_);
    int den = (v1.den * v2.den) / gcd(abs(v1.den), abs(v2.den));
    int num = v1.num * (den / v1.den) + v2.num * (den / v2.den);
    Rational temp(num, den);
    temp.reduce();
    return temp;
}

template<typename T1, typename T2>
Rational operator-(const T1 &v1_, const T2 &v2_) {
    Rational v1(v1_);
    Rational v2(v2_);
    int den = (v1.den * v2.den) / gcd(abs(v1.den), abs(v2.den));
    int num = v1.num * (den / v1.den) - v2.num * (den / v2.den);
    Rational temp(num, den);
    temp.reduce();
    return temp;
}

template<typename T1, typename T2>
Rational operator*(const T1 &v1_, const T2 &v2_) {
    Rational v1(v1_), v2(v2_);
    int num = v1.num * v2.num;
    int den = v1.den * v2.den;
    Rational temp(num, den);
    temp.reduce();
    return temp;
}

template<typename T1, typename T2>
Rational operator/(const T1 &v1_, const T2 &v2_) {
    Rational v1(v1_), v2(v2_);
    int num = v1.num * v2.den;
    int den = v1.den * v2.num;
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
    Rational temp(num, den);
    temp.reduce();
    return Rational(num, den);
}

Rational &operator++(Rational &v1) {
    v1 = v1 + 1;
    return v1;
}

Rational &operator--(Rational &v1) {
    v1 = v1 - 1;
    return v1;
}

Rational operator++(Rational &v1, int) {
    Rational v1_(v1);
    ++v1;
    return v1_;
}

Rational operator--(Rational &v2, int) {
    Rational v2_(v2);
    --v2;
    return v2_;
}

template<typename T1>
Rational &operator+=(Rational &v1, const T1 &v2) {
    v1 = v1 + Rational(v2);
    return v1;
}

template<typename T1>
Rational &operator-=(Rational &v1, const T1 &v2) {
    v1 = v1 - Rational(v2);
    return v1;
}

template<typename T1>
Rational &operator*=(Rational &v1, const T1 &v2) {
    v1 = v1 * Rational(v2);
    return v1;
}

template<typename T1>
Rational &operator/=(Rational &v1, const T1 &v2) {
    v1 = v1 / Rational(v2);
    return v1;
}


std::ostream& operator << (std::ostream& out, const Rational& v) {
    if (v.denominator() == 1) {
        out << v.numerator();
        return out;
    } else {
        string s = "\\frac{" + to_string(v.numerator()) + "}{" + to_string(v.denominator()) + "}";
        out << s;
        return out;
    }
}

std::ostringstream& operator << (std::ostringstream& out, const Rational& v) {
    if (v.denominator() == 1) {
        out << to_string(v.numerator());
        return out;
    } else {
        string s = "\\frac{" + to_string(v.numerator()) + "}{" + to_string(v.denominator()) + "}";
        out << s;
        return out;
    }
}

std::ostringstream& operator << (std::ostringstream& out, const int& v) {
    out << to_string(v);
    return out;
}

istream& operator>>(istream &in, Rational& i)
{
    in >> i.num >> i.den;
    return in;
}

