#include "huge_numbers.h"


number exponentiation(number a,std::vector<int> k,number n){
    number b=1;
    bool flag= false;
    for (int i = 0; i < k.size(); ++i) {
        if (k[i]!=0){
            flag=true;
            break;
        }
    }
    if (flag){
        number A=a;
        if (k[0]==1){
            b=a;
        }
        for (int i = 1; i < k.size(); ++i) {
            A=(unsigned long long)(pow(A,2))%n;
            if (k[i]==1){
                b=(A*b)%n;
            }
        }
    }
    return b;
}


bool simplicity_test(number n){
    if(n%2==0){
        return false;
    }
    for (int i = 1; i <= n; ++i) {
        number a= (rand() % (n-3))+2;
        number r= exponentiation(a,power_decomposition(n-1),n);
        if(r!=1){
            return false;
        }
    }
    return true;
}

std::vector<int> power_decomposition (number g){
    std::vector<int> division;
    for (int j = 64; j >=0 ; --j) {
        if (pow(2,j)<=g){
            division.insert(division.begin(),1);
            g-=pow(2,j);
        }
        else{
            division.insert(division.begin(),0);
        }
    }
    return division;
}

int reverse_element(int A,int B){
    int a=A,b=B;
    int x1,x2,y1,y2,q,r,x,y;
    x2=1;
    x1=0;
    y2=0;
    y1=1;
    while(b>0){
        q=a/b;
        r=a-q*b;
        x=x2-q*x1;
        y=y2-q*y1;
        a=b;
        b=r;
        x2=x1;
        x1=x;
        y2=y1;
        y1=y;
    }
    y=y2;
    while(y<0){
        y+=std::max(B,A);
    }
    while(y>std::max(B,A)){
        y-=std::max(B,A);
    }
    return y;
}

number get_num(char c) {
    int tmp = ALPHABET.find(c);
    if (tmp != std::string::npos) {
        return tmp;
    } else {
        std::cout<<"Error on "<<c<<"\n";
        throw std::invalid_argument("There is no such symbol  in APHABET");
    }
}

char get_char(number n) {
    if (n >= ALPHABET.size()) {
        std::cout<<"Error on "<<n<<"\n";
        throw std::invalid_argument("N is larger than the size of the alphabet");
    }
    return ALPHABET[n];
}

std::vector<number> format_string(const std::string &s) {
    std::vector<number> res;

    for (int i = 0; i < s.size(); i++) {
        char tmp = tolower(s[i]);
        if (ALPHABET.find(tmp) != std::string::npos) {
            res.push_back(get_num(tmp));
        } else {
            std::cout << "Symbol-" << s[i] << " not included in the coding alphabet\n";
        }
    }
    return res;
}