#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>

/*
*¿ÉÒÔ¿¼ÂÇÊ¹ÓÃ·´ÂëÏµÍ³
*/
using namespace std;

class BigInteger
{
private:
    static const int BASE = 10000;
    static const int WIDTH = 4;
    vector<int> s;
    int flag;
public:
    inline bool IsMinus()const { return flag<0;}
    BigInteger(long long int x = 0){*this = x;}
    BigInteger operator = (string& str);
    BigInteger operator = (long long& x);
    BigInteger operator + (const BigInteger& b) const;
    BigInteger operator - (const BigInteger& b) const;
    BigInteger operator - () const{ BigInteger c = *this;c.flag *= -1;return c;}
    BigInteger operator * (const BigInteger& b) const;
    BigInteger operator * (const int& b) const;
    bool comp(const BigInteger& b) const;
    bool operator < (const BigInteger& b) const;
    bool operator > (const BigInteger& b) const{ return b<*this;}
    bool operator != (const BigInteger& b) const{ return b<*this || *this<b;}
    bool operator == (const BigInteger& b) const{ return !(b<*this) && !(*this<b);}
    bool operator <= (const BigInteger& b) const{ return !(b<*this);}
    bool operator >= (const BigInteger& b) const{ return !(*this<b);}
    friend ostream& operator << (ostream &out, const BigInteger& x);
};

ostream& operator << (ostream &out, const BigInteger& x)
{
    if(x.IsMinus())out << "-";
    out << x.s.back();
    char buf[10];
    for(int i = x.s.size()-2; i >= 0; i--){
        snprintf(buf, 10, "%04d", x.s[i]);
        for(int j = 0; j<(int)strlen(buf); j++)out << buf[j];
    }
    return out;
}
istream& operator >> (istream &in, BigInteger& x)
{
    string s;
    if(!(in >> s))return in;
    //****string handle------to delete the prefix zeros***
    string::iterator ptr = s.begin();
    while(*ptr == '-')++ptr;
    while(*ptr == '0' && s.length() > 1){
        s.erase(ptr);
        /*++ptr;---------------------------THE BIG BUG!!!!!!!
        After the first letter erased,
        the ptr still point to the first
        letter, but the position became
        the previous second letter automatically!!!!
        */
    }
#ifdef DEBUG
    cout << s << endl;
#endif // DEBUG
    x = s;
    return in;
}

BigInteger fac(int n);

int main()
{
    BigInteger a, b;
    //cin >> a >> b;
#ifdef DEBUG
    cout << "a:" << a << ' ' << "b:" << b << endl;
#endif // DEBUG
    int n;
    cin >> n;
    cout << fac(n);
    return 0;
}

BigInteger fac(int n)
{
    BigInteger x = 1;
    for(int i = 1; i <= n; i++){
        BigInteger y = i;
        x = x * i;
    }
    return x;
}

BigInteger BigInteger::operator=(long long& x)
{
    s.clear();
    //Wrong way
//    while(x){
//        s.push_back(x%BASE);
//        x/=BASE;
//    }
    if(x<0){
        flag = -1;x*=-1;
    }
    else if(x>0){
        flag = 1;
    }
    else{
        flag = 0;
    }
    do{
        s.push_back(x%BASE);
        x/=BASE;
    }while(x);
    return *this;
}
#define VA//VA and VB two versions
BigInteger BigInteger::operator=(string& str)
{
    s.clear();
    if(str[0] == '-'){
        flag = -1;
        str = str.substr(1, str.length()-1);
    }
    else if(str[0] != '0'){
        flag = 1;
    }
    else{
        flag = 0;//ÊÇ·ñÐèÒª·µ»Ø0.
    }
    int x, len = ((str.length()-1)/WIDTH+1);
    int start, end;
#ifdef VA
    for(int i = 0; i<len; i++){
        end = str.length()-WIDTH*i;
        start = max(0, end-WIDTH);
        x = 0;
        for(int j = start; j<end; j++){
            x = x*10 + str[j] - '0';
        }
        s.push_back(x);
    }
#endif // VA
#ifdef VB
    for(int i = 0; i<len; i++){
        end = str.length()-WIDTH*i;
        start = max(0, end-WIDTH);
        sscanf(str.substr(start, end-start).c_str(), "%d", &x);
        s.push_back(x);
    }
#endif // VB
    return *this;
}

bool BigInteger::comp(const BigInteger& b) const
{
    if(s.size() != b.s.size())return s.size()<b.s.size();
    for(int i = s.size()-1; i>=0; i--){
        if(s[i] != b.s[i])return s[i]<b.s[i];
    }
    return false;//Equal
}

bool BigInteger::operator<(const BigInteger& b) const
{
    if(flag<b.flag)return true;
    else if(flag>b.flag)return false;
    else if(flag<0)return b.comp(*this);
    else if(flag>0)return (*this).comp(b);
    else return false;
}

BigInteger BigInteger::operator+(const BigInteger& b) const
{
    BigInteger c;
    c.s.clear();
    if(IsMinus() != b.IsMinus()){

    //calculate the absolute value
        //set the pointer
        if((*this).comp(b)){
            BigInteger const *  sml = this;
            BigInteger const *  big = &b;
            //start calculate
            int x;
            for(unsigned int i = 0, g = 0; ; i++){
                if(g == 0 && i>=big->s.size())break;
                if(i<sml->s.size())x = big->s[i] - sml->s[i] -g;
                else x = big->s[i]-g;
                if(x<0){
                    x += BASE;
                    g = 1;
                }
                else g = 0;
                c.flag = big->flag;
                c.s.push_back(x);
            }
            return c;
        }
        else {
            BigInteger const * sml = &b;
            BigInteger const * big = this;
            //start calculate
            int x;
            for(unsigned int i = 0, g = 0; ; i++){
                if(g == 0 && i>=big->s.size())break;
                if(i<sml->s.size())x = big->s[i] - sml->s[i] -g;
                else x = big->s[i]-g;
                if(x<0){
                    x += BASE;
                    g = 1;
                }
                else g = 0;
                c.flag = big->flag;
                c.s.push_back(x);
            }
            return c;
        }
    }
    else{
        c.flag = flag;
        int x;
        for(unsigned int i = 0, g = 0; ; i++){
            if(g == 0 && i>=s.size() && i>=b.s.size())break;
            x = g;
            if(i < s.size())x += s[i];
            if(i < b.s.size())x += b.s[i];
            c.s.push_back(x % BASE);
            g = x/BASE;
        }
        return c;
    }
}

BigInteger BigInteger::operator-(const BigInteger& b) const
{
    return (*this+(-b));
}

BigInteger BigInteger::operator*(const int& b) const
{
    BigInteger c;
    c.s.clear();
    int bflag = b>0? 1 : -1;
    c.flag = flag * bflag;
    long long g = 0;
    for(unsigned int i = 0; ; i++){
        if(g == 0 && i>=s.size())break;
        if(i < s.size())g = s[i]*b;
        for(unsigned int j = 0; ; j++){
            if(g == 0)break;
            if(j>c.s.size())c.s.push_back(g%BASE);
            else {
                g += c.s[j];
                c.s[j] = g%BASE;
            }
            g /= BASE;
        }
    }
    return c;
}
