// Kevin Van
// CECS 325-02
// Prog 6 – Big Integers
// Due Date (12/10/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <iomanip> 
#include <vector>
#include <algorithm> 
#include <climits>

using namespace std;

class BigInt{
    private:
        vector<char> v;
        bool isNegative;
        BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1){
            if (n == BigInt(0))
                return a;
            else if (n == BigInt(1))
                return b;
            else
                return fiboHelper(n - 1, b, a + b);
        }
    public:
        BigInt(){
            vector<char> v;
        }
    
        BigInt(string str) {
            isNegative = false;

            if (str == "0") {
                v = {'0'};
                isNegative = false;
                return;
            }

            if (str[0] == '-') {
                isNegative = true;
                v.assign(str.begin() + 1, str.end());
            } else {
                v.assign(str.begin(), str.end());
            }

            for (char ch : v) {
                if (!isdigit(ch)) {
                    throw invalid_argument("Non-numeric characters");
                }
            }
        } 

        BigInt(int n) {
            if (n == 0) {
                v.push_back('0');
                return;
            }

            bool isNegative = n < 0;
            if (isNegative) {
                n = -n;
            }

            while (n > 0) {
                char digit = '0' + (n % 10);
                v.push_back(digit);
                n /= 10;
            }

            if (isNegative) {
                v.push_back('-');
            }

            reverse(v.begin(), v.end());
        }
    
        BigInt operator+(BigInt other) {
            if (v[0] == '-' && other.v[0] != '-') {
                BigInt t = *this;
                t.v.erase(t.v.begin());
                return other - t;
            }

            if (v[0] != '-' && other.v[0] == '-') {
                BigInt o = other;
                o.v.erase(o.v.begin());
                return *this - o;
            }

            if (v[0] == '-' && other.v[0] == '-') {
                BigInt t = *this;
                BigInt o = other;
                t.v.erase(t.v.begin());
                o.v.erase(o.v.begin());

                int carry = 0;
                string result = "";
                int i = t.v.size() - 1, j = o.v.size() - 1;

                while (i > 0 || j >= 0 || carry) {
                    int sum = carry;
                    if (i >= 0)
                        sum += t.v[i--] - '0';
                    if (j >= 0)
                        sum += o.v[j--] - '0';
                    carry = sum / 10;
                    result = char(sum % 10 + '0') + result;
                }
                return BigInt("-" + result);
            }

            int carry = 0;
            string result = "";
            int i = v.size() - 1, j = other.v.size() - 1;

            while (i >= 0 || j >= 0 || carry) {
                int sum = carry;
                if (i >= 0)
                    sum += v[i--] - '0';
                if (j >= 0)
                    sum += other.v[j--] - '0';
                carry = sum / 10;
                result = char(sum % 10 + '0') + result;
            }
            return BigInt(result);
        }
    
        BigInt operator-(BigInt other) {
            if (*this < BigInt(0)){
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t + other) * BigInt(-1));
            }

            if (other < BigInt(0)) {
                BigInt o(other);
                o.v.erase(o.v.begin());
                return (*this + o);
            }

            if (*this < other){
                return ((other-*this) * BigInt(-1));
            }

            int carry = 0;
            int i = size()-1, j = other.size() - 1;
            string result = "";
            
            while (i >= 0 || j >= 0){ 
                int sub = 0;
                if (i >= 0){ 
                    sub = v[i] - '0'; 
                    i--; 
                }
                sub -= carry;
                if (j >= 0){ 
                    sub -= other.v[j] - '0';
                    j--; 
                }
                carry = sub < 0;
                sub = (sub + 10) % 10;
                result = char(sub + '0') + result;
            }
            
            while (result[0] == '0' && result.size() > 1){ 
                result.erase(result.begin()); 
            }
            return BigInt(result);
        }
    
        BigInt operator-(int other) {
            return *this - BigInt(other); 
        }
        
        BigInt operator*(BigInt other) {
            if (*this == BigInt(0) || other == BigInt(0)) {
                return BigInt(0);
            }

            bool isNegative = (v[0] == '-' || other.v[0] == '-') && !(*this < BigInt(0) && other < BigInt(0));
            BigInt t = *this;
            BigInt o = other;

            if (v[0] == '-') {
                t.v.erase(t.v.begin());
            }

            if (other.v[0] == '-') {
                o.v.erase(o.v.begin());
            }

            int n = t.v.size();
            int m = o.v.size();
            vector<int> product(n + m, 0);

            for (int i = n - 1; i >= 0; --i) {
                int digit1 = t.v[i] - '0';
                for (int j = m - 1; j >= 0; --j) {
                    int digit2 = o.v[j] - '0';
                    int mult = digit1 * digit2;
                    int pos = i + j + 1;

                    product[pos] += mult;
                    if (product[pos] >= 10) {
                        product[pos - 1] += product[pos] / 10;
                       product[pos] %= 10; 
                    }
                }
            }

            string result;
            for (int i = 0; i < product.size(); ++i) {
                if (!(result.empty() && product[i] == 0)) {
                    result += (product[i] + '0');
                }
            }

            if (result.empty()) {
                result = "0";
            }

            if (isNegative) {
                result = "-" + result;
            }

            return BigInt(result);
        }
    
        BigInt operator/(BigInt other) {
            if (other == BigInt(0)){
                throw invalid_argument("Division by zero!");
            } 
            else if (other == BigInt(1)) { 
                return *this;
            } 
            else if (other == BigInt(-1)) { 
                return *this * BigInt(-1);
            } 
            else if (*this < BigInt(0)) { 
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t / other) * BigInt(-1)); 
            } 
            else if (other < BigInt(0)) { 
                BigInt o(other);
                o.v.erase(o.v.begin());
                return ((*this / o) * BigInt(-1));
            } 
            else {    
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){ 
                    counter = counter + 1;
                    sub = sub - other;
                }
                return counter;
            } 
        }
        
        BigInt operator% (BigInt other) {
            if(other == BigInt(0)){ 
                throw invalid_argument("Division by zero!");
            }
            else if(other == BigInt(1) || other == BigInt(-1)) { 
                return BigInt(0);
            }
            else if(*this > BigInt(0) && other > BigInt(0)) { 
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){
                    sub = sub - other;
                }
                return sub;
                
            }
            else if(*this < BigInt(0) && other < BigInt(0)) { 
                BigInt counter(0);
                BigInt sub(*this);
                while(sub <= other){
                    sub = sub - other;
                }
                return sub;
            }
            else{
                if(*this < other){
                    BigInt temp(*this);
                    while(temp < BigInt(0)){
                        temp = temp + other;
                    }
                    return temp;
                }
                else{
                    BigInt temp(*this);
                    BigInt o(other * BigInt(-1)); 
                    while(temp > BigInt(0)){
                        temp = temp - o;
                    }
                    return temp;
                }
            }
        }
        
        BigInt operator++(int) {
            BigInt temp(*this);
            *this = *this + 1;
            return temp;
        }
    
        BigInt operator++() {
            *this = *this + 1;
            return *this;
            
        }
    
        char operator[](int index) {					// index function
            return v[index];
        }
    
        bool operator==(BigInt other) {
            if (v.size () != other.size ()) {
                return false;
            }
            for (int i = 0; i < size (); i++) {
                if (v[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }
        
        bool operator!= (BigInt other) {
            return !(*this == other);
        }
        
        bool operator<(BigInt other) {
            if (v[0] == '-') {
                if (other[0] != '-') {
                    return true;
                }
                if (v.size() != other.size()) {
                    return v.size() > other.size();
                }

                for (int i = 0; i < v.size(); i++) {
                    if (v[i] < other[i])
                        return false;
                    if (v[i] > other [i])
                        return true;
                }
                return false;
            }    

            if (other[0] == '-') {
                return false;
            }

            if (v.size() != other.size()) {
                return v.size() < other.size();
            }

            for (int i = 0; i < v.size(); i++) {
                if (v[i] < other[i])
                    return true;
                if (v[i] > other[i])
                    return false;
            }
            return false;
        }       

        bool operator<=(BigInt other) { 
            return (*this < other) || (*this == other);
        }
        
        bool operator>(BigInt other) { 
            if(*this == other){
                return false;
            }
            else {
                return !(*this<other);
            }
        }
        
        bool operator>=(BigInt other) {
            return (*this > other) || (*this == other);
        }
    
        void print() {
            string str = ""; 
            for (int i = 0; i < v.size (); i++){
                str += v[i];
            }
            cout << str << endl;
        }
    
        int size() {
            return v.size();
        } 
    
        BigInt fibo() {
            return fiboHelper(*this);
        }
        
        BigInt fact() {
            if (*this == BigInt(0))
                return BigInt(1);

            return *this * (BigInt(*this - 1).fact());
        }
         
        friend ostream& operator<<(ostream& os, const BigInt& bi) {
            ostringstream output;
            if (bi.v.size() > 12) {
                if (bi.isNegative) {
                    output << '-';
                }
                output << bi.v[0];
                output << '.';
                for (int i = 1; i < min(7, static_cast<int>(bi.v.size())); ++i) {
                    output << bi.v[i];
                }
                output << 'e';
                output << (bi.v.size() - 1);
            } else {
                if (bi.isNegative) {
                    output << '-';
                }
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
	   
void testUnit () {
  int space = 10;
  cout << "\a\nTestUnit:\n" << flush;
  system ("whoami"); 
  system ("date");
  // initialize variables
  BigInt n1 (25);
  BigInt s1 ("25");
  BigInt n2 (1234);
  BigInt s2 ("1234");
  BigInt n3 (n2);
  BigInt fibo (12345);
  BigInt fact (50);
  BigInt imax = INT_MAX; BigInt big ("9223372036854775807");
  // display variables
  cout << "n1(int) :" << setw (space) << n1 << endl;
  cout << "s1(str) :" << setw (space) << s1 << endl;
  cout << "n2(int) :" << setw (space) << n2 << endl;
  cout << "s2(str) :" << setw (space) << s2 << endl;
  cout << "n3(n2) :" << setw (space) << n3 << endl;
  cout << "fibo(12345):" << setw (space) << fibo << endl;
  cout << "fact(50) :" << setw (space) << fact << endl;
  cout << "imax :" << setw (space) << imax << endl;
  cout << "big :" << setw (space) << big << endl;
  cout << "big.print(): "; big.print (); cout << endl;
  cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
  cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
  cout << "fact("<<fact<<") = "<<fact.fact() << endl;
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
