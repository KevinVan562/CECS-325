// Kevin Van
// CECS 325-02
// Prog 6 – BigInt
// Due Date (12/01/2024)
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
            v = vector<char>();
        }
    
        BigInt(string str) {
            v.clear();
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
                    throw invalid_argument("Contains non-numeric characters");
                }
            }
        } 

        BigInt(int num) {
            v.clear();
            isNegative = false;

            if (num < 0) {
                isNegative = true;
                num = -num;
            } else if (num == 0) {
                v.push_back('0');
                return;
            }

            while (num > 0) {
                char ch = '0' + (num % 10);
                v.push_back(ch);
                num /= 10;
            }

            if (isNegative) {
                v.push_back('-');
            }

            reverse(v.begin(), v.end());
        }
    
        BigInt operator+(BigInt other){
            if (*this < BigInt(0)){ // This is negative
                BigInt t(*this);
                t.v.erase(t.v.begin()); // Erase negative
                return other - t; // -x + y == y - x
            }
            if (other < BigInt(0)){// Other is negative
                BigInt o(other);
                o.v.erase(o.v.begin()); // Erase negative
                return (*this - o); // x + -y == x - y
            }
            
            int carry = 0;
            string result = "";
            int i = size() - 1;
            int j = other.size() - 1;

            while (i >= 0 || j >= 0 || carry){ 
                int sum = carry;
                if (i >= 0){ 
                    sum += int(v[i]) - 48; // Convert char into int and add to sum
                    i--; 
                }
                if (j >= 0){ 
                    sum += int(other[j]) - 48;  // Convert char to int and add to sum
                    j--; 
                }
                carry = sum / 10;
                sum = sum % 10;
                result = char(sum + 48) + result; 
            }
            
            return BigInt(result);
        }
    
        BigInt operator- (BigInt other){
            if (*this < BigInt(0)){ // This is negative
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t + other) * BigInt(-1)); // -x - y == (x + y) * -1
            }
            if (other < BigInt(0)){// Other is negative
                BigInt o(other);
                o.v.erase(o.v.begin());
                return (*this + o); // x - -y == x + y
            }
            // Both are positive
            if (*this < other){
                return ((other - *this) * BigInt(-1));
            }

            int carry = 0;
            int i = size() - 1;
            int j = other.size() - 1;
            string result = "";
            
            while (i >= 0 || j >= 0){ 
                int sub = 0;
                if (i >= 0){ 
                    sub = int(v[i])-48; 
                    i--; 
                }
                sub -= carry; // Subtract any carry
                if (j >= 0){ 
                    sub -= int(other[j]) - 48; // Subtract other digit from sub
                    j--; 
                }
                carry = sub < 0; // If sub is negative, set carry to 1 else 0
                sub = (sub + 10) % 10; // If sub is positive, get one's place
                result = char(sub + 48) + result;
            }
            
            //remove preceding 0's
            while (result[0] == '0' && result.size() > 1){ 
                result.erase(result.begin()); 
            }
            return BigInt(result);
        }
    
        BigInt operator-(int other) {
            return *this - BigInt(other); 
        }
        
        BigInt operator+ (int other) {
            return *this + BigInt(other); 
        }
    
        BigInt operator*(BigInt other) {
            string v1(v.begin(), v.end()), v2(other.v.begin(), other.v.end());
            bool isNegative = (v1[0] == '-' ^ v2[0] == '-');
    
            if (v1[0] == '-')
                v1.erase(v1.begin());
            if (v2[0] == '-')
                v2.erase(v2.begin());

            int len1 = v1.size(), len2 = v2.size();
            vector<int> result(len1 + len2, 0);

            for (int i = len1 - 1; i >= 0; --i) {
                for (int j = len2 - 1; j >= 0; --j) {
                    int mul = (v1[i] - '0') * (v2[j] - '0');
                    mul += result[i + j + 1];
                    result[i + j + 1] = mul % 10; // Current digit
                    result[i + j] += mul / 10;  // Carry
                }
            }

            // Convert result to string
            string res;
            for (int num : result) {
                if (!(res.empty() && num == 0)) { // Skip leading zeros
                    res.push_back(num + '0');
                }
            }
            if (res.empty()) res = "0"; // Handle 0 multiplication
            if (isNegative && res != "0") res.insert(res.begin(), '-');
            return BigInt(res);
}


    
        BigInt operator/(BigInt other) {
            if (other == BigInt(0)){ 
                throw invalid_argument("Division by zero!");
            } else if (other == BigInt(1)) { 
                return *this;
            } else if (other == BigInt(-1)) { // Same result as multiply by -1
                return *this * BigInt(-1);
            } else if (*this < BigInt(0)) { // This is negative
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t / other) * BigInt(-1)); // -x / y == (x / y) * -1
            } else if (other < BigInt(0)) { // Other is negative
                BigInt o(other);
                o.v.erase(o.v.begin());
                return ((*this / o) * BigInt(-1)); // x / -y == (x / y) * -1
            } else {    // Both are positive
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){ // Repeated subtraction
                    counter = counter + 1;
                    sub = sub - other;
                }
                return counter;
            } 
        }
        
        BigInt operator% (BigInt other){
            if(other == BigInt(0)){ 
                throw invalid_argument("Division by zero!");
            }
            else if(other == BigInt(1) || other == BigInt(-1)){ 
                return BigInt(0);
            }
            else if(*this > BigInt(0) && other > BigInt(0)){ // Both are positive
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){
                    sub = sub - other;
                }
                return sub;
                
            }
            else if(*this < BigInt(0) && other < BigInt(0)){ // Both are negative
                BigInt counter(0);
                BigInt sub(*this);
                while(sub <= other){
                    sub = sub - other;
                }
                return sub;
            }
            else{   // Opposing signs
                if(*this < other){// This is negative, other is positive
                    BigInt temp(*this);
                    while(temp < BigInt(0)){
                        temp = temp + other;
                    }
                    return temp;
                }
                else{   // This is positive, other is negative
                    BigInt temp(*this);
                    BigInt o(other*BigInt(-1)); // Make other positive
                    while(temp > BigInt(0)){
                        temp = temp - o;
                    }
                    return temp;
                }
            }
        }
        
        BigInt operator++(int){
            BigInt temp(*this);
            *this = *this + 1;
            return temp;
        }
    
        BigInt operator++(){
            *this = *this + 1;
            return *this;
            
        }
    
        char operator[](int index){					// index function
            return v[index];
        }
    
        bool operator==(BigInt other){
            if (v.size () != other.size ()){
                return false;
            }
            for (int i = 0; i < size (); i++){
                if (v[i] != other[i]){
                    return false;
                }
            }
            return true;
        }
        
        bool operator!= (BigInt other){
            return !(*this == other);
        }
        
        bool operator<(BigInt other){
            if(v[0] == '-'){ // This is negative
                if(other[0] != '-'){ // Other is positive
                    return true;
                }
                // Both negative
                else if(v.size() < other.size()){ // This has less digits
                    return false;
                }
                else if(v.size() > other.size()){// This has more digits
                   return true;
                }
                // Both are of equal size
                else{
                    for(int i = 0; i < size(); i++){
                        if(v[i] < other[i]){ // This digit is smaller
                            return false;
                        }
                        else if(v[i] > other[i]){ // This digit is larger
                            return true;
                        }
                    }
                    return false; // Equal
                }
            }
            else{ // This is positive
                if(other[0] == '-'){ // Other is negative
                    return false;
                }
                // Both positive
                else if(v.size() < other.size()){ // This has less digits
                    return true;
                }
                else if(v.size() > other.size()){// This has more digits
                   return false;
                }
                // Both are of equal size
                else{
                    for(int i = 0; i < size(); i++){
                        if(v[i] < other[i]){ // This digit is smaller
                            return true;
                        }
                        else if(v[i] > other[i]){ // This digit is larger
                            return false;
                        }
                    }
                    return false; // Equal
                }
            }
        }
        
        bool operator<=(BigInt other){  // Less than OR equal to
            return (*this < other) || (*this == other);
        }
        
        bool operator>(BigInt other){   // Greater than == !less than
            if(*this == other){
                return false;
            }
            else {
                return !(*this<other);
            }
        }
        
        bool operator>=(BigInt other){
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
        
        BigInt fact(){ 
            if (*this == BigInt(0))
                return BigInt(1);
            BigInt i(*this);
            BigInt fact(1);
            while ((*this / i) != *this) {
                fact = fact * i;
                i = i - 1;
            }
            return fact;
        }
         
        friend ostream& operator<<(ostream& os, const BigInt& bi) {
            ostringstream output;
            if (bi.v.size() > 12) {
                if (bi.isNegative) {
                    output << '-';
                }
                output << bi.v[0];
                output << '.';
                for (size_t i = 1; i < min(size_t(7), bi.v.size()); ++i) {
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
	   
void testUnit (){
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

int main ()
{
    testUnit();
}
