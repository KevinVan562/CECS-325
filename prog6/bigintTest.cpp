
#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <climits>
using namespace std;

class BigInt {
    private:
        vector<char> v;
        bool isNegative;
        BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1) {
            if (n == BigInt(0))
                return a;
            else if (n == BigInt(1))
                return b;
            else
                return fiboHelper(n - 1, b, a + b);
        }

    public:
        BigInt(string);
        BigInt(int);
        BigInt();

        BigInt operator/ (BigInt);
        BigInt operator% (BigInt);
        BigInt operator++(int);
        BigInt operator++();
        BigInt operator[] (int);    // index function
        
        BigInt operator+ (BigInt);
        BigInt operator- (BigInt);
        BigInt operator- (int);
        BigInt operator* (BigInt);
        BigInt absolute();
        
        int getDigitAt(int index); 
        BigInt(vector<char>& value) : v(value) {}

        bool operator==(BigInt other) {
            if (v.size() != other.v.size()) {
                return false;
            }
            for (int i = 0; i < v.size(); i++) {
                if (v[i] != other.v[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(BigInt other) {
            return !(*this == other);
        }

        bool operator<(BigInt other) {
            // Check if this number is negative
            bool isNegative = (v[0] == '-');
            bool otherIsNegative = (other.v[0] == '-');

            if (isNegative && !otherIsNegative) {
                // This is negative, other is positive
                return true;
            }
            if (!isNegative && otherIsNegative) {
                // This is positive, other is negative
                return false;
            }

            if (isNegative) {
                // Both are negative, compare like positive, smaller is larger in terms of negative
                if (v.size() < other.size()) {
                    return true;
                }
                if (v.size() > other.size()) {
                    return false;
                }
                // If they are the same length, compare digit by digit
                for(size_t i = 0; i < v.size(); i++) {
                    if (v[i] < other.v[i]) {
                        return true;
                    }
                    if (v[i] > other.v[i]) {
                        return false;
                    }
                }
                return false;   // They are equal
            } else {
                // Both numbers positive
                if (v.size() < other.size()) {
                    return true;
                }
                if (v.size() > other.size()) {
                    return false;
                }
                // If same length
                for (size_t i = 0; i < v.size(); i++) {
                    if (v[i] < other.v[i]) {
                        return true;
                    }
                    if (v[i] > other.v[i]) {
                        return false;
                    }
                }
                return false;   // Both equal
            }
        }

        bool operator > (BigInt other) {
            if (*this == other) {
                return false;
            } else {
                return !(*this < other);
            }
        }

        bool operator <= (BigInt other) {
            return (*this < other) || (*this == other);
        }

        bool operator >= (BigInt other) {
            return (*this > other) || (*this == other);
        }


        void print() {
            string str = "";
            if (isNegative) {
                str += '-';
            }
            for (int i = 0; i < v.size(); i++) {
                str += v[i];
            }
            cout << str << endl;
        }

        int size() {
            return v.size();
        }

        BigInt fibo(BigInt n) {
            return fiboHelper(n);
        }

        BigInt fact(BigInt n) {
            if (n == BigInt(0))
                return BigInt(1);
            BigInt result(1);
                for (BigInt i(1); i <= n; i = i + BigInt(1)) {
                    result = result * i;
                }
            return result;
        }

        friend ostream& operator<<(ostream& os, const BigInt& bi) {
            ostringstream output;
            if (bi.isNegative && bi.v.size() > 13) {
                output << bi.v[0];
                output << bi.v[1];
                output << '.';

            for (int i = 2; i < 8; ++i) {
                output << bi.v[i];
            }
            output << 'e';
            output << (bi.v.size() - 2);
            }
            else if (bi.v.size() > 12) {
                output << bi.v[0];
                output << '.';

                for (int i = 1; i < 7; ++i) {
                    output << bi.v[i];
                }
                output << 'e';
                output << (bi.v.size() - 1);
            }
            else {
                for (const char& digit : bi.v) {
                    output << digit;
                }
            }
            return os << output.str();
        }

        friend BigInt operator+ (int integer, BigInt other) {
            return BigInt(integer) + other;
        }
};

BigInt::BigInt(int num) {
    v = vector<char>();
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num *= -1;
    }

    if (num == 0) {
        v.push_back('0');
    } else {
        while (num > 0) {
            v.push_back((num % 10) + '0');
            num /= 10;
        }
    }

    if (isNegative) {
        v.push_back('-');
    }
    reverse(v.begin(), v.end());
}

BigInt::BigInt(string str) {
    v = vector<char>();
    if (str == "0") {
        v = vector<char>{'0'};
        return;
    }
    if (str[0] == '-') {
        v.push_back('-');
    }
    for (char ch : str) {
        if (('0' <= ch && ch <= '9')) {
            v.push_back(ch);
        }
        else if (ch != '-') { 
            throw invalid_argument ("String contains non-numeric input");
        }
    }
}

BigInt::BigInt() {}

BigInt BigInt::operator/(BigInt other) {
    if (other == BigInt(0)) {
        throw invalid_argument("Division by Zero");
    }
    if (other == BigInt(1)) {
        return *this;
    }
    if (other == BigInt(-1)) {
        return *this * BigInt(-1);
    }

    bool thisIsNegative = (*this < BigInt(0));
    bool otherIsNegative = (other < BigInt(0));

    if (thisIsNegative) {
        BigInt temp(*this < BigInt(0));
        temp.v.erase(temp.v.begin());
        *this = temp;
    }

    if (otherIsNegative) {
        other.v.erase(other.v.begin());
    }

    BigInt quotient(0);
    BigInt remainder(*this);

    while (remainder >= other) {
        quotient = quotient + BigInt(1);
        remainder = remainder - other;
    }

    if (thisIsNegative != otherIsNegative) {
        quotient = quotient * BigInt(-1);
    }

    return quotient;
}

BigInt BigInt::operator%(BigInt other) {
    if (other == BigInt(0)) {
        throw invalid_argument("Division by Zero");
    }
    if (other == BigInt(1) || other == BigInt(-1)) {
        return BigInt(0);
    }

    if (*this > BigInt(0) && other > BigInt(0)) {
        BigInt remainder(*this);
        while (remainder >= other) {
            remainder = remainder - other;
        }
        return remainder;
    }

    if(*this < BigInt(0) && other < BigInt(0)) {
        BigInt remainder(*this);
        while (remainder <= other) {
            remainder = remainder - other;
        }
        return remainder;
    }

    if (*this < other) {
        BigInt temp(*this);
        while (temp < BigInt(0)) {
            temp = temp + other;
        }
        return temp;
    } else {
        BigInt temp(*this);
        BigInt positiveOther = other * BigInt(-1);
        while (temp > BigInt(0)) {
            temp = temp - positiveOther;
        }
        return temp;
    }
}

BigInt BigInt::operator++(int) {
    BigInt temp(*this);
    *this = *this + BigInt(1);
    return temp;
}

BigInt BigInt::operator++() {
    *this = *this + BigInt(1);
    return *this;
}

BigInt BigInt::operator[](int index) {
    if (index < 0 || index >= v.size()) {
        throw out_of_range("Index out of range");
    }

    return BigInt(v[index]);
}

BigInt BigInt::operator+(BigInt other) {
    // Handles cases where one or both BigInts are negative
    if (*this < BigInt(0)) {
        BigInt temp(*this);
        temp.v.erase(temp.v.begin());   // Remove negative sign
        return other - temp;            // -x + y == y - x
    }
    if (other < BigInt(0)) {
        BigInt temp(other);
        temp.v.erase(temp.v.begin());   // Remove negative sign
        return *this - temp;            // x + -y == x - y
    }

    // Addition for positive numbers
    int carry = 0;
    string result = "";
    int i = size() - 1;
    int j = other.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit_sum = carry;
        if (i >= 0) {
            digit_sum += v[i] - '0';    // Convert char to int and add
            i--;
        }
        if (j >= 0) {
            digit_sum += other.v[j] - '0';  // Convert char to int and add
            j--;
    }
        carry = digit_sum / 10; // Calculate carry
        result.insert(result.begin(), (digit_sum % 10) + '0');
    }
    return BigInt(result);  // Return result as a BigInt
}

BigInt BigInt::operator-(BigInt other) {
    // `this` is negative
    if (*this < BigInt(0)) {
        BigInt temp(*this);
        temp.v.erase(temp.v.begin());           // Remove the negative sign for calculation
        return ((temp + other) * BigInt(-1));   // -x - y = (x + y) * -1
    }
    
    // `other` is negative
    if (other < BigInt(0)) {
        BigInt temp(other);
        temp.v.erase(temp.v.begin());           // Remove the negative sign for calculation
        return (*this + temp);                  // x - (-y) = x + y
    }

    // Both `this` and `other` are positive
    if (*this < other) {
        return ((other - *this) * BigInt(-1)); // Ensure result is negative
    }

    // Perform subtraction digit by digit
    int carry = 0;
    int i = size() - 1; // Start from the least significant digit of `this`
    int j = other.size() - 1; // Start from the least significant digit of `other`
    string result = "";

    while (i >= 0 || j >= 0) {
        int sub = 0;

        // Subtract digit of `this`
        if (i >= 0) {
            sub = getDigitAt(i); // Convert char to int
            i--;
        }

        sub -= carry; // Adjust for any previous carry

        // Subtract digit of `other`
        if (j >= 0) {
            sub -= getDigitAt(j); // Convert char to int
            j--;
        }

        // Calculate new carry (1 if sub is negative, 0 otherwise)
        carry = sub < 0;
        if (carry) {
            sub += 10; // Borrow from the next digit
        }

        // Add current digit to the result
        result = char(sub + '0') + result;
    }

    // Remove leading zeroes
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    return BigInt(result); // Return result as a BigInt object
}

BigInt BigInt::operator-(int other) {
    return *this - BigInt(other);
}

BigInt BigInt::operator*(BigInt other) {
    if (other == BigInt(0)) {
        return BigInt(0);
    }
    if (other == BigInt(1)) {
        return *this;
    }
    if (other == BigInt(-1)) {
        if (*this == BigInt(0)) {
            return BigInt(0);
        }
        BigInt result(*this);
        if(result.v[0] == '-') {
            result.v.erase(result.v.begin());
        } else {
            result.v.insert(result.v.begin(), '-');
        }
        return result;
    }

    bool thisIsNegative = (*this < BigInt(0));
    bool otherIsNegative = (other < BigInt(0));

    BigInt a;
    if (thisIsNegative) {
        a = BigInt(*this).absolute();
    } else {
        a = *this;
    }

    BigInt b;
    if (otherIsNegative) {
        b = BigInt(other).absolute();
    } else {
        b = other;
    }

    BigInt result(0);
    for (BigInt i(0); i < b; i = i + 1) {
        result = result + a;
    }

    if (thisIsNegative != otherIsNegative) {
        if (result.v[0] == '-') {
            result.v.erase(result.v.begin());
        } else {
            result.v.insert(result.v.begin(), '-');
        }
    }
    return result;
}

BigInt BigInt::absolute() {
    if (!v.empty() && v[0] == '-') {
        vector<char> positiveValue(v.begin() + 1, v.end());
        return BigInt(positiveValue);
    }
    return *this;
}

int BigInt::getDigitAt(int index) {
    if (index < 0 || index >= v.size()) {
        throw out_of_range("Index out of range");
    }
    return v[index] - '0';
}

void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"<<flush;
    system("whoami");
    system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");
    // display variables
    cout << "n1(int)    :"<<setw(space)<<n1<<endl;
    cout << "s1(str)    :"<<setw(space)<<s1<<endl;
    cout << "n2(int)    :"<<setw(space)<<n2<<endl;
    cout << "s2(str)    :"<<setw(space)<<s2<<endl;
    cout << "n3(n2)     :"<<setw(space)<<n3<<endl;
    cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
    cout << "fact(50)   :"<<setw(space)<<fact<<endl;
    cout << "imax       :"<<setw(space)<<imax<<endl;
    cout << "big        :"<<setw(space)<<big<<endl;
    cout << "big.print(): "; big.print(); cout << endl;
    cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
    cout << "fibo("<<fibo<<") = "<<fibo.fibo(1) << endl;
    cout << "fact("<<fact<<") = "<<fact.fact(1) << endl;
    cout << "10 + n1 = " << 10+n1 << endl;
    cout << "n1 + 10 = " << n1+10 << endl;
    cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
    cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
    cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
    cout << "s2 * big = ? --> "<< s2 * big<<endl;
    cout << "big * s2 = ? --> "<< big * s2<<endl;
}

int main () {
    testUnit();
}
