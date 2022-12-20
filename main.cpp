#include <iostream>
#include <vector>
#include "RSA_cryptosystem.cpp"
int main() {
    RSA a (17,31);
    std::vector<number> v1 = a.encode("RSA");
    for (int i = 0; i < v1.size(); ++i) {
        std::cout<<v1[i]<<std::endl;
    }
    std::cout << a.decode(a.encode("RSA")) << std::endl;
    std::vector<number> v = RSA::attack(std::vector<number> {474,407},7,527);
    for (int i = 0; i < v.size(); ++i) {
        std::cout<<v[i]<<std::endl;
    }
    return 0;
}
